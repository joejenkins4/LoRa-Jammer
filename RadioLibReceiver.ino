#include <SPI.h>
#include <RadioLib.h>

RFM95 radio = new Module(5,33,14,32);

uint8_t SF = 12;
float BW = 125;
float FR = 868.1;
uint8_t CR = 5;
int8_t PWR = 10;
uint16_t PREAMBLE = 6;

void setup() {
  Serial.begin(9600);
  
  Serial.println(F("[RFM95] Initialising... "));
  int state = radio.begin(FR,BW,SF);
  if (state == RADIOLIB_ERR_NONE) {
    Serial.print(F("Success"));
  } else {
    Serial.print(F("Failed, code "));
    Serial.print(state);
    while (true);
  }
}

void loop() {

    String str;
    int state = radio.receive(str);

    if (state == RADIOLIB_ERR_NONE) {
      // packet was successfully received
      Serial.println(F("[SX1278] Received packet!"));

      // print data of the packet
      Serial.print(F("[SX1278] Data:\t\t"));
      Serial.println(str);

      // print RSSI (Received Signal Strength Indicator)
      Serial.print(F("[SX1278] RSSI:\t\t"));
      Serial.print(radio.getRSSI());
      Serial.println(F(" dBm"));

      // print SNR (Signal-to-Noise Ratio)
      Serial.print(F("[SX1278] SNR:\t\t"));
      Serial.print(radio.getSNR());
      Serial.println(F(" dB"));

      // print frequency error
      Serial.print(F("[SX1278] Frequency error:\t"));
      Serial.print(radio.getFrequencyError());
      Serial.println(F(" Hz"));

    } else if (state == RADIOLIB_ERR_CRC_MISMATCH) {
      // packet was received, but is malformed
      Serial.println(F("[SX1278] CRC error!"));

    } else if (state == RADIOLIB_ERR_RX_TIMEOUT){
      Serial.println(F("TIMEOUT!"));
    } else {
      // some other error occurred
      Serial.print(F("[SX1278] Failed, code "));
      Serial.println(state);

    }
}
