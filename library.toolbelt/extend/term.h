//
// Copyright 2020 Fellipe Augusto Ugliara
//
// Use of this source code is governed by an ISC license that can be found
// in the LICENSE file at https://github.com/ugliara-fellipe/library.toolbelt
//
#ifndef TERM_H
#define TERM_H

#include <stdarg.h>
#include <stdio.h>

// ANSI Escape sequences

// Cursor Functions
#define term_home(line, column) "\x1B[" #line ";" #column "H"
#define term_move(line, column) "\x1B[" #line ";" #column "f"

#define term_up(line) "\x1B[" #line "A"
#define term_down(line) "\x1B[" #line "B"
#define term_forward(column) "\x1B[" #column "C"
#define term_backward(column) "\x1B[" #column "D"

// Cursor Position Functions
#define TERM_SAVE "s"
#define TERM_LOAD "u"

#define term_position(action) "\x1B[" action

// Erase Functions
#define TERM_DISPLAY "2J"
#define TERM_LINE "K"

#define term_erase(option) "\x1B[" option

// Text Attributes
#define TERM_RESET "0"
#define TERM_BOLD "1"

#define term_attr(type) "\x1B[" type "m"

// Foreground Background Colors
#define TERM_BLACK "0"
#define TERM_RED "1"
#define TERM_GREEN "2"
#define TERM_YELLOW "3"
#define TERM_BLUE "4"
#define TERM_MAGENTA "5"
#define TERM_CYAN "6"
#define TERM_WHITE "7"

#define term_foreground(color) "\x1B[3" color "m"
#define term_background(color) "\x1B[4" color "m"

void term_error(const char *format, ...);

#endif
