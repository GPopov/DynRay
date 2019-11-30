add_library(Demos STATIC)
add_library(DynRay::demos ALIAS Demos)

target_sources(Demos PRIVATE src/randomspheres.cpp
               include/demo/randomspheres.hpp)

target_include_directories(
  Demos
  PUBLIC $<INSTALL_INTERFACE:include>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
          ${CMAKE_CURRENT_SOURCE_DIR}/include/demo)

target_compile_features(Demos PRIVATE cxx_alias_templates cxx_std_17)
target_link_libraries(Demos DynRay::DynRay glm)

set(INSTALL_DIR ${CMAKE_BINARY_DIR}/output)
set(INSTALL_LIB_DIR ${INSTALL_DIR}/lib)
set(INSTALL_BIN_DIR ${INSTALL_DIR}/bin)

set(INSTALL_CONFIGDIR ${INSTALL_DIR}/cmake/DynRay)

install(
  TARGETS Demos
  EXPORT demos-export
  LIBRARY DESTINATION ${INSTALL_LIB_DIR}
  ARCHIVE DESTINATION ${INSTALL_LIB_DIR})

install(DIRECTORY include/ DESTINATION ${INSTALL_LIB_DIR}/include)

install(
  EXPORT demos-export
  FILE DemosTargets.cmake
  NAMESPACE DynRay::
  DESTINATION ${INSTALL_DIR}/cmake/Demos)

include(CMakePackageConfigHelpers)
configure_package_config_file(
  ${CMAKE_CURRENT_LIST_DIR}/cmake/DemosConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/DemosConfig.cmake INSTALL_DESTINATION
  ${INSTALL_CONFIGDIR})
export(
  EXPORT demos-export
  FILE ${CMAKE_CURRENT_BINARY_DIR}/DemosTargets.cmake
  NAMESPACE DynRay::)
