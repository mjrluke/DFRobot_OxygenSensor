#include "sen0322.h"

namespace esphome {
namespace sen0322_sensor {

static const char *const TAG = "sen0322_sensor.sensor";

void Sen0322Sensor::setup() {
  ESP_LOGCONFIG(TAG, "Setting up sen0322...");
  if (!this->write_byte(SENSOR_MODE_REGISTER, SENSOR_MODE_AUTO)) {
    ESP_LOGW(TAG, "Error setting measurement mode.");
    this->mark_failed();
  };
}

void Sen0322Sensor::update() { this->read_data_(); }

void Sen0322Sensor::dump_config() {
  ESP_LOGCONFIG(TAG, "DF Robot Oxygen Sensor sen0322:");
  LOG_I2C_DEVICE(this);
  if (this->is_failed()) {
    ESP_LOGE(TAG, "Communication with sen0322 failed!");
  }
  LOG_UPDATE_INTERVAL(this);
}

void Sen0322Sensor::read_data_() {
  uint8_t result[2];
  this->read_bytes(SENSOR_AUTO_READ_REG, result, (uint8_t) 2);
  this->publish_state(((uint16_t) (result[0] << 8) + result[1]));
}

}  // namespace sen0322_sensor
}  // namespace esphome
