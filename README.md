# Ratatouille-Whisker

## Bill of Materials

### Whisker Sensor

| Part                | Description                                                                                                                                                                  | Quantity | Cost    | Weight  | Power Usage |
| ------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | -------- | ------- | ------- | ----------- |
| 3-axis Magnetometer | [Adafruit Wide-Range Triple-axis Magnetometer - MLX90393](https://www.adafruit.com/product/4022)                                                                             | 1        | £10-£20 | 1.5g    | 3.3v        |
| Microcontroller     | [Raspberry Pi Pico](https://www.raspberrypi.com/products/raspberry-pi-pico/)                                                                                                 | 1        | £4-£12  | 4g      | 1.8v-5.5v   |
| 3D Printer Filament | [eSun PLA 1kg Spool](https://esun3dstore.com/collections/pla/products/esun-epla-lite-1-75mm-3d-filament-1kg)                                                                 | 1        | £ 18    | 1kg     | -           |
| Silicone            | [BBDINO Super Elastic Silicone](https://www.bestbuysilicone.com/collections/all-bbdino-product/products/bbdino-super-elastic-silicone-mold-making-rubber-platinum-trial-kit) | 1        | £ 28    | 3x 300g | -           |
| Magnet              | [1 Tube (10 disks) of 5mm x 2mm Magent](https://uk.rs-online.com/web/p/neodymium-magnets/2192248)                                                                            | 1        | £8      |         | -           |
| Demolding Agents    | [Demoulding Vaseline](https://en.pebeo.com/catalogue/vaseline-de-demoulage-gedeo)                                                                                            | 1        | £6      | 75ml    | -           |

Approx. Total Cost: 

### Test Setup

| Part                   | Description                                                                  | Quantity |
| ---------------------- | ---------------------------------------------------------------------------- | -------- |
| PC/SBC                 |                                                                              | 1        |
| Microcontroller        | [Raspberry Pi Pico](https://www.raspberrypi.com/products/raspberry-pi-pico/) | 1        |
| Screws/Bolts/Nuts?     |                                                                              |          |
| Cables?                |                                                                              |          |
| Lead screw/Linear rail |                                                                              |          |
| Extrusion              |                                                                              |          |

### Tools
<!-- Should tools be under BOM or as an independent section? -->

#### Required

- 3D Printer (0.4mm nozzel)
- Soldering iron
- Craft Knife (or equivalent)

#### Recommended

- Prusaslicer (2.7.0 or higher)
  - 3d printer slicer
- Deburring Tool

## Printing

- A couple of `3mf` project files can be imported into your slicing software (we recommend PrusaSlicer) for loading in all the part geometry required for printing a complete whisker assembly kit.
  - Other slicers have not been tested, but others could be used.
  - We provide all the settings for both the Prusa MK3S and Prusa Mini printers
    - Other printers have not been tested but could be used.
- Using a **0.4mm** nozzle is recommended
  - Smaller nozzles can also be used but would result in slower print times, and the quality of the parts when using these setups has not been tested
    - A smaller nozzle would allow for a better result when printing the whisker shafts
  - Nozzles larger than 0.4mm are not recommended due to a reduction in precision when print and could lead to a decrease in print quality and dimensional accuracy for fitting the parts together

**Note:** You may find that the fit of the `Whisker Base` is too tight in the casting jig (even with the small chamfers in the design aimed to reduce this), and it is therefore recommended to scrape each of the outer edges of the print with a knife (or deburring tool) to deburr the edges and prevent sticking, in addition to the use of mold release agent. **It is especially important for the areas of the `whisker base` that were on the print bed and in contact with the brim when printing**

### Slicer settings

**_If users already have their own tuned profiles for their own printers, then you can try those settings and use the guidance below for some additional advice for things that you must be aware of when printing_**

We found the default `quality` settings (for 0.4mm nozzles) worked for printing, with only needing to make two changes:

1. The `Whisker Shaft` should be printed with a **0.1mm** layer height.
2. Set `XY Compensation` (or your slicer's equivalent setting) to a starting value of `-0.1mm`.
   - This is to ensure the holes in the parts are printed with better dimensional accuracy when sliced, improving the fit of parts in each (e.g. Whisker Shaft into the whisker Socket)
   - The value of `-0.1mm` is just a recommended starting point when using Prusaslicer and may need tuning for your specific printer

We also used the default PLA settings used for the `Prusament PLA` filament profile

- We used this even for non-prusament PLAs with success

## [Software Setup](SoftwareSetup.md)
## Hardware Setup

### [Whisker build instructions](BuildInstructions.md) 
Included are easy to follow build instructions and a visual guide for the whisker setup.

## User Guide
## General Testing
## Troubleshooting Guide
## How to Contribute?
## Cite Ratatouille-Whisker
## License
