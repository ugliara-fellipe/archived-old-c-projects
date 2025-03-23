//
// Copyright 2020 Fellipe Augusto Ugliara
//
// Use of this source code is governed by an ISC license that can be found
// in the LICENSE file at https://github.com/ugliara-fellipe/library.toolbelt
//
#include "datatype/pointer.h"
#include "datatype/nil.h"
#include "extend/inspect.h"

static void _alloc_(pointer_t *self, args_t arguments) {
  object_t value = next_arg(arguments, object_t);
  if (value != NULL) {
    attach(value, &(self->value));
  } else {
    self->value = value;
  }
}

static void _free_(pointer_t *self) {
  if (self->value != NULL) {
    detach(self->value, &(self->value));
  }
}

static void _copy_(pointer_t *self, pointer_t *object) {
  if (self->value != NULL) {
    attach(self->value, &(object->value));
  } else {
    object->value = NULL;
  }
}

static bool _equal_(pointer_t *self, pointer_t *object) {
  if (self->value == object->value) {
    return true;
  }
  return false;
}

static void _inspect_(pointer_t *self, inspect_t *inspect) {
  inspect_value_node(inspect, self, "~");
  inspect_add_edge(inspect, self, NULL, self->value, NULL);
  object_inspect(self->value, inspect);
}

def_prototype_source(pointer_t, _alloc_, _free_, _copy_, _equal_, _inspect_);

object_t pointer_get(pointer_t *self) {
  if (self->value == NULL) {
    return NULL;
  }
  object_t result = self;
  while (type_equal(result, "pointer_t")) {
    result = cast(pointer_t *, result)->value;
  }
  return result;
}

void pointer_set(pointer_t *self, object_t object) {
  if (self->value != NULL) {
    detach(self->value, &(self->value));
  }
  if (object != NULL) {
    attach(object, &(self->value));
  } else {
    self->value = object;
  }
}

void pointer_test() {
  nil_t *nil = alloc(nil_t);
  nil_t *point = NULL;
  attach(nil, cast(void **, &point));
  assert(point != NULL);
  detach(nil, cast(void **, &point));
  attach(nil, cast(void **, &point));
  pointer_t *pointer1 = alloc(pointer_t, nil);
  pointer_t *pointer2 = alloc(pointer_t, nil);
  pointer_t *pointer3 = alloc(pointer_t, nil);
  assert(type_equal(pointer1, "pointer_t") == true);
  pointer_set(pointer1, nil);
  pointer_t *pointer4 = copy(pointer3);
  dealloc(pointer4);
  pointer_set(pointer3, NULL);
  pointer_t *pointer5 = copy(pointer3);
  dealloc(pointer5);
  pointer_t *pointer6 = clone(pointer3, nil);
  dealloc(pointer6);
  assert(pointer3->value == NULL);
  pointer_set(pointer3, nil);
  pointer_set(pointer3, NULL);
  assert(pointer3->value == NULL);
  pointer_set(pointer2, NULL);
  assert(pointer2->value == NULL);
  pointer_set(pointer2, nil);
  assert(pointer2->value != NULL);
  pointer_set(pointer3, nil);
  dealloc(pointer3);
  dealloc(nil);
  assert(point == NULL);
  assert(pointer1->value == NULL);
  assert(pointer2->value == NULL);
  dealloc(pointer1);
  dealloc(pointer2);
}
