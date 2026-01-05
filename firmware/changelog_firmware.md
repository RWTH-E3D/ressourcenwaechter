## Change Log

### v1.2.2

03.04.2025

- Fix input mode of button's GPIO

### v1.2.1

04.02.2025

- Update: ESP32 firmware
    - Provide an option to control whether ASC for SCD30 should be enabled or not.

### v1.2.0

22.01.2025

- Update: ESP32 firmware
    - add calibration methods for wind speed sensors
    - add comments

### v1.1.0

27.11.2024

- Update: ESP32 firmware - calibration & fix some bugs

### v1.0.1

23.10.2024

- Hotfix: ESP32 firmware - add software debouncing to prevent the "touch" issue if using an usb charger with noisy power supply or false button presses

### v1.0.0

09.09.2024

Release version v1.0.0 for field study, contains UI for touch display and firmware for esp32. Removed (temporarily) desktop software as it is not planned to be used in the field study.

- New: support DS18B20 for radiant temperature
- Update: UI (display)
- Update: fine tuned default settings of all comfort models in the firmware
- Add: resources of artworks for UI
- Add: results of CFD for hardware design
- Fix: corrected PCB design (footprints)

### v0.2.1
21.06.2024
- New: support power sensor SCT013 (current version 100A / 0-50mA)
- Update: UI (display)
- Update: fix bug for analog sensors via ADC (10->12bit)

### v0.2.0
11.06.2024
- New: new UI (display)
- New: Feedbacksystem in Nextion Display
- Update: change MC from Arduino Nano to ESP32
- Update: optimized code for MC

### v0.1.6
28.06.2021
- Updated: support high dpi
    - tested on 2K monitor (text 100% - 200%)

### v0.1.5
27.06.2021
- Fixed some code errors
- Added:
    - Release version for windows user 
        - by using winpython environment and batch command
        - user can open the application by double-clicking batch file "\_\_RUN\_\_.bat"
        - no need to install python environment or other python packages

### v0.1.4
15.06.2021
- Updated: re-design GUI
- Added:
    - calculator for CLO value
    - setup assistant
    - quick start guide
- Optimized: also works on macOS (10.11 or higher)

### v0.1.3
05.06.2021
- Added: multi-language support (english/german/chinese)

### v0.1.2
03.06.2021
- Added: analysis window
- Updated: GUI
    - changed all fonts into Arial

### v0.1.1
25.05.2021
- Updated: optimized algorithm in Arduino
    - support static PMV model (ISO 7730) for thermal comfort index
        - default clo (clothing insulation) value = 0.7
        - default metabolic rate = 1.2 met (office work)
- Updated: Arduino GUI


### v0.1.0
24.05.2021
- Updated: optimized algorithm of all comfort index
    - support adaptive model (EN 16798-1 2019) and static PMV model (ISO 7730) for thermal comfort index
        - adaptive model:
            - support calculation of outdoor running mean temperature by using free API of openweathermap
        - PMV:
            - add clo (clothing insulation) value in setting window
            - default metabolic rate = 1.2 met (office work)
- Added: platform check to avoid win10toast lib doesn't work on macOS or other platform
- Added: current outdoor temperature and the "feels like" temperature in main window
