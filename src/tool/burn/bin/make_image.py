# -*- coding: latin-1 -*-

import os

# »ñÈ¡½Å±¾ËùÔÚÄ¿Â¼µÄ¾ø¶ÔÂ·¾¶
script_dir = os.path.dirname(os.path.abspath(__file__))

# ÉèÖÃ¹¤×÷Ä¿Â¼Îª½Å±¾ËùÔÚÄ¿Â¼
os.chdir(script_dir)

# ÎÄ¼þÃûºÍÊä³öÎÄ¼þÃû
boot_name = "boot.bin"
image_name = "app.bin"
output_name = "sys.bin"

# ¶¨ÒåÄ¿±êÓ²¼þµÄÉÁ´æ´óÐ¡ºÍ boot.bin µÄ·ÖÅä´óÐ¡£¨ÒÔ×Ö½ÚÎªµ¥Î»£©
FLASH_SIZE = 131072  # 128KB
BOOT_SIZE = 32768  # 32KB

# ¼ì²éÎÄ¼þÊÇ·ñ´æÔÚ
if not os.path.isfile(boot_name):
    print(f"Error: {boot_name} does not exist.")
    input("Press Enter to exit...")
    exit(1)

if not os.path.isfile(image_name):
    print(f"Error: {image_name} does not exist.")
    input("Press Enter to exit...")
    exit(1)

# ¶ÁÈ¡ÎÄ¼þ´óÐ¡
boot_size = os.path.getsize(boot_name)
image_size = os.path.getsize(image_name)

# ¼ì²é boot.bin ´óÐ¡ÊÇ·ñ³¬¹ý·ÖÅäµÄ´óÐ¡
if boot_size > BOOT_SIZE:
    print("Error: boot image size is greater than the allocated boot size")
    input("Press Enter to exit...")
    exit(1)

# ¼ì²éºÏ²¢ºóµÄ´óÐ¡ÊÇ·ñ³¬¹ýÉÁ´æ´óÐ¡
if boot_size + (BOOT_SIZE - boot_size) + image_size > FLASH_SIZE:
    print("Error: combined image size is greater than the available flash size")
    input("Press Enter to exit...")
    exit(1)

# ´ò¿ªÎÄ¼þ
with open(boot_name, "rb") as fB, open(image_name, "rb") as fI, open(output_name, "wb") as fO:
    # Ð´Èë boot.bin ÄÚÈÝ
    fO.write(fB.read())
    
    # ¼ÆËãÌî³ä×Ö½ÚÊý²¢Ð´Èë¿Õ°×ÇøÓò£¬Ê¹ app.bin ÆðÊ¼Î»ÖÃ¶ÔÆëµ½ 32KB
    padding_size = BOOT_SIZE - boot_size
    fO.write(bytearray(padding_size))
    
    # Ð´Èë app.bin ÄÚÈÝ
    fO.write(fI.read())

print("sys.bin created successfully.")

