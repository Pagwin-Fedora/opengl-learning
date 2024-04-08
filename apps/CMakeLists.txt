# based heavily on https://gitlab.com/CLIUtils/modern-cmake/-/blob/master/examples/extended-project/apps/CMakeLists.txt

add_executable(exe_name exe_entry.cpp)

# example library link
#target_link_libraries(exe_name fmt::fmt)

target_compile_features(exe_name PRIVATE cxx_std_20)
