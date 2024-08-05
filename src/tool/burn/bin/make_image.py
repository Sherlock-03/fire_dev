# -*- coding: latin-1 -*-

import os

# ��ȡ�ű�����Ŀ¼�ľ���·��
script_dir = os.path.dirname(os.path.abspath(__file__))

# ���ù���Ŀ¼Ϊ�ű�����Ŀ¼
os.chdir(script_dir)

# �ļ���������ļ���
boot_name = "boot.bin"
image_name = "app.bin"
output_name = "sys.bin"

# ����Ŀ��Ӳ���������С�� boot.bin �ķ����С�����ֽ�Ϊ��λ��
FLASH_SIZE = 131072  # 128KB
BOOT_SIZE = 32768  # 32KB

# ����ļ��Ƿ����
if not os.path.isfile(boot_name):
    print(f"Error: {boot_name} does not exist.")
    input("Press Enter to exit...")
    exit(1)

if not os.path.isfile(image_name):
    print(f"Error: {image_name} does not exist.")
    input("Press Enter to exit...")
    exit(1)

# ��ȡ�ļ���С
boot_size = os.path.getsize(boot_name)
image_size = os.path.getsize(image_name)

# ��� boot.bin ��С�Ƿ񳬹�����Ĵ�С
if boot_size > BOOT_SIZE:
    print("Error: boot image size is greater than the allocated boot size")
    input("Press Enter to exit...")
    exit(1)

# ���ϲ���Ĵ�С�Ƿ񳬹������С
if boot_size + (BOOT_SIZE - boot_size) + image_size > FLASH_SIZE:
    print("Error: combined image size is greater than the available flash size")
    input("Press Enter to exit...")
    exit(1)

# ���ļ�
with open(boot_name, "rb") as fB, open(image_name, "rb") as fI, open(output_name, "wb") as fO:
    # д�� boot.bin ����
    fO.write(fB.read())
    
    # ��������ֽ�����д��հ�����ʹ app.bin ��ʼλ�ö��뵽 32KB
    padding_size = BOOT_SIZE - boot_size
    fO.write(bytearray(padding_size))
    
    # д�� app.bin ����
    fO.write(fI.read())

print("sys.bin created successfully.")

