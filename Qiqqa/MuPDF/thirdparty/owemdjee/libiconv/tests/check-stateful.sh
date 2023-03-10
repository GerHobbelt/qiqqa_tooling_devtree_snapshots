#!/bin/sh
# Simple check of a stateful encoding.
# Usage: check-stateful SRCDIR CHARSET
srcdir="$1"
bindir=../src
charset="$2"
set -e

# charset, modified for use in filenames.
charsetf=`echo "$charset" | sed -e 's,:,-,g'`

if test -f "${srcdir}"/"$charsetf"-snippet.alt; then
  $bindir/iconv -f "$charset" -t UTF-8 < "${srcdir}"/"$charsetf"-snippet.alt > tmp-snippet
  cmp "${srcdir}"/"$charsetf"-snippet.UTF-8 tmp-snippet
  rc1=$?
else
  rc1=0
fi
$bindir/iconv -f "$charset" -t UTF-8 < "${srcdir}"/"$charsetf"-snippet > tmp-snippet
cmp -s "${srcdir}"/"$charsetf"-snippet.UTF-8 tmp-snippet
rc2=$?
$bindir/iconv -f UTF-8 -t "$charset" < "${srcdir}"/"$charsetf"-snippet.UTF-8 > tmp-snippet
cmp -s "${srcdir}"/"$charsetf"-snippet tmp-snippet
rc3=$?
rm -f tmp-snippet
[ $rc1 -ne 0 ] && exit $rc1
[ $rc2 -ne 0 ] && exit $rc2
[ $rc3 -ne 0 ] && exit $rc3
exit 0
