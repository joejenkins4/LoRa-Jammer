#include <SPI.h>
#include <RadioLib.h>

// SX1278 has the following connections:
// 3.3V:      3.3V
// MISO:      19
// MOSI:      23
// SCK:       18
// NSS pin:   5
// DIO0 pin:  32
// RESET pin: 14                  
// DIO1 pin:  33
SX1276 radio = new Module(5,33,14,32); //WRONG NUMBERS IF BROKEN

uint8_t SF = 12;
float BW = 125;                                                                                   
float FR = 868.1;
uint8_t CR = 5;
int8_t PWR = 10;
uint16_t PREAMBLE = 6;

void setup() {
  Serial.begin(9600);

  Serial.print(F("[SX1278] Initializing ... "));
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
  radio.listen();
}

void loop() {
  int state = radio.scanChannel();
  //Serial.println(state);    
  if (state == RADIOLIB_PREAMBLE_DETECTED) {
    // LoRa preamble was detected
    radio.transmit("");
    radio.listen();
  }
  FR = FR + 0.2;
  if (FR > 868.6) {
    FR = 867.1;
  } 
  radio.setFrequency(FR);
}
