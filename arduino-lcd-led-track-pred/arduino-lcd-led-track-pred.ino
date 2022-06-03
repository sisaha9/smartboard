#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <FastLED.h>

#define LED_PIN 3 // LED Pin Number
#define NUM_LEDS 10 // Number of LEDs
#define LED_TYPE WS2811 // Type of LED
#define COLOR_ORDER BRG // Color ordering for LED
CRGB leds[NUM_LEDS];

LiquidCrystal_I2C lcd(0x27,20,4);  

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
  lcd.setCursor(0, 0);
  lcd.print("                    ");
  lcd.setCursor(0, 1);
  lcd.print("                    ");
  lcd.setCursor(0, 2);
  lcd.print("                    ");
  lcd.setCursor(0, 3);
  lcd.print("                    ");
}

void reset_leds() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(0, 0, 0);
  }
  FastLED.show();
}

void print_led(String letter)
{
  reset_leds();
  if(letter == "a"){
    leds[0] = CHSV(0, 0, 255);
    FastLED.show();
    delay(1000);
  }
  else if(letter == "b"){
    leds[1] = CHSV(0, 0, 255);
    FastLED.show();
    delay(1000);
  }
  else if(letter == "c"){
    leds[2] = CHSV(0, 0, 255);
    FastLED.show();
    delay(1000);
  }
  else if(letter == "d"){
    leds[3] = CHSV(0, 0, 255);
    FastLED.show();
    delay(1000);
  }
  else if(letter == "e"){
    leds[4] = CHSV(0, 0, 255);
    FastLED.show();
    delay(1000);
  }
  else if(letter == "f"){
    leds[5] = CHSV(0, 0, 255);
    FastLED.show();
    delay(1000);
  }
  else if(letter == "g"){
    leds[6] = CHSV(0, 0, 255);
    FastLED.show();
    delay(1000);
  }
  else if(letter == "h"){
    leds[7] = CHSV(0, 0, 255);
    FastLED.show();
    delay(1000);
  }
  else {
    reset_leds();
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) // Has Jetson said anything?
  {
    result = Serial.readStringUntil('\n'); // Read output from Jetson except for newline
    letter = result.substring(0, 1); // Get just the character from the serial
    building_sentence = building_sentence + letter; // Add new character to current sentence
    print_led(letter); // Glow LED based off letter
    Serial.println(letter); // Send the current character in the sentence to Jetson
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
  delay(2000);
}
