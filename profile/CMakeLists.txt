add_executable(profile src/main.cpp)

target_compile_features(profile PRIVATE cxx_alias_templates cxx_std_17)
target_link_libraries(
  profile
  DynRay::demos
  DynRay::DynRay
  glm
  benchmark)

add_custom_command(
  TARGET profile POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:DynRay::DynRay>
          $<TARGET_FILE_DIR:profile>)

add_custom_command(
  TARGET profile POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:benchmark>
          $<TARGET_FILE_DIR:profile>)
