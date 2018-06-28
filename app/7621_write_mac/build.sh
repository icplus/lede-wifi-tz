#!/bin/sh

CROSS_COMPILE=/home/cwp/lede-zte-832/staging_dir/toolchain-mips_24kc_gcc-5.4.0_musl/bin/
  export STAGING_DIR=/home/cwp/lede-zte-832/staging_dir/toolchain-mips_24kc_gcc-5.4.0_musl/
CC=${CROSS_COMPILE}mips-openwrt-linux-gcc

${CC} -o mac_set mac-set.c
