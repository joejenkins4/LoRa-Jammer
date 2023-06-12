#include <SPI.h>
#include <RadioLib.h>

SX1276 radio = new Module(5,33,14,32);

uint8_t SF = 12;
float BW = 125;
float FR = 868.1;
uint8_t CR = 5;
int8_t PWR = 10;
uint16_t PREAMBLE = 6;

void setup() {
  Serial.begin(9600);

  Serial.print(F("[SX1278] Initializing constant jammer... "));
  int state = radio.begin(FR,BW,SF);
  radio.setCodingRate(CR);
  radio.setPreambleLength(PREAMBLE);
  radio.setOutputPower(PWR);
  if (state == RADIOLIB_ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.print(state);
    while(true);
  }
}

void loop() {
  radio.transmit("");
}
