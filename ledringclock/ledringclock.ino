#include <Adafruit_NeoPixel.h>
#define PIN 1
#define NUMPIXELS 12

int hours = 0;
int minutes = 0;
int seconds = 0;
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

  leds[ seconds / 5 ] = 1;
  leds[ minutes / 5 ] = 2;
  leds[ hours ] = 3;

  for ( int i = 0; i < 12; ++i ) {
    Serial.print(leds[ i ]);
    if (leds[ i ] == 3) {
        Serial.println("True 3");
      pixels.setPixelColor(i, pixels.Color(0, 150, 0));
    }
    else if (leds[ i ] == 2) {
      Serial.println("True 2");
      pixels.setPixelColor(i, pixels.Color(150, 0, 0));
    }
    else if (leds[ i ] == 1) {
      Serial.println("True 1");
      pixels.setPixelColor(i, pixels.Color(0, 0, 150));
    }
    else {
      Serial.println("False");
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    }
    pixels.show();
  }
  Serial.println("");
  pixels.show();
}

void loop() {
  currentMillis = millis();
  if (currentMillis - previousMillis >= 1) {
    previousMillis = currentMillis;
    tick();
    updateclock();
  }
}
