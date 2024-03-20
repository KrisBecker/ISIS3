# CMake module for find_package(psmrts)
# Finds include directory and all applicable libraries
#
# Sets the following:
#   PSMRTS_INCLUDE_DIR
#   PSMRTS_LIBRARY

message( STATUS "PSMRTS_DIR: "  ${CMAKE_CURRENT_SOURCE_DIR} )

find_path(PSMRTS_INCLUDE_DIR
  NAME PsmrtsUtilities.hpp  NaifUtilities.hpp
  PATH_SUFFIXES psmrts
)

get_filename_component(PSMRTS_ROOT_INCLUDE_DIR "${PSMRTS_INCLUDE_DIR}" DIRECTORY)

message(STATUS "PSMRTS_ROOT_INCLUDE_DIR: " ${PSMRTS_ROOT_INCLUDE_DIR} )
message(STATUS "PSMRTS_INCLUDE_DIR:      " ${PSMRTS_INCLUDE_DIR} )
#message(STATUS "PSMRTS_LIBRARY:          " ${PSMRTS_LIBRARY} )
