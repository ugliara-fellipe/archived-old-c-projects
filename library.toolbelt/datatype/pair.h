//
// Copyright 2020 Fellipe Augusto Ugliara
//
// Use of this source code is governed by an ISC license that can be found
// in the LICENSE file at https://github.com/ugliara-fellipe/library.toolbelt
//
#ifndef PAIR_H
#define PAIR_H

#include "datatype/text.h"
#include "extend/prototype.h"

typedef struct {
  text_t *key;
  object_t value;
} pair_t;

def_prototype_header(pair_t);

#define pair_value(type, pair) cast(type *, pair->value)

void pair_test();

#endif
