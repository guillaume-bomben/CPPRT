# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\CPPRT_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\CPPRT_autogen.dir\\ParseCache.txt"
  "CPPRT_autogen"
  )
endif()
