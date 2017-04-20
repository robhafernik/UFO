# UFO Sculpture

Code that runs the UFO

## Background

In about 2008, I found a discarded valve cover in a field.  I suspect it had once held a high-pressure valve for a natural gas pipeline.  It was heavy (about fifteen pounds or seven kilos) and made of fairly high strength steel.  Around the edge, it had sixteen holes for bolts to hold it on (which is how I know it was for a high-pressure valve, those sixteen bolts could hold thousands of pounds of pressure) and a big hole in the middle, through which the original valve stem had protruded.  I took this artifact home, intending to find something to do with it.  As a bonus, my wife loves it when I find trash in a field and bring it home so I can convert it to "art" at some remote time.

After seven or eight years, I decided to act.  I cleaned up the valve cover, painted the front of it flat black with silver highlights and installed a bunch of addressable LED lights in it (see the photos).  The code in this project lights up the sculpture and gives it 
the "UFO Ambiance".  *Yes, calling it a "sculpture" is highly pretentious, but I don't know what else to call it.*

The sculpture now whiles away its days on a shelf in a curio cabinet in our dining room.  It turns out that it makes a nice, lively
nightlight and my wife does not hate it.

## Hardware

The UFO uses an Arduino microcontroller board and a series of 23 Neopixel individually addressable RGB LEDs, all of which can be 
picked up from Adafruit [Adafruit](https://www.adafruit.com).  Two types of Neopixels were used, the individual ones, printed on a
snap-off sheet [NeoPixel Sheet](https://www.adafruit.com/product/1558) and a seven-pixel board (used in the center of the sculpture)
called a [Neopixel Jewel](https://www.adafruit.com/product/2226).  The Arduino board is available from many supplieers.

It's wise to obey the advice in Adafruit's [Neopixel UberGuide](https://learn.adafruit.com/adafruit-neopixel-uberguide).  There are
nuances to hooking them up (such as putting a 470-Ohm resistor in series in the data line and a 1000 micro-Farad capacitor across the
power supply to the pixels) that are helpful if you want your pixels to have a long life.

The code only does one thing that is sohpisticated in a very small way: it gamma corrects the LEDs so that a gradual fade from zero
to one hundred percent brightness is a smooth, even transition.  The idea for this gamma correction (but not the code) came from an
[article in Hackaday](http://hackaday.com/2016/08/23/rgb-leds-how-to-master-gamma-and-hue-for-perfect-brightness/), which you can 
check out if you want to understand what I've done in more detail.  There is also a detailed Wikipedia entry on 
[gamma correction](https://en.wikipedia.org/wiki/Gamma_correction) that you may find helpful.

## License

This code, such as it is, is available under the [MIT license](http://opensource.org/licenses/MIT).
