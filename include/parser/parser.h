#pragma once

#include <types/types.h>

ast_parent_t astParseExpression(token_vector_t *tokens);
ast_parent_t astParseTokens(token_vector_t *tokens);