#!/bin/bash
if [ -z "$1" ]; then
	FILENAME="Pong_vita.vpk"
else
	FILENAME="$1"
fi

vita-elf-create output.elf output.velf
vita-make-fself output.velf eboot.bin
vita-mksfoex -s TITLE_ID="PONG01" "Pong (PS Vita)" param.sfo
vita-pack-vpk -s param.sfo -b eboot.bin $FILENAME
