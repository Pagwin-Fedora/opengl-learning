
mk_debug_setup:
    rm -r build
    cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
