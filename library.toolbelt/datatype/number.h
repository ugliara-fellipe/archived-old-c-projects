//
// Copyright 2020 Fellipe Augusto Ugliara
//
// Use of this source code is governed by an ISC license that can be found
// in the LICENSE file at https://github.com/ugliara-fellipe/library.toolbelt
//
#ifndef NUMBER_H
#define NUMBER_H

#include "extend/prototype.h"

typedef struct {
  double value;
} number_t;

def_prototype_header(number_t);

void number_test();

#endif
