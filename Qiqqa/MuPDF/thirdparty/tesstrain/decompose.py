#!/usr/bin/env python3

# SPDX-License-Identifier: Apache-2.0

import argparse
import io
import unicodedata

# Command line arguments.
arg_parser = argparse.ArgumentParser(description='Decompose all ground truth texts for the given files to prepare training.')
arg_parser.add_argument("filename", help="filename of text file", nargs='*')
arg_parser.add_argument("-n", "--dry-run", help="show which files would be changed but don't change them", action="store_true")
arg_parser.add_argument("-v", "--verbose", help="show ignored files", action="store_true")

args = arg_parser.parse_args()

# Read all files and overwrite them with normalized text if necessary.
for filename in args.filename:
    with io.open(filename, "r", encoding="utf-8") as f:
        try:
            text = f.read()
        except UnicodeDecodeError:
            if args.verbose:
                print(filename + " (ignored)")
            continue
        new_text = text \
                .replace('Ä', 'Ä') \
                .replace('Ö', 'Ö') \
                .replace('Ü', 'Ü') \
                .replace('ä', 'ä') \
                .replace('ï', 'ï') \
                .replace('ö', 'ö') \
                .replace('ü', 'ü') \
                .replace('ë', 'ë') \
                .replace('É', 'É') \
                .replace('á', 'á') \
                .replace('é', 'é') \
                .replace('ó', 'ó') \
                .replace('ś', 'ś') \
                .replace('È', 'È') \
                .replace('à', 'à') \
                .replace('è', 'è') \
                .replace('ò', 'ò') \
                .replace('ō', 'ō') \
                .replace('ñ', 'ñ') \
                .replace('ç', 'ç') \
                .replace('Ô', 'Ô') \
                .replace('â', 'â') \
                .replace('ê', 'ê') \
                .replace('û', 'û') \
                .replace('ř', 'ř') \
                .replace('ž', 'ž') \
                .replace('ô', 'ô') \
                .replace('ő', 'ő') \
                .replace('Š', 'Š') \
                .replace('↉', '0⁄3') \
                .replace('½', '1⁄2') \
                .replace('⅓', '1⁄3') \
                .replace('¼', '1⁄4') \
                .replace('⅕', '1⁄5') \
                .replace('⅙', '1⁄6') \
                .replace('⅐', '1⁄7') \
                .replace('⅛', '1⁄8') \
                .replace('⅑', '1⁄9') \
                .replace('⅒', '1⁄10') \
                .replace('⅔', '2⁄3') \
                .replace('⅖', '2⁄5') \
                .replace('¾', '3⁄4') \
                .replace('⅗', '3⁄5') \
                .replace('⅜', '3⁄8') \
                .replace('⅘', '4⁄5') \
                .replace('⅚', '5⁄6') \
                .replace('⅝', '5⁄8') \
                .replace('⅞', '7⁄8') \
                .replace('¹/₁₆', '1⁄16') \
                .replace('⁶/₁₆', '6⁄16') \
                .replace('Ž', 'Ž')
        if text != new_text:
            print(filename)
            if not args.dry_run:
                with io.open(filename, "w", encoding="utf-8") as out:
                    out.write(new_text)
