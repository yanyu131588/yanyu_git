#!/bin/bash

set +x
set -e

#rm -rf build/ log/
INSTALL_PATH=$(pwd)

source_dir=$(pwd)/install
target_dir=$(pwd)/ros2_so
if [ ! -d "$target_dir" ]; then
  echo "$target_dir does not exit, create it!"
  mkdir -p $target_dir
fi

CFLAGS="${TARGET_FLAGS}" \
CXXFLAGS="${TARGET_FLAGS}" \
CC="${TARGET_GCC}" \
CCSHARED="${TARGET_GCC} -fpic" \
CXX="arm-openwrt-linux-gnueabi-g++" \
LD="${TARGET_GCC}" \
LDSHARED="${TARGET_GCC} -shared" \
CPPFLAGS="-I${STAGING_DIR}/usr/include -I${STAGING_DIR}/include -I${STAGING_DIR}/../toolchain/usr/include -I${STAGING_DIR}/../toolchain/include -I${STAGING_DIR}/usr/include/python3.10" \
LDFLAGS="${TARGET_LDFLAGS} -lrcpputils -lrcutils -lspdlog -lfmt -lz -lpython3.10" \
_PYTHON_HOST_PLATFORM="linux-arm" \
__PYVENV_LAUNCHER__="/usr/bin/python3.10" \
PYTHONPATH="${STAGING_DIR}/usr/lib/python3.10:${STAGING_DIR}/usr/lib/python3.10/site-packages:/usr/lib/python3.10/site-packages" \
PYTHONDONTWRITEBYTECODE=1 \
PYTHONOPTIMIZE="" \
_python_sysroot="${STAGING_DIR}" \
_python_prefix="/usr" \
_python_exec_prefix="/usr" \
CMAKE_COMMAND="${HOST_BIN}/cmake" \
AMENT_PREFIX_PATH="${STAGING_DIR}/usr" \
"${HOST_BIN}/colcon" build \
--cmake-force-configure \
--cmake-args \
-DCMAKE_SYSTEM_NAME=Linux \
-DCMAKE_SYSTEM_VERSION=1 \
-DCMAKE_SYSTEM_PROCESSOR=arm \
-DCMAKE_BUILD_TYPE=Release \
-DCMAKE_C_FLAGS_RELEASE="-DNDEBUG" \
-DCMAKE_CXX_FLAGS_RELEASE="-DNDEBUG" \
-DCMAKE_C_COMPILER_LAUNCHER="" \
-DCMAKE_C_COMPILER="${CROSS_COMPILE}gcc" \
-DCMAKE_CXX_COMPILER_LAUNCHER="" \
-DCMAKE_CXX_COMPILER="${CROSS_COMPILE}g++" \
-DCMAKE_ASM_COMPILER_LAUNCHER="" \
-DCMAKE_ASM_COMPILER="${CROSS_COMPILE}gcc" \
-DCMAKE_EXE_LINKER_FLAGS:STRING="${TARGET_LDFLAGS} -lrcpputils -lrcutils -lspdlog -lfmt -lz" \
-DCMAKE_MODULE_LINKER_FLAGS:STRING="${TARGET_LDFLAGS} -lrcpputils -lrcutils -lspdlog -lfmt -lz -Wl,-Bsymbolic-functions" \
-DCMAKE_SHARED_LINKER_FLAGS:STRING="${TARGET_LDFLAGS} -lrcpputils -lrcutils -lspdlog -lfmt -lz -Wl,-Bsymbolic-functions" \
-DCMAKE_AR="${CROSS_COMPILE}gcc-ar" \
-DCMAKE_NM="${CROSS_COMPILE}gcc-nm" \
-DCMAKE_RANLIB="${CROSS_COMPILE}gcc-ranlib" \
-DCMAKE_FIND_ROOT_PATH="${STAGING_DIR}/usr;${STAGING_DIR}/../toolchain" \
-DCMAKE_FIND_ROOT_PATH_MODE_PROGRAM=BOTH \
-DCMAKE_FIND_ROOT_PATH_MODE_LIBRARY=ONLY \
-DCMAKE_FIND_ROOT_PATH_MODE_INCLUDE=ONLY \
-DCMAKE_STRIP="${CROSS_COMPILE}strip" \
-DCMAKE_INSTALL_PREFIX=/usr \
-DDL_LIBRARY="${STAGING_DIR}" \
-DCMAKE_PREFIX_PATH="${STAGING_DIR}" \
-DCMAKE_SKIP_RPATH=TRUE \
-DCMAKE_EXPORT_PACKAGE_REGISTRY=FALSE \
-DCMAKE_EXPORT_NO_PACKAGE_REGISTRY=TRUE \
-DCMAKE_FIND_USE_PACKAGE_REGISTRY=FALSE  \
-DCMAKE_FIND_PACKAGE_NO_PACKAGE_REGISTRY=TRUE \
-DCMAKE_FIND_USE_SYSTEM_PACKAGE_REGISTRY=FALSE \
-DCMAKE_FIND_PACKAGE_NO_SYSTEM_PACKAGE_REGISTRY=TRUE \
-DPython3_EXECUTABLE="${HOST_BIN}/python3.10" \
-DPYTHON_EXECUTABLE="${HOST_BIN}/python3.10" \
-DBUILD_TESTING=OFF \
-DSECURITY=ON

find "$source_dir" -name "*.so" -exec cp {} "$target_dir" \;

unset INSTALL_PATH

