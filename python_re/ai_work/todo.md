一、整体实验思路

1. 数据准备：加载CIFAR-10数据集，进行预处理（标准化、数据增强等）。
2. 模型构建：
   • 5层CNN：自定义一个包含5层卷积的网络。

   • VGG16：使用预训练或从头训练的VGG16（适配CIFAR-10的32x32输入）。

   • ResNet18：使用预训练或从头训练的ResNet18。

3. 训练与评估：使用相同的超参数（批次大小、学习率、优化器等）训练三个模型，记录训练时间、准确率等指标。
4. 结果分析：对比三个模型的性能差异，并分析原因。

二、实验内容详细步骤（对应“三、实验内容”）

1. 数据预处理

import torch
import torchvision
import torchvision.transforms as transforms

# 数据增强和标准化
transform_train = transforms.Compose([
    transforms.RandomCrop(32, padding=4),
    transforms.RandomHorizontalFlip(),
    transforms.ToTensor(),
    transforms.Normalize((0.4914, 0.4822, 0.4465), (0.2023, 0.1994, 0.2010)),
])

transform_test = transforms.Compose([
    transforms.ToTensor(),
    transforms.Normalize((0.4914, 0.4822, 0.4465), (0.2023, 0.1994, 0.2010)),
])

# 加载数据集
trainset = torchvision.datasets.CIFAR10(root='./data', train=True, download=True, transform=transform_train)
testset = torchvision.datasets.CIFAR10(root='./data', train=False, download=True, transform=transform_test)


2. 模型定义（关键部分）

（1）5层CNN模型

import torch.nn as nn

class SimpleCNN(nn.Module):
    def __init__(self, num_classes=10):
        super(SimpleCNN, self).__init__()
        self.conv_layers = nn.Sequential(
            nn.Conv2d(3, 32, 3, padding=1),  # 32x32x32
            nn.ReLU(),
            nn.MaxPool2d(2),  # 16x16x32
            
            nn.Conv2d(32, 64, 3, padding=1), # 16x16x64
            nn.ReLU(),
            nn.MaxPool2d(2),  # 8x8x64
            
            nn.Conv2d(64, 128, 3, padding=1), # 8x8x128
            nn.ReLU(),
            nn.Conv2d(128, 256, 3, padding=1), # 8x8x256
            nn.ReLU(),
            nn.Conv2d(256, 256, 3, padding=1), # 8x8x256
            nn.ReLU(),
            nn.MaxPool2d(2)  # 4x4x256
        )
        self.classifier = nn.Linear(256 * 4 * 4, num_classes)

    def forward(self, x):
        x = self.conv_layers(x)
        x = x.view(x.size(0), -1)
        x = self.classifier(x)
        return x


（2）VGG16（适配CIFAR-10）

import torchvision.models as models

def vgg16_cifar10():
    model = models.vgg16(pretrained=False)
    # 修改第一层卷积，适应32x32输入
    model.features[0] = nn.Conv2d(3, 64, kernel_size=3, padding=1)
    # 修改分类器
    model.classifier[6] = nn.Linear(4096, 10)
    return model


（3）ResNet18

def resnet18_cifar10():
    model = models.resnet18(pretrained=False)
    # 修改第一层卷积，适应32x32输入
    model.conv1 = nn.Conv2d(3, 64, kernel_size=3, stride=1, padding=1, bias=False)
    # 移除第一个池化层（保持分辨率）
    model.maxpool = nn.Identity()
    # 修改全连接层
    model.fc = nn.Linear(512, 10)
    return model


3. 训练循环模板

def train_model(model, train_loader, test_loader, epochs=10):
    criterion = nn.CrossEntropyLoss()
    optimizer = torch.optim.Adam(model.parameters(), lr=0.001)
    
    for epoch in range(epochs):
        model.train()
        for inputs, labels in train_loader:
            optimizer.zero_grad()
            outputs = model(inputs)
            loss = criterion(outputs, labels)
            loss.backward()
            optimizer.step()
        
        # 每个epoch后在测试集上评估
        accuracy = evaluate_model(model, test_loader)
        print(f'Epoch {epoch+1}, Accuracy: {accuracy:.2f}%')

def evaluate_model(model, test_loader):
    model.eval()
    correct = 0
    total = 0
    with torch.no_grad():
        for inputs, labels in test_loader:
            outputs = model(inputs)
            _, predicted = torch.max(outputs.data, 1)
            total += labels.size(0)
            correct += (predicted == labels).sum().item()
    return 100 * correct / total


三、实验结果分析要点（对应“四、实验结果截图”）

1. 准确率对比表：
   模型 测试准确率 训练时间 参数量
5层CNN XX.XX% X分钟 X.XM
VGG16 XX.XX% X分钟 XX.XM
ResNet18 XX.XX% X分钟 XX.XM

2. 训练曲线图：绘制三个模型的训练损失和准确率随epoch的变化曲线。

3. 混淆矩阵：展示每个模型在10个类别上的分类效果。

四、提高部分：设计决策探讨

你可以通过以下对比实验来探讨设计决策的影响：

1. 卷积层数量：比较3层、5层、7层CNN的效果。
2. 卷积核大小：对比3x3、5x5、7x7卷积核。
3. 池化策略：比较MaxPooling、AveragePooling、Strided Convolution。
4. 激活函数：ReLU、LeakyReLU、ELU的对比。
5. 归一化层：有/无BatchNorm的对比。

五、实验心得体会（对应“六、实验心得体会”）

在这一部分，你可以从以下角度展开：

1. 模型复杂度与性能的权衡：ResNet18凭借残差连接在深层网络中表现更好。
2. 训练效率对比：5层CNN训练最快，但准确率有限；VGG16参数多，训练慢。
3. 过拟合问题：复杂模型在小数据集上容易过拟合，需要数据增强等技巧。
4. 实际应用启示：根据任务需求选择合适的模型复杂度。

六、完整代码结构建议


experiment/
├── models/
│   ├── simple_cnn.py
│   ├── vgg16_cifar.py
│   └── resnet18_cifar.py
├── utils/
│   ├── data_loader.py
│   └── trainer.py
├── main.py
└── requirements.txt

