#!/bin/sh
# Simple check of transliteration facilities.
# Usage: check-translit SRCDIR FILE FROMCODE TOCODE
srcdir="$1"
bindir=../src
file="$2"
fromcode="$3"
tocode="$4"
set -e
$bindir/iconv -f "$fromcode" -t "$tocode"//TRANSLIT < "${srcdir}"/"$file"."$fromcode" > tmp
cmp -s "${srcdir}"/"$file"."$tocode" tmp
rc=$?
rm -f tmp
[ $rc -ne 0 ] && exit $rc
exit 0
