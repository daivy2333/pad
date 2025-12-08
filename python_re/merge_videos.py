import os
import subprocess
import tempfile

def merge_videos(folder, output="output.mp4"):
    """
    合并指定文件夹中的所有MP4视频文件，按文件名中的数字顺序排序

    参数:
        folder (str): 包含视频文件的文件夹路径
        output (str): 输出视频文件名，默认为"output.mp4"
    """
    # 检查文件夹是否存在
    if not os.path.exists(folder):
        print(f"错误: 文件夹 '{folder}' 不存在")
        return

    # 获取所有 mp4 文件，按数字排序
    files = [f for f in os.listdir(folder) if f.endswith(".mp4")]

    if not files:
        print(f"错误: 文件夹 '{folder}' 中没有找到MP4文件")
        return

    # 将文件名中的数字提取出来排序
    try:
        files_sorted = sorted(files, key=lambda x: int(os.path.splitext(x)[0]))
    except ValueError:
        # 如果文件名不是纯数字，则按字母顺序排序
        files_sorted = sorted(files)
        print("警告: 文件名不是纯数字，将按字母顺序排序")

    print("拼接顺序：", files_sorted)

    # 创建临时文件列表
    with tempfile.NamedTemporaryFile(mode='w', suffix='.txt', delete=False) as temp_file:
        temp_list_path = temp_file.name
        for filename in files_sorted:
            file_path = os.path.join(folder, filename)
            # 使用绝对路径，避免路径问题
            file_path = os.path.abspath(file_path)
            temp_file.write(f"file '{file_path}'\n")

    try:
        # 使用FFmpeg合并视频
        command = [
            'ffmpeg',
            '-f', 'concat',
            '-safe', '0',
            '-i', temp_list_path,
            '-c', 'copy',
            '-y',  # 覆盖输出文件而不询问
            output
        ]

        print("开始合并视频...")
        subprocess.run(command, check=True)
        print(f"处理完成！输出文件: {output}")
    except subprocess.CalledProcessError as e:
        print(f"合并视频时出错: {e}")
    except FileNotFoundError:
        print("错误: 未找到FFmpeg，请确保已安装FFmpeg并添加到系统路径")
    finally:
        # 删除临时文件
        if os.path.exists(temp_list_path):
            os.unlink(temp_list_path)

if __name__ == "__main__":
    # 检查是否安装了FFmpeg
    try:
        subprocess.run(['ffmpeg', '-version'], check=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    except (subprocess.CalledProcessError, FileNotFoundError):
        print("错误: 未找到FFmpeg，请先安装FFmpeg")
        print("在Ubuntu/Debian上安装: sudo apt install ffmpeg")
        print("在CentOS/RHEL上安装: sudo yum install ffmpeg")
        print("在macOS上安装: brew install ffmpeg")
        exit(1)

    merge_videos("videos", "merged_output.mp4")
