/*
 * This is the code that runs the 23 neo pixels on the UFO Sculpture (see photos).
 * Written by Rob Hafernik, Spring, 2017.
 *
 * This code is release under the Creative Commons Attribution license.  
 * You may distribute, remix, tweak, and build upon your work, even commercially, as 
 * long as you credit me for the original creation.
 * See: https://creativecommons.org/licenses/by/4.0/
 * 
 * IMPORTANT: pay attention to the advice and restrictions in the Adafruit Neopixel Uberguide:
 * https://learn.adafruit.com/adafruit-neopixel-uberguide/
 * 
 * The Adafruit Neopixels used in this project can be found here:
 * https://www.adafruit.com/products/1558
 * 
 * See Adafruit NeoPixel library for more info about the code:
 * https://github.com/adafruit/Adafruit_NeoPixel
 */

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

/*
 * The UFO sculpture has 16 Neopixels in a big ring around a core of 7 Neopixels
 * (in the form of a Neopixel Jewel) in the center, for a total of 23 pixels.
 * See photos for more on the scupture itself.
 */

#define PIN                     6
#define PIX_IN_RING            23
#define PIX_IN_CIRCLE          16

#define FADE_VELOCITY         600
#define FADE_FAST_VELOCITY    100
#define SPIN_VELOCITY         100
#define SPARKLE_VELOCITY       10
#define CHASE_VELOCITY        100

// mode variable: 0 = slow, calm fades     1 = spin animations     2 = colorful mix     3 -= pixels chase in circle
int mode = 3;

// gamma table, brightness correction
// see:   http://hackaday.com/2016/08/23/rgb-leds-how-to-master-gamma-and-hue-for-perfect-brightness/
// Array "gam" holds 100 values of brightness from 0 to 100 percent, corrected for apparent brightness
// using a gamma value of 2.0

int gam[]   = { 0,  0,  0,  0,  1,  1,  1,  1,  2,  2,
                2,  3,  3,  4,  4,  5,  6,  7,  8,  9,
               10, 11, 12, 13, 14, 15, 17, 18, 19, 21,
               22, 24, 26, 27, 29, 31, 33, 34, 36, 38,
               40, 42, 44, 47, 49, 51, 53, 56, 58, 61,
               63, 66, 68, 71, 74, 77, 79, 82, 85, 88,
               91, 94, 98,101,104,107,111,114,117,121,
              124,128,132,135,139,143,147,151,155,159,
              163,167,171,175,179,184,188,193,197,201,
              206,211,215,220,225,230,235,239,244,250};
              // take it easy on yourself: write a little program to generate this list :)

// "strip" holds the data buffer for the Neopixels
Adafruit_NeoPixel strip = Adafruit_NeoPixel(23, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();

  // power on self test, flash all to white for three seconds
  for (short j = 0; j < PIX_IN_RING; ++j) { setPix (j, 99, 99, 99); }
  strip.show();
  delay (3000);

  // turn back off
  for (short j = 0; j < PIX_IN_RING; ++j) { setPix (j, 0, 0, 0); }
  strip.show();

  // initialize randome number generator
  randomSeed(analogRead(0));
}

// Main loop
void loop() {
  if(mode == 0) {

    // Slow, calm fades from one color to the next

    crossFadeAll (  0,   0,   0, 100,   0,   0, 100, FADE_VELOCITY);
    crossFadeAll (100,   0,   0,   0, 100,   0, 100, FADE_VELOCITY);
    crossFadeAll (  0, 100,   0,   0,   0, 100, 100, FADE_VELOCITY);
    crossFadeAll (  0,   0, 100, 100,   0,   0, 100, FADE_VELOCITY);
    
    crossFadeAll (100,   0,   0,   0, 100, 100, 100, FADE_VELOCITY);
    crossFadeAll (0,   100, 100, 100,   0, 100, 100, FADE_VELOCITY);
    crossFadeAll (100,   0, 100, 100, 100,   0, 100, FADE_VELOCITY);

    crossFadeAll (100, 100,   0, 100, 100, 100, 100, FADE_VELOCITY);
    crossFadeAll (100, 100, 100,   0,   0,   0, 100, FADE_VELOCITY);

  } else if (mode == 1) {

    // spinning animations
    
    crossFadeAll (  0,   0,  0,    0,   0,  80,  20, FADE_FAST_VELOCITY);
    spinner ( 128, 8,   0,   0,  80, SPIN_VELOCITY);
    crossFadeAll (  0,   0, 80,   60,  60,  60,  20, FADE_FAST_VELOCITY);
    spinner ( 128, 4,  80, 80,  80, SPIN_VELOCITY);
    crossFadeAll ( 60,  60, 60,  80,    0,   0,  20, FADE_FAST_VELOCITY);
    spinner ( 128, 4,  80,  0,  0, SPIN_VELOCITY);
    crossFadeAll ( 80,   0,  0,   0,    0,   0,  20, FADE_FAST_VELOCITY);
  } else if (mode == 2) {

    // random colorful mix
    
    for (short j = 0; j < PIX_IN_RING; ++j) { setPix (j, 0, 0, 0); }
    strip.show();
    delay(SPARKLE_VELOCITY);
    sparkle(400, 90);
    
  } else if (mode == 3) {

    // chasing pixels
    for (short j = 0; j < PIX_IN_RING; ++j) { setPix (j, 0, 0, 0); }
    strip.show();
    chase ( 60,0,0,  80,80,80,  128);
    
    for (short j = 0; j < PIX_IN_RING; ++j) { setPix (j, 0, 0, 0); }
    strip.show();
    chase ( 40,40,0,  0,0,80,  128);

    for (short j = 0; j < PIX_IN_RING; ++j) { setPix (j, 0, 0, 0); }
    strip.show();
    chase ( 80,80,80,  0,0,0,  128);

    for (short j = 0; j < PIX_IN_RING; ++j) { setPix (j, 0, 0, 0); }
    strip.show();
    chase ( 0,0,30,  0,0,90,  128);

  }

  // go from mode to mode
  mode = (mode + 1) % 4; 
}

/*
 * Lights chasing around in a circle
 */
void chase(short rback, short gback, short bback, short r, short g, short b, int reps) {
  short pos = 3;

  // calculate the faded following pixels
  short rdelta = ((r - rback)/3);
  short gdelta = ((g - gback)/3);
  short bdelta = ((b - bback)/3);

  short r1 = r - rdelta;
  short g1 = g - gdelta;
  short b1 = b - bdelta;

  short r2 = r - rdelta - rdelta;
  short g2 = g - gdelta - gdelta;
  short b2 = b - bdelta - rdelta;

  // set all to background
  for (short i = 0; i < PIX_IN_RING; ++i) {
        setPix(i, rback, gback, bback);
  }

  // set lead and following pixels
  for (short c = 0; c< reps; ++c) {
    pos = pos % PIX_IN_CIRCLE;
    
    short pm1 = pos - 1;
    if(pm1 < 0) { pm1 += PIX_IN_CIRCLE; }
    short pm2 = pos - 2;
    if(pm2 < 0) { pm2 += PIX_IN_CIRCLE; }
    short pm3 = pos - 3;
    if(pm3 < 0) { pm3 += PIX_IN_CIRCLE; }

    setPix(pos, r, g, b);
    setPix(pm1, r1, g1, b1);
    setPix(pm2, r2, g2, b2);
    setPix(pm3, rback, gback, bback);

    ++pos;

    strip.show();
    delay(CHASE_VELOCITY);
  }
}
 
/*
 * Random, colorful mix.  maxBrite is percent, not 0-255 absolute value
 */
void sparkle(int repeats, int maxBrite) {
  int spots[] = { 0, 7, 14, 5, 12, 3, 10, 1, 8, 15, 6, 13, 2, 11, 4, 9 };

  for(int j = 0; j < repeats; ++j) {
    // center five pixels get 
    int rr = random(maxBrite/2);
    int gg = random(maxBrite/2);
    int bb = random(maxBrite/2);

    setPix(PIX_IN_CIRCLE+6, rr, 0, 0);
    setPix(PIX_IN_CIRCLE+5, 0, gg, 0);
    setPix(PIX_IN_CIRCLE+4, 0, 0, bb);
    setPix(PIX_IN_CIRCLE+3, rr, 0, 0);
    setPix(PIX_IN_CIRCLE+2, 0, gg, 0);
    setPix(PIX_IN_CIRCLE+1, 0, 0, bb);
    setPix(PIX_IN_CIRCLE, rr, gg, bb);

    // outer circle of 16 gets random pixels 
    for(int i = 0; i < 16; ++i) {
  
      rr = random(maxBrite);
      gg = random(maxBrite);
      bb = random(maxBrite);

      setPix(spots[i], rr, gg, bb);
      strip.show();
      delay(SPARKLE_VELOCITY);
    }
  }
}

/*
 * Spin a pattern around n times, R, G, and B in PERCENT, not absolute values
 */
 void spinner (short n, short m, short r, short g, short b, int pause) {
  int pos = 0;

  for (short i = 0; i <= n; ++i) {
    // set every pixel in string to black
    for (short j = 0; j < strip.numPixels(); ++j) { setPix (j, 0, 0, 0); }

    // set center pixels to same rgb, but one pixel at a time
    setPix(PIX_IN_CIRCLE,   r, 0, 0);
    setPix(PIX_IN_CIRCLE+1, 0, g, 0);
    setPix(PIX_IN_CIRCLE+2, 0, 0, b);
    setPix(PIX_IN_CIRCLE+3, r, 0, 0);
    setPix(PIX_IN_CIRCLE+4, 0, g, 0);
    setPix(PIX_IN_CIRCLE+5, 0, 0, b);
    setPix(PIX_IN_CIRCLE+6, r, g, b);
    
    // draw spinners
    for (short j = pos; j < PIX_IN_CIRCLE; j += m) {
      setPix (j, r, g, b);
    }
    
    strip.show();
    delay(pause);
    pos = (pos + 1) % m;
  }
 }

/*
 * Fade in "steps" steps from the rgb1 values to the rgb2 values, with "pause" delay between steps
 * R, G, and B values are in PERCENT brightness (0-100%), NOT 0-255 absolute values
 */
void crossFadeAll(short r1, short g1, short b1, short r2, short g2, short b2, int steps, int pause) {
  short deltaR = (r2 - r1) / steps;
  short deltaG = (g2 - g1) / steps;
  short deltaB = (b2 - b1) / steps;
  short r = r1;
  short g = g1;
  short b = b1;

  // run through "steps" loops
  for(short i = 0; i < steps; ++i) {

    // set all pixels to rgb value
    for (short j = 0; j < PIX_IN_CIRCLE; ++j) { setPix (j, r, g, b); }

    // set center pixels to same rgb, but one pixel at a time
    setPix(PIX_IN_CIRCLE,   r, 0, 0);
    setPix(PIX_IN_CIRCLE+1, 0, g, 0);
    setPix(PIX_IN_CIRCLE+2, 0, 0, b);
    setPix(PIX_IN_CIRCLE+3, r, 0, 0);
    setPix(PIX_IN_CIRCLE+4, 0, g, 0);
    setPix(PIX_IN_CIRCLE+5, 0, 0, b);
    setPix(PIX_IN_CIRCLE+6, r, g, b);

    // advance to next value
    r += deltaR;
    g += deltaG;
    b += deltaB;

    // show and wait
    strip.show();
    delay(pause);
  }
}

/*
 * Set a pixel to a color-corrected percentage of brightness for r,g,b using
 * lookups into gamma table defined above.
 */
void setPix (int i, int r, int g, int b) {
  if(r < 0) { r = 0; }
  else if (r > 99) { r = 99; }
  if(g < 0) { g = 0; }
  else if (g > 99) { g = 99; }
  if(b < 0) { b = 0; }
  else if (b > 99) { b = 99; }

  strip.setPixelColor(i, strip.Color(gam[r], gam[g], gam[b]));
}

