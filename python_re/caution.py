import pandas as pd
import matplotlib.pyplot as plt
from datetime import datetime
import os

# 文件名
FILE_NAME = "weight_records.csv"

# 目标体重 (可选, 单位 kg)
TARGET_WEIGHT = 65  

def add_weight(weight):
    """记录一次体重到 CSV 文件"""
    date = datetime.now().strftime("%Y-%m-%d")
    record = {"Date": date, "Weight": weight}
    
    if os.path.exists(FILE_NAME):
        df = pd.read_csv(FILE_NAME)
        df = pd.concat([df, pd.DataFrame([record])], ignore_index=True)
    else:
        df = pd.DataFrame([record])
    
    df.to_csv(FILE_NAME, index=False)
    print(f"✅ 已记录: {date}, 体重 {weight} kg")

def plot_trend():
    """绘制体重趋势折线图"""
    if not os.path.exists(FILE_NAME):
        print("⚠️ 暂无数据，请先记录体重")
        return
    
    df = pd.read_csv(FILE_NAME)
    df["Date"] = pd.to_datetime(df["Date"])
    df = df.sort_values("Date")

    # 绘制折线图
    plt.figure(figsize=(10, 6))
    plt.plot(df["Date"], df["Weight"], marker="o", label="体重 (kg)")
    
    # 添加目标体重线
    if TARGET_WEIGHT:
        plt.axhline(TARGET_WEIGHT, color="r", linestyle="--", label=f"目标: {TARGET_WEIGHT}kg")
    
    # 最近 7 天 / 30 天平均
    if len(df) >= 7:
        avg_7 = df["Weight"].tail(7).mean()
        plt.axhline(avg_7, color="g", linestyle=":", label=f"最近7天均值: {avg_7:.1f}kg")
    if len(df) >= 30:
        avg_30 = df["Weight"].tail(30).mean()
        plt.axhline(avg_30, color="b", linestyle=":", label=f"最近30天均值: {avg_30:.1f}kg")

    plt.xlabel("日期")
    plt.ylabel("体重 (kg)")
    plt.title("体重趋势折线图")
    plt.legend()
    plt.grid(True)
    plt.show()

def main():
    while True:
        print("\n====== 体重记录小助手 ======")
        print("1. 记录一次体重")
        print("2. 查看趋势折线图")
        print("3. 退出")
        choice = input("请输入选项 (1/2/3): ").strip()

        if choice == "1":
            try:
                weight = float(input("请输入当前体重 (kg): "))
                add_weight(weight)
            except ValueError:
                print("⚠️ 输入无效，请输入数字")
        elif choice == "2":
            plot_trend()
        elif choice == "3":
            print("👋 已退出，祝你健康！")
            break
        else:
            print("⚠️ 无效选项，请重新输入")

if __name__ == "__main__":
    main()
