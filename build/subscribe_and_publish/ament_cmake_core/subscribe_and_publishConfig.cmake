# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_subscribe_and_publish_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED subscribe_and_publish_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(subscribe_and_publish_FOUND FALSE)
  elseif(NOT subscribe_and_publish_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(subscribe_and_publish_FOUND FALSE)
  endif()
  return()
endif()
set(_subscribe_and_publish_CONFIG_INCLUDED TRUE)

# output package information
if(NOT subscribe_and_publish_FIND_QUIETLY)
  message(STATUS "Found subscribe_and_publish: 0.0.0 (${subscribe_and_publish_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'subscribe_and_publish' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${subscribe_and_publish_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(subscribe_and_publish_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${subscribe_and_publish_DIR}/${_extra}")
endforeach()
