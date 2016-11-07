/*

  IN PROGRESS!!!

  RISD Programming Sound: Performance Systems
  Prof. Shawn Greenlee

  Teensy LC with SparkFun Multiplexer Breakout - 8 Channel (74HC4051)

  touchRead example with Multiplexer

  Code adapted from:
  1) Yann Seznec www.yannseznec.com
  2) pjrc (makers of Teensy)
  3) Mux_Analog_Input SparkFun Multiplexer Analog Input Example
  Jim Lindblom @ SparkFun Electronics
  August 15, 2016
  https://github.com/sparkfun/74HC4051_8-Channel_Mux_Breakout

  Hardware Hookup:
Mux Breakout ----------- Teensy
     S0 ------------------- 2
     S1 ------------------- 3
     S2 ------------------- 4
     Z -------------------- input pin 
    VCC ------------------- 3.3v
    GND ------------------- GND
    (VEE should be connected to GND)

*/

// pin definitions
const int selectPins[3] = {2, 3, 4}; // S0~2, S1~3, S2~4  // these could be wired to multiple multiplexer boards
const int zInput1 = 15; // Connect common (Z) to 15 (touch input), one input pin for 8 ctlin objects
const int zInput2 = 16; // Connect common (Z) to 16 (touch input), one input pin for 8 ctlin objects
const int zInput3 = 17; // Connect common (Z) to 17 (touch input), one input pin for 8 ctlin objects


// the MIDI channel number to send messages
const int channel = 1;

elapsedMillis msec = 0;

void setup() {
  // Serial.begin(38400); // for serial monitoring, troubleshooting
  // Set up the select pins as outputs:

  for (int i = 0; i < 3; i++)
  {
    pinMode(selectPins[i], OUTPUT);
    digitalWrite(selectPins[i], HIGH);
  }
  pinMode(zInput1, INPUT); // Set up Z as an input
  pinMode(zInput2, INPUT); // Set up Z as an input
  pinMode(zInput3, INPUT); // Set up Z as an input

}

void loop() {

  // speed limit

  if (msec >= 50) {
    msec = 0;

    // loop through all eight multiplexer pins.

    for (byte pin = 0; pin <= 7; pin++) {
      selectMuxPin(pin); // Select one at a time
      int inputValue1 = touchRead(15); // and read Z
      usbMIDI.sendControlChange(pin + 1, constrain(map(inputValue1 >> 3, 1000, 5000, 0, 127), 0, 127), 1);
    }

    for (byte pin = 0; pin <= 7; pin++) {
      selectMuxPin(pin); // Select one at a time
      int inputValue2 = touchRead(16); // and read Z
      usbMIDI.sendControlChange(pin + 9, constrain(map(inputValue2 >> 3, 1000, 5000, 0, 127), 0, 127), 1);
    }

    for (byte pin = 0; pin <= 7; pin++) {
      selectMuxPin(pin); // Select one at a time
      int inputValue3 = touchRead(17); // and read Z
      usbMIDI.sendControlChange(pin + 17, constrain(map(inputValue3 >> 3, 1000, 5000, 0, 127), 0, 127), 1);
    }

    while (usbMIDI.read()) {
      // ignore incoming messages
    }
  }
}



// The selectMuxPin function sets the S0, S1, and S2 pins
// accordingly, given a pin from 0-7.
void selectMuxPin(byte pin)
{
  for (int i = 0; i < 3; i++)
  {
    if (pin & (1 << i))
      digitalWrite(selectPins[i], HIGH);
    else
      digitalWrite(selectPins[i], LOW);
  }
}

