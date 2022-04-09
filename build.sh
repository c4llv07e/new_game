#!/bin/sh

SOURCES=$(find src -name "*.c")
LIBS=(sdl2 lua53)
ADD_LINKS=(SDL2_ttf)
CC=${CC:-tcc}
DEBUG=${DEBUG:-true}
DEBUG_PREFIX=${DEBUG_PREFIX:-"-g"}

[[ $DEBUG = true ]] \
    && DEBUG_PARAM=$DEBUG_PREFIX \
        || DEBUG_PARAM=''

LIB_PARAM=""
for lib in ${LIBS[@]};
do
    LIB_PARAM="$LIB_PARAM $(pkgconf --libs --cflags $lib)";
done;

for link in ${ADD_LINKS[@]};
do
    LIB_PARAM="$LIB_PARAM -l$link";
done;

[[ -n "$SOURCES" ]] \
    && echo $CC $DEBUG_PARAM $LIB_PARAM $SOURCES -o main \
    && exit 0 \
    || echo "error on build" \
    && exit 1
