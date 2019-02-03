#include <Arduino.h>
#include <SPI.h>
#include "octasonic.h"

#define CMD_GET_PROTOCOL_VERSION 0x01
#define CMD_SET_SENSOR_COUNT     0x02
#define CMD_GET_SENSOR_COUNT     0x03
#define CMD_GET_SENSOR_READING   0x04
#define CMD_SET_INTERVAL         0x05
#define CMD_TOGGLE_LED           0x06

Octasonic::Octasonic(unsigned int _chipSelect) {
  this->chipSelect = _chipSelect;

  pinMode(chipSelect, OUTPUT);
  digitalWrite(chipSelect, HIGH);

  // init SPI
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  SPI.begin();
}

unsigned int Octasonic::get_protocol_version() {
  return sendThenReceive(CMD_GET_PROTOCOL_VERSION << 4);
}

unsigned int Octasonic::set_sensor_count(unsigned int sensor_count) {
  return sendThenReceive(CMD_SET_SENSOR_COUNT << 4 | sensor_count);
}

unsigned int Octasonic::get_sensor_count() {
  return sendThenReceive(CMD_GET_SENSOR_COUNT << 4);
}

void Octasonic::toggle_led() {
  send(CMD_TOGGLE_LED << 4);
}

unsigned int Octasonic::get_sensor_reading(unsigned int index) {
  return sendThenReceive(CMD_GET_SENSOR_READING << 4 | index);
}

/* set the interval between polling sensors in intervals of 10 ms up to a maximum of 15 x 10 ms */
/*void Octasonic::set_poll_interval(unsigned int n) {
  send(CMD_SET_INTERVAL << 4 | n);
}
*/


unsigned int Octasonic::sendThenReceive(unsigned int n) {
  send(n);
  return send(0x00);
}

unsigned int Octasonic::send(unsigned int n) {
  // Serial.print("Octasonic::send() sends ");
  // Serial.println(n, HEX);
  digitalWrite(chipSelect, LOW);
  unsigned int response = SPI.transfer(n);
  digitalWrite(chipSelect, HIGH);
  // Serial.print("Octasonic::send() returns ");
  // Serial.println(response, HEX);
  return response;
}



