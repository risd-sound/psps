
/* code borrowed from Yann Seznec www.yannseznec.com
and pjrc - these sources are in public domain

remember to select MIDI as your USB Type in the Tools menu

*/


#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int val = 0;    // variable to store the servo position

// set analog pins

int const numPins = 0; //  set number of analog inputs to use
int currentVal[numPins];
int newVal[numPins];
int analogPins[] = {
  // set which analog pins to use
};


// set digital pins

int const numDigPinsCC = 0; // number of digital pins to send CC
int currentDigcc[numDigPinsCC];
int digitalpincc[] = {
  // which digital pins to use for sending CC
};
int digInputcc[numDigPinsCC];

// the MIDI channel number to send messages
const int channel = 1;

elapsedMillis msec = 0;


void setup() {

  myservo.attach(3);  // attaches the servo on pin 3 to the servo object
  usbMIDI.setHandleControlChange(HandleCC);


  // pinMode(0, INPUT_PULLUP);
  // pinMode(1, INPUT_PULLUP);
  // pinMode(2, INPUT_PULLUP);
  // pinMode(3, OUTPUT);
  // pinMode(4, INPUT_PULLUP);
  // pinMode(5, INPUT_PULLUP);
  // pinMode(6, INPUT_PULLUP);
  // pinMode(7, INPUT_PULLUP);
  // pinMode(8, INPUT_PULLUP);
  // pinMode(9, INPUT_PULLUP);
  // pinMode(10, INPUT_PULLUP);
  // pinMode(11, INPUT_PULLUP);
  // pinMode(12, INPUT_PULLUP);
  // pinMode(13, INPUT_PULLUP);
}

void loop() {
  if (msec >= 20) {
    msec = 0;

    // digital pins sending CC
    for (int i = 0; i < numDigPinsCC; i++) {
      if (digitalRead(digitalpincc[i]) == 1 && currentDigcc[i] == 0) {
        usbMIDI.sendControlChange(i + 50, 0, channel);
        currentDigcc[i] = 1;
      }
      if (digitalRead(digitalpincc[i]) == 0  && currentDigcc[i] == 1) {
        usbMIDI.sendControlChange(i + 50, 127, channel);
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

  usbMIDI.read();

  //  while (usbMIDI.read()) {
  //    // ignore incoming messages
  //  }
}

void HandleCC(byte channel, byte number, byte value) {

  if (number == 60) {
  val = value;
  val = map (val, 0, 127, 0, 179);
  myservo.write(val);
  delay(15);
  }
  
}





