#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);  // 20x4 I2C LCD

// Pin Definitions
const int buttonPin = 3;             // Button connected to D3
const int buzzerPin = 2;             // Buzzer connected to D2
int buttonState = 0;                 // Current state of the button
int lastButtonState = LOW;           // Previous state of the button
int score = -1;                      // Score counter for button presses

// Original shape characters
byte first[] = { 0x00, 0x00, 0x03, 0x04, 0x08, 0x10, 0x10, 0x10 };
byte second[] = { 0x00, 0x00, 0x11, 0x0A, 0x04, 0x00, 0x00, 0x00 };
byte third[] = { 0x00, 0x00, 0x18, 0x04, 0x02, 0x09, 0x05, 0x01 };
byte fourth[] = { 0x08, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00 };
byte fifth[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x0A, 0x04 };
byte sixth[] = { 0x02, 0x04, 0x08, 0x10, 0x00, 0x00, 0x00, 0x00 };

// Pressed shape characters
byte pressedFirst[] = { 0x00, 0x00, 0x00, 0x03, 0x07, 0x0F, 0x0F, 0x0F };
byte pressedSecond[] = { 0x00, 0x00, 0x00, 0x11, 0x1B, 0x1F, 0x1F, 0x1F };
byte pressedThird[] = { 0x00, 0x00, 0x00, 0x18, 0x1C, 0x1E, 0x1E, 0x1E };
byte pressedFourth[] = { 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00 };
byte pressedFifth[] = { 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x0E, 0x04, 0x00 };
byte pressedSixth[] = { 0x1C, 0x18, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00 };

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  lcd.init();                        // Initialize the LCD
  lcd.backlight();

  // Load the original shape
  loadOriginalShape();
  displayShape();

  // Initial display setup
  lcd.setCursor(5, 1);
  lcd.print("PopPW");               // Start score at 0
}

void loadOriginalShape() {
  lcd.createChar(0, first);
  lcd.createChar(1, second);
  lcd.createChar(2, third);
  lcd.createChar(3, fourth);
  lcd.createChar(4, fifth);
  lcd.createChar(5, sixth);
}

void loadPressedShape() {
  lcd.createChar(0, pressedFirst);
  lcd.createChar(1, pressedSecond);
  lcd.createChar(2, pressedThird);
  lcd.createChar(3, pressedFourth);
  lcd.createChar(4, pressedFifth);
  lcd.createChar(5, pressedSixth);
}

void displayShape() {
  lcd.setCursor(12, 1);
  lcd.write(0);
  lcd.setCursor(13, 1);
  lcd.write(1);
  lcd.setCursor(14, 1);
  lcd.write(2);
  lcd.setCursor(12, 2);
  lcd.write(3);
  lcd.setCursor(13, 2);
  lcd.write(4);
  lcd.setCursor(14, 2);
  lcd.write(5);
}

void resetScore() {
  score = 0;
  lcd.setCursor(7, 2);
  lcd.print("   ");  // Clear previous score
  lcd.setCursor(7, 2);
  lcd.print(score);
}

void loop() {
  // Read the current state of the button
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH && lastButtonState == LOW) {
    // Button pressed, load and display the pressed shape
    loadOriginalShape();
    displayShape();

    // Increment score
    score++;
    lcd.setCursor(7, 2); // Position for score
    lcd.print(score);

    // Play pop sound
    tone(buzzerPin, 500, 200); // Tone at 100Hz for 200ms
  } else if (buttonState == LOW && lastButtonState == HIGH) {
    // Button released, revert to original shape
    loadPressedShape();
    displayShape();
  }

  // Update lastButtonState to the current state
  lastButtonState = buttonState;
}

