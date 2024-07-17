export CC := "clang"
export CXX := "clang++"
mk_debug_setup:
    rm -rf build
    cmake -B build -DCMAKE_BUILD_TYPE=Debug -G Ninja
mk_release_setup:
    rm -rf build
    cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
