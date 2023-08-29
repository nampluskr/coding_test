## Keras U-Net+MobileNetV2

* https://www.kaggle.com/code/mistag/train-keras-u-net-mobilenetv2/notebook

### Unet with Pretrained Encoder

```python
def unet_vgg_model():
    inputs = Input((IMG_SIZE, IMG_SIZE, 3), name="input_image")
    
    encoder = MobileNetV2(input_tensor=inputs, weights="imagenet", include_top=False, alpha=0.35)
    skip_connection_names = ["input_image", "block_1_expand_relu", "block_3_expand_relu", "block_6_expand_relu"]
    encoder_output = encoder.get_layer("block_13_expand_relu").output
    
    f = [16, 32, 64, 128]
    x = encoder_output
    for i in range(1, len(skip_connection_names)+1, 1):
        x_skip = encoder.get_layer(skip_connection_names[-i]).output
        x = UpSampling2D((2, 2))(x)
        x = Concatenate()([x, x_skip])
        
        x = Conv2D(f[-i], (3, 3), padding="same")(x)
        x = BatchNormalization()(x)
        x = Activation("relu")(x)
        
        x = Conv2D(f[-i], (3, 3), padding="same")(x)
        x = BatchNormalization()(x)
        x = Activation("relu")(x)
        
    x = Conv2D(1, (1, 1), padding="same")(x)
    x = Activation("sigmoid")(x)
    
    model = Model(inputs, x)
    return model
```

### Metrics and Loss Functions

```python
smooth = 1.

def dice_coef(y_true, y_pred):
    y_true_f = K.flatten(y_true)
    y_pred_f = K.flatten(y_pred)
    intersection = K.sum(y_true_f * y_pred_f)
    return (2. * intersection + smooth) / (K.sum(y_true_f) + K.sum(y_pred_f) + smooth)

def dice_coef_loss(y_true, y_pred):
    return 1.-dice_coef(y_true, y_pred)

def iou(y_true, y_pred):
    def f(y_true, y_pred):
        intersection = (y_true * y_pred).sum()
        union = y_true.sum() + y_pred.sum() - intersection
        x = (intersection + 1e-15) / (union + 1e-15)
        x = x.astype(np.float32)
        return x
    return tf.numpy_function(f, [y_true, y_pred], tf.float32)

def tversky(y_true, y_pred, smooth=1, alpha=0.7):
    y_true_pos = K.flatten(y_true)
    y_pred_pos = K.flatten(y_pred)
    true_pos = K.sum(y_true_pos * y_pred_pos)
    false_neg = K.sum(y_true_pos * (1 - y_pred_pos))
    false_pos = K.sum((1 - y_true_pos) * y_pred_pos)
    return (true_pos + smooth) / (true_pos + alpha * false_neg + (1 - alpha) * false_pos + smooth)

def tversky_loss(y_true, y_pred):
    return 1 - tversky(y_true, y_pred)

def focal_tversky_loss(y_true, y_pred, gamma=0.75):
    tv = tversky(y_true, y_pred)
    return K.pow((1 - tv), gamma)
```

## UNet-MobileNet-Pytorch

* https://github.com/YZY-stack/UNet-MobileNet-Pytorch/tree/66a6227dbab01c0976b288f295c79f9601a87edf

```python
from mobilenet.mobile import MobileNet
import torch.nn as nn
from collections import OrderedDict
import torch
import torchsummary as summary

class Down(nn.Module):
    """Downscaling with maxpool then double conv"""

    def __init__(self, in_channels, out_channels):
        super().__init__()
        self.maxpool_conv = nn.Sequential(
            nn.MaxPool2d(2),
            DoubleConv(in_channels, out_channels)
        )

    def forward(self, x):
        return self.maxpool_conv(x)


class DoubleConv(nn.Module):
    """(convolution => [BN] => ReLU) * 2"""

    def __init__(self, in_channels, out_channels, mid_channels=None):
        super().__init__()
        if not mid_channels:
            mid_channels = out_channels
        self.double_conv = nn.Sequential(
            nn.Conv2d(in_channels, mid_channels, kernel_size=3, padding=1),
            nn.BatchNorm2d(mid_channels),
            nn.ReLU(inplace=True),
            nn.Conv2d(mid_channels, out_channels, kernel_size=3, padding=1),
            nn.BatchNorm2d(out_channels),
            nn.ReLU(inplace=True)
        )

    def forward(self, x):
        return self.double_conv(x)


def conv2d(filter_in, filter_out, kernel_size, groups=1, stride=1):
    pad = (kernel_size - 1) // 2 if kernel_size else 0
    return nn.Sequential(OrderedDict([
        ("conv", nn.Conv2d(filter_in, filter_out, kernel_size=kernel_size, stride=stride, padding=pad, groups=groups, bias=False)),
        ("bn", nn.BatchNorm2d(filter_out)),
        ("relu", nn.ReLU6(inplace=True)),
    ]))


class mobilenet(nn.Module):
    def __init__(self, n_channels):
        super(mobilenet, self).__init__()
        self.model = MobileNet(n_channels)

    def forward(self, x):
        out3 = self.model.layer1(x)
        out4 = self.model.layer2(out3)
        out5 = self.model.layer3(out4)

        return out3, out4, out5


class OutConv(nn.Module):
    def __init__(self, in_channels, out_channels):
        super(OutConv, self).__init__()
        self.conv = nn.Conv2d(in_channels, out_channels, kernel_size=1)

    def forward(self, x):
        return self.conv(x)


class UNet(nn.Module):
    def __init__(self, n_channels, num_classes):
        super(UNet, self).__init__()
        self.n_channels = n_channels
        self.num_classes = num_classes

        # ---------------------------------------------------#
        #   64,64,256；32,32,512；16,16,1024
        # ---------------------------------------------------#
        self.backbone = mobilenet(n_channels)

        self.up1 = nn.Upsample(scale_factor=2, mode='nearest')
        self.conv1 = DoubleConv(1024, 512)

        self.up2 = nn.Upsample(scale_factor=2, mode='nearest')
        self.conv2 = DoubleConv(1024, 256)

        self.up3 = nn.Upsample(scale_factor=2, mode='nearest')
        self.conv3 = DoubleConv(512, 128)

        self.up4 = nn.Upsample(scale_factor=2, mode='nearest')
        #nn.Upsample(scale_factor=2, mode='bilinear')
        self.conv4 = DoubleConv(128, 64)

        self.oup = nn.Conv2d(64, num_classes, kernel_size=1)

    def forward(self, x):
        #  backbone
        x2, x1, x0 = self.backbone(x)
        # print(f"x2.shape: {x2.shape}, x1: {x1.shape}, x0: {x0.shape} ")

        P5 = self.up1(x0)
        P5 = self.conv1(P5)           # P5: 26x26x512
        # print(P5.shape)
        P4 = x1                       # P4: 26x26x512
        P4 = torch.cat([P4, P5], axis=1)   # P4: 26x26x1024
        # print(f"cat 后是： {P4.shape}")

        P4 = self.up2(P4)             # 52x52x1024
        P4 = self.conv2(P4)           # 52x52x256
        P3 = x2                       # x2 = 52x52x256
        P3 = torch.cat([P4, P3], axis=1)  # 52x52x512

        P3 = self.up3(P3)
        P3 = self.conv3(P3)

        P3 = self.up4(P3)
        P3 = self.conv4(P3)

        out = self.oup(P3)
        # print(f"out.shape is {out.shape}")

        return out
```

### Loss Functions and Metrics

```python
from torch.autograd import Function

class DiceCoeff(Function):
    """Dice coeff for individual examples"""

    def forward(self, input, target):
        self.save_for_backward(input, target)
        eps = 0.0001
        self.inter = torch.dot(input.view(-1), target.view(-1))
        self.union = torch.sum(input) + torch.sum(target) + eps

        t = (2 * self.inter.float() + eps) / self.union.float()
        return t

    # This function has only a single output, so it gets only one gradient
    def backward(self, grad_output):

        input, target = self.saved_variables
        grad_input = grad_target = None

        if self.needs_input_grad[0]:
            grad_input = grad_output * 2 * (target * self.union - self.inter) \
                         / (self.union * self.union)
        if self.needs_input_grad[1]:
            grad_target = None

        return grad_input, grad_target


def dice_coeff(input, target):
    """Dice coeff for batches"""
    if input.is_cuda:
        s = torch.FloatTensor(1).cuda().zero_()
    else:
        s = torch.FloatTensor(1).zero_()

    for i, c in enumerate(zip(input, target)):
        s = s + DiceCoeff().forward(c[0], c[1])

    return s / (i + 1)
```