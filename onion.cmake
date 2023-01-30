# Тут указываем параметры для кросс-компиляции. В Cmake это попадает при запуске через аргумент -DCMAKE_TOOLCHAIN_FILE=onion.cmake
# the name of the target operating system
set(CMAKE_SYSTEM_NAME Linux)

# which compilers to use for C and C++
set(CMAKE_C_COMPILER   /home/vitalya/onion/source/staging_dir/toolchain-mipsel_24kc_gcc-7.3.0_musl/bin/mipsel-openwrt-linux-gcc)
set(CMAKE_CXX_COMPILER /home/vitalya/onion/source/staging_dir/toolchain-mipsel_24kc_gcc-7.3.0_musl/bin/mipsel-openwrt-linux-g++)

# where is the target environment located
set(CMAKE_FIND_ROOT_PATH  
    /home/vitalya/onion/source/staging_dir/toolchain-mipsel_24kc_gcc-7.3.0_musl
    )

# adjust the default behavior of the FIND_XXX() commands:
# search programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# search headers and libraries in the target environment
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)