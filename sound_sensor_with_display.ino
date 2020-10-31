#include <Adafruit_SSD1306.h>
#include <Wire.h>

const uint8_t sound_sensor_pin = A6;
const uint8_t SCREEN_WIDTH = 128, SCREEN_HEIGHT = 64, OLED_RESET = 4;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

uint16_t analogVal = 0;
uint8_t y_map=0, x_map=0;
uint8_t array_counter = 0;
uint8_t x_array[128], y_array[128]; //array to store x and y coordinate

void setup() {
  // put your setup code here, to run once:
  pinMode(sound_sensor_pin, INPUT);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
}

void loop() {
  // put your main code here, to run repeatedly:
  analogVal = analogRead(sound_sensor_pin);
  y_map = map(analogVal, 0, 1023, 0, 64);
  display.clearDisplay();
  if(array_counter > 127){
    array_counter = 0;
  }

  x_array[array_counter] = array_counter;
  y_array[array_counter] = y_map;

  for(int i=0; i<array_counter; i++){
    display.drawPixel(x_array[array_counter], y_array[array_counter], WHITE);
  }
  
  array_counter++;
  display.display();
  delay(500);
  
}
