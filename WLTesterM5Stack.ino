// WLTesterM5Stack bbd

#include <M5Stack.h>

#define SECONDS(s)    ((s) * 1000)
#define MINUTES(m)    SECONDS(m * 60)


const uint8_t WL_PIN = 35;  // 水分計センサ
float wlRate = 0.0;

void
WlInit(void) {
  pinMode(WL_PIN, INPUT);
}

float
GetWl(void)
{
  int v = analogRead(WL_PIN);
//Serial.printf("ML(%d):%8.3f\r\n", i, v);
  return ((4096.0 - v) / 4096.0) * 100.0;
}

void
PrintWl(void)
{
  static float minWl = 100.0;
  static float maxWl = 0.0;
  char buf[256];
  float wl = GetWl();

  minWl = (minWl < wl) ? minWl : wl;
  maxWl = (wl < maxWl) ? maxWl : wl;
  sprintf(buf, "WL:%.1f S:%.1f L:%.1f", wl, minWl, maxWl);
  M5.Lcd.println(buf);
  Serial.println(buf);
}

void
setup() {
  M5.begin(true, false, true, true);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextFont(4);
  M5.Lcd.printf("WLTesterM5Stack\n");
  Serial.begin(115200);
  Serial.println("WLTesterM5Stack");

  PrintWl();
}

void
loop() {
  PrintWl();
 
  delay(SECONDS(3));
}
