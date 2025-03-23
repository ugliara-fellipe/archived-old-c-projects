//
// Copyright 2020 Fellipe Augusto Ugliara
//
// Use of this source code is governed by an ISC license that can be found
// in the LICENSE file at https://github.com/ugliara-fellipe/library.toolbelt
//
#ifndef TEXT_H
#define TEXT_H

#include "extend/prototype.h"

typedef struct {
  char *value;
} text_t;

def_prototype_header(text_t);

bool text_compare(text_t *self, const char *str);
void text_append(text_t *self, const char *str);
void text_set(text_t *self, const char *str);
size_t text_size(text_t *self);
void text_reverse(text_t *self);
void text_from_int(text_t *self, int number);
void text_from_double(text_t *self, double number);
void text_from_file(text_t *self, const char *file_path_name);
bool text_contains(text_t *self, const char *str);
void text_trim(text_t *self);
void text_to_file(text_t *self, const char *file_path_name);
void text_sub(text_t *self, index_t init, size_t size);
void text_replace(text_t *self, const char *replace, const char *with);

#define text_for_split(id, str, split, part, code)                             \
  text_t *temp##id = alloc(text_t, str);                                       \
  char *save_##id;                                                             \
  char *part = strtok_r(temp##id->value, split, &(save_##id));                 \
  while (part != NULL) {                                                       \
    code;                                                                      \
    part = strtok_r(NULL, split, &(save_##id));                                \
  }                                                                            \
  dealloc(temp##id)

void text_test();

#endif
