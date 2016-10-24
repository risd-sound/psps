// the MIDI channel number to send messages
const int channel = 1;

void setup() {
}


void loop()
{

  // sensor 1
  int a = touchRead(A9);
  int b = touchRead(A8);
  int c = ((a - b) * 127 / (a + b));
  int d = abs(c);
  usbMIDI.sendControlChange(1, d, channel);

  // sensor 2
  int e = touchRead(A4);
  int f = touchRead(A3);
  int g = ((e - f) * 127 / (e + f));
  int h = abs(g);
  usbMIDI.sendControlChange(2, h, channel);

  // sensor 3
  int i = touchRead(A2);
  int j = touchRead(A1);
  int k = ((i - j) * 127 / (i + j));
  int l = abs(k);
  usbMIDI.sendControlChange(3, l, channel);

  
  delay(100);


}






