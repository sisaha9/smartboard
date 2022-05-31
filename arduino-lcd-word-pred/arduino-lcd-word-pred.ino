#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);  

int current_idx = 0; // Current index to send to jetson
String sentence = "Bring me an apple"; // Sentence we will progressively send to Jetson
String result = ""; // Variable to store response from Jetson
int MAX_WIDTH = 20; // Maximum width of screen
String building_sentence = "";

void setup() {
  // put your setup code here, to run once:
  lcd.init(); // initialize LCD
  lcd.backlight(); // open the backlight
  Serial.begin(9600); // Baudrate to communicate with Jetson
}

void reset_lcd()
{
  lcd.setCursor(0, 0);
  lcd.print("                    ");
  lcd.setCursor(0, 1);
  lcd.print("                    ");
  lcd.setCursor(0, 2);
  lcd.print("                    ");
  lcd.setCursor(0, 3);
  lcd.print("                    ");
}


void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) // Has Jetson said anything?
  {
    reset_lcd();
    result = Serial.readStringUntil('\n'); // Read output from Jetson except for newline
    if (result != "ready") // If this is not the starting handshake
    {
      lcd.setCursor ( 0, 0 );            // go to the top left corner
      if (result.length() > MAX_WIDTH) // If the predictions are greater than the max width
      {
        lcd.print(result.substring(0, MAX_WIDTH)); // Print first MAX_WIDTH characters
        lcd.setCursor(0, 1); // Move to 2nd row
        lcd.print(result.substring(MAX_WIDTH, result.length())); // Print remaining characters
      }
      else
      {
        lcd.print(result); // Print all predictions on the first row
      }
      lcd.setCursor ( 0, 2 );            // go to the third row
      if (building_sentence.length() > MAX_WIDTH) // if the sentence is more than 20 characters
      {
        lcd.print(building_sentence.substring(0, MAX_WIDTH)); // print first 20 characters
        lcd.setCursor ( 0, 3 ); // go to the fourth row
        lcd.print(building_sentence.substring(MAX_WIDTH, building_sentence.length())); // Print the remaining characters
      }
      else
      {
        lcd.print(building_sentence); // print the whole sentence
      }
    }
    if (current_idx < sentence.length()) // As long as we have not reached end of sentence
    {
      building_sentence = building_sentence + sentence[current_idx]; // Add new character to current sentence
      Serial.println(sentence[current_idx]); // Send the current character in the sentence to Jetson
      current_idx++; // Increment index to send new character next time
    }
  }
  delay(2000);
}
