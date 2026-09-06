#pragma once

#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "esphome/components/uart/uart.h"
#include "esphome/core/component.h"

#include <cstdint>
#include <string>
#include <vector>

namespace esphome {
namespace ld2460 {

class LD2460Component : public Component, public uart::UARTDevice {
 public:
  static const uint8_t MAX_TARGETS = 5;

  void setup() override;
  void loop() override;
  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::DATA; }

  // Hardware Command Triggers
  void set_reporting_state(bool enable);
  void set_installation_mode(uint8_t mode);
  void set_installation_params(float height_m, float angle_deg);
  void set_detection_range(float max_distance_m, float start_angle_deg, float end_angle_deg);
  void set_sensitivity(uint8_t sensitivity);
  void set_baud_rate(uint8_t baud_index);
  void restart_radar();
  void factory_reset();

  // (Retain existing setter methods for sensors, buffer sizes, intervals, etc.)
  void set_raw_text_sensor(text_sensor::TextSensor *raw_text_sensor) { this->raw_text_sensor_ = raw_text_sensor; }
  void set_summary_text_sensor(text_sensor::TextSensor *summary_text_sensor) { this->summary_text_sensor_ = summary_text_sensor; }
  void set_firmware_text_sensor(text_sensor::TextSensor *firmware_text_sensor) { this->firmware_text_sensor_ = firmware_text_sensor; }
  void set_installation_mode_text_sensor(text_sensor::TextSensor *installation_mode_text_sensor) { this->installation_mode_text_sensor_ = installation_mode_text_sensor; }
  void set_presence_binary_sensor(binary_sensor::BinarySensor *presence_binary_sensor) { this->presence_binary_sensor_ = presence_binary_sensor; }
  void set_target_count_sensor(sensor::Sensor *target_count_sensor) { this->target_count_sensor_ = target_count_sensor; }
  void set_byte_count_sensor(sensor::Sensor *byte_count_sensor) { this->byte_count_sensor_ = byte_count_sensor; }
  void set_target_x_sensor(uint8_t index, sensor::Sensor *target_x_sensor);
  void set_target_y_sensor(uint8_t index, sensor::Sensor *target_y_sensor);
  void set_target_distance_sensor(uint8_t index, sensor::Sensor *target_distance_sensor);
  void set_target_angle_sensor(uint8_t index, sensor::Sensor *target_angle_sensor);
  
 protected:
  struct TargetSensors {
    sensor::Sensor *x{nullptr};
    sensor::Sensor *y{nullptr};
    sensor::Sensor *distance{nullptr};
    sensor::Sensor *angle{nullptr};
  };

  struct Target {
    int16_t raw_x{0};
    int16_t raw_y{0};
    float x_m{0.0f};
    float y_m{0.0f};
    float distance_m{0.0f};
    float angle_deg{0.0f};
  };

  void send_query_mode_command_();
  void send_query_version_command_();
  
  // (Retain existing protected parsing methods and variables)
  void process_rx_buffer_();
  void process_report_frame_(const std::vector<uint8_t> &frame);
  void process_command_frame_(const std::vector<uint8_t> &frame);
  
  text_sensor::TextSensor *raw_text_sensor_{nullptr};
  text_sensor::TextSensor *summary_text_sensor_{nullptr};
  text_sensor::TextSensor *firmware_text_sensor_{nullptr};
  text_sensor::TextSensor *installation_mode_text_sensor_{nullptr};
  binary_sensor::BinarySensor *presence_binary_sensor_{nullptr};
  sensor::Sensor *target_count_sensor_{nullptr};
  sensor::Sensor *byte_count_sensor_{nullptr};
  TargetSensors target_sensors_[MAX_TARGETS]{};
  std::vector<uint8_t> rx_buffer_{};
  
  // Internal state variables omitted for brevity (retain from previous implementation)
};

}  // namespace ld2460
}  // namespace esphome
