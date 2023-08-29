import torch
import torch.nn.functional as F

import numpy as np
from tqdm import tqdm
import sys
from copy import deepcopy
import os
import pathlib


def binary_accuracy(y_pred, y_true):
    """ Binary classification (y_pred: logits without sigmoid)"""
    y_pred = torch.round(torch.sigmoid(y_pred))     ## float32 (float)
    return torch.eq(y_pred, y_true).float().mean()


def accuracy(y_pred, y_true):
    """ Multi-class classification (y_pred: logtis without sofrmax) """
    y_pred = y_pred.argmax(dim=1)                   ## int64 (long)
    return torch.eq(y_pred, y_true).float().mean()


def iou(y_pred, y_true):
    # if y_pred.ndim > y_true.ndim:
    #     y_pred = y_pred.sigmoid().round()

    y_pred = y_pred.flatten().float()
    y_true = y_true.flatten().float()
    intersection = torch.dot(y_pred, y_true).sum()
    union = y_true.sum() + y_pred.sum() - intersection
    return intersection / (union + 1e-10)


def dice_coeff(y_pred, y_true):
    # if y_pred.ndim > y_true.ndim:
    #     y_pred = y_pred.sigmoid().round()

    y_pred = y_pred.flatten().float()       ## (N, h, w) -> (N,) 0 or 1
    y_true = y_true.flatten().float()       ## (N, h, w) -> (N,) 0 or 1
    intersection = torch.dot(y_pred, y_true).sum()
    return 2*intersection / (y_true.sum() + y_pred.sum() + 1e-10)


class MulticlassIOU():
    def __init__(self, n_classes):
        self.n_classes = n_classes
        
    def __call__(self, y_pred, y_true):
        y_pred = y_pred.argmax(dim=1)   ## (N, n_classes, h, w) -> (N, h, w)
        y_pred_onehot = F.one_hot(y_pred, num_classes=self.n_classes)
        y_true_onehot = F.one_hot(y_true, num_classes=self.n_classes)
        
        iou_sum = 0
        for i in range(1, self.n_classes):
            iou_sum += iou(y_pred_onehot[..., i], y_true_onehot[..., i])
        return iou_sum / (self.n_classes - 1)


class MulticlassDiceCoeff():
    def __init__(self, n_classes):
        self.n_classes = n_classes
        
    def __call__(self, y_pred, y_true):
        y_pred = y_pred.argmax(dim=1)   ## (N, n_classes, h, w) -> (N, h, w)
        y_pred_onehot = F.one_hot(y_pred, num_classes=self.n_classes)
        y_true_onehot = F.one_hot(y_true, num_classes=self.n_classes)
        
        dice_coeff_sum = 0
        for i in range(1, self.n_classes):
            dice_coeff_sum += dice_coeff(y_pred_onehot[..., i], y_true_onehot[..., i])
        return dice_coeff_sum / (self.n_classes - 1)


class Trainer():
    def __init__(self, model, optimizer, loss_fn, metric_fn, metric_name=None):
        self.model = model
        self.optimizer = optimizer
        self.loss_fn = loss_fn
        self.metric_fn = metric_fn
        self.metric_name = 'acc' if metric_name is None else metric_name
        self.device = next(model.parameters()).device

    def train_step(self, x, y):
        x, y = x.to(self.device), y.to(self.device)
        self.optimizer.zero_grad()
        pred = self.model(x)
        loss = self.loss_fn(pred, y)
        loss.backward()
        self.optimizer.step()

        metric = self.metric_fn(pred, y)
        return {'loss': loss.item(), 'metric': metric.item()}

    @torch.no_grad()
    def test_step(self, x, y):
        x, y = x.to(self.device), y.to(self.device)
        pred = self.model(x)
        loss = self.loss_fn(pred, y)

        metric = self.metric_fn(pred, y)
        return {'loss': loss.item(), 'metric': metric.item()}

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

                print("Epoch[%3d/%3d] loss=%.4f, %s=%.4f, val_loss=%.4f, val_%s=%.4f" % (
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
            train_pbar = tqdm(train_loader, leave=False, file=sys.stdout, ascii=True, ncols=100)

            for x, y in train_pbar:
                result = self.train_step(x, y)
                train_loss = np.append(train_loss, result['loss'])
                train_metric = np.append(train_metric, result['metric'])
                train_pbar.set_description("Epoch[%3d/%3d] loss=%.4f, %s=%.4f" % (
                    epoch, n_epochs,
                    train_loss.mean(), self.metric_name, train_metric.mean()))

            if valid_loader is not None:
                test_loss, test_metric = np.array([]), np.array([])
                valid_pbar = tqdm(valid_loader, leave=False, file=sys.stdout, ascii=True, ncols=100)

                for x, y in valid_pbar:
                    result = self.test_step(x, y)
                    test_loss = np.append(test_loss, result['loss'])
                    test_metric = np.append(test_metric, result['metric'])
                    valid_pbar.set_description(">> val_loss=%.4f, val_%s=%.4f" % (
                        test_loss.mean(), self.metric_name, test_metric.mean()))

                print("Epoch[%3d/%3d] loss=%.4f, %s=%.4f, val_loss=%.4f, val_%s=%.4f" % (
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
        self.device = next(model.parameters()).device

    def train_step(self, x, y):
        self.model.train()
        x, y = x.to(self.device), y.to(self.device)

        self.optimizer.zero_grad()
        pred = self.model(x)
        loss = self.loss_fn(pred, y)
        loss.backward()
        self.optimizer.step()

        results = {'loss': loss.item()}
        for metric_name, metric_fn in self.metrics.items():
            results[metric_name] = metric_fn(pred, y).item()
        return results

    @torch.no_grad()
    def test_step(self, x, y):
        self.model.eval()
        x, y = x.to(self.device), y.to(self.device)

        pred = self.model(x)
        loss = self.loss_fn(pred, y)

        results = {'loss': loss.item()}
        for metric_name, metric_fn in self.metrics.items():
            results[metric_name] = metric_fn(pred, y).item()
        return results

    def update_history(self, results):
        for key, value in results.items():
            self.history[key].append(value.mean())

    def fit(self, train_loader, n_epochs, valid_loader=None):
        self.history = {'loss': []}
        self.history.update({key: [] for key in self.metrics.keys()})

        if valid_loader is not None:
            self.history['val_loss'] = []
            self.history.update({f"val_{key}": [] for key in self.metrics.keys()})

        for epoch in range(1, n_epochs + 1):

            ## Training
            train_results = {'loss': np.array([])}
            train_results.update({key: np.array([]) for key in self.metrics.keys()})
            train_pbar = tqdm(train_loader, leave=False, file=sys.stdout, ascii=True, ncols=100)

            for x, y in train_pbar:
                results = self.train_step(x, y)

                for key in results.keys():
                    train_results[key] = np.append(train_results[key], results[key])

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
                valid_results.update({f"val_{key}": np.array([]) for key in self.metrics.keys()})
                valid_pbar = tqdm(valid_loader, leave=False, file=sys.stdout, ascii=True, ncols=100)

                for x, y in valid_pbar:
                    results = self.test_step(x, y)

                    for key in results.keys():
                        valid_results[f"val_{key}"] = np.append(valid_results[f"val_{key}"], results[key])

                    valid_template = ', '.join([f"{key}={value.mean():.4f}"
                                                for key, value in valid_results.items()])
                    valid_pbar.set_description(">> " + valid_template)

                print(train_template, "|", valid_template)
                self.update_history(train_results)
                self.update_history(valid_results)

        return self.history

    def evaluate(self, test_loader):
        test_results = {'loss': np.array([])}
        test_results.update({key: np.array([]) for key in self.metrics.keys()})
        test_pbar = tqdm(test_loader, leave=False, file=sys.stdout, ascii=True, ncols=100)

        for x, y in test_pbar:
            results = self.test_step(x, y)
            for key in test_results.keys():
                test_results[key] = np.append(test_results[key], results[key])

            test_template = ', '.join([f"test_{key}={value.mean():.4f}"
                                        for key, value in test_results.items()])
            test_pbar.set_description(">> " + test_template)

        return {key:value.mean() for key, value in test_results.items()}


class TrainerWithEarlyStopping(TrainerWithMetrics):

    def fit(self, train_loader, n_epochs, valid_loader, model_name="", patience=5, min_loss=0.0001):
        self.history = {'loss': []}
        self.history.update({key: [] for key in self.metrics.keys()})
        self.history['val_loss'] = []
        self.history.update({f"val_{key}": [] for key in self.metrics.keys()})

        best_loss, counter = np.inf, 1
        for epoch in range(1, n_epochs + 1):

            ## Training
            train_results = {'loss': np.array([])}
            train_results.update({key: np.array([]) for key in self.metrics.keys()})
            train_pbar = tqdm(train_loader, leave=False, file=sys.stdout, ascii=True, ncols=100)

            for x, y in train_pbar:
                results = self.train_step(x, y)

                for key in results.keys():
                    train_results[key] = np.append(train_results[key], results[key])

                train_template = f"Epoch[{epoch:3d}/{n_epochs:3d}] "
                train_template += ', '.join([f"{key}={value.mean():.4f}"
                                       for key, value in train_results.items()])
                train_pbar.set_description(train_template)

            ## Validation
            valid_results = {'val_loss': np.array([])}
            valid_results.update({f"val_{key}": np.array([]) for key in self.metrics.keys()})
            valid_pbar = tqdm(valid_loader, leave=False, file=sys.stdout, ascii=True, ncols=100)

            for x, y in valid_pbar:
                results = self.test_step(x, y)

                for key in results.keys():
                    valid_results[f"val_{key}"] = np.append(valid_results[f"val_{key}"], results[key])

                valid_template = ', '.join([f"{key}={value.mean():.4f}"
                                            for key, value in valid_results.items()])
                valid_pbar.set_description(">> " + valid_template)

            self.update_history(train_results)
            self.update_history(valid_results)

            ## Early Stopping
            current_loss = valid_results['val_loss'].mean()
            if current_loss < best_loss and (best_loss - current_loss) > min_loss:
                best_loss = current_loss
                best_epoch = epoch
                best_model = deepcopy(self.model.state_dict())
                counter = 1
            else:
                counter += 1

            print(f"{train_template} | {valid_template} ({counter})")
            if counter == patience:
                print(f">> Early stopped! (Best epoch={best_epoch})")
                break

        self.model.load_state_dict(best_model)
        if model_name != "":
            model_dir = os.path.dirname(model_name)
            pathlib.Path(model_dir).mkdir(parents=True, exist_ok=True)
            torch.save(best_model, model_name)

        return self.history