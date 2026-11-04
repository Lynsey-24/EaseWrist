#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED specs: 0.91 inch, commonly 128x32
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1

// The I2C address is usually 0x3C
Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET
);

// GSR Sensor Analog Input
const int GSR_PIN = A0;

int sensorValue = 0;

void setup() {
  Serial.begin(9600);

  // Initialize I2C：UNO SDA=A4，SCL=A5
  Wire.begin();

  // Initialize OLED
  if (!display.begin(
        SSD1306_SWITCHCAPVCC,
        0x3C
      )) {
    while (true) {
      // OLED Initialization failed
    }
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(2);
  display.setCursor(0, 8);
  display.print("0");
  display.display();
}

void loop() {
  // Read the raw GSR analog value：0~1023
  sensorValue = analogRead(GSR_PIN);

  // Serial port outputs pure numbers
  Serial.println(sensorValue);

  // OLED Show numbers only
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);

  // Center display according to the number of digits
  int16_t x1, y1;
  uint16_t textWidth, textHeight;

  char valueText[5];
  snprintf(valueText, sizeof(valueText),
           "%d", sensorValue);

  display.getTextBounds(
    valueText, 0, 0,
    &x1, &y1, &textWidth, &textHeight
  );

  int x = (SCREEN_WIDTH - textWidth) / 2;
  int y = (SCREEN_HEIGHT - textHeight) / 2;

  display.setCursor(x, y);
  display.print(valueText);
  display.display();

  // Updates every 500 milliseconds
  delay(500);
}
