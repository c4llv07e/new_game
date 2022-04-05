#!/bin/sh

SOURCES=$(find src -name "*.c")
LIBS=(SDL2 lua)
LIB_PREFIX=${LIB_PREFIX:-"-l"}
CC=${CC:-tcc}
DEBUG=${DEBUG:-true}
DEBUG_PREFIX=${DEBUG_PREFIX:-"-g"}

[[ $DEBUG = true ]] \
    && DEBUG_PARAM=$DEBUG_PREFIX \
        || DEBUG_PARAM=''

LIB_PARAM=""
for i in ${LIBS[@]};
do
    LIB_PARAM="$LIB_PARAM $LIB_PREFIX$i ";
done;

[[ -n "$SOURCES" ]] \
    && $CC $DEBUG_PARAM $LIB_PARAM $SOURCES -o main \
    && exit 0 \
    || echo "error on build" \
    && exit 1
