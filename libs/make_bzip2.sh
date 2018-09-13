#!/bin/bash
set -e

if [ ! -f "$1/libbz2.a" ]; then

    CC=gcc
    AR=ar

    BIGFILES="-D_FILE_OFFSET_BITS=64"
    CFLAGS="-Wall -Winline -O2 -fPIC $BIGFILES"

    gcc ${CFLAGS} -c bzip2-1.0.6/blocksort.c -o $1/blocksort.o
    gcc ${CFLAGS} -c bzip2-1.0.6/huffman.c -o $1/huffman.o
    gcc ${CFLAGS} -c bzip2-1.0.6/crctable.c -o $1/crctable.o
    gcc ${CFLAGS} -c bzip2-1.0.6/randtable.c -o $1/randtable.o
    gcc ${CFLAGS} -c bzip2-1.0.6/compress.c -o $1/compress.o
    gcc ${CFLAGS} -c bzip2-1.0.6/decompress.c -o $1/decompress.o
    gcc ${CFLAGS} -c bzip2-1.0.6/bzlib.c -o $1/bzlib.o

    $AR cq $1/libbz2.a $1/blocksort.o $1/huffman.o $1/crctable.o $1/randtable.o $1/randtable.o $1/compress.o $1/decompress.o $1/bzlib.o
fi
