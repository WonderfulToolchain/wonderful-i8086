#!/bin/bash

if [ -z "$WONDERFUL_TOOLCHAIN" ]; then
	echo Please define WONDERFUL_TOOLCHAIN to point to the location of the Wonderful toolchain.
	exit 1;
fi

PREFIX=$WONDERFUL_TOOLCHAIN/i8086
PARALLEL=-j6
GMP_VERSION=6.1.2
ISL_VERSION=0.16.1
MPC_VERSION=1.0.3
MPFR_VERSION=3.1.5
