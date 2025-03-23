//
// Copyright 2020 Fellipe Augusto Ugliara
//
// Use of this source code is governed by an ISC license that can be found
// in the LICENSE file at https://github.com/ugliara-fellipe/library.toolbelt
//
#include "datatype/text.h"
#include "extend/inspect.h"

static void _alloc_(text_t *self, args_t arguments) {
  char *value = next_arg(arguments, char *);
  self->value = calloc(strlen(value) + 1, sizeof(char));
  strcpy(self->value, value);
}

static void _free_(text_t *self) { free(self->value); }

static void _copy_(text_t *self, text_t *object) {
  object->value = calloc(strlen(self->value) + 1, sizeof(char));
  strcpy(object->value, self->value);
}

static bool _equal_(text_t *self, text_t *object) {
  if (strcmp(self->value, object->value)) {
    return false;
  }
  return true;
}

static void _inspect_(text_t *self, inspect_t *inspect) {
  inspect_value_node(inspect, self, self->value);
}

def_prototype_source(text_t, _alloc_, _free_, _copy_, _equal_, _inspect_);

bool text_compare(text_t *self, const char *str) {
  if (strcmp(self->value, str)) {
    return false;
  }
  return true;
}

void text_append(text_t *self, const char *str) {
  self->value = realloc(self->value,
                        (strlen(self->value) + strlen(str) + 1) * sizeof(char));
  strcat(self->value, str);
}

void text_set(text_t *self, const char *str) {
  free(self->value);
  self->value = calloc(strlen(str) + 1, sizeof(char));
  strcpy(self->value, str);
}

size_t text_size(text_t *self) { return strlen(self->value); }

void text_reverse(text_t *self) {
  text_t *temp = copy(self);
  size_t size = strlen(self->value);
  for (index_t i = 0; i < size; i++) {
    temp->value[i] = self->value[(size - 1) - i];
  }
  text_set(self, temp->value);
  dealloc(temp);
}

void text_from_int(text_t *self, int number) {
  int length = snprintf(NULL, 0, "%d", number);
  free(self->value);
  self->value = calloc(length + 1, sizeof(char));
  snprintf(self->value, length + 1, "%d", number);
}

void text_from_double(text_t *self, double number) {
  double length = snprintf(NULL, 0, "%g", number);
  free(self->value);
  self->value = calloc(length + 1, sizeof(char));
  snprintf(self->value, length + 1, "%g", number);
}

void text_from_file(text_t *self, const char *file_path_name) {
  char *content = NULL;
  long length;
  FILE *file = fopen(file_path_name, "rb");

  if (file) {
    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fseek(file, 0, SEEK_SET);
    content = malloc(length + 1);
    if (content != NULL) {
      fread(content, 1, length, file);
      content[length] = '\0';
    }
    fclose(file);
  }

  if (content != NULL) {
    text_set(self, content);
    free(content);
  }
}

bool text_contains(text_t *self, const char *str) {
  if (strstr(self->value, str) != NULL) {
    return true;
  }
  return false;
}

void text_trim(text_t *self) {
  char *init = self->value;
  while (isspace(*init)) {
    init++;
  }
  char *end = init + strlen(init);
  if (end != init) {
    end--;
    while (isspace(*end)) {
      end--;
    }
    *(end + 1) = '\0';
  }
  text_t *temp = alloc(text_t, init);
  text_set(self, temp->value);
  dealloc(temp);
}

void text_to_file(text_t *self, const char *file_path_name) {
  FILE *file = fopen(file_path_name, "wb");
  if (file != NULL) {
    fputs(self->value, file);
    fclose(file);
  }
}

void text_sub(text_t *self, index_t init, size_t size) {
  if (size > 0) {
    text_t *temp = copy(self);
    temp->value[init + size] = '\0';
    text_set(self, temp->value + init);
    dealloc(temp);
  } else {
    text_set(self, "");
  }
}

void text_replace(text_t *self, const char *replace, const char *with) {
  char *origin = self->value;
  char *result;
  index_t index, count = 0;
  size_t with_size = strlen(with);
  size_t replace_size = strlen(replace);

  for (index = 0; origin[index] != '\0'; index++) {
    if (strstr(&origin[index], replace) == &origin[index]) {
      count++;
      index += replace_size - 1;
    }
  }
  result = (char *)malloc(index + count * (with_size - replace_size) + 1);

  index = 0;
  while (*origin) {
    if (strstr(origin, replace) == origin) {
      strcpy(&result[index], with);
      index += with_size;
      origin += replace_size;
    } else {
      result[index++] = *origin++;
    }
  }

  result[index] = '\0';
  text_set(self, result);
  free(result);
}

void text_test() {
  text_t *text1 = alloc(text_t, "text1");
  context_set(text1, "test");
  assert(strcmp(context_get(text1), "test") == 0);
  assert(text_compare(text1, "text1") == true);
  text_t *text2 = copy(text1);
  assert(text_compare(text2, "text1") == true);
  text_t *text3 = clone(text2, "text3");
  context_set(text3, "test3");
  assert(strcmp(context_get(text3), "test3") == 0);
  assert(type_equal(text3, "text_t") == true);
  assert(text_compare(text3, "text3") == true);
  dealloc(text1);
  assert(text_compare(text2, "text1") == true);
  dealloc(text2);
  assert(text_compare(text3, "text3") == true);
  text_append(text3, "append");
  assert(text_compare(text3, "text3append") == true);
  text_reverse(text3);
  assert(text_compare(text3, "dneppa3txet") == true);
  text_t *text4 = alloc(text_t, "  test  ");
  text_trim(text4);
  assert(text_compare(text4, "test") == true);
  text_replace(text3, "e", "r");
  assert(text_compare(text3, "dnrppa3txrt") == true);
  dealloc(text4);
  dealloc(text3);
}
