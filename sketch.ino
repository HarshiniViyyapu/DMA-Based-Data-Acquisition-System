HardwareTimer *MyTimer = new HardwareTimer(TIM1);

volatile bool sampleFlag = false;

uint16_t adcBuffer[10];
int bufferIndex = 0;

void timerCallback() {
  sampleFlag = true;
}

void setup() {
  Serial.begin(115200);

  MyTimer->setOverflow(10, HERTZ_FORMAT);
  MyTimer->attachInterrupt(timerCallback);
  MyTimer->resume();

  Serial.println("================================");
  Serial.println("DMA-Based Data Acquisition Demo");
  Serial.println("Sampling Rate: 10 Hz");
  Serial.println("Buffer Size: 10 Samples");
  Serial.println("================================");
}

void loop() {

  if (sampleFlag) {
    sampleFlag = false;

    adcBuffer[bufferIndex] = analogRead(A4);
    bufferIndex++;

    if (bufferIndex >= 10) {

      Serial.println();
      Serial.println("BUFFER FULL");

      for (int i = 0; i < 10; i++) {
        Serial.print("Sample ");
        Serial.print(i);
        Serial.print(" = ");
        Serial.println(adcBuffer[i]);
      }

      Serial.println("----------------------------");

      bufferIndex = 0;
    }
  }
}