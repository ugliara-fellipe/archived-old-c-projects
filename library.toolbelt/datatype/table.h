//
// Copyright 2020 Fellipe Augusto Ugliara
//
// Use of this source code is governed by an ISC license that can be found
// in the LICENSE file at https://github.com/ugliara-fellipe/library.toolbelt
//
#ifndef TABLE_H
#define TABLE_H

#include "datatype/list.h"
#include "datatype/pair.h"
#include "extend/prototype.h"

typedef struct {
  list_t *values;
} table_t;

def_prototype_header(table_t);

void table_add(table_t *self, const char *key, object_t value);
void table_del(table_t *self, const char *key);
pair_t *table_get_pair(table_t *self, const char *key);
#define table_get(self, type, key)                                             \
  cast(type *, table_get_pair(self, key)->value)

#define table_for(self, index, type, key, value_name, code)                    \
  list_for(self->values, index, pair_t, pair, text_t *key = pair->key;         \
           type *value_name = pair->value; code)

void table_test();

#endif
