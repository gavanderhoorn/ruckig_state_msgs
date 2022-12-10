# Copyright (c) 2021, G.A. vd. Hoorn
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.


# Ruckig's internal state as a ROS message.
#
# Fields (and sometimes comments) taken from:
#
#  - ruckig.h
#  - input_parameter.h
#  - output_parameter.h
#
# Internal Ruckig enums are encoded as Ruckig* fields with corresponding .msg
# files providing the enum values.


# a ROS header (facilitates synchronisation with other data streams)
std_msgs/Header header

# Time step between updates (cycle time) in [s]
float64 delta_time

# Result of the OTGs update function
Result work_result

# Active type of control (position, velocity, ..)
ControlInterface active_control_interface

# Active type of synchronization
Synchronization active_synchronization

# Active type of duration discretization
DurationDiscretization active_duration_discretisation

# Currently configured limits
float64[] max_velocity
float64[] max_acceleration
float64[] max_jerk

# Enabled DOFs (original member name: 'enabled')
bool[] enabled_dofs

# Optional: minimum duration of a trajectory [s]
float64 min_duration

# Optional: minimum velocity (same units as '*_velocity')
float64[] min_velocity

# Optional: minimum acceleration (same units as '*_acceleration')
float64[] min_acceleration

# State set as 'current'
float64[] current_position
float64[] current_velocity
float64[] current_acceleration

# State set as 'target'
float64[] target_position
float64[] target_velocity
float64[] target_acceleration

# Was a new trajectory calculation performed in the last cycle?
bool new_calculation

# Current time on trajectory (original member name: 'time') [s]
float64 current_time

# Computational duration of the last update call [us]
float64 calculation_duration

# Output of the OTG
float64[] new_position
float64[] new_velocity
float64[] new_acceleration
