// paired with US5881LUA hall effect sensor


// set analog input pins

int const numPins = 0; //  set number of analog inputs to use
int currentVal[numPins];
int newVal[numPins];
int analogPins[] = {
  // set which analog pins to use
};
//
//

// set digital input pins
int const numDigPinsCC = 4; // number of digital pins to send CC
int currentDigcc[numDigPinsCC];
int digitalpincc[] = {
5, 6, 7, 8, // which digital pins to use for sending CC
};
int digInputcc[numDigPinsCC];


// the MIDI channel number to send messages
const int channel = 1;

elapsedMillis msec = 0;

// Here set each what to do when each 0 or 127 MIDI values are received i.e. HIGH or LOW

void ccsolenoid (byte channel, byte number, byte value) {

  if (number == 60 && value == 127) {
    digitalWrite(0, HIGH);
  } else if (number == 60 && value == 0) {
    digitalWrite(0, LOW);
  }

  if (number == 61 && value == 127) {
    digitalWrite(1, HIGH);
  } else if (number == 61 && value == 0) {
    digitalWrite(1, LOW);
  }

  if (number == 62 && value == 127) {
    digitalWrite(2, HIGH);
  } else if (number == 62 && value == 0) {
    digitalWrite(2, LOW);
  }

  if (number == 63 && value == 127) {
    digitalWrite(3, HIGH);
  } else if (number == 63 && value == 0) {
    digitalWrite(3, LOW);
  }
}


void setup() {
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  //  pinMode(4, OUTPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  //  pinMode(9, INPUT_PULLUP);
  //  pinMode(10, INPUT_PULLUP);
  //  pinMode(11, INPUT_PULLUP);
  //  pinMode(12, INPUT_PULLUP);
  //  pinMode(13, INPUT_PULLUP);

}

// STOP DO NOT ALTER BELOW UNLESS YOU KNOW WHAT YOU ARE DOING!

void loop() {
  if (msec >= 20) {
    msec = 0;

    // digital pins sending CC

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

    // analog pins

        for (int i = 0; i < numPins; i++) {
    
          newVal[i] = analogRead(analogPins[i]);
    
          if (abs(newVal[i] - currentVal[i]) > 3) {
            usbMIDI.sendControlChange(i + 1, newVal[i] >> 3, channel);
            currentVal[i] = newVal[i];
          }
        }
  }
  usbMIDI.setHandleControlChange(ccsolenoid) ;
  usbMIDI.read();
}
















