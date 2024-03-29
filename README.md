# Ratatouille-Whisker

## Bill of Materials

### Whisker Sensor

| Part                                                    | Description | Quantity |Cost    |Weight|Power Usage |
| ------------------------------------------------------- | ----------- | -------- |--------|------|------------|
| Adafruit Wide-Range Triple-axis Magnetometer - MLX90393 |[Link to product](https://www.adafruit.com/product/4022)| 1        |£10-£20 |1.5g  |3.3v        |
| Raspberry Pi Pico                                       |[Link to product](https://www.raspberrypi.com/products/raspberry-pi-pico/)| 1        |£4-£12  |4g    |1.8v-5.5v   |
| Filament?                                               |             |          |        |      |            |
| Screws/Bolts/Nuts?                                      |             |          |        |      |            |
| Silicone                                                |[Link to product](https://www.bestbuysilicone.com/)|          |        |      |            |
| Magnet                                                  |[Link to product]()             | 1        |        |      |            |
| Cables?                                                 |             |          |        |      |            |
| Demoulding Spray?                                       |             |          |        |      |            |
| Pipette/Containers/etc???                               |             |          |        |      |            |

Approx. Total Cost: 

### Test Setup

| Part                   | Description | Quantity |
| ---------------------- | ----------- | -------- |
| PC/SBC                 |             | 1        |
| Raspberry Pi Pico      |             | 1        |
| Screws/Bolts/Nuts?     |             |          |
| Cables?                |             |          |
| Lead screw/Linear rail |             |          |
| Extrusion              |             |          |

### Tools

## Software Setup

### General Information

Ratatouille-Whisker is powered by a Raspberry Pi Pico. The Pi Pico was chosen for its low cost and dual-core architecture. One core is responsible for receiving and processing data from the magnetometer through I2C, and the other is responsible for transmitting the results over UART to a computer for post-processing.

The Arduino IDE was used to develop the necessary firmware. The Arduino IDE is a convenient wrapper for the Raspberry Pi Pico SDK and enables rapid prototyping. Developing using the Raspberry Pi Pico SDK is also recommended by the Ratatouille-Whisker team but would require additional development time for library integration.

The [arduino-MLX90393](https://github.com/Ratatouille-Whiskers/arduino-MLX90393) library was forked and modified from Teddy Yapo's original library (see relevant [repo](https://github.com/tedyapo/arduino-MLX90393)). The library was modified to allow I2C addresses to be defined manually in the `begin()` function. The modification was necessary as the sensor boards the team was experimenting with featured I2C addresses that did not align with the respective documentation.

A Python script is also provided as a simple serial port listener (using the `pyserial` library) and logger.

### [Step-by-Step Guide](documentation/software-setup.md)

## Hardware Setup
## User Guide
## General Testing
## Troubleshooting Guide
## How to Contribute?
## Cite Ratatouille-Whisker
## License