
#ifndef RUCKIG_STATE_MSGS_INCLUDE_RUCKIG_STATE_MSGS_MESSAGE_UTILS_H_
#define RUCKIG_STATE_MSGS_INCLUDE_RUCKIG_STATE_MSGS_MESSAGE_UTILS_H_

// Copyright (c) 2021, G.A. vd. Hoorn
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

#include <array>
#include <type_traits>
#include <vector>

#include <ruckig_state_msgs/InternalState.h>


namespace {

template <typename SeqElemT, std::size_t ArrayNumElems>
std::vector<SeqElemT> toVector(const std::array<SeqElemT, ArrayNumElems>& arr)
{
  return {arr.begin(), arr.end()};
}

template <std::size_t ArrayNumElems>
std::vector<uint8_t> toVector(const std::array<bool, ArrayNumElems>& arr)
{
  return {arr.begin(), arr.end()};
}

template<typename EnumT>
constexpr auto toUnderlying(EnumT const& e) noexcept
{
  static_assert(std::is_enum_v<EnumT>, "EnumT not a class enum type");
  return static_cast<std::underlying_type_t<EnumT>>(e);
}

} // ~namespace


namespace ruckig_state_msgs {


template <typename RuckigResultT, typename RuckigT, typename RuckigInputT, typename RuckigOutputT>
void toRosMessage(
  RuckigResultT const& result,
  RuckigT const& otg,
  RuckigInputT const& rinput,
  RuckigOutputT const& routput,
  ruckig_state_msgs::InternalState& msg
)
{
  // caller is responsible for setting the header.stamp field

  // populate the rest of the fields
  msg.delta_time = otg.delta_time;

  msg.work_result.value = result;

  msg.active_control_interface.value = toUnderlying(rinput.control_interface);
  msg.active_synchronization.value = toUnderlying(rinput.synchronization);
  msg.active_duration_discretisation.value = toUnderlying(rinput.duration_discretization);

  msg.max_velocity = toVector(rinput.max_velocity);
  msg.max_acceleration = toVector(rinput.max_acceleration);
  msg.max_jerk = toVector(rinput.max_jerk);

  // list of bool are mapped to std::vector<uint8_t> to avoid std::vector<bool>
  // see http://wiki.ros.org/msg#Fields, section "Array Handling"
  msg.enabled_dofs = toVector(rinput.enabled);

  if (rinput.minimum_duration)
      msg.min_duration = *rinput.minimum_duration;
  if (rinput.min_velocity)
      msg.min_velocity = toVector(*rinput.min_velocity);
  if (rinput.min_acceleration)
      msg.min_acceleration = toVector(*rinput.min_acceleration);

  msg.current_position = toVector(rinput.current_position);
  msg.current_velocity = toVector(rinput.current_velocity);
  msg.current_acceleration = toVector(rinput.current_acceleration);

  msg.target_position = toVector(rinput.target_position);
  msg.target_velocity = toVector(rinput.target_velocity);
  msg.target_acceleration = toVector(rinput.target_acceleration);

  msg.new_calculation = routput.new_calculation;
  msg.current_time = routput.time;
  msg.calculation_duration = routput.calculation_duration;

  msg.new_position = toVector(routput.new_position);
  msg.new_velocity = toVector(routput.new_velocity);
  msg.new_acceleration = toVector(routput.new_acceleration);
}


template <typename RuckigResultT, typename RuckigT, typename RuckigInputT, typename RuckigOutputT>
ruckig_state_msgs::InternalState toRosMessage(
  RuckigResultT const& result,
  RuckigT const& otg,
  RuckigInputT const& rinput,
  RuckigOutputT const& routput
)
{
  ruckig_state_msgs::InternalState msg;
  toRosMessage(result, otg, rinput, routput, msg);
  return msg;
}


} // ~namespace ruckig_state_msgs


#endif // RUCKIG_STATE_MSGS_INCLUDE_RUCKIG_STATE_MSGS_MESSAGE_UTILS_H_
