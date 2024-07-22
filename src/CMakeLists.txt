# based heavily on https://gitlab.com/CLIUtils/modern-cmake/-/blob/master/examples/extended-project/src/CMakeLists.txt

# example from when I was doing raft cpp impl
#set(HEADER_LIST "${raft_cpp_impl_SOURCE_DIR}/include/raft/lib.hpp")

add_library(utils buffers.cpp shaders.cpp ${HEADER_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(utils PUBLIC ../include)

# the libs
target_link_libraries(utils PUBLIC glad glfw fmt)

target_compile_features(utils PUBLIC cxx_std_17)

# IDEs should put the headers in a nice place
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})
