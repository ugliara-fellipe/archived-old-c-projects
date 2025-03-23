//
// Copyright 2020 Fellipe Augusto Ugliara
//
// Use of this source code is governed by an ISC license that can be found
// in the LICENSE file at https://github.com/ugliara-fellipe/library.toolbelt
//
#include "extend/term.h"

void term_error(const char *format, ...) {
  va_list arg;
  va_start(arg, format);
  fprintf(stderr, term_foreground(TERM_RED)
                      term_attr(TERM_BOLD) "error: " term_attr(TERM_RESET));
  vfprintf(stderr, format, arg);
  va_end(arg);
}
