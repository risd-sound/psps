// with Teensy just stick a wire into pins 0, 1, 3, 4, 15, 16, 17, 18, 19, 22, 23
// and they become capactive sensors, no other electronic components required

// adapted from http://little-scale.blogspot.com Sebastian Tomczak


void setup() {
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);  
}

void loop() {
 
  usbMIDI.sendControlChange(1, constrain(map(touchRead(15), 1000, 5000, 0, 127), 0, 127), 1);
  usbMIDI.sendControlChange(2, constrain(map(touchRead(16), 1000, 5000, 0, 127), 0, 127), 1);
  usbMIDI.setHandleControlChange(ccled) ;
  usbMIDI.read();
  delay (20);
}


void ccled (byte channel, byte number, byte value) {

  // D0

  if (number == 60 && value == 127) {
    digitalWrite(0, HIGH);
  } else if (number == 60 && value == 0) {
    digitalWrite(0, LOW);
  }

  //D1

  if (number == 61 && value == 127) {
    digitalWrite(1, HIGH);
  } else if (number == 61 && value == 0) {
    digitalWrite(1, LOW);
  }
}

