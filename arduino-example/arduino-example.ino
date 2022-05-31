int current_idx = 0; // Current index to send to jetson
String sentence = "Bring me an apple"; // Sentence we will progressively send to Jetson
String result = ""; // Variable to store response from Jetson

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Baudrate to communicate with Jetson
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) // Has Jetson said anything?
  {
    result = Serial.readStringUntil('\n'); // Read output from Jetson except for newline
    if (result != "ready") // If this is not the starting handshake
    {
      Serial.println(result); // Send the result back to Jetson
    }
    if (current_idx < sentence.length()) // As long as we have not reached end of sentence
    {
      Serial.println(sentence[current_idx]); // Send the current character in the sentence
      current_idx++; // Increment index to send new character next time
    }
  }
  delay(500);
}
