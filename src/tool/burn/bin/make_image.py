# -*- coding: latin-1 -*-

import os

# 获取脚本所在目录的绝对路径
script_dir = os.path.dirname(os.path.abspath(__file__))

# 设置工作目录为脚本所在目录
os.chdir(script_dir)

# 文件名和输出文件名
boot_name = "boot.bin"
image_name = "app.bin"
output_name = "sys.bin"

# 定义目标硬件的闪存大小和 boot.bin 的分配大小（以字节为单位）
FLASH_SIZE = 131072  # 128KB
BOOT_SIZE = 32768  # 32KB

# 检查文件是否存在
if not os.path.isfile(boot_name):
    print(f"Error: {boot_name} does not exist.")
    input("Press Enter to exit...")
    exit(1)

if not os.path.isfile(image_name):
    print(f"Error: {image_name} does not exist.")
    input("Press Enter to exit...")
    exit(1)

# 读取文件大小
boot_size = os.path.getsize(boot_name)
image_size = os.path.getsize(image_name)

# 检查 boot.bin 大小是否超过分配的大小
if boot_size > BOOT_SIZE:
    print("Error: boot image size is greater than the allocated boot size")
    input("Press Enter to exit...")
    exit(1)

# 检查合并后的大小是否超过闪存大小
if boot_size + (BOOT_SIZE - boot_size) + image_size > FLASH_SIZE:
    print("Error: combined image size is greater than the available flash size")
    input("Press Enter to exit...")
    exit(1)

# 打开文件
with open(boot_name, "rb") as fB, open(image_name, "rb") as fI, open(output_name, "wb") as fO:
    # 写入 boot.bin 内容
    fO.write(fB.read())
    
    # 计算填充字节数并写入空白区域，使 app.bin 起始位置对齐到 32KB
    padding_size = BOOT_SIZE - boot_size
    fO.write(bytearray(padding_size))
    
    # 写入 app.bin 内容
    fO.write(fI.read())

print("sys.bin created successfully.")

