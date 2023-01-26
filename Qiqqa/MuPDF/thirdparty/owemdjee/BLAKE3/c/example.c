#include "blake3.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef _MSC_VER
#include <unistd.h>
#else
#include <io.h>

typedef int ssize_t;

#if !defined(STDIN_FILENO)
#define STDIN_FILENO 0
#endif

#endif // _MSC_VER

#include "monolithic_examples.h"


#if defined(BUILD_MONOLITHIC)
#define main      BLAKE3_example_main
#endif

int main(void)
{
  // Initialize the hasher.
  blake3_hasher hasher;
  blake3_hasher_init(&hasher);

  // Read input bytes from stdin.
  unsigned char buf[65536];
  while (1) {
    ssize_t n = read(STDIN_FILENO, buf, sizeof(buf));
    if (n > 0) {
      blake3_hasher_update(&hasher, buf, n);
    } else if (n == 0) {
      break; // end of file
    } else {
      fprintf(stderr, "read failed: %s\n", strerror(errno));
      return EXIT_FAILURE;
    }
  }

  // Finalize the hash. BLAKE3_OUT_LEN is the default output length, 32 bytes.
  uint8_t output[BLAKE3_OUT_LEN];
  blake3_hasher_finalize(&hasher, output, BLAKE3_OUT_LEN);

  // Print the hash as hexadecimal.
  for (size_t i = 0; i < BLAKE3_OUT_LEN; i++) {
    printf("%02x", output[i]);
  }
  printf("\n");
  return EXIT_SUCCESS;
}
