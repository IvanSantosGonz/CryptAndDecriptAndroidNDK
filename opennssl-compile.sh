#!/bin/bash
set -e
set -x

# Set directory
SCRIPTPATH='/home/ivan'
export ANDROID_NDK_HOME=/home/ivan/android-ndk-r21e/android-ndk-r21e
OPENSSL_DIR=$SCRIPTPATH/openssl-1.1.1k/openssl-1.1.1k

toolchains_path=/home/ivan/android-ndk-r21e/android-ndk-r21e/toolchains/llvm/prebuilt/linux-x86_64

# Set compiler clang, instead of gcc by default
CC=clang

# Add toolchains bin directory to PATH
PATH=$toolchains_path/bin:$PATH

# Set the Android API levels
ANDROID_API=21

cd ${OPENSSL_DIR}
# Android architectures can be android-arm, android-arm64, android-x86, android-x86_64 etc
for architecture in android-arm android-arm64 android-x86 android-x86_64
do
   # Create the make file
   ./Configure ${architecture} -D__ANDROID_API__=$ANDROID_API

   # Build
   make

   # Copy the outputs
   OUTPUT_INCLUDE=$SCRIPTPATH/output/include
   OUTPUT_LIB=$SCRIPTPATH/output/lib/${architecture}
   mkdir -p $OUTPUT_INCLUDE
   mkdir -p $OUTPUT_LIB
   cp -RL include/openssl $OUTPUT_INCLUDE
   cp libcrypto.so $OUTPUT_LIB
   cp libcrypto.a $OUTPUT_LIB
   cp libssl.so $OUTPUT_LIB
   cp libssl.a $OUTPUT_LIB

   make clean
   rm ${OPENSSL_DIR}/Makefile
done
