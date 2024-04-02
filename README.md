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

- You can find a couple of `3mf` project files that you can import into your slicing software (we recommend PrusaSlicer) for loading in all the part geometry required to print a complete whisker assembly kit.
  - Other slicers can be used but have not been tested.
  - We provide all the settings for both the Prusa MK3S and Prusa Mini printers
    - Other printers can be used.
- Use of 0.4mm nozzles is recommended
  - Smaller nozzles could also be used but would result in slower print times, and the quality of the parts when using these setups has not been tested
  - nozzles larger than 0.4mm are not recommended due to a reduction in precision when print and could lead to a decrease in print quality

**Note:** You may find that the fit of the `Whisker Base` is too tight in the casting jig (even with the small chamfers in the design aimed to reduce this), and it is therefore recommended to scrape each of the outer edges of the print with a knife (or deburring tool) to debur the edges and prevent sticking. **It is especially important for the areas of the `whisker base` that were on the print bed and in contact with the brim when printing**

### Slicer settings

**_If users already have their own tuned profiles for their own printers, then you can try those settings and use the guidance below for some additional guidance for things that you must be aware of when printing_**

We found the default `quality` settings (for 0.4mm nozzles) worked for printing, with only needing to make two changes:

1. The `Whisker Shaft` should be printed with a **0.1mm** layer height.
2. Set `XY Compensation` (or your slicer's equivalent setting) to a starting value of `-0.1mm`.
   - This is to ensure the holes in the parts are printed with better dimensional accuracy when sliced, improving the fit of parts in each (e.g. Whisker Shaft into the whisker Socket)
   - The value of `-0.1mm` is just a recommended starting point when using Prusaslicer and may need tuning for your specific printer

We also used the default PLA settings used for the `Prusament PLA` filament profile

- We used this even for non-prusament PLAs with success

## [Software Setup](SoftwareSetup.md)
## Hardware Setup
## User Guide
## General Testing
## Troubleshooting Guide
## How to Contribute?
## Cite Ratatouille-Whisker
## License
## Progress Report Link Test
Continue on to [Progress Report](ProgressReport.md)
