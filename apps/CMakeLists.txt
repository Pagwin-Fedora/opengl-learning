# based heavily on https://gitlab.com/CLIUtils/modern-cmake/-/blob/master/examples/extended-project/apps/CMakeLists.txt

add_executable(basic_window basic_window.cpp)

# example library link
#target_link_libraries(exe_name fmt::fmt)

target_compile_features(basic_window PRIVATE cxx_std_20)
