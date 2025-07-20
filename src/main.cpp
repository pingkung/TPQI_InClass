#include <Arduino.h>
#include <DHT.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define DHTPIN 4
#define DHTTYPE DHT11

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

DHT dht(DHTPIN, DHTTYPE);

void function_interrupt();

int counter = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(14, INPUT);
  attachInterrupt(14, function_interrupt, RISING);
  Serial.begin(115200);
  dht.begin();

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  Serial.printf("Temperature = %.2f\n", dht.readTemperature());
  Serial.printf("Counter = %d\n", counter);
  // Serial.print("Counter = ");
  // Serial.print(counter);
  // Serial.println();
  delay(2000);
}

void IRAM_ATTR function_interrupt(){
  counter++; // counter = counter + 1;
}
