//
// Copyright 2020 Fellipe Augusto Ugliara
//
// Use of this source code is governed by an ISC license that can be found
// in the LICENSE file at https://github.com/ugliara-fellipe/library.toolbelt
//
#ifndef LOGIC_H
#define LOGIC_H

#include "extend/prototype.h"

typedef struct {
  bool value;
} logic_t;

def_prototype_header(logic_t);

void logic_test();

#endif
