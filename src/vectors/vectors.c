#include <vectors/vectors.h>

char_vector_t* newCharVector() {
    char_vector_t* vec = (char_vector_t*)malloc(sizeof(char_vector_t));

    if (!vec) {
        printf("\033[1;31mALLOCATION ERRO\033[0m: Failed to allocate memory "
               "for a char_vector\n");
        exit(1);
    }

    vec->data = NULL;

    vec->size     = 0;
    vec->capacity = 0;

    return vec;
}

char_vector_t* charVectorFromString(const char* string) {
    char_vector_t* vec = newCharVector();

    while (*string != '\0') {
        char c = *string;
        charVectorPush(vec, c);
        string++;
    }

    return vec;
}

void resetCharVector(char_vector_t* vector) {
    vector->size = 0;
}

void freeCharVector(char_vector_t* vector) {
    if (!vector) return;

    if (!vector->data) {
        free(vector);
        return;
    } else {
        free(vector->data);
        free(vector);
    }
}

void charVectorPush(char_vector_t* vector, char val) {
    if (vector->data == NULL) {
        vector->data = (char*)malloc(sizeof(char));

        vector->capacity = 1;
    } else if (vector->size >= vector->capacity) {
        vector->capacity *= 2;
        vector->data =
                (char*)realloc(vector->data, sizeof(char) * vector->capacity);
    }

    vector->data[vector->size] = val;
    vector->size++;
}

char charVectorPop(char_vector_t* vector) {
    if (vector->size > 0) {
        char c = vector->data[vector->size - 1];

        vector->size--;
        return c;
    }

    return '\0';
}

char charVectorPeek(char_vector_t* vector, size_t index) {
    if (index > vector->size) return '\0';

    return vector->data[index];
}

token_vector_t* newTokenVector() {
    token_vector_t* vec = (token_vector_t*)malloc(sizeof(token_vector_t));

    vec->data = NULL;

    vec->size     = 0;
    vec->capacity = 0;

    return vec;
}

void tokenVectorPush(token_vector_t* vector, token_t val) {
    if (vector->data == NULL) {
        vector->data = (token_t*)malloc(sizeof(token_t));

        vector->capacity = 1;
    } else if (vector->size >= vector->capacity) {
        vector->capacity *= 2;
        vector->data = (token_t*)realloc(vector->data,
                                         sizeof(token_t) * vector->capacity);
    }

    vector->data[vector->size] = val;
    vector->size++;
}

token_t tokenVectorPop(token_vector_t* vector) {
    if (vector->size > 0) {
        token_t t = vector->data[vector->size - 1];

        vector->size--;
        return t;
    }

    return (token_t){.type = KSCRIPT_TOKEN_TYPE_EOF};
}

token_t tokenVectorPeek(token_vector_t* vector, size_t index) {
    if (index > vector->size) {
        return (token_t){.type = KSCRIPT_TOKEN_TYPE_EOF};
    }

    return vector->data[index];
}

void freeTokenVector(token_vector_t* vector) {
    if (!vector) return;

    if (!vector->data) {
        free(vector);
        return;
    } else {
        free(vector->data);
        free(vector);
    }
}

ast_node_t* newNode() {
    ast_node_t* node = (ast_node_t*)malloc(sizeof(ast_node_t));

    node->left  = NULL;
    node->right = NULL;

    return node;
}

void freeNode(ast_node_t* node) {
    if (!node) return;
    if (node->lexeme && node->lexeme_owned) free(node->lexeme);

    freeNode(node->left);
    freeNode(node->right);

    free(node);
}

symbol_table_t* newSymbolTable() {
    symbol_table_t* t = (symbol_table_t*)malloc(sizeof(symbol_table_t));

    t->entries = NULL;

    t->size     = 0;
    t->capacity = 0;

    return t;
}

void freeSymbolTable(symbol_table_t* table) {
    if (!table) return;

    if (!table->entries) {
        free(table);
        return;
    } else {
        free(table->entries);
        free(table);

        return;
    }
}

void symbolTablePush(symbol_table_t* table, st_entry_t entry) {
    if (table->entries == NULL) {
        table->entries = (st_entry_t*)malloc(sizeof(st_entry_t));

        table->capacity = 1;
    } else if (table->size >= table->capacity) {
        table->capacity *= 2;
        table->entries = (st_entry_t*)realloc(table->entries,
                                         sizeof(st_entry_t) * table->capacity);
    }

    table->entries[table->size] = entry;
    table->size++;
}

st_entry_t symbolTablePop(symbol_table_t* table) {
    if (table->size > 0) {
        st_entry_t t = table->entries[table->size - 1];

        table->size--;
        return t;
    }

    return (st_entry_t){.type = KSCRIPT_ST_ENTRY_TYPE_EOF};
}

st_entry_t symbolTablePeek(symbol_table_t* table, size_t index) {
    if (index > table->size) {
        return (st_entry_t){.type = KSCRIPT_ST_ENTRY_TYPE_EOF};
    }

    return table->entries[index];
}