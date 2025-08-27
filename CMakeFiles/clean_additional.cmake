# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\hz_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\hz_autogen.dir\\ParseCache.txt"
  "hz_autogen"
  )
endif()
