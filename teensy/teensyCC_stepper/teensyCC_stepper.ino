// using Adafruit TB6612 Motor breakout board
// note from Adafruit:

// POWER PINS
// Vmotor - This is the voltage for the motors, not for the logic level. Keep this voltage between 4.5V and 13.5V. This power supply will get noisy so if you have a system with analog readings or RF other noise-sensitive parts, you may need to keep the power supplies seperate (or filtered!)
// Vcc - this is the voltage for the logic levels. Set to the voltage logic you'll be using on your microcontroller. E.g. for Arduinos, 5V is probably what you want. Can be 2.7V to 5.5V so good for 3V or 5V logic
// GND - This is the shared logic and motor ground. All grounds are connected

// SIGNAL PINS
// INA1, INA2 - these are the two inputs to the Motor A H-bridges
// PWMA - this is the PWM input for the Motor A H-bridges, if you dont need PWM control, connect this to logic high.
// INB1, INB2 - these are the two inputs to the Motor B H-bridges
// PWMB - this is the PWM input for the Motor B H-bridges, if you dont need PWM control, connect this to logic high.
// STBY - this is the standby pin for quickly disabling both motors, pulled up to Vcc thru a 10K resistor. Connect to ground to disable.

// MOTOR PINS
// Motor A - these are the two outputs for motor A, controlled by INA1, INA2 and PWMA
// Motor B - these are the two outputs for motor B, controlled by INB1, INB2 and PWMB

// Power supply to +/- input as alternative to Vmotor pin
// Vcc to 3v on Teensy (power bus on breadboard)
// GND to ground on Teensy (ground bus on breadboard)
// AIN2 to Digital 4 on Teensy
// AIN1 to Digital 5 on Teensy
// BIN1 to Digital 6 on Teensy
// BIN2 to Digital 7 on Teensy
// PWMA and PWMB to Vcc (Vcc row on breadboard)


#include <Stepper.h>

const int stepsPerRevolution = 513;  // steps per revolution for motor - see motor documentation 

// initialize the stepper library on pins 4 through 7:
Stepper myStepper(stepsPerRevolution, 4, 5, 6, 7);
const int channel = 1; // the MIDI channel number to send messages
elapsedMillis msec = 0;


void setup() {
  myStepper.setSpeed(40); // the speed at 40 rpm, see motor documentation for maximum considering voltage
  usbMIDI.setHandleControlChange(HandleCC);
}

void loop() {
  usbMIDI.read();
}


void HandleCC(byte channel, byte number, byte value) {
  if (msec >= 20) {
    msec = 0;
    if (number == 60 && value == 127) {
      // step one revolution  in one direction:
      myStepper.step(stepsPerRevolution);
    }
    if (number == 60 && value == 0) {
      // step one revolution in the other direction:
      myStepper.step(-stepsPerRevolution);
    }
  }
}

