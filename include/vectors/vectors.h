#pragma once

#include <stdint.h>
#include <tokenizer/tokenizer.h>

typedef struct {
     char     *data;

     size_t   size;
     size_t   capacity;

} char_vector_t;

typedef struct {
     token    *data;

     size_t   size;
     size_t   capacity;

} token_vector_t;

char_vector_t      newCharVector();
void               charVectorPush(char_vector_t vector, char val);
char               charVectorPop(char_vector_t vector);
void               charVectorPopAt(char_vector_t vector, size_t index);

char               charVectorPeek(char_vector_t vector, size_t index);
