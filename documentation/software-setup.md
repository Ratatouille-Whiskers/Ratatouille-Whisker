# Ratatouille-Whisker

## Software Setup

Back to  [README](../README.md#software-setup)

### Step 1: Arduino IDE Setup

Download the official Arduino IDE from [here](https://www.arduino.cc/en/software). Then, follow the installation instructions outlined [here](https://github.com/earlephilhower/arduino-pico) to add the Raspberry Pi Pico board to the boards manager.

Open `whisker_firmware.ino` under `software/whisker_firmware` using the Arduino IDE. Select Raspberry Pi Pico as the current board.

Compilation will fail as `MLX90393.h` does not exist.

### Step 2: Install the MLX90393 Library

Go to the library's repository ([here](https://github.com/Ratatouille-Whiskers/arduino-MLX90393)) and click on `Code > Download ZIP`. The library can be installed following the instructions listed [here](https://support.arduino.cc/hc/en-us/articles/5145457742236-Add-libraries-to-Arduino-IDE). Skip to the *Importing a .zip Library* and *Manual installation* sections.

### Step 3: Upload the Code

To upload the sketch, you will need to hold the BOOTSEL button down while plugging in the Raspberry Pi Pico to your computer. Then hit the upload button and the sketch should be transferred and start to run. After the first upload, this may not be necessary as the arduino-pico core has auto-reset support.

Back to  [README](../README.md#software-setup)    
