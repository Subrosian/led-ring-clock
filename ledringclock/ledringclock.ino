#include <Adafruit_NeoPixel.h>
#define PIN 2
#define NUMPIXELS 12

int hours = 1;
int minutes = 0;
int seconds = 0;
int hoursled = 0;
int minutesled = 0;
int secondsled = 0;
unsigned long previousMillis = 0;
unsigned long currentMillis = 0;
int leds[ 12 ] ;

String inputString = "";
bool stringComplete = false;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin();
  Serial.begin(9600);
  inputString.reserve(200);
}

void tick() {
  seconds = seconds + 1;
  if (seconds == 60) {
    seconds = 0;
    minutes = minutes + 1;
  }
  if (minutes == 60) {
    minutes = 0;
    hours = hours + 1;
  }
  if (hours == 13) {
    hours = 1;
  }
  Serial.print("Time is ");
  Serial.print(hours);
  Serial.print(":");
  Serial.print(minutes);
  Serial.print(":");
  Serial.println(seconds);
}

void updateclock() {
  for ( int i = 0; i < 12; ++i ) {
    leds[ i ] = 0;
  }

  pixels.clear();
  secondsled = seconds / 5;
  minutesled = minutes / 5;
  hoursled = hours;
  // H S M
  pixels.setPixelColor(secondsled, pixels.Color(0, 20, 0));
  pixels.setPixelColor(minutesled, pixels.Color(0, 0, 20));
  pixels.setPixelColor(hoursled, pixels.Color(20, 0, 0));

  if (secondsled == minutesled) {
    pixels.setPixelColor(secondsled, pixels.Color(0, 20, 20));
  }
  if (secondsled == hoursled) {
    pixels.setPixelColor(secondsled, pixels.Color(20, 20, 0));
  }
  if (minutesled == hoursled) {
    pixels.setPixelColor(minutesled, pixels.Color(20, 0, 20));
  }
  if ((secondsled == minutesled) && (minutesled == hoursled)) {
    pixels.setPixelColor(secondsled, pixels.Color(20, 20, 20));
  }
  pixels.show();
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    inputString += inChar;
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}

void loop() {
  currentMillis = millis();
  if (currentMillis - previousMillis >= 1000) {
    previousMillis = currentMillis;
    tick();
    updateclock();
  }
  if (stringComplete) {
    Serial.println(inputString);
    if (inputString.startsWith("set")) {
      hours = inputString.substring(4, 6).toInt();
      minutes = inputString.substring(7, 9).toInt();
      seconds = inputString.substring(10, 12).toInt();
      Serial.println("Time Set");
    }
    inputString = "";
    stringComplete = false;
  }
}
