
const int motorEn = 22;
const int motorIn1 = 2;
const int motorIn2 = 4;  

void setup() {
  // these likely aren't the right pin names
  // replace these with whatever pins i decide to use on the esp
  pinMode(motorIn1, OUTPUT);
  pinMode(motorIn2, OUTPUT);
  pinMode(motorEn, OUTPUT);
  
  ledcAttach(motorEn, 5000, 8);
}

void loop() { // 'proof of concept' ahh, just untested filler essentially
  // forward
  digitalWrite(motorIn1, HIGH);
  digitalWrite(motorIn2, LOW);
  ledcWrite(motorEn, 200); // speed ranges from 0-255
  delay(2000);

  // stop
  digitalWrite(motorIn1, LOW);
  digitalWrite(motorIn2, LOW);
  delay(1000);
}
