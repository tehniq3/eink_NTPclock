# eink_NTPclock
based on https://github.com/ZinggJM/GxEPD library

info about display: https://www.waveshare.com/2.9inch-e-paper-module.htm

// eink->ESP8266:
- SS(CS) = GPIO15->D8,
- SCL(SCK) = GPIO14->D5,
- SDA(DIN,MOSI) = GPIO13->D7,
- BUSY = GPIO16->D0,
- RST = GPIO5->D1,
- DC = GPIO4->D2
// https://randomnerdtutorials.com/esp8266-pinout-reference-gpios/



296x128, 2.9inch E-Ink Display Module, SPI Interface:
- Operating voltage: 3.3V/5V
- Interface: 3-wire SPI, 4-wire SPI
- Outline dimension: 89.5mm × 38mm
- Display size: 66.89mm × 29.05mm
- Dot pitch: 0.138 × 0.138
- Resolution: 296 × 128
- Display color: black, white
- Grey level: 2 
- Partial refresh time: 0.3s
- Full refresh time: 2s
- Refresh power: 26.4mW(typ.)
- Standby power: <0.017mW
- Viewing angle: >170°


