#!/bin/bash

. defs.sh

fetch_http_tar () {
	if [ ! -f "$1" ] || [ ! tar tf "$1" >/dev/null 2>/dev/null ]; then
		echo "=== Downloading "$1"... ==="
		if [ -d "$2" ]; then
			rm -r "$2"
		fi
		rm -f "$1"
		if ! wget -O "$1" "$3"; then
			echo "Error!"
			exit 1
		fi
	fi
	if [ ! -d "$2" ]; then
		echo "=== Extracting "$1"... ==="
		if ! tar xf "$1"; then
			echo "Error!"
			exit 1
		fi
	fi
}

fetch_git () {
	if [ ! -d "$1" ]; then
		echo "=== Cloning "$1"... ==="
		if git clone "$2"; then
			return 0
		else
			echo "Error!"
			exit 1
		fi
	else
		echo "=== Updating "$1"... ==="
		cd "$1"
		if git pull; then
			cd ".."
			return 0
		else
			echo "Error!"
			exit 1
		fi
	fi
}

fetch_git binutils-ia16 https://github.com/WonderfulToolchain/gcc-ia16
fetch_git gcc-ia16 https://github.com/WonderfulToolchain/gcc-ia16
fetch_git SuperFamiconv https://github.com/WonderfulToolchain/SuperFamiconv
fetch_http_tar gmp-$GMP_VERSION.tar.bz2 gmp-$GMP_VERSION https://gmplib.org/download/gmp/gmp-$GMP_VERSION.tar.bz2
fetch_http_tar mpfr-$MPFR_VERSION.tar.bz2 mpfr-$MPFR_VERSION https://www.mpfr.org/mpfr-$MPFR_VERSION/mpfr-$MPFR_VERSION.tar.bz2
fetch_http_tar mpc-$MPC_VERSION.tar.gz mpc-$MPC_VERSION https://ftp.gnu.org/gnu/mpc/mpc-$MPC_VERSION.tar.gz
fetch_http_tar isl-$ISL_VERSION.tar.bz2 isl-$ISL_VERSION https://gcc.gnu.org/pub/gcc/infrastructure/isl-$ISL_VERSION.tar.bz2
