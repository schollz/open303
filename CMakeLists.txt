####################################################################################################
# CMakeLists file for Open303
####################################################################################################

####################################################################################################
# basic project config
cmake_minimum_required(VERSION 3.8)
set(project_name "Open303")
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/src/cmake_modules ${CMAKE_MODULE_PATH})

set(CMAKE_CXX_STANDARD 14)

####################################################################################################
# load modules
include(SuperColliderServerPlugin RESULT_VARIABLE server_plugin_found)
if(NOT server_plugin_found)
  message(FATAL_ERROR "Could not find server plugin functions module")
endif()

include(SuperColliderCompilerConfig RESULT_VARIABLE compiler_config_found)
if(NOT compiler_config_found)
  message(FATAL_ERROR "Could not find compiler config module")
endif()

# Windows - puts redistributable DLLs in install directory
include(InstallRequiredSystemLibraries)

sc_check_sc_path("${SC_PATH}")
message(STATUS "Found SuperCollider: ${SC_PATH}")
set(
  SC_PATH "${SC_PATH}" CACHE PATH
  "Path to SuperCollider source. Relative paths are treated as relative to this script" FORCE
)

include("${SC_PATH}/SCVersion.txt")
message(STATUS "Building plugins for SuperCollider version: ${SC_VERSION}")

# set project here to avoid SCVersion.txt clobbering our version info
project(${project_name})
sc_do_initial_compiler_config() # do after setting project so compiler ID is available

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT OR NOT CMAKE_INSTALL_PREFIX)
  message(WARNING "No install prefix provided, defaulting to $BUILD_DIR/install")
  set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "Install prefix" FORCE)
endif()

message(STATUS "Install directory set to: ${CMAKE_INSTALL_PREFIX}")

####################################################################################################
# options
option(SUPERNOVA "Build plugins for supernova" OFF)
option(SCSYNTH "Build plugins for scsynth" ON)
option(NATIVE "Optimize for native architecture" OFF)
option(STRICT "Use strict warning flags" OFF)
option(NOVA_SIMD "Build plugins with nova-simd support." ON)

####################################################################################################
# include libraries

if(NOVA_SIMD)
  add_definitions(-DNOVA_SIMD)
  include_directories(${SC_PATH}/external_libraries/nova-simd)
endif()

####################################################################################################
# Plugins
####################################################################################################

# Open303
set(
  Open303_cpp_files
  src/plugins/Open303/Open303.cpp
  src/plugins/Open303/Open303.hpp
  src/plugins/Open303/DSP/rosic_Open303.cpp
  src/plugins/Open303/DSP/rosic_Open303.h
  src/plugins/Open303/DSP/rosic_BlendOscillator.cpp
  src/plugins/Open303/DSP/rosic_BlendOscillator.h
  src/plugins/Open303/DSP/rosic_MipMappedWaveTable.cpp
  src/plugins/Open303/DSP/rosic_MipMappedWaveTable.h
  src/plugins/Open303/DSP/rosic_TeeBeeFilter.cpp
  src/plugins/Open303/DSP/rosic_TeeBeeFilter.h
  src/plugins/Open303/DSP/rosic_AnalogEnvelope.cpp
  src/plugins/Open303/DSP/rosic_AnalogEnvelope.h
  src/plugins/Open303/DSP/rosic_DecayEnvelope.cpp
  src/plugins/Open303/DSP/rosic_DecayEnvelope.h
  src/plugins/Open303/DSP/rosic_LeakyIntegrator.cpp
  src/plugins/Open303/DSP/rosic_LeakyIntegrator.h
  src/plugins/Open303/DSP/rosic_OnePoleFilter.cpp
  src/plugins/Open303/DSP/rosic_OnePoleFilter.h
  src/plugins/Open303/DSP/rosic_BiquadFilter.cpp
  src/plugins/Open303/DSP/rosic_BiquadFilter.h
  src/plugins/Open303/DSP/rosic_EllipticQuarterBandFilter.cpp
  src/plugins/Open303/DSP/rosic_EllipticQuarterBandFilter.h
  src/plugins/Open303/DSP/rosic_FourierTransformerRadix2.cpp
  src/plugins/Open303/DSP/rosic_FourierTransformerRadix2.h
  src/plugins/Open303/DSP/rosic_Complex.cpp
  src/plugins/Open303/DSP/rosic_Complex.h
  src/plugins/Open303/DSP/GlobalFunctions.cpp
  src/plugins/Open303/DSP/GlobalFunctions.h
  src/plugins/Open303/DSP/GlobalDefinitions.h
  src/plugins/Open303/DSP/rosic_RealFunctions.cpp
  src/plugins/Open303/DSP/rosic_RealFunctions.h
  src/plugins/Open303/DSP/rosic_NumberManipulations.cpp
  src/plugins/Open303/DSP/rosic_NumberManipulations.h
  src/plugins/Open303/DSP/rosic_FunctionTemplates.cpp
  src/plugins/Open303/DSP/rosic_FunctionTemplates.h
  src/plugins/Open303/DSP/fft4g.c
)

set(
  Open303_sc_files
  src/plugins/Open303/Open303.sc
)

set(
  Open303_schelp_files
  src/plugins/Open303/Open303.schelp
)

sc_add_server_plugin(
  "${project_name}" # destination directory
  "Open303" # target name
  "${Open303_cpp_files}"
  "${Open303_sc_files}"
  "${Open303_schelp_files}"
)
