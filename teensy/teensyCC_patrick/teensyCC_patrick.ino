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


  Hardware Hookup:
  Mux Breakout ----------- Teensy
     S0 ------------------- 2
     S1 ------------------- 3
     S2 ------------------- 4
     Z -------------------- input pins A0 and A1 (for two multiplexer boards)
    VCC ------------------- 3.3v
    GND ------------------- GND
    (VEE should be connected to GND)



*/

// pin definitions for multiplexer
const int selectPins[3] = {2, 3, 4}; // S0~2, S1~3, S2~4
const int zInput1 = A0; // Connect common (Z) to A0 (analog input)
const int zInput2 = A1; // Connect common (Z) to A1 (analog input)

// this section sets the analog pins, change where indicated (not used here)
int const numPins = 0; // change the numer to how many analog pins you will use
int currentVal[numPins];
int newVal[numPins];
int analogPins[] = {
  // list the numbers of each pin you will use seperated by a comma
};


// set digital pins for buttons and switches
int const numDigPinsCC = 16; // change the number to how many digital pins you will use
int currentDigcc[numDigPinsCC];
int digitalpincc[] = {
  5, 6, 7, 8, 9, 10, 11, 12, 16, 17, 18, 19, 20, 21, 22, 23,// list the numbers of each pin you will use seperated by a comma
};

int digInputcc[numDigPinsCC];






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
  
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(16, INPUT_PULLUP);
  pinMode(17, INPUT_PULLUP);
  pinMode(18, INPUT_PULLUP);
  pinMode(19, INPUT_PULLUP);
  pinMode(20, INPUT_PULLUP);
  pinMode(21, INPUT_PULLUP);
  pinMode(22, INPUT_PULLUP);
  pinMode(23, INPUT_PULLUP);




}

void loop() {

  // speed limit

  if (msec >= 50) {
    msec = 0;

    // Loop through all eight multiplexer pins for A0.  ctlin 1 - 8

    for (byte pin = 0; pin <= 7; pin++) {
      selectMuxPin(pin); // Select one at a time
      int inputValue1 = analogRead(A0); // and read Z
      usbMIDI.sendControlChange(pin + 1, inputValue1 >> 3, channel);
    }

    // Loop through all eight multiplexer pins for A1. ctlin 9 - 16

    for (byte pin = 0; pin <= 7; pin++) {
      selectMuxPin(pin); // Select one at a time
      int inputValue2 = analogRead(A1); // and read Z
      usbMIDI.sendControlChange(pin + 9, inputValue2 >> 3, channel);
    }
    
    // digital pins input sending CC messages beginning at ctlin 51 thru 67 for Pd

    for (int i = 0; i < numDigPinsCC; i++) {
      if (digitalRead(digitalpincc[i]) == 1 && currentDigcc[i] == 0) {
        usbMIDI.sendControlChange(i + 51, 0, channel);
        currentDigcc[i] = 1;
      }
      if (digitalRead(digitalpincc[i]) == 0  && currentDigcc[i] == 1) {
        usbMIDI.sendControlChange(i + 51, 127, channel);
        currentDigcc[i] = 0;
      }
    }

    // analog pins input sending CC messages beginning at ctlin 1 for Pd

    for (int i = 0; i < numPins; i++) {

      newVal[i] = analogRead(analogPins[i]);

      if (abs(newVal[i] - currentVal[i]) > 3) {
        usbMIDI.sendControlChange(i + 1, newVal[i] >> 3, channel);
        currentVal[i] = newVal[i];
      }
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

