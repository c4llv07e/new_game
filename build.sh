#!/usr/bin/env bash

SOURCES=$(find src -name "*.c")
LINKS=(SDL2 SDL2_ttf lua5.3)
INCLUDES=("/usr/include/SDL2" "/usr/include/lua5.3")
CC=${CC:-tcc}
DEBUG=${DEBUG:-true}
DEBUG_PREFIX=${DEBUG_PREFIX:-"-g"}

[[ $DEBUG = true ]] \
    && DEBUG_PARAM=$DEBUG_PREFIX \
        || DEBUG_PARAM=''

LIB_PARAM=""
for inc in ${INCLUDES[@]};
do
    LIB_PARAM="$LIB_PARAM -I$inc";
done;

for link in ${LINKS[@]};
do
    LIB_PARAM="$LIB_PARAM -l$link";
done;

[[ -n "$SOURCES" ]] \
    && $CC $DEBUG_PARAM $LIB_PARAM $SOURCES -o main \
    && exit 0 \
    || echo "error on build" \
    && exit 1
