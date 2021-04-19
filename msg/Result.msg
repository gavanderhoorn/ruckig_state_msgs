
# Auto-generated on 2021-04-19T20:38:36.514527 from:
#
#  ruckig/include/ruckig/input_parameter.hpp
#
# Any modifications will be lost upon regeneration.

# Enum-level Doxygen for Result:
#
#  "Result type of the OTGs update function"
#

# The trajectory is calculated normally
int32 WORKING=0

# Trajectory has reached its final position
int32 FINISHED=1

# Unclassified error
int32 ERROR=-1

# Error in the input parameter
int32 ERROR_INVALID_INPUT=-100

# The trajectory duration exceed the numeral limits
int32 ERROR_TRAJECTORY_DURATION=-101

# Error during the extremel time calculation (Step 1)
int32 ERROR_EXECUTION_TIME_CALCULATION=-110

# Error during the synchronization calculation (Step 2)
int32 ERROR_SYNCHRONIZATION_CALCULATION=-111

# data
int32 value
