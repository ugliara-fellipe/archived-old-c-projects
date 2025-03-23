//
// Copyright 2020 Fellipe Augusto Ugliara
//
// Use of this source code is governed by an ISC license that can be found
// in the LICENSE file at https://github.com/ugliara-fellipe/library.toolbelt
//
#include "datatype/number.h"
#include "extend/inspect.h"

static void _alloc_(number_t *self, args_t arguments) {
  double value = next_arg(arguments, double);
  self->value = value;
}

static void _free_(number_t *self) {}

static void _copy_(number_t *self, number_t *object) {
  object->value = self->value;
}

static bool _equal_(number_t *self, number_t *object) {
  if (self->value == object->value) {
    return true;
  }
  return false;
}

static void _inspect_(number_t *self, inspect_t *inspect) {
  char value[50];
  snprintf(value, 50, "%.2f", self->value);
  inspect_value_node(inspect, self, value);
}

def_prototype_source(number_t, _alloc_, _free_, _copy_, _equal_, _inspect_);

void number_test() {
  number_t *number = alloc(number_t, 3.0);
  assert(type_equal(number, "number_t") == true);
  dealloc(number);
}
