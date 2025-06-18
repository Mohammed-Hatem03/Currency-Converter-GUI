# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Currency_Converter_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Currency_Converter_autogen.dir\\ParseCache.txt"
  "Currency_Converter_autogen"
  )
endif()
