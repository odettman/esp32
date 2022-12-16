#include <FastLED.h>

//  This is standalone - doesn't need WiFi
//    Since LEDs are modular, the ESP can be brought inside for updates
//      so no need for OTA.
//
//  Fade the LEDs in a red and green pattern (random for each pixel)
//  Add glitter randomly

FASTLED_USING_NAMESPACE

//#define PIN D2

#define DATA_PIN          25    // D6 for ESP8266, 25 for ESP32
#define LED_TYPE          WS2812
#define COLOR_ORDER       RGB   // This is different for string LEDs (RGB) vs panel LEDs (GRB) vs strip LEDs (GRB)
#define NUM_LEDS          58
#define MAX_BRIGHTNESS    128
#define FRAMES_PER_SECOND 15

CRGB leds[NUM_LEDS];

/* TODO

*/

DEFINE_GRADIENT_PALETTE (christmas_gp) {
  0, 255, 0, 0,    // red
  64, 0, 0, 0,     // black
  128, 0, 255, 0,  // green
  192, 0, 0, 0,    // black
  255, 255, 0, 0   // red
};

CRGBPalette16 christmas = christmas_gp;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.print("File Name: ");
  Serial.println(__FILE__);
  Serial.print("Loaded Date: ");
  Serial.println(__DATE__);
  Serial.print("Loaded Time: ");
  Serial.println(__TIME__);
  


  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  // set master brightness control
  FastLED.setBrightness(MAX_BRIGHTNESS);
}

int ndex = 0;
uint8_t hue = 0;

void loop() {
  hueloop();
  //orangeloop();
  //christmasloop();
  
}

void hueloop() {
  EVERY_N_MILLISECONDS(1000 / FRAMES_PER_SECOND) {  
    // #FF6600 Hex Color | RGB: 255, 102, 0 | BLAZE ORANGE, ORANGE RED -- This is KTM Orange (24,100,100 HSV 17,255,255 #11FFFF) 
    leds[ndex] = CHSV(hue,255,255);
    leds[NUM_LEDS - ndex] = CHSV(hue,255,255);
    FastLED.show();
    ndex++;

    if (ndex > (NUM_LEDS/2)) {
      ndex = 0;
      hue+=16;
    }
  }
  EVERY_N_MILLISECONDS(3) {
    fadeToBlackBy(leds, NUM_LEDS, 1);
  }
}

void orangeloop() {
  EVERY_N_MILLISECONDS(1000 / FRAMES_PER_SECOND) {  
    // #FF6600 Hex Color | RGB: 255, 102, 0 | BLAZE ORANGE, ORANGE RED -- This is KTM Orange (24,100,100 HSV 17,255,255 #11FFFF) 
    leds[ndex] = CHSV(17,255,255);
    leds[NUM_LEDS - ndex] = CRGB(255, 102, 0);
    FastLED.show();
    ndex++;

    if (ndex > (NUM_LEDS/2)) ndex = 0;
  }
  EVERY_N_MILLISECONDS(3) {
    fadeToBlackBy(leds, NUM_LEDS, 1);
  }
}

void christmasloop()
{
  EVERY_N_MILLISECONDS(1000 / FRAMES_PER_SECOND) {
    uint8_t rnd = random8(0, NUM_LEDS);
    Serial.println(rnd);
    leds[rnd] = ColorFromPalette(christmas, random8(), 255, LINEARBLEND);
  }
  EVERY_N_MILLISECONDS(7) {
    fadeToBlackBy(leds, NUM_LEDS, 1);
  }

  //addGlitter(2);
  // send the 'leds' array out to the actual LED strip
  FastLED.show();
}





void addGlitter( fract8 chanceOfGlitter)
{
  if ( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}
