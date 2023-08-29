import numpy as np
import matplotlib.pyplot as plt
import skimage
from matplotlib.patches import Rectangle
import os
import pathlib


def get_rect(bbox, image_size):
    x, y, w, h = bbox
    height, width = image_size

    xmin = int((x - w/2.)*width)
    xmax = int((x + w/2.)*width)
    ymin = int((y - h/2.)*height)
    ymax = int((y + h/2.)*height)
    return xmin, ymin, xmax - xmin, ymax - ymin


def show_images(images, labels=None, class_names=None,
                bboxes=None, bbox_color='r',
                bboxes2=None, bbox_color2='b',
                n_cols=5, width=12, rotation=False, denormalize=False):
    if isinstance(images[0], str):
        images = [skimage.io.imread(path) for path in images]

    n_images = len(images)
    n_rows = n_images // n_cols + (1 if n_images % n_cols else 0)
    height = width*n_rows/n_cols

    fig, axes = plt.subplots(n_rows, n_cols, figsize=(width, height))
    for i, ax in enumerate(axes.flat):
        if i < n_images:
            img = images[i]
            if rotation:
                img = skimage.transform.rotate(img, 90)

            if denormalize and img.ndim == 3:
                img *= np.array([0.229, 0.224, 0.225])
                img += np.array([0.485, 0.456, 0.406])
                img = img.clip(0, 1)

            # if img.ndim < 3:
            #     img = skimage.color.gray2rgb(img)

            ax.imshow(img)
            # ax.imshow(img, cmap='gray_r')

            if labels is not None:
                if class_names is not None:
                    ax.set_title(class_names[int(labels[i])])
                else:
                    ax.set_title(int(labels[i]))

            if bboxes is not None:
                x, y, w, h = get_rect(bboxes[i], image_size=img.shape[:2])
                ax.add_patch(Rectangle((x, y), w, h, fill=False, color=bbox_color))

            if bboxes2 is not None:
                x, y, w, h = get_rect(bboxes2[i], image_size=img.shape[:2])
                ax.add_patch(Rectangle((x, y), w, h, fill=False, color=bbox_color2))

        ax.set_axis_off()
    fig.tight_layout()

    if labels is None:
        fig.subplots_adjust(wspace=0, hspace=0)
    plt.show()


def plot_progress(history, skip=1, model_name="", save_history=False):
    fig, ax = plt.subplots(figsize=(8, 4))
    for key, value in history.items():
        epochs = range(1, len(value) + 1)
        ax.plot(epochs[::skip], value[::skip], 'o-', label=key)

    img_name = os.path.basename(model_name).split('.')[0]
    ax.set_title(img_name, fontsize=15)
    ax.set_xlabel("Epochs", fontsize=12)
    ax.tick_params(labelsize=12)
    ax.legend(fontsize=12)
    ax.grid(color='k', ls=':', lw=1)
    fig.tight_layout()

    if save_history:
        img_dir = os.path.dirname(model_name)
        img_name += "_hist.png"

        pathlib.Path(img_dir).mkdir(parents=True, exist_ok=True)
        plt.savefig(os.path.join(img_dir, img_name), pad_inches=0)
        plt.close()
    else:
        plt.show()


if __name__ == "__main__":
    pass