//
// Copyright 2020 Fellipe Augusto Ugliara
//
// Use of this source code is governed by an ISC license that can be found
// in the LICENSE file at https://github.com/ugliara-fellipe/library.toolbelt
//
#include "datatype/pair.h"
#include "extend/inspect.h"

static void _alloc_(pair_t *self, args_t arguments) {
  char *key = next_arg(arguments, char *);
  object_t value = next_arg(arguments, object_t);
  self->key = alloc(text_t, key);
  context_set(self->key, "key");
  self->value = value;
}

static void _free_(pair_t *self) {
  dealloc(self->key);
  dealloc(self->value);
}

static void _copy_(pair_t *self, pair_t *object) {
  object->key = copy(self->key);
  object->value = copy(self->value);
}

static bool _equal_(pair_t *self, pair_t *object) {
  return (equal(self->key, object->key) && equal(self->value, object->value));
}

static void _inspect_(pair_t *self, inspect_t *inspect) {
  inspect_pair_node(inspect, self);
  object_inspect(self->value, inspect);
}

def_prototype_source(pair_t, _alloc_, _free_, _copy_, _equal_, _inspect_);

void pair_test() {
  text_t *t1 = alloc(text_t, "value");
  pair_t *pair = alloc(pair_t, "key", t1);
  assert(type_equal(pair, "pair_t") == true);
  assert(text_compare(pair_value(text_t, pair), "value") == true);
  assert(text_compare(pair->key, "key") == true);
  dealloc(pair);
}
