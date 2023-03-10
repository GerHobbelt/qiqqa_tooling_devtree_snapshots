Long: remove-partial
Help: Remove output file on errors
See-also: fail
Category: curl
Example: --remove-partial -o output $URL
Added: 7.83.0
---
When curl returns an error when told to save output in a local file, this
option removes that saved file before exiting. This prevevents curl from
leaving a partial file in the case of an error during transfer.

If the output is not a file, this option has no effect.
