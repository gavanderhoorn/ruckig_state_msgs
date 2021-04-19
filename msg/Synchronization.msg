
# Auto-generated on 2021-04-19T20:38:36.514527 from:
#
#  ruckig/include/ruckig/input_parameter.hpp
#
# Any modifications will be lost upon regeneration.

# Enum-level Doxygen for Synchronization:
#
#  ""
#

# Phase synchronize the DoFs when possible, else fallback to "Time" strategy
int32 PHASE=0

# Always synchronize the DoFs to reach the target at the same time (Default)
int32 TIME=1

# Synchronize only when necessary (e.g. for non-zero target velocity or acceleration)
int32 TIME_IF_NECESSARY=2

# Calculate every DoF independently
int32 NONE=3

# data
int32 value
