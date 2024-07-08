
mk_debug_setup:
    rm -rf build
    cmake -B build -DCMAKE_BUILD_TYPE=Debug # -G Ninja
