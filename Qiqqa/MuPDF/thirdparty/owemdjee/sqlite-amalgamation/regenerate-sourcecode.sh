#! /bin/bash
#
# SQLite source tree is assumed to sit in    ../sqlite/
# 

REPODIR=$( pwd )
echo "REPODIR=$REPODIR"

cd ../sqlite/
make clean
rm -f sqliteInt_expanded.h
rm -f src/ctime.c

# make sqlite3_cfg.h
tclsh tool/mkctimec.tcl
make amalgamation

tclsh tool/mksqliteInt_h.tcl --linemacros=0
# commenting out the static definitions fixes MSVC error C2133: 'sqlite3OpcodeProperty': unknown size
# BUT introruces other problems for us in amalgamation1, etc., which we will fix there, locally.
sed -i -E -e 's/(SQLITE_PRIVATE[^;]+;)/\/* \1 *\//g' 	sqliteInt_expanded.h
cp sqliteInt_expanded.h            $REPODIR/sqliteInt.h

# also copy the dirent.h from the dirent project:
cp -n ../dirent/include/dirent.h   $REPODIR
cp -n sqlite_cfg.h                 $REPODIR

echo "Copy generated files to amalgamation repo in $REPODIR..."
cp sqlite3.c $REPODIR/sqlite3.c
cp sqlite3.h $REPODIR/sqlite3.h
cp shell.c sqlite3.1 sqlite3_analyzer.c sqlite3_checker.c sqlite3ext.* sqlite3rc.* sqlite3session.* src/obj_interfaces.h include/*.h monolithic_examples.h $REPODIR
