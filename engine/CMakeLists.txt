set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(dynray STATIC)
add_library(DynRay::DynRay ALIAS dynray)

target_sources(dynray PRIVATE 
   src/object.cpp 
   src/renderer.cpp 
   src/camera.cpp
   src/light.cpp
   src/material.cpp
   src/scene.cpp
   include/engine/object.hpp 
   include/engine/material.hpp
   include/engine/renderer.hpp 
   include/engine/scene.hpp
   include/engine/camera.hpp
   include/engine/light.hpp
   include/engine/hitrecord.hpp
)

target_include_directories(dynray
   PUBLIC 
     $<INSTALL_INTERFACE:include>
     $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
   PRIVATE
     ${CMAKE_CURRENT_SOURCE_DIR}/src
     ${CMAKE_CURRENT_SOURCE_DIR}/include/engine
)

target_link_libraries(dynray glm)
target_compile_features(dynray 
   PRIVATE 
     cxx_alias_templates 
     cxx_auto_type 
     cxx_constexpr 
     cxx_override
     cxx_range_for
     cxx_right_angle_brackets
     cxx_final
     cxx_std_17
)


set(INSTALL_DIR ${CMAKE_BINARY_DIR}/output)
set(INSTALL_LIB_DIR ${INSTALL_DIR}/lib)
set(INSTALL_BIN_DIR ${INSTALL_DIR}/bin)

set(INSTALL_CONFIGDIR ${INSTALL_DIR}/cmake/DynRay)

install(TARGETS dynray
   EXPORT dynray-export
   LIBRARY DESTINATION ${INSTALL_LIB_DIR}
   ARCHIVE DESTINATION ${INSTALL_LIB_DIR}
)


install(DIRECTORY
   include/
   DESTINATION ${INSTALL_LIB_DIR}/include
)

install(EXPORT dynray-export
   FILE 
     DynRayTargets.cmake
   NAMESPACE
     DynRay::
   DESTINATION
     ${INSTALL_DIR}/cmake/DynRay
)

include(CMakePackageConfigHelpers)
configure_package_config_file(
   ${CMAKE_CURRENT_LIST_DIR}/cmake/DynRayConfig.cmake.in
   ${CMAKE_CURRENT_BINARY_DIR}/DynRayConfig.cmake
   INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)
export(EXPORT dynray-export FILE ${CMAKE_CURRENT_BINARY_DIR}/DynRayTargets.cmake NAMESPACE DynRay::)

set_target_properties(dynray PROPERTIES EXPORT_NAME DynRay)

add_subdirectory_with_folder("tests" test)