/*

  IN PROGRESS!!!!!

  RISD Programming Sound: Performance Systems
  Prof. Shawn Greenlee


  Teensy LC with SparkFun Multiplexer Breakout - 8 Channel (74HC4051)

  Analog Input Example

  Code adapted from:
  1) Yann Seznec http://www.yannseznec.com/works/teensy-usb-midi-controller-code/
  2) pjrc (makers of Teensy)
  3) Mux_Analog_Input SparkFun Multiplexer Analog Input Example
  Jim Lindblom @ SparkFun Electronics
  August 15, 2016
  https://github.com/sparkfun/74HC4051_8-Channel_Mux_Breakout

*/

// pin definitions
const int selectPins[3] = {2, 3, 4}; // S0~2, S1~3, S2~4
const int zInput1 = A0; // Connect common (Z) to A0 (analog input)
const int zInput2 = A1; // Connect common (Z) to A1 (analog input)
const int zInput3 = A2; // Connect common (Z) to A2 (analog input)
const int zInput4 = A3; // Connect common (Z) to A3 (analog input)

// the MIDI channel number to send messages
const int channel = 1;

elapsedMillis msec = 0;

void setup() {

  // Set up the select pins as outputs:
  for (int i = 0; i < 3; i++) {
    pinMode(selectPins[i], OUTPUT);
    digitalWrite(selectPins[i], HIGH);
  }
  pinMode(zInput1, INPUT); // Set up Z as an input
  pinMode(zInput2, INPUT); // Set up Z as an input
  pinMode(zInput3, INPUT); // Set up Z as an input
  pinMode(zInput4, INPUT); // Set up Z as an input
}

void loop() {

  // speed limit

  if (msec >= 50) {
    msec = 0;

    // Loop through all eight multiplexer pins for A0.

    for (byte pin = 0; pin <= 7; pin++) {
      selectMuxPin(pin); // Select one at a time
      int inputValue1 = analogRead(A0); // and read Z
      usbMIDI.sendControlChange(pin + 1, inputValue1 >> 3, channel);
    }

    // Loop through all eight multiplexer pins for A1.

    for (byte pin = 0; pin <= 7; pin++) {
      selectMuxPin(pin); // Select one at a time
      int inputValue2 = analogRead(A1); // and read Z
      usbMIDI.sendControlChange(pin + 9, inputValue2 >> 3, channel);
    }


    // Loop through all eight multiplexer pins for A2.

    for (byte pin = 0; pin <= 7; pin++) {
      selectMuxPin(pin); // Select one at a time
      int inputValue3 = analogRead(A2); // and read Z
      usbMIDI.sendControlChange(pin + 17, inputValue3 >> 3, channel);
    }

    // Loop through all eight multiplexer pins for A3.

    for (byte pin = 0; pin <= 7; pin++) {
      selectMuxPin(pin); // Select one at a time
      int inputValue4 = analogRead(A3); // and read Z
      usbMIDI.sendControlChange(pin + 25 , inputValue4 >> 3, channel);
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

