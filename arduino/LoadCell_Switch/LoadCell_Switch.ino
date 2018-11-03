#include <HX711_ADC.h>

HX711_ADC LoadCell(2, 3);

#define SAMPLES 4
#define ANETA8_OUT 4

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(ANETA8_OUT, OUTPUT);
  Serial.begin(9600);
  Serial.println("Wait...");
  LoadCell.begin(64);
  long stabilisingtime = 25; // tare preciscion can be improved by adding a few seconds of stabilising time
  LoadCell.start(stabilisingtime);
  LoadCell.setCalFactor(696.0); // user set calibration factor (float)
  Serial.println("Startup + tare is complete");
}

void loop() {
  //update() should be called at least as often as HX711 sample rate; >10Hz@10SPS, >80Hz@80SPS
  //longer delay in scetch will reduce effective sample rate (be carefull with delay() in loop)
  LoadCell.update();
  float i = LoadCell.getData();
  if (i<-20) {
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(ANETA8_OUT, LOW);
  } else {
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(ANETA8_OUT, HIGH);
  }
  Serial.println(i);
}
