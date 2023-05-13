# eink_NTPclock
based on https://github.com/ZinggJM/GxEPD library

my artile: https://nicuflorica.blogspot.com/2023/05/ceas-ntp-pe-afisaj-e-ink-de-29.html

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

![clock](https://blogger.googleusercontent.com/img/b/R29vZ2xl/AVvXsEj_pDQTesVZGvGNLALiFsD45U4zjP5oOCPKUkN2QrzHQtvOI9tD0JkwJIRYINIPZOqHAiyPPYiKOrY8ITVnaxOTezFss728iY0ZM-9ewCMRjVoaS1Lu-STTKU2vgnfDZDeKMyNNBqUQKpyUQeyO6I5e9Eq3TfCuzuyZ8eUAMk61PO1MOFkRyjddWCz2rQ/w200-h150/NTP_clock_eink_V2_1b_info.jpg)

![schematic](https://blogger.googleusercontent.com/img/b/R29vZ2xl/AVvXsEg6abTY_4yMitfW19afjoGDTavqp4buFCAC4_jNCAqhKK2_CeYPikFkODVbY3J6hZVI3F8lYVS15LzE6qGS-MP1xtphbj0p2CxRArHmb5xT6a180S1c5Lw_e3Xi7ShZK_p8xfy22TRTktAiV1zL_UDFTLpcc4Hn9jnm23bwyN-cNFf8NYF59z2uQ9BbQQ/w400-h146/NTP_clock_eink_sch_v1.png)
