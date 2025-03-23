//
// Copyright 2020 Fellipe Augusto Ugliara
//
// Use of this source code is governed by an ISC license that can be found
// in the LICENSE file at https://github.com/ugliara-fellipe/library.toolbelt
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "datatype/list.h"
#include "datatype/pair.h"
#include "datatype/table.h"
#include "extend/crash.h"
#include "extend/inspect.h"
#include "extend/prototype.h"

inspect_t *inspect_alloc() {
  inspect_t *object = malloc(sizeof(inspect_t));
  object->nodes = calloc(1, sizeof(char));
  object->edges = calloc(1, sizeof(char));
  return object;
}

void inspect_dealloc(inspect_t *self) {
  free(self->nodes);
  free(self->edges);
  free(self);
}

static void inspect_init_graph(FILE *graph) {
  const char init[] = "digraph G {\n";
  fputs(init, graph);
}

static void inspect_exit_graph(FILE *graph) {
  const char exit[] = "}";
  fputs(exit, graph);
}

void inspect_perform(inspect_t *self, const char *snapshot) {
  int length = strlen(snapshot) + 3 + 1;
  char *snapshot_file = calloc(length, sizeof(char));
  strcat(snapshot_file, snapshot);
  strcat(snapshot_file, ".gv");

  FILE *graph = fopen(snapshot_file, "w");
  free(snapshot_file);
  if (graph == NULL) {
    crash("Cannot open graph file.");
  }

  inspect_init_graph(graph);
  fputs(self->nodes, graph);
  fputs("\n", graph);
  fputs(self->edges, graph);
  inspect_exit_graph(graph);

  if (fclose(graph) == EOF) {
    crash("Error closing destination file.");
  }
}

static void inspect_append(char **self, const char *value) {
  int length = strlen(*self) + strlen(value) + 1;
  *self = realloc(*self, sizeof(char) * length);
  strcat(*self, value);
}

void inspect_value_node(inspect_t *self, void *object, const char *value) {
  char address_str[30];
  snprintf(address_str, 30, "\"%p\"", object);
  inspect_append(&(self->nodes), "  ");
  inspect_append(&(self->nodes), address_str);
  inspect_append(&(self->nodes), " [shape=record, label=\"");
  if (context_get(object) != NULL) {
    inspect_append(&(self->nodes), context_get(object));
    inspect_append(&(self->nodes), "\\n");
  }
  inspect_append(&(self->nodes), value);
  inspect_append(&(self->nodes), " :");
  inspect_append(&(self->nodes), object_type(object));
  inspect_append(&(self->nodes), "\"];\n");
}

void inspect_pair_node(inspect_t *self, void *object) {
  char address_str[30];
  snprintf(address_str, 30, "\"%p\"", object);
  inspect_append(&(self->nodes), "  ");
  inspect_append(&(self->nodes), address_str);
  inspect_append(&(self->nodes), " [shape=record, label=\"{");
  if (context_get(object) != NULL) {
    inspect_append(&(self->nodes), context_get(object));
    inspect_append(&(self->nodes), "\\n");
  }
  pair_t *pair = (pair_t *)object;
  inspect_append(&(self->nodes), pair->key->value);
  inspect_append(&(self->nodes), " :text_t | <value> ~ :object_t");
  inspect_append(&(self->nodes), "}\"];\n");

  char address_value_str[30];
  snprintf(address_value_str, 30, "\"%p\"", pair->value);
  inspect_append(&(self->edges), "  ");
  inspect_append(&(self->edges), address_str);
  inspect_append(&(self->edges), ":value -> ");
  inspect_append(&(self->edges), address_value_str);
  inspect_append(&(self->edges), ";\n");
}

void inspect_list_node(inspect_t *self, void *object, void *list) {
  char address_str[30];
  snprintf(address_str, 30, "\"%p\"", object);
  inspect_append(&(self->nodes), "  ");
  inspect_append(&(self->nodes), address_str);
  inspect_append(&(self->nodes), " [shape=record, label=\"{");

  for (size_t index = 0; index < ((list_t *)list)->size; index++) {
    inspect_append(&(self->nodes), "<i");
    char index_str[50];
    snprintf(index_str, 50, "%zu", index);
    inspect_append(&(self->nodes), index_str);
    inspect_append(&(self->nodes), "> ");
    inspect_append(&(self->nodes), index_str);
    inspect_append(&(self->nodes), " | ");
  }
  if (context_get(object) != NULL) {
    inspect_append(&(self->nodes), context_get(object));
    inspect_append(&(self->nodes), "\\n");
  }
  inspect_append(&(self->nodes), " :");
  inspect_append(&(self->nodes), object_type(object));
  inspect_append(&(self->nodes), "}\"];\n");
}

void inspect_add_edge(inspect_t *self, void *from, const char *from_id,
                      void *to, const char *to_id) {
  char from_str[30];
  snprintf(from_str, 30, "\"%p\"", from);

  char to_str[30];
  snprintf(to_str, 30, "\"%p\"", to);

  inspect_append(&(self->edges), "  ");
  inspect_append(&(self->edges), from_str);
  if (from_id != NULL) {
    inspect_append(&(self->edges), ":");
    inspect_append(&(self->edges), from_id);
  }
  inspect_append(&(self->edges), " -> ");

  inspect_append(&(self->edges), to_str);
  if (to_id != NULL) {
    inspect_append(&(self->edges), ":");
    inspect_append(&(self->edges), to_id);
  }

  inspect_append(&(self->edges), ";\n");
}
