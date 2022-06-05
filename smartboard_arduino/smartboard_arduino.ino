#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <FastLED.h>

#define LED_PIN 3 // LED Pin Number
#define NUM_LEDS 39 // Number of LEDs
#define LED_TYPE WS2811 // Type of LED
#define COLOR_ORDER BRG // Color ordering for LED
CRGB leds[NUM_LEDS];

LiquidCrystal_I2C lcd(0x27,20,4);  // Object defining LCD address, width and height

String result = ""; // Variable to store response from Jetson and later predictions
String letter = ""; // Variable to store letter coming from Jetson
int MAX_WIDTH = 20; // Maximum width of screen
String building_sentence = ""; // Sentence we will progressively receive from Jetson

void setup() {
  // put your setup code here, to run once:
  lcd.init(); // initialize LCD
  lcd.backlight(); // open the backlight
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  Serial.begin(9600); // Baudrate to communicate with Jetson
}

void reset_lcd()
{
  lcd.setCursor(0, 0); // Go to first row
  lcd.print("                    "); // Add 20 spaces
  lcd.setCursor(0, 1); // Go to second row
  lcd.print("                    "); // Add 20 spaces
  lcd.setCursor(0, 2); // Go to 3rd row
  lcd.print("                    "); // Add 20 spaces
  lcd.setCursor(0, 3); // Go to 4th row
  lcd.print("                    "); // Add 20 spaces
}

void reset_leds() {
  for (int i = 0; i < NUM_LEDS; i++) { // Go through every LED
    leds[i] = CHSV(0, 0, 0); // Set it to no glow
  }
  FastLED.show(); // Show it's effect in real world
}

void print_led(String letter)
{
  reset_leds(); // Reset all the LEDS
  // Depending on which letter we get, set it's LED index to glow white
  if(letter == "a" || letter == "A"){
    leds[0] = CHSV(0, 0, 255);
    FastLED.show();
    delay(1000);
  }
  else if(letter == "b" || letter == "B"){
    leds[1] = CHSV(0, 0, 255);
    FastLED.show();
    delay(1000);
  }
  else if(letter == "c" || letter == "C"){
    leds[2] = CHSV(0, 0, 255);
    FastLED.show();
    delay(1000);
  }
  else if(letter == "d" || letter == "D"){
    leds[3] = CHSV(0, 0, 255);
    FastLED.show();
    delay(1000);
  }
  else if(letter == "e" || letter == "E"){
    leds[4] = CHSV(0, 0, 255);
    FastLED.show();
    delay(1000);
  }
  else if(letter == "f" || letter == "F"){
    leds[5] = CHSV(0, 0, 255);
    FastLED.show();
    delay(1000);
  }
  else if(letter == "g" || letter == "G"){
    leds[6] = CHSV(0, 0, 255);
    FastLED.show();
    delay(1000);
  }
  else if(letter == "h" || letter == "H"){
    leds[7] = CHSV(0, 0, 255);
    FastLED.show();
    delay(1000);
  }
  else if(letter == "i" || letter == "I"){
    leds[8] = CHSV(0, 0, 255);
    FastLED.show();
    delay(1000);
  }
  else if(letter == "j" || letter == "J"){
    leds[17] = CHSV(0, 0, 255);
    FastLED.show();
    delay(1000);
  }
  else if(letter == "k" || letter == "K"){
    leds[16] = CHSV(0, 0, 255);
    FastLED.show();
    delay(1000);
  }
  else if(letter == "l" || letter == "L"){
    leds[15] = CHSV(0, 0, 255);
    FastLED.show();
    delay(1000);
  }
  else if(letter == "m" || letter == "M"){
    leds[14] = CHSV(0, 0, 255);
    FastLED.show();
    delay(1000);
  }
  else if(letter == "n" || letter == "N"){
    leds[13] = CHSV(0, 0, 255);
    FastLED.show();
    delay(1000);
  }
  else if(letter == "o" || letter == "O"){
    leds[12] = CHSV(0, 0, 255);
    FastLED.show();
    delay(1000);
  }
  else if(letter == "p" || letter == "P"){
    leds[11] = CHSV(0, 0, 255);
    FastLED.show();
    delay(1000);
  }
  else if(letter == "q" || letter == "q"){
    leds[10] = CHSV(0, 0, 255);
    FastLED.show();
    delay(1000);
  }
  else if(letter == "r" || letter == "R"){
    leds[9] = CHSV(0, 0, 255);
    FastLED.show();
    delay(1000);
  }
  else if(letter == "s" || letter == "S"){
    leds[18] = CHSV(0, 0, 255);
    FastLED.show();
    delay(1000);
  }
  else if(letter == "t" || letter == "T"){
    leds[19] = CHSV(0, 0, 255);
    FastLED.show();
    delay(1000);
  }
  else if(letter == "u" || letter == "U"){
    leds[20] = CHSV(0, 0, 255);
    FastLED.show();
    delay(1000);
  }
  else if(letter == "v" || letter == "V"){
    leds[21] = CHSV(0, 0, 255);
    FastLED.show();
    delay(1000);
  }
  else if(letter == "w" || letter == "W"){
    leds[22] = CHSV(0, 0, 255);
    FastLED.show();
    delay(1000);
  }
  else if(letter == "x" || letter == "X"){
    leds[23] = CHSV(0, 0, 255);
    FastLED.show();
    delay(1000);
  }
  else if(letter == "y" || letter == "y"){
    leds[24] = CHSV(0, 0, 255);
    FastLED.show();
    delay(1000);
  }
  else if(letter == "z" || letter == "Z"){
    leds[25] = CHSV(0, 0, 255);
    FastLED.show();
    delay(1000);
  }
  else if (letter == " "){
    leds[38] = CHSV(0, 0, 255);
    FastLED.show();
    delay(1000);
  }
  // If the letter doesn't match an LED reset all of them
  else {
    reset_leds();
  }
  delay(500); // Let the LED glow for a bit more
  reset_leds(); // Reset the LEDs again
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) // Has Jetson said anything?
  {
    result = Serial.readStringUntil('\n'); // Read output from Jetson except for newline
    letter = result.substring(0, 1); // Get just the character from the serial
    building_sentence = building_sentence + letter; // Add new character to current sentence
    print_led(letter); // Glow LED based off letter
    result = result.substring(1, result.length()); // Get the predictions
    reset_lcd(); // Reset the LCD
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
  delay(1000); // Delay by 1 second to get Arduino ready
}
