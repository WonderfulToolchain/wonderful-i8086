#!/bin/bash

## base definitions

if [ -z "$WONDERFUL_TOOLCHAIN" ]; then
	echo Please define WONDERFUL_TOOLCHAIN to point to the location of the Wonderful toolchain.
	exit 1;
fi

. defs.sh
if [ ! -z "$CROSS" ]; then
	. defs-cross-"$CROSS".sh

	if [ -z "$WONDERFUL_NATIVE_TOOLCHAIN" ]; then
		echo Please define WONDERFUL_NATIVE_TOOLCHAIN to point to the location of the native Wonderful toolchain.
		exit 1;
	fi

	export PATH="$WONDERFUL_NATIVE_TOOLCHAIN"/i8086/bin:"$PATH"

	CROSS_CONFIGURE=( "--host=$CROSS_HOST" )
	BUILD_PREFIX=build-"$CROSS"
else
	CROSS_CONFIGURE=( )
	BUILD_PREFIX=build
	HOST_EXECUTABLE_SUFFIX=
fi

component_requested() {
	needle=$1
	shift
	while (( "$#" )); do
		if [ "$1" = "all" ] || [ "$1" = "$needle" ]; then
			return 0
		fi
		shift
	done
	return 1
}

## binutils/gcc

if component_requested binutils $@; then
	echo "=== Building binutils ==="
	rm -rf "$BUILD_PREFIX"-binutils
	mkdir "$BUILD_PREFIX"-binutils
	pushd "$BUILD_PREFIX"-binutils
	../binutils-ia16/configure "${CROSS_CONFIGURE[@]}" \
		--target=ia16-elf --prefix="$PREFIX" \
		--enable-ld-default --enable-gold=yes \
		--enable-targets=ia16-elf \
		--enable-x86-hpa-segelf=yes \
		--disable-gdb \
		--disable-gprof \
		--disable-libdecnumber \
		--disable-readline \
		--disable-sim \
		--disable-nls \
		--disable-werror
	make
	make -j1 install
	popd
fi

GMP_PREFIX=`realpath ../"$BUILD_PREFIX"-gmp-out`
MPFR_PREFIX=`realpath ../"$BUILD_PREFIX"-mpfr-out`
MPC_PREFIX=`realpath ../"$BUILD_PREFIX"-mpc-out`
ISL_PREFIX=`realpath ../"$BUILD_PREFIX"-isl-out`

if component_requested gcc-deps $@; then
	echo "=== Building GCC dependencies ==="
	for i in "$BUILD_PREFIX"-gmp "$BUILD_PREFIX"-gmp-out "$BUILD_PREFIX"-mpfr "$BUILD_PREFIX"-mpfr-out "$BUILD_PREFIX"-mpc "$BUILD_PREFIX"-mpc-out "$BUILD_PREFIX"-isl "$BUILD_PREFIX"-isl-out; do
		if [ -d "$i" ]; then
			rm -rf "$i"
		fi
		mkdir "$i"
	done
	pushd "$BUILD_PREFIX"-gmp
	# CC_FOR_BUILD=gcc fixes the following error when cross-compiling:
	# checking for build system executable suffix... configure: error: Cannot determine executable suffix
	CC_FOR_BUILD=gcc ../gmp-$GMP_VERSION/configure "${CROSS_CONFIGURE[@]}" --prefix="$GMP_PREFIX" --disable-shared
	make
	make -j1 install
	popd
	pushd "$BUILD_PREFIX"-mpfr
	../mpfr-$MPFR_VERSION/configure "${CROSS_CONFIGURE[@]}" --prefix="$MPFR_PREFIX" --with-gmp="$GMP_PREFIX" --disable-shared
	make
	make -j1 install
	popd
	pushd "$BUILD_PREFIX"-mpc
	../mpc-$MPC_VERSION/configure "${CROSS_CONFIGURE[@]}" --prefix="$MPC_PREFIX" --with-gmp="$GMP_PREFIX" --with-mpfr="$MPFR_PREFIX" --disable-shared
	make
	make -j1 install
	popd
	pushd "$BUILD_PREFIX"-isl
	../isl-$ISL_VERSION/configure "${CROSS_CONFIGURE[@]}" --prefix="$ISL_PREFIX" --with-gmp-prefix="$GMP_PREFIX" --disable-shared
	make
	make -j1 install
	popd
fi

if component_requested gcc $@; then
	echo "=== Building GCC ==="
	rm -rf "$BUILD_PREFIX"-gcc
	mkdir "$BUILD_PREFIX"-gcc
	pushd "$BUILD_PREFIX"-gcc
	../gcc-ia16/configure "${CROSS_CONFIGURE[@]}" \
		--target=ia16-elf --prefix="$PREFIX" \
		--with-bugurl="https://github.com/WonderfulToolchain/gcc-ia16/issues" \
		--without-headers \
		--enable-languages=c \
		--disable-libssp \
		--disable-libquadmath \
		--disable-libstdcxx \
		--disable-multilib \
		--with-gmp="$GMP_PREFIX" --with-mpfr="$MPFR_PREFIX" --with-mpc="$MPC_PREFIX" --with-isl="$ISL_PREFIX"
	make
	make -j1 install

	# Build libgcc for WSwan target.
	make clean-target-libgcc
	make all-target-libgcc CFLAGS_FOR_TARGET="-O2 -march=v30mz -mtune=v30mz -mregparmcall -mcmodel=medium -msegelf"
	mkdir -p "$PREFIX"/wswan/lib
	install -m 644 ia16-elf/libgcc/libgcc.a "$PREFIX"/wswan/lib

	# Build libgcc for WWitch target.
	# TODO: Broken (unwind-c.c does not build).
	#make clean-target-libgcc
	#make all-target-libgcc CFLAGS_FOR_TARGET="-Os -march=v30mz -mtune=v30mz -mregparmcall -mcmodel=small -msegelf -mno-callee-assume-ss-data-segment"
	#mkdir -p "$PREFIX"/wwitch/lib
	#install -m 644 ia16-elf/libgcc/libgcc.a "$PREFIX"/wwitch/lib

	popd
fi

## utilities

if component_requested lzsa $@; then
	echo "=== Building lzsa ==="
	pushd lzsa
	make -j1 clean
	if [ ! -z "$CROSS" ]; then
		CC="$CROSS_CC" CXX="$CROSS_CXX" make APP=lzsa"$HOST_EXECUTABLE_SUFFIX"
	else
		make APP=lzsa"$HOST_EXECUTABLE_SUFFIX"
	fi
	cp -a lzsa"$HOST_EXECUTABLE_SUFFIX" \
		"$PREFIX"/bin/wf-lzsa"$HOST_EXECUTABLE_SUFFIX"
	popd
fi

if component_requested superfamiconv $@; then
	echo "=== Building SuperFamiconv ==="
	pushd SuperFamiconv
	make -j1 clean
	if [ ! -z "$CROSS" ]; then
		CC="$CROSS_CC" CXX="$CROSS_CXX" make
	else
		make
	fi
	cp -a bin/superfamiconv"$HOST_EXECUTABLE_SUFFIX" \
		"$PREFIX"/bin/wf-superfamiconv"$HOST_EXECUTABLE_SUFFIX"
	popd
fi
