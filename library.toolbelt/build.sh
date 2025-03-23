#
# Copyright 2020 Fellipe Augusto Ugliara
#
# Use of this source code is governed by an ISC license that can be found 
# in the LICENSE file at https://github.com/ugliara-fellipe/library.toolbelt
#
# --------------------
#
# Run this script to deploy toolbelt library and tests
# It require clang; to install use the command:
#
#   $ sudo apt install clang
#
rm -rf ./deploy
mkdir deploy
mkdir deploy/object
mkdir deploy/include
mkdir deploy/include/datatype
mkdir deploy/include/extend

clang extend/term.c -c -I . -o deploy/object/term.o
clang extend/crash.c -c -I . -o deploy/object/crash.o
clang extend/inspect.c -c -I . -o deploy/object/inspect.o
clang extend/prototype.c -c -I . -o deploy/object/prototype.o

clang datatype/text.c -c -I . -o deploy/object/text.o
clang datatype/pair.c -c -I . -o deploy/object/pair.o
clang datatype/function.c -c -I . -o deploy/object/function.o
clang datatype/pointer.c -c -I . -o deploy/object/pointer.o
clang datatype/logic.c -c -I . -o deploy/object/logic.o
clang datatype/nil.c -c -I . -o deploy/object/nil.o
clang datatype/number.c -c -I . -o deploy/object/number.o
clang datatype/list.c -c -I . -o deploy/object/list.o
clang datatype/table.c -c -I . -o deploy/object/table.o
clang datatype/graph.c -c -I . -o deploy/object/graph.o

clang test.c deploy/object/*.o -I . -o deploy/test

cp datatype/*.h deploy/include/datatype/
cp extend/*.h deploy/include/extend/
cp toolbelt.h deploy/include/
