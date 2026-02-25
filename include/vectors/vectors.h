#pragma once

#include <types/types.h>
#include <stdlib.h>

#include <assert.h>
#include <stdio.h>

char_vector_t* newCharVector();
char_vector_t* charVectorFromString(const char* string);
void           resetCharVector(char_vector_t* vector);
void           freeCharVector(char_vector_t* vector);

void charVectorPush(char_vector_t* vector, char val);
char charVectorPop(char_vector_t* vector);

char charVectorPeek(char_vector_t* vector, size_t index);

token_vector_t* newTokenVector();
void            tokenVectorPush(token_vector_t* vector, token_t val);
token_t         tokenVectorPop(token_vector_t* vector);

token_t         tokenVectorPeek(token_vector_t* vector, size_t index);
void            freeTokenVector(token_vector_t* vector);

ast_node_t* newNode();
void freeNode(ast_node_t* node);