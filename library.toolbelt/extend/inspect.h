//
// Copyright 2020 Fellipe Augusto Ugliara
//
// Use of this source code is governed by an ISC license that can be found
// in the LICENSE file at https://github.com/ugliara-fellipe/library.toolbelt
//
#ifndef INSPECT_H
#define INSPECT_H

typedef struct {
  char *nodes;
  char *edges;
} inspect_t;

inspect_t *inspect_alloc();
void inspect_dealloc(inspect_t *self);

void inspect_perform(inspect_t *self, const char *file_path_name);

void inspect_value_node(inspect_t *self, void *object, const char *value);

void inspect_pair_node(inspect_t *self, void *object);

void inspect_list_node(inspect_t *self, void *object, void *list);

void inspect_add_edge(inspect_t *self, void *from, const char *from_id,
                      void *to, const char *to_id);

#endif
