#! /bin/bash
#

# collect all feature defines from the source code:
grep '^\s*#[^/*]*SQLITE_' -h *.c *.h | tr -s '\t\r\n (#)!<>|?:=+-' '\n' | grep '^SQLITE_' | grep -v '[a-z]' | sort | uniq > feature_list.lst

