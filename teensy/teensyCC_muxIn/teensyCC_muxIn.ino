/*

  IN PROGRESS!!!

  RISD Programming Sound: Performance Systems
  Prof. Shawn Greenlee

  Teensy LC with SparkFun Multiplexer Breakout - 8 Channel (74HC4051)

  Analog Input Example

  Code adapted from:
  1) Yann Seznec www.yannseznec.com
  2) pjrc (makers of Teensy)
  3) Mux_Analog_Input SparkFun Multiplexer Analog Input Example
  Jim Lindblom @ SparkFun Electronics
  August 15, 2016
  https://github.com/sparkfun/74HC4051_8-Channel_Mux_Breakout

*/

// pin definitions
const int selectPins[3] = {2, 3, 4}; // S0~2, S1~3, S2~4
const int zOutput = 5;
const int zInput = A0; // Connect common (Z) to A0 (analog input)

// the MIDI channel number to send messages
const int channel = 1;

elapsedMillis msec = 0;

void setup() {

  // Set up the select pins as outputs:
  for (int i = 0; i < 3; i++)
  {
    pinMode(selectPins[i], OUTPUT);
    digitalWrite(selectPins[i], HIGH);
  }
  pinMode(zInput, INPUT); // Set up Z as an input

}

void loop() {

  // speed limit

  if (msec >= 50) {
    msec = 0;

    // Loop through all eight multiplexer pins.

    for (byte pin = 0; pin <= 7; pin++) {
      selectMuxPin(pin); // Select one at a time
      int inputValue = analogRead(A0); // and read Z
      usbMIDI.sendControlChange(pin + 1, inputValue >> 3, channel);
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

