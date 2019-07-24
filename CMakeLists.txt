cmake_minimum_required(VERSION 3.8.0)
project(DynRay VERSION 0.1.0 LANGUAGES CXX)
list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_SOURCE_DIR}/cmake)

add_library(dynray src/dynray.cpp)
add_library(DynRay::DynRay ALIAS dynray)

target_include_directories(dynray
    PUBLIC 
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/DynRay)

install(TARGETS dynray
    EXPORT dynray-export
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)


install(DIRECTORY dynray
    include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT dynray-export
    FILE 
        DynRayTargets.cmake
    NAMESPACE
        DynRay::
    DESTINATION
        ${CMAKE_INSTALL_LIBDIR}/cmake/DynRay
)

include(CMakePackageConfigHelpers)
configure_package_config_file(
    ${CMAKE_CURRENT_LIST_DIR}/cmake/DynRayConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/DynRayConfig.cmake
    INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

#export(EXPORT dynray-export FILE ${CMAKE_CURRRENT_BINARY_DIR}/DynRayTargets.cmake NAMESPACE DynRay::)

#set_target_properties(dynray PROPERTIES EXPORT_NAME DynRay)

add_subdirectory(test)

