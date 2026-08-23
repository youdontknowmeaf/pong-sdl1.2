#!/bin/bash
echo "========================================="
if [ -z "$1" ]; then
	3dsxtool build/*.elf Pong_3DS_Edition.3dsx
else
	3dsxtool build/*.elf $1
fi
file *.3dsx
echo "========================================="
echo "You can give it a custom name like that: ./make_3dsx_from_elf.sh custom_name.3dsx"
