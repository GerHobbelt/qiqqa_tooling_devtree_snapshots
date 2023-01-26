#!/bin/sh
#
# png2uri version 1.0.6, July 7, 2012.
#
# NO COPYRIGHT RIGHTS ARE CLAIMED TO THIS SOFTWARE.
#
# To the extent possible under law, the author has waived all copyright and
# related or neighboring rights to this work. This work is published from
# the United States of America in 2012.
#
# This png2uri software may be used freely in any way.
#
# The source is the original work of the person named below.  No other person
# or organization has made contributions to this work.
#
# ORIGINAL AUTHORS
#     The following people have contributed to the code or comments in this
#     file.  None of the people below claim any rights with regard to the
#     contents of this file.
#
#     Glenn Randers-Pehrson <glennrp at users.sourceforge.net> is the author.
#     John Bowler <jbower at acm.org> contributed some useful suggestions.
#
# png2uri is a command-line application that creates an HTML "img" tag on
# standard output containing a data URI in accordance with RFC-2397, from
# a PNG file or from a PNG datastream received from standard input.
# Other formats besides the default, PNG, are supported, via the "-f" or
# "--format" option or, if that option was not supplied, by inspection of the
# filename extension.
#
# Usage: png2uri [-f type|--format type] [-u|--uri_only] [infile [outfile]]
#
#        options: -f|--format TYPE: 
#                 write "image/TYPE" instead of "image/png" in the
#                 data uri.  TYPE can be png, jpg, jpeg, bmp, or gif,
#                 or any of those in upper case.  To write any other
#                 type, include the complete MIME type as in
#                 "--format image/x-jng" or "-f audio/mpeg".
#
#                 -u|--uri_only|--url_only
#                 omit the surrounding "img" tag and only write the
#                 data URI.
#
# Requires /bin/sh and a "base64" or "uuencode -m" that encodes its input
# in base64 according to RFC-3548 and writes the result on standard output,
# and a working "sed".
#
# If you prefer a web-based converter or a java application, this isn't
# it. Use your search engine and look for "data uri" to find one.
#
# This script figures out which of base64(1) or uuencode(1) to use, since
# neither is always present (uuencode must be installed as part of "sharutils"
# on Gnu/Linux platforms, which often hasn't happened).

png2uri_encode(){
base64 2>/dev/null || uuencode -m "====" | grep -v "===="
}

PNG2URI_FMT="unknown"
PNG2URI_URI="true"

while true
do
case X$1 in
  X-f|X--format)
    shift

    case X$1 in
      Xpng|XPNG)
        PNG2URI_FMT=image/png
        ;;

      Xjpeg|XJPEG|Xjpg|XJPG)
        PNG2URI_FMT=image/jpeg
        ;;

      Xbmp|XBMP)
        PNG2URI_FMT=image/bmp
        ;;

      Xgif|XGIF)
        PNG2URI_FMT=image/gif
        ;;

      *)
        PNG2URI_FMT=$1
        ;;
    esac
    shift
    ;;

  X-u|X--ur*)
      PNG2URI_URI="false"
      shift
      ;;

  X)
      # Convert standard input.
      case X$PNG2URI_FMT in
        Xunknown)
          PNG2URI_FMT=image/png
          ;;
      esac

      case X$PNG2URI_URI in
        Xfalse)
          echo "data:$PNG2URI_FMT;base64," &&
          png2uri_encode
          ;;

        *)
          echo "<img alt=\"PNG\" title=\"PNG\" src=\"" &&
          echo "data:$PNG2URI_FMT;base64," &&
          png2uri_encode
          echo "\">"
          ;;
      esac
      exit
      ;;

  *)
      # Convert the named file.

      # First make sure there weren't extra arguments
      case $# in
        1)
          :  # OK, continue
          ;;
        2)
          exec < "$1" > "$2"
          ;;
        *)
          echo "png2uri: too many arguments: $*" >&2
          echo "usage: png2uri [options] [infile [outfile]" >&2
          exit 1
          ;;
      esac

      case X$PNG2URI_FMT in
        Xunknown)
          PNG2URI_FMT=image/png
          png2uri_extension=`echo $1 | sed "s/.*\.//"`

          case X$png2uri_extension in
              Xjpeg|XJPEG|Xjpg|XJPG)
                PNG2URI_FMT=image/jpeg
                ;;

              Xbmp|XBMP)
                PNG2URI_FMT=image/bmp
                ;;

              Xgif|XGIF)
                PNG2URI_FMT=image/gif
                ;;
            esac
          ;;
      esac

      case X$PNG2URI_URI in
        Xfalse)
            echo "data:$PNG2URI_FMT;base64," &&
            png2uri_encode < "$1"
            ;;
        *)
            echo "<img alt=\"PNG\" title=\"PNG\" src=\"" &&
            echo "data:$PNG2URI_FMT;base64," &&
            png2uri_encode < "$1"
            echo "\">"
            ;;
      esac
      exit
      ;;
esac
done
