#include <HX711_ADC.h>
#include <movingAvg.h>

HX711_ADC LoadCell(2, 3);
movingAvg mySensor(10);

#define ANETA8_OUT 5

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(ANETA8_OUT, OUTPUT);
  Serial.begin(57600);
  Serial.println("Wait...");
  LoadCell.begin(64);
  long stabilisingtime = 25; // tare preciscion can be improved by adding a few seconds of stabilising time
  LoadCell.start(stabilisingtime);
  LoadCell.setCalFactor(696.0); // user set calibration factor (float)
  mySensor.begin();
  Serial.println("Startup + tare is complete");
}

void loop() {
  LoadCell.update();
  int LoadCellRead = round(LoadCell.getData()*1000);
  mySensor.reading(LoadCellRead);
  
  if ((LoadCellRead-mySensor.getAvg())<-2000) {
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(ANETA8_OUT, LOW);
  } else {
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(ANETA8_OUT, HIGH);
  }
  
  Serial.print(LoadCellRead);
  Serial.print("\t");
  Serial.print(mySensor.getAvg());
  Serial.print("\t");
  Serial.println(LoadCellRead-mySensor.getAvg());
}