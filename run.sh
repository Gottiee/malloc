#!/bin/sh
# export LD_LIBRARY_PATH=..
# export LD_PRELOAD=libft_malloc.so
# $@

export LD_LIBRARY_PATH=$(pwd)
export LD_PRELOAD=libft_malloc.so
$@