<p align="center">
 <img src="http://content.arduino.cc/brand/arduino-color.svg" width="50%" />
</p>

# Ambilight-Arduino-part

This software part installs on your Arduino UNO and works with [Ambilight for MacOS](https://github.com/sergeich5/Ambilight-MacOS)

# Ambilight?

Ambilight (Ambient Lighting Technology) is a background lighting technology for televisions that was invented and patented by Philips Electronics.

<p align="center"><img src="http://app.shopsline.ru/img-pic/kf/Hf3e4eb92d8c64b29bbdbb7538dbdf9c6I/DIY-Ambilight-RGB-5050.jpg_q50.jpg" width="50%" /></p>

# Before use

## Install FastLED library in your Arduino IDE

If you don't have FastLED library installed in Arduino IDE

```Arduino IDE
Tools -> Manage Libraries -> FastLED -> install (worked with 3.3.2)
```

Add Library to the project

```Arduino IDE
Sketch -> Include library -> FastLED
```

### RGBW Leds

If you have RGBW (RGB+White) Leds use that library: <https://github.com/sosiskus/FastLED-with-RGBW-leds>

# Configuration

Configure `NUM_LEDS` (number of addressable leds)
Change `DATA_PIN` to that one you want to use.
You have to know your Chipset FastLED.addLeds(YOUR_CHIP_HERE, DATA_PIN, YOUR_RGB_ORDER_HERE)

# Connection scheme

Led strip uses much power so that's why it's impossible to user the same power Arduino uses. U need to connect another power supply (for exmaple, use one more usb cables (**without data connection!!!**))

<img src="https://github.com/sergeich5/Ambilight-Arduino-part/blob/master/Arduino%20scheme.jpg?raw=true" width="100%" />
