# Microcontroller Firmware

The firmware for the microcontroller (Espressif ESP-32 DevKitC WROOM-32D/E) is written using [Arduino IDE](https://www.arduino.cc/en/software). 

[arduino_gui_TouchDisplay](./Arduino/arduino_gui_TouchDisplay) contains the latest firmware version for the Ressource Guardian. The libraries required are documented in `requirements.txt`.

[windsensor_rev_p_vs_c](./Arduino/windsensor_rev_p_vs_c) is the code implementation for evaluating calibration methods of different wind speed sensors as described in our paper.

[DIY Guide: Assembling Resource Guardian](https://rw.e3d.rwth-aachen.de/en/wiki/assembling-ressourcenwaechter/)

## How to configure the sensors being used?

See the [Wiki page](https://rw.e3d.rwth-aachen.de/en/wiki/sensor-configurations/) for supported sensors.

All supported I2C sensors can be automatically detected. If the address of your I2C sensor differs from the default address, you can modify it in `pin_cfg.h`.

Other supported analog sensors can be manually configured in `module_cfg.h`. Details are also available on our [Wiki page](https://rw.e3d.rwth-aachen.de/en/wiki/sensor-configurations/).

## How to calibrate the sensors?

See the [Wiki page](https://rw.e3d.rwth-aachen.de/en/wiki/sensor-calibration/) for sensor calibration.