#!/bin/bash

## base definitions

. defs.sh

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
	rm -rf build-binutils
	mkdir build-binutils
	pushd build-binutils
	../binutils-ia16/configure \
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

GMP_PREFIX="`realpath ../build-gmp-out`"
MPFR_PREFIX="`realpath ../build-gmp-out`"
MPC_PREFIX="`realpath ../build-gmp-out`"
ISL_PREFIX="`realpath ../build-gmp-out`"

if component_requested gcc-deps $@; then
	echo "=== Building GCC dependencies ==="
	for i in build-gmp build-gmp-out build-mpfr build-mpfr-out build-mpc build-mpc-out build-isl build-isl-out; do
		if [ -d "$i" ]; then
			rm -rf "$i"
		fi
		mkdir "$i"
	done
	pushd build-gmp
	../gmp-$GMP_VERSION/configure --prefix="$GMP_PREFIX" --disable-shared
	make
	make -j1 install
	popd
	pushd build-mpfr
	../mpfr-$MPFR_VERSION/configure --prefix="$MPFR_PREFIX" --with-gmp="$GMP_PREFIX" --disable-shared
	make
	make -j1 install
	popd
	pushd build-mpc
	../mpc-$MPC_VERSION/configure --prefix="$MPC_PREFIX" --with-gmp="$GMP_PREFIX" --with-mpfr="$MPFR_PREFIX" --disable-shared
	make
	make -j1 install
	popd
	pushd build-isl
	../isl-$ISL_VERSION/configure --prefix="$ISL_PREFIX" --with-gmp-prefix="$GMP_PREFIX" --disable-shared
	make
	make -j1 install
	popd
fi

if component_requested gcc $@; then
	echo "=== Building GCC ==="
	rm -rf build-gcc
	mkdir build-gcc
	pushd build-gcc
	../gcc-ia16/configure \
		--target=ia16-elf --prefix="$PREFIX" \
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
	make
	cp -a lzsa $PREFIX/bin/wf-lzsa
	popd
fi

if component_requested superfamiconv $@; then
	echo "=== Building SuperFamiconv ==="
	pushd SuperFamiconv
	make -j1 clean
	make
	cp -a bin/superfamiconv $PREFIX/bin/wf-superfamiconv
	popd
fi

