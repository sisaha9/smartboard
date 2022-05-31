int current_idx = 0;
String sentence = "Bring me an apple";
String result = "";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0)
  {
    result = Serial.readStringUntil('\n');
    if (result != "ready")
    {
      Serial.println(result);
    }
    if (current_idx < sentence.length())
    {
      Serial.println(sentence[current_idx]);
      current_idx++; 
    }
  }
  delay(500);
}
