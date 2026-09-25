#include <Keypad.h>
#include <Servo.h>

// ---------- Keypad ----------
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {6, 7, 8, 9};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// ---------- Servo ----------
Servo myServo;
const int servoPin = 10;

// ---------- Outputs ----------
const int buzzerPin = 11;
const int greenLED = 12;
const int redLED = 13;

// ---------- Password ----------
String password = "1234";
String input = "";

void setup() {
  myServo.attach(servoPin);
  myServo.write(0);

  pinMode(buzzerPin, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  Serial.begin(9600);

  Serial.println("Enter Password:");
}

void loop() {

  char key = keypad.getKey();

  if (key) {

    Serial.print(key);

    // # = submit password
    if (key == '#') {

      if (input == password) {

        Serial.println("\nAccess Granted!");

        digitalWrite(greenLED, HIGH);
        digitalWrite(redLED, LOW);
        digitalWrite(buzzerPin, LOW);

        myServo.write(90);

        delay(3000);

        myServo.write(0);
        digitalWrite(greenLED, LOW);

      } else {

        Serial.println("\nAccess Denied!");

        digitalWrite(redLED, HIGH);
        digitalWrite(greenLED, LOW);

        digitalWrite(buzzerPin, HIGH);
        delay(1000);
        digitalWrite(buzzerPin, LOW);

        digitalWrite(redLED, LOW);
      }

      input = "";
    }

    // * = clear password
    else if (key == '*') {
      input = "";
      Serial.println("\nPassword Cleared");
    }

    // Store entered number
    else {
      input += key;
    }
  }
}