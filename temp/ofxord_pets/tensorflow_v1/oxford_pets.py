import os
from glob import glob
import random
import re
import pathlib

from sklearn.model_selection import StratifiedKFold
import xml.etree.ElementTree as et
import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle


def download_data(url, data_path):
    import requests
    from tqdm import tqdm

    files_size = int(requests.head(url).headers["content-length"])
    pathlib.Path(data_path).mkdir(parents=True, exist_ok=True)
    file_path = os.path.join(data_path, os.path.basename(url))

    pbar = tqdm(total=files_size, unit='B', unit_scale=True, unit_divisor=1024,
                ascii=True, desc=os.path.basename(url), ncols=100)

    with requests.get(url, stream=True) as req, open(file_path, 'wb') as file:
        for chunk in req.iter_content(chunk_size=1024):
            data_size = file.write(chunk)
            pbar.update(data_size)
        pbar.close()


def extract(file_path, extract_path):
    import shutil

    print(">> Extracting", os.path.basename(file_path))
    shutil.unpack_archive(file_path, extract_path)
    pathlib.Path(file_path).unlink()
    print(">> Complete!")


def check_dataset(data_dir, download=False):
    url_dataset = "https://www.robots.ox.ac.uk/~vgg/data/pets/data/images.tar.gz"
    url_groundtruth = "https://www.robots.ox.ac.uk/~vgg/data/pets/data/annotations.tar.gz"
    urls = [url_dataset, url_groundtruth]

    if not pathlib.Path(data_dir).exists():
        print(">> Dataset path is invalid.")
        if download:
            for url in urls:
                download_data(url, data_dir)
                filename = os.path.join(data_dir, os.path.basename(url))
                extract(filename, data_dir)
    else:
        print(">> Dataset path is valid.")


def get_paths_labels(file_dir, file_type, n_classes, fold=0):
    """ Oxford III Pet Dataset: images/bboxes/masks and labels """

    def get_class_name(path):
        p = os.path.splitext(os.path.basename(path))[0]
        return re.sub('_\d+', '', p)

    def get_species(path):
        p = os.path.splitext(os.path.basename(path))[0]
        return 'cat' if p[0].isupper() else 'dog'

    assert file_type in ("*.jpg", "*.xml", "*.png")

    ## image paths:
    invalid_filenames = ['Egyptian_Mau_14',  'Egyptian_Mau_139', 'Egyptian_Mau_145',
                         'Egyptian_Mau_156', 'Egyptian_Mau_167', 'Egyptian_Mau_177',
                         'Egyptian_Mau_186', 'Egyptian_Mau_191', 'Abyssinian_5',
                         'Abyssinian_34',    'chihuahua_121',    'beagle_116']

    file_dir = os.path.abspath(file_dir)
    image_paths = []
    for path in glob(os.path.join(file_dir, file_type)):
        filename = os.path.basename(path).split('.')[0]
        if filename not in invalid_filenames:
            image_paths.append(path)

    ## image labels:
    if n_classes == 37:
        class_names = list(set([get_class_name(path) for path in image_paths]))
        class_names.sort()
        class2label = {cls:lbl for lbl, cls in enumerate(class_names)}
        image_labels = [class2label[get_class_name(path)] for path in image_paths]
    else:
        class_names = ['cat', 'dog']
        class2label = {cls:lbl for lbl, cls in enumerate(class_names)}
        image_labels = [class2label[get_species(path)] for path in image_paths]

    ## train/valid splits (8:2)
    skf = StratifiedKFold(n_splits=5, shuffle=True, random_state=42)
    train_indices, valid_indices = [], []
    for t, v in skf.split(image_paths, image_labels):
        random.shuffle(t)
        random.shuffle(v)
        train_indices.append(t)
        valid_indices.append(v)

    train_paths = [image_paths[idx] for idx in train_indices[fold]]
    train_labels = [image_labels[idx] for idx in train_indices[fold]]

    valid_paths = [image_paths[idx] for idx in valid_indices[fold]]
    valid_labels = [image_labels[idx] for idx in valid_indices[fold]]

    return (train_paths, train_labels), (valid_paths, valid_labels), class_names


def get_bbox(bbox_path):
    tree = et.parse(bbox_path)

    width = float(tree.find('./size/width').text)
    height = float(tree.find('./size/height').text)
    xmin = float(tree.find('./object/bndbox/xmin').text)
    xmax = float(tree.find('./object/bndbox/xmax').text)
    ymin = float(tree.find('./object/bndbox/ymin').text)
    ymax = float(tree.find('./object/bndbox/ymax').text)

    x = (xmax + xmin)/width/2.
    y = (ymax + ymin)/height/2.
    w = (xmax - xmin)/width
    h = (ymax - ymin)/height

    return [x, y, w, h]


def get_image_path(path, image_dir):
    p = os.path.splitext(os.path.basename(path))[0]
    return os.path.join(image_dir, p + ".jpg")


def get_rect(bbox, img_size):
    x, y, w, h = bbox
    xmin = int((x - w/2.)*img_size[0])
    xmax = int((x + w/2.)*img_size[0])
    ymin = int((y - h/2.)*img_size[1])
    ymax = int((y + h/2.)*img_size[1])
    return xmin, ymin, xmax - xmin, ymax - ymin


def show_images(images, labels=None, bboxes=None, class_names=None,
                n_cols=5, width=12, img_size=None):
    n_rows = images.shape[0] // n_cols + (1 if images.shape[0] % n_cols else 0)
    height = width*n_rows/n_cols

    fig, axes = plt.subplots(n_rows, n_cols, figsize=(width, height))
    for i, ax in enumerate(axes.flat):
        if i < images.shape[0]:
            ax.imshow(images[i])
            if labels is not None:
                if class_names is not None:
                    ax.set_title(class_names[labels[i]])
                else:
                    ax.set_title(labels[i])
            if bboxes is not None and img_size is not None:
                xmin, ymin, width, height = get_rect(bboxes[i], img_size=img_size)
                ax.add_patch(Rectangle((xmin, ymin), width, height, fill=False, color='r', lw=2))
        ax.set_axis_off()
    fig.tight_layout()

    if labels is None:
        plt.subplots_adjust(wspace=0, hspace=0)
    plt.show()