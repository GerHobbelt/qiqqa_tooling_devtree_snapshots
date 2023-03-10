#!/bin/sh
# Simple check of transliteration failure.
# Usage: check-translitfailure SRCDIR FILE FROMCODE TOCODE
srcdir="$1"
bindir=../src
file="$2"
fromcode="$3"
tocode="$4"
$bindir/iconv -f "$fromcode" -t "$tocode"//TRANSLIT < "${srcdir}"/"$file"."$fromcode" >/dev/null 2>/dev/null
test $? = 1
exit $?
