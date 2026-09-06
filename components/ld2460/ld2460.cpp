#include "ld2460.h"
#include "esphome/core/log.h"

namespace esphome {
namespace ld2460 {

static const char *const TAG = "ld2460";

void LD2460Component::set_reporting_state(bool enable) {
  // 0x06: Open/Close reporting function
  uint8_t frame[12] = {0xFD, 0xFC, 0xFB, 0xFA, 0x06, 0x0C, 0x00, 
                       static_cast<uint8_t>(enable ? 0x01 : 0x00), 
                       0x04, 0x03, 0x02, 0x01};
  this->write_array(frame, sizeof(frame));
  this->flush();
}

void LD2460Component::set_installation_mode(uint8_t mode) {
  // 0x09: Set installation mode (01: Side, 02: Top)
  uint8_t frame[12] = {0xFD, 0xFC, 0xFB, 0xFA, 0x09, 0x0C, 0x00, mode, 0x04, 0x03, 0x02, 0x01};
  this->write_array(frame, sizeof(frame));
  this->flush();
}

void LD2460Component::set_installation_params(float height_m, float angle_deg) {
  // 0x07: Set installation height (m*100) and angle (°*100)
  uint8_t frame[15] = {0xFD, 0xFC, 0xFB, 0xFA, 0x07, 0x0F, 0x00};
  int16_t h_cm = static_cast<int16_t>(height_m * 100.0f);
  int16_t ang = static_cast<int16_t>(angle_deg * 100.0f);
  
  frame[7] = h_cm & 0xFF;
  frame[8] = (h_cm >> 8) & 0xFF;
  frame[9] = ang & 0xFF;
  frame[10] = (ang >> 8) & 0xFF;
  frame[11] = 0x04; frame[12] = 0x03; frame[13] = 0x02; frame[14] = 0x01;
  this->write_array(frame, sizeof(frame));
  this->flush();
}

void LD2460Component::set_detection_range(float max_distance_m, float start_angle_deg, float end_angle_deg) {
  // 0x11: Detection range setting (Distance*10, Start Angle*10, End Angle*10)
  uint8_t frame[16] = {0xFD, 0xFC, 0xFB, 0xFA, 0x11, 0x10, 0x00};
  uint8_t dist_units = static_cast<uint8_t>(max_distance_m * 10.0f);
  int16_t start_ang = static_cast<int16_t>(start_angle_deg * 10.0f);
  int16_t end_ang = static_cast<int16_t>(end_angle_deg * 10.0f);
  
  frame[7] = dist_units;
  frame[8] = start_ang & 0xFF;
  frame[9] = (start_ang >> 8) & 0xFF;
  frame[10] = end_ang & 0xFF;
  frame[11] = (end_ang >> 8) & 0xFF;
  frame[12] = 0x04; frame[13] = 0x03; frame[14] = 0x02; frame[15] = 0x01;
  this->write_array(frame, sizeof(frame));
  this->flush();
}

void LD2460Component::set_sensitivity(uint8_t sensitivity) {
  // 0x13: Sensitivity setting (01: High, 02: Medium, 03: Low)
  uint8_t frame[12] = {0xFD, 0xFC, 0xFB, 0xFA, 0x13, 0x0C, 0x00, sensitivity, 0x04, 0x03, 0x02, 0x01};
  this->write_array(frame, sizeof(frame));
  this->flush();
}

void LD2460Component::set_baud_rate(uint8_t baud_index) {
  // 0x0E: Set baud rate index
  uint8_t frame[12] = {0xFD, 0xFC, 0xFB, 0xFA, 0x0E, 0x0C, 0x00, baud_index, 0x04, 0x03, 0x02, 0x01};
  this->write_array(frame, sizeof(frame));
  this->flush();
}

void LD2460Component::restart_radar() {
  // 0x0D: Restart radar
  uint8_t frame[12] = {0xFD, 0xFC, 0xFB, 0xFA, 0x0D, 0x0C, 0x00, 0x01, 0x04, 0x03, 0x02, 0x01};
  this->write_array(frame, sizeof(frame));
  this->flush();
}

void LD2460Component::factory_reset() {
  // 0x10: Restore factory settings
  uint8_t frame[12] = {0xFD, 0xFC, 0xFB, 0xFA, 0x10, 0x0C, 0x00, 0x01, 0x04, 0x03, 0x02, 0x01};
  this->write_array(frame, sizeof(frame));
  this->flush();
}

}  // namespace ld2460
}  // namespace esphome
