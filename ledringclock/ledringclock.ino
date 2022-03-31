#include <Adafruit_NeoPixel.h>
#define PIN 2
#define NUMPIXELS 12

int hours = 0;
int minutes = 0;
int seconds = 0;
int hoursled = 0;
int minutesled = 0;
int secondsled = 0;

unsigned long previousMillis = 0;
unsigned long currentMillis = 0;
int leds[ 12 ] ;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin();
  Serial.begin(9600);
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
  Serial.print(": ");
  Serial.println(seconds);
}

void updateclock() {
  for ( int i = 0; i < 12; ++i ) {
    leds[ i ] = 0;
  }

  pixels.clear(); // Set all pixel colors to 'off'
  secondsled = seconds / 5;
  minutesled = minutes / 5;
  hoursled = hours;

  pixels.setPixelColor(secondsled, pixels.Color(0, 150, 0));
  pixels.setPixelColor(minutesled, pixels.Color(150, 0, 0));
  pixels.setPixelColor(hoursled, pixels.Color(0, 0, 150));

  if (secondsled == minutesled) {
    pixels.setPixelColor(secondsled, pixels.Color(150, 150, 0));
  }
  if (secondsled == hoursled) {
    pixels.setPixelColor(secondsled, pixels.Color(0, 150, 150));
  }
  if (minutesled == hoursled) {
    pixels.setPixelColor(minutesled, pixels.Color(0, 150, 150));
  }
  if ((secondsled == minutesled) && (minutesled == hoursled)) {
    pixels.setPixelColor(secondsled, pixels.Color(150, 150, 150));
  }
  pixels.show();
}

void loop() {
  currentMillis = millis();
  if (currentMillis - previousMillis >= 1000) {
    previousMillis = currentMillis;
    tick();
    updateclock();
  }
}
