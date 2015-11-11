cmake_minimum_required (VERSION 2.6)
project (opensecurity)

set(OPENSECURITY_VERSION_MAJOR "0")
set(OPENSECURITY_VERSION_MINOR "0")
set(OPENSECURITY_VERSION_PATCH "0")
set(OPENSECURITY_VERSION "${OPENSECURITY_VERSION_MAJOR}.${OPENSECURITY_VERSION_MINOR}.${OPENSECURITY_VERSION_PATCH}")
set(OPENSECURITY_VERSION_DATE "2012.12.30")

# give OPENSECURITY 1 series a few more soversions
set(OPENSECURITY_SOVERSION "00")

set(CMAKE_INSTALL_PREFIX /usr/local)

# fetch all the local directories for generated code
get_filename_component(OPENSECURITY_LIB_DIR ./lib ABSOLUTE)
get_filename_component(OPENSECURITY_BIN_DIR ./bin ABSOLUTE)
get_filename_component(OPENSECURITY_INC_DIR ./include ABSOLUTE)
get_filename_component(OPENSECURITY_SRC_DIR ./src ABSOLUTE)
get_filename_component(OPENSECURITY_SHARE_DIR ./share ABSOLUTE)
get_filename_component(OPENSECURITY_BUILD_DIR ./build ABSOLUTE)
get_filename_component(OPENSECURITY_SCRIPTS_DIR ./scripts ABSOLUTE)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(CMAKE_CXX_FLAGS "-g -Wall")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall") # -fprofile-arcs -ftest-coverage")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall") # -fprofile-arcs -ftest-coverage")

set(EXECUTABLE_OUTPUT_PATH ${OPENSECURITY_BIN_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OPENSECURITY_LIB_DIR})

## set the cmake defaults for libraries and binaries
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OPENSECURITY_LIB_DIR} CACHE PATH 
  "Output directory for the dynamic libraries" )
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OPENSECURITY_BIN_DIR} CACHE PATH
  "Output directory for the binaries" )
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OPENSECURITY_LIB_DIR} CACHE PATH 
  "Output directory for the static libraries (archives)" )

########################################################
# Find Boost
########################################################
find_package(Boost COMPONENTS thread date_time iostreams program_options 
  filesystem system REQUIRED)

if(Boost_FOUND)
        include_directories(${Boost_INCLUDE_DIRS})
endif()

########################################################
# Find OpenCV
########################################################
find_package (OpenCV REQUIRED )

if (OpenCV_FOUND)
message("=======================")
message("OpenCV Found")
message("Directories:")
message("${OpenCV_INCLUDE_DIRS}")
include_directories(${OpenCV_INCLUDE_DIRS})
message("-----------------------")
endif (OpenCV_FOUND)

INSTALL(DIRECTORY ${OPENSECURITY_INC_DIR} DESTINATION ${CMAKE_INSTALL_PREFIX}
  FILES_MATCHING REGEX .*\\.h|.*\\.proto
)

#INSTALL(TARGETS ${} 
#  LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
#  PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
#)

install(DIRECTORY ${OPENSECURITY_LIB_DIR}/ 
  DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
  )

## let cmake know where the headers are
include_directories(${OPENSECURITY_INC_DIR})

## copy to opensecurity/include
file(GLOB_RECURSE INCLUDE_FILES RELATIVE ${OPENSECURITY_SRC_DIR} src/*.h)
foreach(I ${INCLUDE_FILES})
  configure_file(${OPENSECURITY_SRC_DIR}/${I} ${OPENSECURITY_INC_DIR}/opensecurity/${I} @ONLY)
endforeach()

add_subdirectory(src)
