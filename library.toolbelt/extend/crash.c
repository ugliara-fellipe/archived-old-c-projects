//
// Copyright 2020 Fellipe Augusto Ugliara
//
// Use of this source code is governed by an ISC license that can be found
// in the LICENSE file at https://github.com/ugliara-fellipe/library.toolbelt
//
#include "extend/crash.h"

void *crash_and_exit(const char *format, ...) {
  va_list arguments;
  va_start(arguments, format);
  vfprintf(stderr, format, arguments);
  va_end(arguments);
  exit(EXIT_FAILURE);
  return NULL;
}
