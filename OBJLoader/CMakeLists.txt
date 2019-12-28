add_library(objloader STATIC)
add_library(DynRay::OBJLoader ALIAS objloader)
target_sources(
    objloader
    PRIVATE
    src/objloader.cpp
    include/objloader/objloader.hpp)

target_include_directories(
    objloader
    PUBLIC $<INSTALL_INTERFACE:include>
           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
            ${CMAKE_CURRENT_SOURCE_DIR}/include/objloader)

target_link_libraries(
  objloader
  DynRay::DynRay
  tinyobjloader
  glm
)

target_compile_features(objloader PRIVATE cxx_alias_templates cxx_std_17)

set(INSTALL_DIR ${CMAKE_BINARY_DIR}/output)
set(INSTALL_LIB_DIR ${INSTALL_DIR}/lib)
set(INSTALL_BIN_DIR ${INSTALL_DIR}/bin)

set(INSTALL_CONFIGDIR ${INSTALL_DIR}/cmake/DynRay)

install(
  TARGETS objloader
  EXPORT objloader-export
  LIBRARY DESTINATION ${INSTALL_LIB_DIR}
  ARCHIVE DESTINATION ${INSTALL_LIB_DIR})

install(DIRECTORY include/ DESTINATION ${INSTALL_LIB_DIR}/include)

install(
  EXPORT objloader-export
  FILE OBJLoaderTargets.cmake
  NAMESPACE DynRay::
  DESTINATION ${INSTALL_DIR}/cmake/OBJLoader)

include(CMakePackageConfigHelpers)
configure_package_config_file(
  ${CMAKE_CURRENT_LIST_DIR}/cmake/OBJLoaderConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/OBJLoaderConfig.cmake INSTALL_DESTINATION
  ${INSTALL_CONFIGDIR})

export(
  EXPORT objloader-export
  FILE ${CMAKE_CURRENT_BINARY_DIR}/OBJLoaderTargets.cmake
  NAMESPACE DynRay::)
