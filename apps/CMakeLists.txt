# based heavily on https://gitlab.com/CLIUtils/modern-cmake/-/blob/master/examples/extended-project/apps/CMakeLists.txt

add_executable(basic_window basic_window.cpp)
target_link_libraries(basic_window PUBLIC glad glfw fmt)
target_compile_features(basic_window PRIVATE cxx_std_20)

add_executable(first_triangle first_triangle.cpp)
target_link_libraries(first_triangle PUBLIC glad glfw fmt)
target_compile_features(first_triangle PRIVATE cxx_std_20)

add_executable(utils_triangle utils_triangle.cpp)
target_link_libraries(utils_triangle PUBLIC glad glfw fmt utils)
target_compile_features(utils_triangle PRIVATE cxx_std_20)
