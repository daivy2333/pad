import warnings
from sklearn.datasets import load_wine
from sklearn.model_selection import train_test_split, GridSearchCV, RandomizedSearchCV, cross_val_score
from sklearn.preprocessing import StandardScaler
from sklearn.linear_model import LogisticRegression
from sklearn.tree import DecisionTreeClassifier
from sklearn.cluster import KMeans
from sklearn.decomposition import PCA
from sklearn.metrics import accuracy_score
from sklearn import svm
from scipy.stats import randint

# 忽略部分版本警告，保持输出整洁
warnings.filterwarnings('ignore')

# ==========================================
# 1. 数据加载与预处理
# ==========================================
print(">>> 1. 加载葡萄酒数据集并进行预处理")
wine = load_wine()
X = wine.data
y = wine.target

# 划分训练集和测试集 (70% 训练, 30% 测试)，使用分层抽样保持类别比例
X_train, X_test, y_train, y_test = train_test_split(
    X, y, random_state=12, stratify=y, test_size=0.3
)

# 数据标准化
# 注意：先在训练集上fit，然后分别transform训练集和测试集，避免数据泄露
scaler = StandardScaler()
X_train_scaled = scaler.fit_transform(X_train)
X_test_scaled = scaler.transform(X_test)

print(f"数据集形状: {X.shape}, 类别数量: {len(wine.target_names)}")
print("-" * 50)

# ==========================================
# 2. 分类模型 (逻辑回归 & 决策树)
# ==========================================
print(">>> 2. 训练分类模型")

# --- 逻辑回归 (替代原代码的线性回归，因为这是分类任务) ---
# 使用标准化后的数据训练逻辑回归
lr = LogisticRegression(max_iter=1000) # 增加迭代次数以确保收敛
lr.fit(X_train_scaled, y_train)
y_pred_lr = lr.predict(X_test_scaled)
acc_lr = accuracy_score(y_test, y_pred_lr)
print(f"逻辑回归准确率: {acc_lr:.4f}")

# --- 决策树 ---
# 决策树对数据缩放不敏感，可以使用原始数据，但为了统一流程这里使用标准化数据
clf = DecisionTreeClassifier(max_depth=5, random_state=12)
clf.fit(X_train_scaled, y_train)
y_pred_clf = clf.predict(X_test_scaled)
y_prob_clf = clf.predict_proba(X_test_scaled) # 预测概率
acc_clf = accuracy_score(y_test, y_pred_clf)
print(f"决策树准确率: {acc_clf:.4f}")
print("-" * 50)

# ==========================================
# 3. 聚类模型 (K-Means)
# ==========================================
print(">>> 3. 训练K-Means聚类模型")
# 葡萄酒数据集有3个类别，因此我们设置聚类中心为3
kmeans = KMeans(n_clusters=3, random_state=0, n_init='auto')
kmeans.fit(X_train_scaled) # 使用标准化数据
y_pred_kmeans = kmeans.predict(X_test_scaled)
# 注意：聚类标签可能与原始标签不一致（例如0可能对应类别2），这里仅展示预测结果
print(f"聚类中心形状: {kmeans.cluster_centers_.shape}")
print(f"前10个测试样本的聚类预测结果: {y_pred_kmeans[:10]}")
print("-" * 50)

# ==========================================
# 4. 降维 (PCA)
# ==========================================
print(">>> 4. PCA主成分分析")
# 使用全部数据进行PCA拟合以查看整体方差分布
pca = PCA(n_components=3)
X_pca = pca.fit_transform(X) # 通常在标准化数据上做PCA效果更好，这里演示使用原始数据

print("各主成分解释方差比例:", pca.explained_variance_ratio_)
print("各主成分解释方差值:", pca.explained_variance_)
print("-" * 50)

# ==========================================
# 5. 模型评估 (交叉验证)
# ==========================================
print(">>> 5. 交叉验证评估")
# 使用决策树进行5折交叉验证，使用F1分数作为评价指标
# 对于多分类问题，使用 'f1_weighted' 或 'f1_macro'
clf_cv = DecisionTreeClassifier(max_depth=5, random_state=12)
scores = cross_val_score(clf_cv, X_train_scaled, y_train, cv=5, scoring='f1_weighted')
print(f"决策树 5折交叉验证 F1分数: {scores}")
print(f"平均 F1 分数: {scores.mean():.4f}")
print("-" * 50)

# ==========================================
# 6. 超参数调优 (网格搜索 & 随机搜索)
# ==========================================
print(">>> 6. 超参数调优")

# --- 网格搜索 ---
print("--- 网格搜索 ---")
svc = svm.SVC()
params = {'kernel': ['linear', 'rbf'], 'C': [1, 10]}
grid_search = GridSearchCV(svc, params, cv=5)
grid_search.fit(X_train_scaled, y_train)
print(f"网格搜索最佳参数: {grid_search.best_params_}")
print(f"网格搜索最佳模型准确率: {grid_search.best_score_:.4f}")

# --- 随机搜索 ---
print("\n--- 随机搜索 ---")
svc = svm.SVC()
param_dist = {'kernel': ['linear', 'rbf'], 'C': randint(1, 20)}
random_search = RandomizedSearchCV(svc, param_dist, n_iter=10, random_state=12)
random_search.fit(X_train_scaled, y_train)
print(f"随机搜索最佳参数: {random_search.best_params_}")
print(f"随机搜索最佳模型准确率: {random_search.best_score_:.4f}")
