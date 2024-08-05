# -*- coding: UTF8 -*-

''' Imports '''
import os
import sys
import shutil
import datetime

def ensure_directory_exists(file_path):
    if not os.path.exists(file_path):
            os.makedirs(file_path)

def main():
    ''' Main - Entry point '''
    try:
        # 获取当前工作目录
        current_dir = os.getcwd()

        # 构建路径
        bin_dir = os.path.normpath(os.path.join(current_dir, 'bin', 'v0.1', 'arm_app'))
        src_name = os.path.normpath(os.path.join(current_dir, '..', '..', 'MDK-ARM', 'arm_application.bin'))
        dst_name1 = os.path.normpath(os.path.join(current_dir, 'burn', 'bin'))
        dst_name2 = os.path.normpath(os.path.join(current_dir, 'boot', 'uart_boot_tool'))

        # 确保目标目录存在
        ensure_directory_exists(bin_dir)
        ensure_directory_exists(dst_name1)
        ensure_directory_exists(dst_name2)

        # 生成带时间戳的文件名
        image_name = "arm_app"
        time_stamp = datetime.datetime.now().strftime('%Y%m%d-%H%M%S')
        dst_name_time = os.path.join(bin_dir, f"{image_name}_{time_stamp}.bin")

        # 重命名为app.bin
        dst_name1_burn = os.path.join(dst_name1, "app.bin")
        dst_name2_boot = os.path.join(dst_name2, "app.bin")

        # 检查源文件是否存在
        if not os.path.exists(src_name):
            sys.exit(1)

        # 复制文件
        shutil.copy(src_name, dst_name_time)
        shutil.copy(src_name, dst_name1_burn)
        shutil.copy(src_name, dst_name2_boot)

    except Exception as e:
        sys.exit(1)

if __name__ == '__main__':
    main()
