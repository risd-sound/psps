
// this section sets the analog pins, change where indicated

int const numPins = 12; // change the numer to how many analog pins you will use
int currentVal[numPins];
int newVal[numPins];
int analogPins[] = {
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11// list the numbers of each pin you will use seperated by a comma
};


// set digital pins

int const numDigPinsCC = 6; // change the number to how many digital pins you will use
int currentDigcc[numDigPinsCC];
int digitalpincc[] = {
  0, 1, 2, 3, 4, 5// list the numbers of each pin you will use seperated by a comma
};

int digInputcc[numDigPinsCC];

// the MIDI channel number to send messages
const int channel = 1; // don't change unless you know what you are doing 

elapsedMillis msec = 0; // don't change 

void setup() {

  // This tells the digital pins how to function, comment out any unused pins

  pinMode(0, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
//  pinMode(6, INPUT_PULLUP);
//  pinMode(7, INPUT_PULLUP);
//  pinMode(8, INPUT_PULLUP);
//  pinMode(9, INPUT_PULLUP);
//  pinMode(10, INPUT_PULLUP);
//  pinMode(11, INPUT_PULLUP);
//  pinMode(12, INPUT_PULLUP);
//  pinMode(13, INPUT_PULLUP);
}


/*

OK, if you've gotten this far you should be all set with your code.

Click the Verify button and Teensyduino should launch.

DO NOT CHANGE ANYTHING BELOW THIS COMMENT

UNLESS YOU KNOW WHAT YOU ARE DOING!


*/

void loop() {

  // establish a speed limit

  if (msec >= 20) {
    msec = 0;

    // digital pins input sending CC messages beginning at ctlin 51 for Pd

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
  }

  // MIDI Controllers can discard incoming MIDI messages.
  // http://forum.pjrc.com/threads/24179-Teensy-3-Ableton-Analog-CC-causes-midi-crash

  while (usbMIDI.read()) {
    // ignore incoming messages
  }
}







