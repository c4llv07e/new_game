#!/usr/bin/env bash

SOURCES=$(find src -name "*.c")
LIBS=(SDL2 SDL2_ttf lua)
LIB_PREFIX=${LIB_PREFIX:-"-l"}
CC=${CC:-tcc}
DEBUG=${DEBUG:-true}
DEBUG_PREFIX=${DEBUG_PREFIX:-"-g"}
AM_GITHUB_ACTION=${AM_GITHUB_ACTION:-false}
FOR_GITHUB_ACTION=""

[[ $DEBUG = true ]] \
    && DEBUG_PARAM=$DEBUG_PREFIX \
        || DEBUG_PARAM=''

LIB_PARAM=""
for i in ${LIBS[@]};
do
    LIB_PARAM="$LIB_PARAM $LIB_PREFIX$i ";
done;

[[ $AM_GITHUB_ACTION = true ]] && FOR_GITHUB_ACTION="$FOR_GITHUB_ACTION -I/usr/include/lua5.3"

[[ -n "$SOURCES" ]] \
    && $CC $DEBUG_PARAM $LIB_PARAM $FOR_GITHUB_ACTION $SOURCES -o main \
    && exit 0 \
    || echo "error on build" \
    && exit 1
