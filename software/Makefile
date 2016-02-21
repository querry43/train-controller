
FIRMWARE := nodemcu-master-9-modules-2016-01-18-03-30-44-float.bin

all:

status:

terminal:
	nodemcu-uploader terminal

upload:
	cd external/nodemcu-mcp4131 && nodemcu-uploader upload *.lua
	cd external/nodemcu-tools   && nodemcu-uploader upload *.lua
	cd external/nodemcu-tools/webserver && nodemcu-uploader upload *.lua
	nodemcu-uploader upload --restart *.lua

flash:
	esptool.py write_flash --verify 0x00000 $(FIRMWARE)

update-submodules:
	cd external/nodemcu-mcp4131 && git fetch && git reset --hard origin/master
	cd external/nodemcu-tools   && git fetch && git reset --hard origin/master
