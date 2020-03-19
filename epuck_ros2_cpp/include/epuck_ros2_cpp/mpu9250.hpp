// Copyright 1996-2020 Cyberbotics Ltd.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef EPUCK_ROS2_CPP__MPU9250_HPP_
#define EPUCK_ROS2_CPP__MPU9250_WRAPPER_HPP_

#include "epuck_ros2_cpp/i2c_wrapper.hpp"

#include <inttypes.h>
#include <memory>

#include "geometry_msgs/msg/vector3.hpp"

class MPU9250 {
public:
  MPU9250(std::shared_ptr<I2CWrapper> i2c);
  void calibrate();
  void read();

  geometry_msgs::msg::Vector3 getAngularVelocity();
  geometry_msgs::msg::Vector3 getLinearAcceleration();

private:
  int read_register(char reg, char *data, int size);
  void read_raw(int16_t *rawAccelerometer, int16_t *rawGyroscope);

  char mBuffer[6];
  float mGyroscope[3];
  float mAccelerometer[3];
  int16_t mRawGyroscope[3];
  int16_t mRawAccelerometer[3];
  int16_t mOffsetGyroscope[3];
  int16_t mOffsetAccelerometer[3];
  int mAddress;

  std::shared_ptr<I2CWrapper> mI2c;
};

#endif  // EPUCK_ROS2_CPP__I2C_WRAPPER_HPP_