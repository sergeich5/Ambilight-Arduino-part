#include <noise.h>
#include <bitswap.h>
#include <fastspi_types.h>
#include <pixelset.h>
#include <fastled_progmem.h>
#include <led_sysdefs.h>
#include <hsv2rgb.h>
#include <fastled_delay.h>
#include <colorpalettes.h>
#include <color.h>
#include <fastspi_ref.h>
#include <fastspi_bitbang.h>
#include <controller.h>
#include <fastled_config.h>
#include <colorutils.h>
#include <chipsets.h>
#include <pixeltypes.h>
#include <fastspi_dma.h>
#include <fastpin.h>
#include <fastspi_nop.h>
#include <platforms.h>
#include <lib8tion.h>
#include <cpp_compat.h>
#include <fastspi.h>
#include <FastLED.h>
#include <dmx.h>
#include <power_mgt.h>

#include <Thread.h> // https://github.com/ivanseidel/ArduinoThread
// if using RGBW Leds: https://github.com/sosiskus/FastLED-with-RGBW-leds
#define NUM_LEDS 20 // Change to the numbers of addressable LEDs
#define DATA_PIN 13 // Change to your Data Pin
#define CHIPSET WS2812B // Change your Chipset to WS2812B WS2812 TM1809 UCS1903B, and so forth

CRGB leds[NUM_LEDS];
byte buff[NUM_LEDS*3 + 1];
byte cur_led = 0;
byte old_colors[NUM_LEDS*3];
byte colors[NUM_LEDS*3];
byte old_brightness = 50;
byte brightness = 1;
Thread ledsPrinter = Thread();

void setup() {
  Serial.begin(115200);
  // Change your Chipset to WS2812B WS2812 TM1809 UCS1903B, and so forth
  FastLED.addLeds<CHIPSET, DATA_PIN, RGB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip ); //TypicalLEDStrip UncorrectedColor //.setTemperature(WarmFluorescent); //.setCorrection( 0xFFAFAF ); //.setCorrection( TypicalLEDStrip )
  FastLED.setBrightness(1);
  pinMode(DATA_PIN, OUTPUT);

  ledsPrinter.onRun(ledsPrint);
  ledsPrinter.setInterval(20);
}

void loop() {
  if (ledsPrinter.shouldRun()) {
    ledsPrinter.run();
  }
  
  while (Serial.available() > 0){
    if (Serial.read() == 255) {
      byte len = 0;
      len = Serial.readBytes(buff, NUM_LEDS*3 + 1);
      if (len==NUM_LEDS*3 + 1) {
        brightness = buff[0];
        for (int i = 1; i < sizeof(buff); i++) {
          colors[i] = buff[i];
        }
      }
    }
    else {
      //Serial.flush();
    }
  }
  //getData();
}
void getData() {
  for (int i = 0; i < NUM_LEDS + 2; i++) {
    while (!Serial.available());
    
    byte chr = Serial.read();
    
    if (chr == 0 && i != 0) {
      break;
    }
    else if (i == 1) {
      brightness = chr;
    }
    else if (i == NUM_LEDS + 1) {
      colors[i-2] = chr;
      break;
    }
    else {
      colors[i-2] = chr;
    }
  }
}
void ledsPrint() {
  if (old_brightness < brightness) {
    old_brightness++;
    FastLED.setBrightness(old_brightness);
  }
  if (old_brightness > brightness) {
    old_brightness = old_brightness - 1;
    FastLED.setBrightness(old_brightness);
  }
  
  byte d;
  for (int i = 0; i < sizeof(old_colors); i++) {
    d = ceil((colors[i] - old_colors[i]) / 20);
    old_colors[i] += d;
  }

  for (int i = 0; i < NUM_LEDS; i++) {
    byte r = old_colors[i*3 + 1];
    byte g = old_colors[i*3 + 2];
    byte b = old_colors[i*3 + 0];
    leds[i] = CRGB(r, g, b);
    //leds[i] = CRGB(colors[i*3 + 0], colors[i*3 + 1], colors[i*3 + 2]);
  }
  FastLED.show();
}