#! /bin/bash

for f in S:/OCR-selected/debug.tests/*.jpg S:/OCR-selected/debug.tests/*.png S:/OCR-selected/debug.tests/*.jp2 S:/OCR-selected/font.samples.and.tough.stuff/*.jpg S:/OCR-selected/font.samples.and.tough.stuff/*.png S:/OCR-selected/font.samples.and.tough.stuff/*.gif S:/OCR-selected/font.samples.and.tough.stuff/*.tiff S:/OCR-selected/font.samples.and.tough.stuff/*.webp ; do
	DST="$( basename "$f" )"
	echo "$f  --> $DST"

	"bin/Debug-Unicode-64bit-x64/mutool_ex.exe" tesseract  --loglevel debug -l eng+rus+chi_sim+chi_tra+deu+fra+spa+jpn+hin+urd+vie+osd \
		-c debug-all=1 \
		-c classify_debug_level=2 \
		-c paragraph_text_based=Y \
		"$f"   \
		"S:/OCR-test-runs/$DST-PAR-N"
done		
