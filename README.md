
# Boebot Control Simplification Headers

## Contains headers for:

- BOEBOT wheel control within the normalised range of -1.0f to 1.0f
- LED control and initialisation
- 'common.h' header file for a variety of useful functions

**There will be more to come with time and requests**



## How Do I use it?

### Cloning the Repository

#### From the Terminal:
``` 
git clone https://github.com/Off1cial/BOEBOT.git
```
#### With the GUI:
- Download the repository as a .zip and extract it to a directory of your choice
### Windows & Most Configurations (Arduino IDE)

- Clone this repository to a directory of your choosing
- Open the folder/files with the Arduino IDE or Visual Studio Code with the appropriate plugins
- Go through the typical setup, ensuring you're using the correct COM ports for your Arduino
- All done
### Forbidden Linux Distros 

This is for Linux distributions on which you do not wish to use the Arduino IDE.

This setup can be used with terminal editors like Neovim/Vim, as well as Visual Studio Code

For other Linux distributions such as Ubuntu or Linux Mint, you can probably find working installations of the Arduino IDE online, otherwise you can attempt to use this guide, adjusting the installation commands to use your package manager instead of pacman.
#### Arch Linux & Derivatives without Arduino IDE

##### Install the Required Packages

```
sudo pacman -S arduino-cli arduino-language-server avr-gcc avr-libc avrdude clang
```
##### Verify the Installation
```
arduino-cli version
command -v arduino-cli
```
##### Initialise the Arduino CLI
###### Create the default configuration
```
arduino-cli config init
```
###### Download the board index
```
arduino-cli core update-index
```
###### Install the AVR board platform
```
arduino-cli core install arduino:avr
```
###### Verify the platform installation
```
arduino-cli core list
```
###### Connecting the Arduino
```
arduino-cli board list
```

Should output something similar to:

```text
/dev/ttyACM0 serial   Serial Port (USB) Arduino UNO arduino:avr:uno arduino:avr
```

###### Serial port permissions:

```
sudo usermod -aG uucp "$USER"
```

You must then log out of your session completely to apply the new permission

##### Installing Arduino Libraries

Arduino libraries do not come with the board platform and must be installed separately.

For the Servo library, required to control the boebot wheels:
```
arduino-cli lib install Servo
```
##### Creating a Project:

The Arduino CLI expects the sketch directory to contain the primary .ino file of the same name. For example:

```text
Bot/
└── Bot.ino
```

Create your directory via the terminal or GUI:
```
mkdir -p ~/dev/arduino
cd ~/dev/arduino
```

Clone the repository into this folder
```
git clone https://github.com/Off1cial/BOEBOT.git
```

You should then have the directory ~/dev/arduino/boebot/ , which contains .h, .hpp, .c, .cpp, .ino files etc..

##### Automating the workflow with Makefile

This repository contains a 'Makefile' that you can use to automate the process of building, flashing and running your sketches

The Makefile looks something like this:

```Makefile
BOARD  := arduino:avr:uno
PORT   ?= /dev/ttyACM0
CLI    := arduino-cli
SKETCH := $(CURDIR)
BUILD  := $(CURDIR)/build

.PHONY: all build upload flash monitor ports clean

all: build

build:
	$(CLI) compile --fqbn $(BOARD) \
		--build-path $(BUILD) $(SKETCH)

upload:
	$(CLI) upload -p $(PORT) \
		--fqbn $(BOARD) $(SKETCH)

flash: build upload

monitor:
	$(CLI) monitor -p $(PORT) \
		--config baudrate=115200

ports:
	$(CLI) board list

clean:
	rm -rf $(BUILD)
```

**NOTE: It is extremely important that you check the 'PORT' variable, as this can vary between systems, in order to check this you should run
```
arduino-cli board list
```

You may see something along the lines of '/dev/ttyACM0 or /dev/ttyUSB0', you should place that in the Makefile, on the line 

``` Makefile
PORT ?= /dev/ttyACM0
```

so that the 'ACM0' or 'USB0' aligns with what the Arduino CLI is seeing**

###### Using the Makefile

The Makefile comes with a set of commands that you can use in your terminal, within the project directory:


| Command      | Purpose                                                        |
| ------------ | -------------------------------------------------------------- |
| make         | Compile the sketch                                             |
| make build   | Compile the sketch                                             |
| make upload  | Uploads the sketch                                             |
| make flash   | Compiles & uploads the sketch                                  |
| make monitor | Opens the serial monitor at the baud specified in the Makefile |
| make ports   | List the detected boards and serial ports                      |
| make clean   | Delete the generated build files                               |
