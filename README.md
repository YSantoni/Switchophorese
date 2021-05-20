# Switchophorese
An open source Field Inversion Gel Electrophoresis module, programmable via touchscreen.
Connect this module between your classic lab power supply and your gel tray.

This open source laboratory equipment is based on :

- Arduino mega
- Tft 2.8 lcd touch screen shield
- Mosfet full h-bridge circuit

Specs : suitable for gel electrophoresis or field inversion electrophoresis

- 40v to 200v
- max 6.5 amps
- 20ns switching time

Programmable elements :

- pre-heating timer
- runtime timer
- first pulse duration
- last pulse duration
- ratio forward/backward pulse
- linear or exponential time ramp

Libraries used :

https://github.com/prenticedavid/MCUFRIEND_kbv

https://github.com/adafruit/Adafruit_TouchScreen

![102794269-6e10de80-43ab-11eb-8156-e7d295066625](https://user-images.githubusercontent.com/84445386/118828240-605d7780-b8bd-11eb-9069-ffc0e54f67ed.jpg)


![group](https://user-images.githubusercontent.com/84445386/118958045-568d5000-b961-11eb-83b9-2e7a44948cfc.png)

First screen : Welcome screen, touch anywhere to begin.

Second screen : Set the duration for the pre-heating timer "Init" and the runtime timer "Run". Select hour, minute, or second and set it with "+" and "-" square, when done touch                 "OK" to go to the next screen.

Third screen : Set the duration of the first and last forward pulse of the run (minimum steps of 10ms). Set the duration of the backward pulse as a ratio of the forward pulse.
                You can choose linear or exponential to have the desired evolution of pulse duration during the run.

Fourth screen : The recap screen with all the parameters you have entered, when ready press "Begin".

Fifth screen : The run screen
