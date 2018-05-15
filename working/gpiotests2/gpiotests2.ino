void setup() {
  Serial.begin(9600);
}

void loop() {
  if(Serial.available()){
    int currentNumber = Serial.parseInt();
    Serial.println(currentNumber);
  }

}


