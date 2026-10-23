BOARD  := arduino:avr:uno
PORT   ?= /dev/ttyUSB0
CLI    := arduino-cli
SKETCH := $(CURDIR)

.PHONY: all build upload flash monitor ports clean

all: build

build:
#	$(CLI) compile --fqbn $(BOARD) --build-path build $(SKETCH)
	$(CLI) compile \
		--fqbn $(BOARD) \
		--build-path build \
		--build-property compiler.c.elf.extra_flags="-Wl,-u,vfprintf -lprintf_flt -lm" \
		$(SKETCH)

upload:
	$(CLI) upload -p $(PORT) --fqbn $(BOARD) --input-dir build $(SKETCH)

flash: build upload

monitor:
	$(CLI) monitor -p $(PORT) --config baudrate=9600

ports:
	$(CLI) board list

clean:
	rm -rf build
