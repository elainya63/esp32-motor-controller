// bluetooth setup
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED)  || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please  run `make menuconfig` to and enable it
#endif


#if !defined(CONFIG_BT_SPP_ENABLED)
#error  Serial Bluetooth not available or not enabled. It is only available for the ESP32  chip.
#endif

// variables and shit
BluetoothSerial SerialBT;
String text = ""; // io buffer of some sort
enum BT { CTL_ON, CTL_OFF, UNDEFINED }; // input states, increase in future
int BT = CTL_OFF; // default state

// motor setup
int motor1Pin1 = 27; 
int motor1Pin2 = 26; 
int enable1Pin = 14; 
 
// PWM properties...
const int freq = 30000;
const int resolution = 8; // 8-bit resolution (0-255)
int dutyCycle = 200;

 
void setup() {
  // sets the pins as outputs:
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  
  // configure LEDC PWM directly on the pin (No channel or ledcSetup required)
  ledcAttach(enable1Pin, freq, resolution);
 
  Serial.begin(115200); // serial monitor

  SerialBT.begin("Motor Test"); // start bt (motor test is device name)
}
 
void loop() {
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  } // who knows lowkey

  if (SerialBT.available() > 0) {
    text = SerialBT.readStringUntil('\n'); 
    text.trim(); // only get the actual usable stuff

    if (text == "Motor On"){ BT = CTL_ON; }
    else if (text == "Motor Off"){ BT = CTL_OFF; }
    else { BT = UNDEFINED; } // input unrecognised

    switch (BT) { // match cases to outputs
      case 0 : // motor on
          Serial.println("Moving Forward");
          digitalWrite(motor1Pin1, LOW);
          digitalWrite(motor1Pin2, HIGH); 
          ledcWrite(enable1Pin, 255); // Ensure enable pin is fully high
        break;

      case 1 : // motor off
          Serial.println("Motor stopped");
          digitalWrite(motor1Pin1, LOW);
          digitalWrite(motor1Pin2, LOW);
          ledcWrite(enable1Pin, 0); // Turn off PWM output
        break;

      case 2 : // undefined
        Serial.println("undefined input");
        break;
    }
  }

  delay(20);
 
  // // Stop the DC motor
  // Serial.println("Motor stopped");
  // digitalWrite(motor1Pin1, LOW);
  // digitalWrite(motor1Pin2, LOW);
  // ledcWrite(enable1Pin, 0); // Turn off PWM output
  // delay(1000);
 
  // // Move DC motor backwards at maximum speed
  // Serial.println("Moving Backwards");
  // digitalWrite(motor1Pin1, HIGH);
  // digitalWrite(motor1Pin2, LOW); 
  // ledcWrite(enable1Pin, 255);
  // delay(2000);
 
  // // Stop the DC motor
  // Serial.println("Motor stopped");
  // digitalWrite(motor1Pin1, LOW);
  // digitalWrite(motor1Pin2, LOW);
  // ledcWrite(enable1Pin, 0);
  // delay(1000);
 
  // // Move DC motor forward with increasing speed
  // digitalWrite(motor1Pin1, HIGH);
  // digitalWrite(motor1Pin2, LOW);
  // while (dutyCycle <= 255){
  //   // Target the pin directly instead of a channel
  //   ledcWrite(enable1Pin, dutyCycle);   
  //   Serial.print("Forward with duty cycle: ");
  //   Serial.println(dutyCycle);
  //   dutyCycle = dutyCycle + 5;
  //   delay(500);
  // }
  // dutyCycle = 200;
}
