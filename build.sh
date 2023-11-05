#!/usr/bin/env bash

set -xe

CFLAGS="-std=c99 -Wall -Wextra -pedantic -Wall"
gcc -o genarr ./main.c $CFLAGS
