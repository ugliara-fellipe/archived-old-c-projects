//
// Copyright 2020 Fellipe Augusto Ugliara
//
// Use of this source code is governed by an ISC license that can be found
// in the LICENSE file at https://github.com/ugliara-fellipe/library.toolbelt
//
#ifndef LIST_H
#define LIST_H

#include "extend/prototype.h"

typedef struct node_t node_t;

typedef enum {
  LIST_HEAD = 0,
  LIST_TAIL = (SIZE_MAX - 1),
  LIST_INVALID_INDEX = SIZE_MAX
} list_flag_t;

struct node_t {
  object_t value;
  node_t *next;
};

typedef struct {
  size_t size;
  node_t *head;
  node_t *tail;
} list_t;

def_prototype_header(list_t);

void list_add(list_t *self, index_t index, object_t value);
void list_del(list_t *self, index_t index);
object_t list_extract(list_t *self, index_t index);
object_t list_get_object(list_t *self, index_t index);
#define list_get(self, type, index) cast(type *, list_get_object(self, index))

#define list_for(self, index, type, item, code)                                \
  do {                                                                         \
    node_t *node = self->head;                                                 \
    for (index_t index = 0; index < self->size; index++) {                     \
      type *item = node->value;                                                \
      code;                                                                    \
      node = node->next;                                                       \
    }                                                                          \
  } while (false)

void list_test();

#endif
