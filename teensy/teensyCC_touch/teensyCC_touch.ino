// the MIDI channel number to send messages
const int channel = 1;

void setup() {
//  Serial.begin(38400);
}


void loop()
{
  int a = touchRead(A9);
  int b = touchRead(A8);
//  Serial.println ((a - b) * 127 / (a + b));
  int c = ((a - b) * 127 / (a + b));
  int d = abs(c);
  usbMIDI.sendControlChange(1, d, channel);
  delay(100);


}






