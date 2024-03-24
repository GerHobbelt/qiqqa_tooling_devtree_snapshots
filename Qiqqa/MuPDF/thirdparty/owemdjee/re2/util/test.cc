// Copyright 2009 The RE2 Authors.  All Rights Reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <stdio.h>
#include <string>

#include "util/test.h"

#include "monolithic_examples.h"


namespace testing {
std::string TempDir() { return "/tmp/"; }
}  // namespace testing

struct Test {
  void (*fn)(void);
  const char *name;
};

static Test tests[10000];
static int ntests;

void RegisterTest(void (*fn)(void), const char *name) {
  tests[ntests].fn = fn;
  tests[ntests++].name = name;
}


#if defined(BUILD_MONOLITHIC)
#define main  re2_test_main
#endif

int main(void) {
  for (int i = 0; i < ntests; i++) {
    printf("%s\n", tests[i].name);
    tests[i].fn();
  }
  printf("PASS\n");
  return 0;
}
