#!/bin/sh
# Convenience script for fetching auxiliary files that are omitted from
# the version control repository of this package.
#
# This script requires either
#   - the GNULIB_TOOL environment variable pointing to the gnulib-tool script
#     in a gnulib checkout, or
#   - an internet connection.

# Copyright (C) 2003-2022 Free Software Foundation, Inc.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

# Usage: ./autopull.sh

GNULIB_REPO_URL="https://git.savannah.gnu.org/gitweb/?p=gnulib.git;a=blob_plain;hb=HEAD;f="

for file in build-aux/install-sh build-aux/mkinstalldirs \
            build-aux/compile build-aux/ar-lib \
            lib/filename.h; do
  if test -n "$GNULIB_TOOL"; then
    $GNULIB_TOOL --copy-file $file $file
  else
    wget -q --timeout=5 -O $file.tmp "${GNULIB_REPO_URL}$file" \
      && mv $file.tmp $file
  fi
done
chmod a+x build-aux/install-sh build-aux/mkinstalldirs \
          build-aux/compile build-aux/ar-lib

echo "$0: done.  Now you can run './autogen.sh'."
