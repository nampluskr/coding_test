import tensorflow as tf
import numpy as np
from tqdm import tqdm
import sys
from copy import deepcopy
import os
import pathlib


@tf.function
def binary_accuracy(y_true, y_pred):
    """ Binary classification (y_pred: logits without sigmoid)"""
    y_pred = tf.squeeze(tf.round(tf.sigmoid(y_pred)))   ## float32
    return tf.reduce_mean(tf.cast(tf.equal(y_true, y_pred), tf.float32))


@tf.function
def accuracy(y_true, y_pred):
    """ Multi-class classification (y_pred: logtis without softmax) """
    y_pred = tf.argmax(y_pred, axis=-1)                 ## int64
    return tf.reduce_mean(tf.cast(tf.equal(y_true, y_pred), tf.float32))


@tf.function
def iou(y_true, y_pred):
    if tf.rank(y_pred) > tf.rank(y_true):
        y_pred = tf.round(tf.sigmoid(y_pred))

    y_true = tf.reshape(y_true, [-1])
    y_pred = tf.reshape(y_pred, [-1])

    intersection = tf.reduce_sum(y_true * y_pred)
    union = tf.reduce_sum(y_true) + tf.reduce_sum(y_pred) - intersection
    return intersection / (union + 1e-10)


@tf.function
def dice_coeff(y_true, y_pred):
    if tf.rank(y_pred) > tf.rank(y_true):
        y_pred = tf.round(tf.sigmoid(y_pred))

    y_true = tf.reshape(y_true, [-1])
    y_pred = tf.reshape(y_pred, [-1])

    intersection = tf.reduce_sum(y_true * y_pred)
    return  2*intersection / (tf.reduce_sum(y_true) + tf.reduce_sum(y_pred) + 1e-10)


class MulticlassDiceCoeff():
    def __init__(self, n_classes):
        self.n_classes = n_classes

    def __call__(self, y_true, y_pred):
        y_pred = tf.argmax(y_pred, axis=-1)   ## (N, n_classes, h, w) -> (N, h, w)
        y_pred_onehot = tf.one_hot(y_pred, depth=self.n_classes)
        y_true_onehot = tf.one_hot(y_true, depth=self.n_classes)

        dice_coeff_sum = 0
        for i in range(1, self.n_classes):
            dice_coeff_sum += dice_coeff(y_pred_onehot[..., i], 
                                         y_true_onehot[..., i])
        return dice_coeff_sum / (self.n_classes - 1)


class MulticlassIOU():
    def __init__(self, n_classes):
        self.n_classes = n_classes

    def __call__(self, y_true, y_pred):
        y_pred = tf.argmax(y_pred, axis=-1)   ## (N, n_classes, h, w) -> (N, h, w)
        y_pred_onehot = tf.one_hot(y_pred, depth=self.n_classes)
        y_true_onehot = tf.one_hot(y_true, depth=self.n_classes)

        iou_sum = 0
        for i in range(1, self.n_classes):
            iou_sum += iou(y_pred_onehot[..., i], y_true_onehot[..., i])
        return iou_sum / (self.n_classes - 1)


class Trainer():
    def __init__(self, model, optimizer, loss_fn, metric_fn, metric_name=None):
        self.model = model
        self.optimizer = optimizer
        self.loss_fn = loss_fn
        self.metric_fn = metric_fn
        self.metric_name = 'acc' if metric_name is None else metric_name

    @tf.function
    def train_step(self, x, y):
        with tf.GradientTape() as tape:
            pred = self.model(x, training=True)
            loss = self.loss_fn(y, pred)

        gradients = tape.gradient(loss, self.model.trainable_variables)
        self.optimizer.apply_gradients(zip(gradients, 
                                           self.model.trainable_variables))

        metric = self.metric_fn(y, pred)
        return {'loss': float(loss), 'metric': float(metric)}

    @tf.function
    def test_step(self, x, y):
        pred = self.model(x, training=False)
        loss = self.loss_fn(y, pred)
        metric = self.metric_fn(y, pred)
        return {'loss': float(loss), 'metric': float(metric)}

    def fit(self, train_loader, n_epochs, valid_loader=None):
        for epoch in range(1, n_epochs + 1):

            train_loss, train_metric = np.array([]), np.array([])
            for x, y in train_loader:
                result = self.train_step(x, y)
                train_loss = np.append(train_loss, result['loss'])
                train_metric = np.append(train_metric, result['metric'])

            if valid_loader is not None:
                test_loss, test_metric = np.array([]), np.array([])
                for x, y in valid_loader:
                    result = self.test_step(x, y)
                    test_loss = np.append(test_loss, result['loss'])
                    test_metric = np.append(test_metric, result['metric'])

                print("Epoch[%3d/%3d] loss=%.4f, %s=%.4f, \
                    val_loss=%.4f, val_%s=%.4f" % (
                    epoch, n_epochs,
                    train_loss.mean(), self.metric_name, train_metric.mean(),
                    test_loss.mean(), self.metric_name, test_metric.mean()))
            else:
                print("Epoch[%3d/%3d] loss=%.4f, %s=%.4f" % (
                    epoch, n_epochs,
                    train_loss.mean(), self.metric_name, train_metric.mean()))

    def evaluate(self, dataloader):
        test_loss, test_metric = np.array([]), np.array([])
        for x, y in dataloader:
            result = self.test_step(x, y)
            test_loss = np.append(test_loss, result['loss'])
            test_metric = np.append(test_metric, result['metric'])
        return test_loss.mean(), test_metric.mean()


class TrainerTQDM(Trainer):

    def fit(self, train_loader, n_epochs, valid_loader=None):
        for epoch in range(1, n_epochs + 1):
            train_loss, train_metric = np.array([]), np.array([])
            train_pbar = tqdm(train_loader, leave=False, file=sys.stdout, 
                              ascii=True, ncols=100)

            for x, y in train_pbar:
                result = self.train_step(x, y)
                train_loss = np.append(train_loss, result['loss'])
                train_metric = np.append(train_metric, result['metric'])
                train_pbar.set_description("Epoch[%3d/%3d] loss=%.4f, %s=%.4f" % (
                    epoch, n_epochs,
                    train_loss.mean(), self.metric_name, train_metric.mean()))

            if valid_loader is not None:
                test_loss, test_metric = np.array([]), np.array([])
                valid_pbar = tqdm(valid_loader, leave=False, file=sys.stdout, 
                                  ascii=True, ncols=100)

                for x, y in valid_pbar:
                    result = self.test_step(x, y)
                    test_loss = np.append(test_loss, result['loss'])
                    test_metric = np.append(test_metric, result['metric'])
                    valid_pbar.set_description(">> val_loss=%.4f, val_%s=%.4f" % (
                        test_loss.mean(), self.metric_name, test_metric.mean()))

                print("Epoch[%3d/%3d] loss=%.4f, %s=%.4f, \
                    val_loss=%.4f, val_%s=%.4f" % (
                    epoch, n_epochs,
                    train_loss.mean(), self.metric_name, train_metric.mean(),
                    test_loss.mean(), self.metric_name, test_metric.mean()))
            else:
                print("Epoch[%3d/%3d] loss=%.4f, %s=%.4f" % (
                    epoch, n_epochs,
                    train_loss.mean(), self.metric_name, train_metric.mean()))


class TrainerWithMetrics():
    def __init__(self, model, optimizer, loss_fn, metrics={}):
        self.model = model
        self.optimizer = optimizer
        self.loss_fn = loss_fn
        self.metrics = metrics

    @tf.function
    def train_step(self, x, y):
        with tf.GradientTape() as tape:
            pred = self.model(x, training=True)
            loss = self.loss_fn(y, pred)

        gradients = tape.gradient(loss, self.model.trainable_variables)
        self.optimizer.apply_gradients(zip(gradients, 
                                           self.model.trainable_variables))

        results = {'loss': float(loss)}
        for metric_name, metric_fn in self.metrics.items():
            results[metric_name] = float(metric_fn(y, pred))
        return results

    @tf.function
    def test_step(self, x, y):
        pred = self.model(x, training=False)
        loss = self.loss_fn(y, pred)

        results = {'loss': float(loss)}
        for metric_name, metric_fn in self.metrics.items():
            results[metric_name] = float(metric_fn(y, pred))
        return results

    def update_history(self, results):
        for key, value in results.items():
            self.history[key].append(value.mean())

    def fit(self, train_loader, n_epochs, valid_loader=None):
        self.history = {'loss': []}
        self.history.update({key: [] for key in self.metrics.keys()})

        if valid_loader is not None:
            self.history['val_loss'] = []
            self.history.update({f"val_{key}": [] 
                                 for key in self.metrics.keys()})

        for epoch in range(1, n_epochs + 1):

            ## Training
            train_results = {'loss': np.array([])}
            train_results.update({key: np.array([]) 
                                  for key in self.metrics.keys()})
            train_pbar = tqdm(train_loader, leave=False, file=sys.stdout, 
                              ascii=True, ncols=100)

            for x, y in train_pbar:
                results = self.train_step(x, y)

                for key in results.keys():
                    train_results[key] = np.append(train_results[key], 
                                                   results[key])

                train_template = f"Epoch[{epoch:3d}/{n_epochs:3d}] "
                train_template += ', '.join([f"{key}={value.mean():.4f}"
                                       for key, value in train_results.items()])
                train_pbar.set_description(train_template)

            ## Validation
            if valid_loader is None:
                print(train_template)
                self.update_history(train_results)
            else:
                valid_results = {'val_loss': np.array([])}
                valid_results.update({f"val_{key}": np.array([]) 
                                      for key in self.metrics.keys()})
                valid_pbar = tqdm(valid_loader, leave=False, file=sys.stdout, 
                                  ascii=True, ncols=100)

                for x, y in valid_pbar:
                    results = self.test_step(x, y)

                    for key in results.keys():
                        valid_results[f"val_{key}"] = np.append(
                            valid_results[f"val_{key}"], results[key])

                    valid_template = ', '.join(
                        [f"{key}={value.mean():.4f}" 
                         for key, value in valid_results.items()])
                    valid_pbar.set_description(">> " + valid_template)

                print(train_template, "|", valid_template)
                self.update_history(train_results)
                self.update_history(valid_results)

        return self.history

    def evaluate(self, test_loader):
        test_results = {'loss': np.array([])}
        test_results.update({key: np.array([]) 
                             for key in self.metrics.keys()})
        test_pbar = tqdm(test_loader, leave=False, file=sys.stdout, 
                         ascii=True, ncols=100)

        for x, y in test_pbar:
            results = self.test_step(x, y)
            for key in test_results.keys():
                test_results[key] = np.append(test_results[key], results[key])

            test_template = ', '.join(
                [f"test_{key}={value.mean():.4f}"
                 for key, value in test_results.items()])
            test_pbar.set_description(">> " + test_template)

        return {key:value.mean() for key, value in test_results.items()}


class TrainerWithEarlyStopping(TrainerWithMetrics):
    def fit(self, train_loader, n_epochs, valid_loader, model_name="", 
            patience=5, min_loss=0.0001):
        self.history = {'loss': []}
        self.history.update({key: [] for key in self.metrics.keys()})
        self.history['val_loss'] = []
        self.history.update({f"val_{key}": [] 
                             for key in self.metrics.keys()})

        best_loss, counter = np.inf, 1
        for epoch in range(1, n_epochs + 1):

            ## Training
            train_results = {'loss': np.array([])}
            train_results.update({key: np.array([]) 
                                  for key in self.metrics.keys()})
            train_pbar = tqdm(train_loader, leave=False, file=sys.stdout, 
                              ascii=True, ncols=100)

            for x, y in train_pbar:
                results = self.train_step(x, y)

                for key in results.keys():
                    train_results[key] = np.append(train_results[key], 
                                                   results[key])

                train_template = f"Epoch[{epoch:3d}/{n_epochs:3d}] "
                train_template += ', '.join(
                    [f"{key}={value.mean():.4f}"
                     for key, value in train_results.items()])
                train_pbar.set_description(train_template)

            ## Validation
            valid_results = {'val_loss': np.array([])}
            valid_results.update({f"val_{key}": np.array([]) 
                                  for key in self.metrics.keys()})
            valid_pbar = tqdm(valid_loader, leave=False, file=sys.stdout, 
                              ascii=True, ncols=100)

            for x, y in valid_pbar:
                results = self.test_step(x, y)

                for key in results.keys():
                    valid_results[f"val_{key}"] = np.append(
                        valid_results[f"val_{key}"], results[key])

                valid_template = ', '.join(
                    [f"{key}={value.mean():.4f}"
                     for key, value in valid_results.items()])
                valid_pbar.set_description(">> " + valid_template)

            self.update_history(train_results)
            self.update_history(valid_results)

            ## Early Stopping
            current_loss = valid_results['val_loss'].mean()
            if current_loss < best_loss and (best_loss - current_loss) > min_loss:
                best_loss = current_loss
                best_epoch = epoch
                best_model = deepcopy(self.model.get_weights())
                counter = 1
            else:
                counter += 1

            print(f"{train_template} | {valid_template} ({counter})")
            if counter == patience:
                print(f">> Early stopped! (Best epoch={best_epoch})")
                break

        self.model.set_weights(best_model)
        if model_name != "":
            model_dir = os.path.dirname(model_name)
            pathlib.Path(model_dir).mkdir(parents=True, exist_ok=True)
            self.model.save_weights(model_name)

        return self.history


def predict(model, dataloader):
    preds = np.array([])
    for x, _ in dataloader:
        y_pred = model.predict(x)
    preds = np.concatenate([preds, y_pred], axis=0)
    return preds