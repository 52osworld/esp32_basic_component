#!/bin/bash
python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp32 --port /dev/ttyUSB0 --baud 1152000 read_flash 0x110000 0x100000 spiffs.bin
