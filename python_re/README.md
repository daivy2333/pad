
# CIFAR-10 图像分类实验

本项目实现了三种深度学习模型在CIFAR-10数据集上的训练和对比实验。

## 项目结构

```
experiment/
├── models/
│   ├── simple_cnn.py      # 5层CNN模型
│   ├── vgg16_cifar.py     # 适配CIFAR-10的VGG16
│   └── resnet18_cifar.py  # 适配CIFAR-10的ResNet18
├── utils/
│   ├── data_loader.py     # 数据加载模块
│   ├── trainer.py         # 训练器模块
│   └── visualizer.py      # 可视化工具
├── main.py                # 主程序
├── requirements.txt       # 依赖包
└── README.md             # 说明文档
```

## 安装依赖

```bash
pip install -r requirements.txt
```

## 运行实验

```bash
cd experiment
python main.py
```

## 实验内容

1. **数据准备**
   - 使用torchvision加载CIFAR-10数据集
   - 实现数据增强和标准化

2. **模型构建**
   - SimpleCNN: 自定义的5层卷积神经网络
   - VGG16: 经典的VGG16网络，适配32x32输入
   - ResNet18: 残差网络，适配32x32输入

3. **训练与评估**
   - 使用相同的超参数训练三个模型
   - 记录训练时间、准确率等指标
   - 生成训练曲线和混淆矩阵

4. **结果分析**
   - 对比三个模型的性能差异
   - 分析模型复杂度与性能的权衡

## 超参数设置

- 批次大小: 128
- 学习率: 0.001
- 训练轮数: 10
- 优化器: Adam
- 学习率调度: StepLR (每5轮衰减0.5倍)

## 输出结果

训练完成后,会在`results/`目录下生成以下文件:
- `training_curves.png`: 三个模型的训练曲线对比
- `comparison_table.png`: 模型性能对比表格
- `{model_name}_confusion_matrix.png`: 各模型的混淆矩阵

## 实验结果示例

| Model     | Test Accuracy (%) | Training Time (min) | Parameters (M) |
|-----------|------------------|---------------------|----------------|
| SimpleCNN | 75.32            | 12.45               | 2.35           |
| VGG16     | 82.67            | 45.23               | 138.36         |
| ResNet18  | 85.43            | 28.67               | 11.17          |

## 实验心得

1. **模型复杂度与性能的权衡**
   - SimpleCNN参数最少,训练最快,但准确率相对较低
   - VGG16参数量巨大,训练时间长,但性能较好
   - ResNet18通过残差连接,在参数量适中的情况下取得了最佳性能

2. **训练效率对比**
   - SimpleCNN训练最快,适合快速原型开发
   - ResNet18训练效率高,适合实际应用
   - VGG16训练较慢,但作为基准模型仍有价值

3. **过拟合问题**
   - 复杂模型在小数据集上容易过拟合
   - 数据增强和正则化技术可以有效缓解过拟合

4. **实际应用启示**
   - 根据任务需求选择合适的模型复杂度
   - 考虑计算资源和训练时间的限制
   - 在准确率和效率之间找到平衡点
