// Demo the quad alphanumeric display LED backpack kit
// scrolls through every character, then scrolls Serial
// input onto the display

#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

// 0 DP N M L K J H G2 G1 F E D C B A
//
// FAAAAAB
// FH.J.KB
// F.HJK.B
// .G1.G2.
// E.LMN.C
// EL.M.NC
// EDDDDDC DP

Adafruit_AlphaNum4 alpha70 = Adafruit_AlphaNum4();
Adafruit_AlphaNum4 alpha71 = Adafruit_AlphaNum4();

void setup() {
  alpha70.begin(0x70);  // pass in the address
  alpha71.begin(0x71);  // pass in the address
  //alpha70.setBrightness(1);
  //alpha70.blinkRate(3);

  alpha70.writeDigitRaw(0, 0b1111111111111111); // 0 DP N M L K J H G2 G1 F E D C B A
  alpha70.writeDigitRaw(1, 0b1111111111111111); 
  alpha70.writeDigitRaw(2, 0b1111111111111111); 
  alpha70.writeDigitRaw(3, 0b1111111111111111); 
  alpha71.writeDigitRaw(0, 0b1111111111111111);
  alpha71.writeDigitRaw(1, 0b1111111111111111); 
  alpha71.writeDigitRaw(2, 0b1111111111111111); 
  alpha71.writeDigitRaw(3, 0b1111111111111111); 
  alpha70.writeDisplay();
  alpha71.writeDisplay();
  delay(1000);

  alpha70.clear();
  alpha71.clear();
  alpha70.writeDisplay();
  alpha71.writeDisplay();
}

char displaybuffer[8] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
String showMe = "FAR OUT IN THE UNCHARTED BACKWATERS OF THE UNFASHIONABLE END OF THE WESTERN SPIRAL ARM OF THE GALAXY LIES A SMALL UNREGARDED YELLOW SUN. ORBITING THIS AT A DISTANCE OF ROUGHLY NINETY-TWO MILLION MILES IS AN UTTERLY INSIGNIFICANT LITTLE BLUE GREEN PLANET WHOSE APE-DESCENDED LIFE FORMS ARE SO AMAZINGLY PRIMITIVE THAT THEY STILL THINK DIGITAL WATCHES ARE A PRETTY NEAT IDEA...     ";

void loop() {
  for (int i=0; i<showMe.length(); i++) {
  
    char c = showMe.charAt(i);
    if (! isprint(c)) return; // only printable!
  
    // scroll down display
    displaybuffer[0] = displaybuffer[1];
    displaybuffer[1] = displaybuffer[2];
    displaybuffer[2] = displaybuffer[3];
    displaybuffer[3] = displaybuffer[4];
    displaybuffer[4] = displaybuffer[5];
    displaybuffer[5] = displaybuffer[6];
    displaybuffer[6] = displaybuffer[7];
    displaybuffer[7] = c;
 
    // set every digit to the buffer
    alpha70.writeDigitAscii(0, displaybuffer[0]);
    alpha70.writeDigitAscii(1, displaybuffer[1]);
    alpha70.writeDigitAscii(2, displaybuffer[2]);
    alpha70.writeDigitAscii(3, displaybuffer[3]);
    alpha71.writeDigitAscii(0, displaybuffer[4]);
    alpha71.writeDigitAscii(1, displaybuffer[5]);
    alpha71.writeDigitAscii(2, displaybuffer[6]);
    alpha71.writeDigitAscii(3, displaybuffer[7]);
 
    // write it out!
    alpha70.writeDisplay();
    alpha71.writeDisplay();
    delay(175);
  } 
}