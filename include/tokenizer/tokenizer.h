#pragma once

#include <vectors/vectors.h>
#include <stdio.h>

#include <stdlib.h>
#include <ctype.h>

char_vector_t       *fileToCharVector(const char *path);

token_vector_t      *tokenize(char_vector_t *vector);