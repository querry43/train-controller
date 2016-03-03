FIRMWARE := nodemcu-master-9-modules-2016-01-18-03-30-44-float.bin

all:

terminal:
	nodemcu-uploader terminal

upload:
	$(MAKE) -C external/nodemcu-mcp4131 upload
	$(MAKE) -C external/nodemcu-tools upload
	nodemcu-uploader upload --restart *.lua *.html *.js

flash:
	esptool.py write_flash --verify 0x00000 $(FIRMWARE)

update-submodules:
	cd external/nodemcu-mcp4131 && git fetch && git reset --hard origin/master
	cd external/nodemcu-tools   && git fetch && git reset --hard origin/master

.PHONY: all terminal upload flash update-submodules
