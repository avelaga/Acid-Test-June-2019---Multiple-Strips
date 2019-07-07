#include <FastLED.h>

#define NUM_LEDS 150
#define PIN1 3
#define PIN2 4
#define PIN3 5
#define PIN4 6
#define NUM_STRIPS 2
float hue;
float inc[NUM_STRIPS];
float noisePos[NUM_STRIPS];
CRGB leds[NUM_STRIPS][NUM_LEDS];
float toAdd;

void setup() {
  LEDS.addLeds<WS2812, PIN1, RGB>(leds[0], NUM_LEDS);
  LEDS.addLeds<WS2812, PIN2, RGB>(leds[1], NUM_LEDS);
  //  LEDS.addLeds<WS2812, PIN3, RGB>(leds[2], NUM_LEDS);
  //  LEDS.addLeds<WS2812, PIN4, RGB>(leds[3], NUM_LEDS);
  for (int x = 0; x < NUM_STRIPS; x++) {
    inc[x] = 0;
  }
  LEDS.setBrightness(255);
  hue = 0;
}

// NOT ENOUGH MEMORY ON NANO FOR MORE THAN 2
void loop() {
  for (int strip = 0; strip < NUM_STRIPS; strip++) {
    toAdd = map(inoise8(noisePos), 0, 255, -2, 7);
    noisePos[strip] += .03; // how fast the variability changes
    inc[strip] += toAdd; // controls speed, make it randomize between range of 1 to 4
    hue = inc[strip];

    for (int i = 0; i < NUM_LEDS; i++) {
      leds[strip][i] = CHSV(hue, 255, 255);
      hue += 1.5; // incremenration of hues in the strip
    }
    //  delay(60);
  }
  FastLED.show();
}
