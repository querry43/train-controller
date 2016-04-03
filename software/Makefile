export NODEMCU_UPLOADER ?= nodemcu-uploader
export ESPTOOL ?= esptool.py
export PORT ?= 
export SPEED ?= 

FIRMWARE := nodemcu-master-9-modules-2016-01-18-03-30-44-float.bin

all:

terminal:
	$(NODEMCU_UPLOADER) $(SPEED) $(PORT) terminal

restart:
	$(NODEMCU_UPLOADER) $(SPEED) $(PORT) node restart

htdocs/control.js.gz: htdocs/control.js
	gzip -c $< > $@

upload: htdocs/control.js.gz
	$(NODEMCU_UPLOADER) $(SPEED) $(PORT) upload --compile *.lua htdocs/*.lua
	$(NODEMCU_UPLOADER) $(SPEED) $(PORT) upload htdocs/*.html htdocs/*.gz htdocs/*.css htdocs/*.js

upload-all:
	$(MAKE) -C external/nodemcu-mcp4131 upload
	$(MAKE) -C external/nodemcu-tools upload
	$(MAKE) upload

flash:
	$(ESPTOOL) $(PORT) write_flash --verify 0x00000 $(FIRMWARE)

update-submodules:
	cd external/nodemcu-mcp4131 && git fetch && git reset --hard origin/master
	cd external/nodemcu-tools   && git fetch && git reset --hard origin/master

.PHONY: all terminal restart upload upload-all flash update-submodules
