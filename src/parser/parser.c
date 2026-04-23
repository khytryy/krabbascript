#include <parser/parser.h>

binding_power_t getBindingPower(token_type type) {
    switch (type) {
        case KSCRIPT_TOKEN_TYPE_OPEN_PAREN:
            return (binding_power_t){1.0f, 1.1f};
            break;
        case KSCRIPT_TOKEN_TYPE_CLOSED_PAREN:
            return (binding_power_t){1.0f, 1.1f};
            break;
        case KSCRIPT_TOKEN_TYPE_SBRACKET_OPEN:
            return (binding_power_t){1.0f, 1.1f};
            break;
        case KSCRIPT_TOKEN_TYPE_SBRACKET_CLOSED:
            return (binding_power_t){1.0f, 1.1f};
            break;
        case KSCRIPT_TOKEN_TYPE_DOT:
            return (binding_power_t){1.0f, 1.1f};
            break;
        case KSCRIPT_TOKEN_TYPE_ARROW:
            return (binding_power_t){1.0f, 1.1f};
            break;
        case KSCRIPT_TOKEN_TYPE_PLUS_PLUS:
            return (binding_power_t){1.0f, 1.1f};
            break;
        case KSCRIPT_TOKEN_TYPE_MINUS_MINUS:
            return (binding_power_t){1.0f, 1.1f};
            break;
        case KSCRIPT_TOKEN_TYPE_MORE_THAN:
            return (binding_power_t){10.0f, 10.1f};
            break;
        case KSCRIPT_TOKEN_TYPE_LESS_THAN:
            return (binding_power_t){10.0f, 10.1f};
            break;
        case KSCRIPT_TOKEN_TYPE_LESS_EQU:
            return (binding_power_t){10.0f, 10.1f};
            break;
        case KSCRIPT_TOKEN_TYPE_GREATER_EQU:
            return (binding_power_t){10.0f, 10.1f};
            break;
        case KSCRIPT_TOKEN_TYPE_EQUALS_EQUALS:
            return (binding_power_t){9.0f, 9.1f};
            break;
        case KSCRIPT_TOKEN_TYPE_NOT_EQU:
            return (binding_power_t){9.0f, 9.1f};
            break;
        case KSCRIPT_TOKEN_TYPE_LOGICAL_AND:
            return (binding_power_t){5.0f, 5.1f};
            break;
        case KSCRIPT_TOKEN_TYPE_LOGICAL_OR:
            return (binding_power_t){5.0f, 5.1f};
            break;
        default:
            return (binding_power_t){0.0f, 0.0f};
            break;
    }
}

ast_node_t* tokenToNode(token_t token) {
    ast_node_t* node = newNode();

    switch (token.type) {
        case KSCRIPT_TOKEN_TYPE_LITERAL:
            node->type         = KSCRIPT_AST_NODE_TYPE_LITERAL;
            node->lexeme       = strdup(token.s);
            node->lexeme_owned = true;

            break;
        case KSCRIPT_TOKEN_TYPE_BOOL_LITERAL:
            node->type = KSCRIPT_AST_NODE_TYPE_BOOL_LITERAL;

            node->lexeme       = token.b == true ? "true" : "false";
            node->lexeme_owned = false;

            break;
        case KSCRIPT_TOKEN_TYPE_STR_LITERAL:
            node->type = KSCRIPT_AST_NODE_TYPE_STR_LITERAL;

            node->lexeme       = strdup(token.s);
            node->lexeme_owned = true;

            break;
        case KSCRIPT_TOKEN_TYPE_INT_LITERAL:
            node->type = KSCRIPT_AST_NODE_TYPE_INT_LITERAL;

            char buffer[32];
            int  len = snprintf(buffer, sizeof(buffer), "%d", token.i);

            node->lexeme       = malloc(len + 1);
            node->lexeme_owned = true;

            memcpy(node->lexeme, buffer, len + 1);

            break;
        case KSCRIPT_TOKEN_TYPE_EOF:
            node->type = KSCRIPT_AST_NODE_TYPE_EOF;

            node->lexeme       = "EOF";
            node->lexeme_owned = false;

            break;
        case KSCRIPT_TOKEN_TYPE_PLUS:
            node->type = KSCRIPT_AST_NODE_TYPE_PLUS;

            node->lexeme       = "+";
            node->lexeme_owned = false;

            break;
        case KSCRIPT_TOKEN_TYPE_MINUS:
            node->type = KSCRIPT_AST_NODE_TYPE_MINUS;

            node->lexeme       = "-";
            node->lexeme_owned = false;

            break;
        case KSCRIPT_TOKEN_TYPE_STAR:
            node->type = KSCRIPT_AST_NODE_TYPE_MUL;

            node->lexeme       = "*";
            node->lexeme_owned = false;

            break;
        case KSCRIPT_TOKEN_TYPE_SLASH:
            node->type = KSCRIPT_AST_NODE_TYPE_DIV;

            node->lexeme       = "/";
            node->lexeme_owned = false;

            break;
        case KSCRIPT_TOKEN_TYPE_LOGICAL_AND:
            node->type = KSCRIPT_AST_NODE_TYPE_LOGICAL_AND;

            node->lexeme       = "&&";
            node->lexeme_owned = false;

            break;
        case KSCRIPT_TOKEN_TYPE_LOGICAL_OR:
            node->type = KSCRIPT_AST_NODE_TYPE_LOGICAL_OR;

            node->lexeme       = "||";
            node->lexeme_owned = false;

            break;
        case KSCRIPT_TOKEN_TYPE_BWISE_AND:
            node->type = KSCRIPT_AST_NODE_TYPE_BWISE_AND;

            node->lexeme       = "&";
            node->lexeme_owned = false;

            break;
        case KSCRIPT_TOKEN_TYPE_BWISE_OR:
            node->type = KSCRIPT_AST_NODE_TYPE_BWISE_OR;

            node->lexeme       = "|";
            node->lexeme_owned = false;

            break;
        case KSCRIPT_TOKEN_TYPE_BWISE_XOR:
            node->type = KSCRIPT_AST_NODE_TYPE_BWISE_XOR;

            node->lexeme       = "^";
            node->lexeme_owned = false;

            break;

        case KSCRIPT_TOKEN_TYPE_STR:
            node->type = KSCRIPT_AST_NODE_TYPE_STR_TYPE;

            node->lexeme       = "str";
            node->lexeme_owned = false;

            break;

        case KSCRIPT_TOKEN_TYPE_I64:
            node->type = KSCRIPT_AST_NODE_TYPE_I64_TYPE;

            node->lexeme       = "i64";
            node->lexeme_owned = false;

            break;

        case KSCRIPT_TOKEN_TYPE_I32:
            node->type = KSCRIPT_AST_NODE_TYPE_I32_TYPE;

            node->lexeme       = "i32";
            node->lexeme_owned = false;

            break;

        case KSCRIPT_TOKEN_TYPE_I16:
            node->type = KSCRIPT_AST_NODE_TYPE_I16_TYPE;

            node->lexeme       = "i16";
            node->lexeme_owned = false;

            break;

        case KSCRIPT_TOKEN_TYPE_I8:
            node->type = KSCRIPT_AST_NODE_TYPE_I8_TYPE;

            node->lexeme       = "i8";
            node->lexeme_owned = false;

            break;

        case KSCRIPT_TOKEN_TYPE_U64:
            node->type = KSCRIPT_AST_NODE_TYPE_U64_TYPE;

            node->lexeme       = "u64";
            node->lexeme_owned = false;

            break;

        case KSCRIPT_TOKEN_TYPE_U32:
            node->type = KSCRIPT_AST_NODE_TYPE_U32_TYPE;

            node->lexeme       = "u32";
            node->lexeme_owned = false;

            break;

        case KSCRIPT_TOKEN_TYPE_U16:
            node->type = KSCRIPT_AST_NODE_TYPE_U16_TYPE;

            node->lexeme       = "u16";
            node->lexeme_owned = false;

            break;

        case KSCRIPT_TOKEN_TYPE_U8:
            node->type = KSCRIPT_AST_NODE_TYPE_U8_TYPE;

            node->lexeme       = "u8";
            node->lexeme_owned = false;

            break;

        case KSCRIPT_TOKEN_TYPE_F64:
            node->type = KSCRIPT_AST_NODE_TYPE_F64_TYPE;

            node->lexeme       = "f64";
            node->lexeme_owned = false;

            break;

        case KSCRIPT_TOKEN_TYPE_F32:
            node->type = KSCRIPT_AST_NODE_TYPE_F32_TYPE;

            node->lexeme       = "f32";
            node->lexeme_owned = false;

            break;

        case KSCRIPT_TOKEN_TYPE_BOOL:
            node->type = KSCRIPT_AST_NODE_TYPE_BOOL_TYPE;

            node->lexeme       = "bool";
            node->lexeme_owned = false;

            break;

        case KSCRIPT_TOKEN_TYPE_PTR:
            node->type = KSCRIPT_AST_NODE_TYPE_PTR_TYPE;

            node->lexeme       = "ptr";
            node->lexeme_owned = false;

            break;

        default:
            errors_generated++;
            printf("\033[1;31mERROR\033[0m: Unexpected token ");
            deTokenizeTokenKeyword(token);

            node->type = KSCRIPT_AST_NODE_TYPE_NONE;

            break;
    }

    return node;
}

expression_t*
astParseExpression(token_vector_t* tokens, size_t* index, float min_bp) {
    ast_node_t* lhs = tokenToNode(tokenVectorPeek(tokens, *index));
    (*index)++;

    while (true) {
        token_t op = tokenVectorPeek(tokens, *index);
        if (op.type == KSCRIPT_TOKEN_TYPE_EOF) break;

        binding_power_t bp =
                getBindingPower(tokenVectorPeek(tokens, *index).type);

        if (bp.left < min_bp) break;

        (*index)++;
        ast_node_t* op_node = tokenToNode(op);

        ast_node_t* rhs = astParseExpression(tokens, index, bp.right);

        op_node->left  = lhs;
        op_node->right = rhs;

        lhs = op_node;
    }
    return lhs;
}

ast_parent_t* astParseTokens(token_vector_t* tokens, char* source_file) {
    ast_parent_t* parent = newNode();
    size_t        index  = 0;

    if (tokenVectorEof(tokens, 0)) {
        parent->type = KSCRIPT_AST_NODE_TYPE_EOF;
        return parent;
    }

    // Parse val statement
    if (!tokenVectorEof(tokens, index) &&
        tokenVectorPeek(tokens, index).type == KSCRIPT_TOKEN_TYPE_VAL) {

        index++;
        ast_parent_t* parent = parserHandleVal(tokens, &index, source_file);

        // So this causes the segfault because we're trying to access memory
        // that we didn't allocate...
        parserDumpNode(parent, 0);
    }

    // TODO: Parse var statement

    return parent;
}

symbol_table_t* createSymbolTableFromTokens(token_vector_t* tokens) {
    (void)tokens;
    symbol_table_t* t = {0};

    // TODO
    return t;
}

ast_parent_t*
parserHandleVal(token_vector_t* tokens, size_t* index, char* source_file) {
    if (tokenVectorEof(tokens, *index)) {
        errors_generated++;
        printf("%s:%d:%d: \033[1;31mSYNTAX ERROR\033[0m: Incomplete val "
               "statement. Expected a literal, got EOF\n",
               source_file,
               tokenVectorPeek(tokens, *index).line,
               tokenVectorPeek(tokens, *index).col);

        return newNode();
    }

    if (tokenVectorPeek(tokens, *index).type != KSCRIPT_TOKEN_TYPE_LITERAL) {
        errors_generated++;
        printf("%s:%d:%d: \033[1;31mSYNTAX ERROR\033[0m: Expected a literal, "
               "got ",
               source_file,
               tokenVectorPeek(tokens, *index).line,
               tokenVectorPeek(tokens, *index).col);
        deTokenizeTokenKeyword(tokenVectorPeek(tokens, *index));
        printf("\n");

        return newNode();
    }

    token_t ident = tokenVectorPeek(tokens, *index);
    (*index)++;

    if (tokenVectorEof(tokens, *index)) {
        errors_generated++;
        printf("%s:%d:%d: \033[1;31mSYNTAX ERROR\033[0m: Incomplete val "
               "statement. Expected = or :, got EOF\n",
               source_file,
               tokenVectorPeek(tokens, *index).line,
               tokenVectorPeek(tokens, *index).col);

        return newNode();
    }

    if (!tokenVectorEof(tokens, *index) &&
        tokenVectorPeek(tokens, *index).type != KSCRIPT_TOKEN_TYPE_EQUALS &&
        tokenVectorPeek(tokens, *index).type != KSCRIPT_TOKEN_TYPE_COLON) {

        errors_generated++;
        printf("%s:%d:%d: \033[1;31mSYNTAX ERROR\033[0m: Expected = or :, "
               "got ",
               source_file,
               tokenVectorPeek(tokens, *index).line,
               tokenVectorPeek(tokens, *index).col);

        deTokenizeTokenKeyword(tokenVectorPeek(tokens, *index));
        printf("\n");

        return newNode();
    }

    // Handle the equals sign
    if (!tokenVectorEof(tokens, *index) &&
        tokenVectorPeek(tokens, *index).type == KSCRIPT_TOKEN_TYPE_EQUALS) {
        (*index)++;
        token_vector_t* buffer = newTokenVector();

        if (tokenVectorEof(tokens, *index)) {
            errors_generated++;
            printf("%s:%d:%d: \033[1;31mSYNTAX ERROR\033[0m: Expected "
                   "expression, "
                   "got EOF\n",
                   source_file,
                   tokenVectorPeek(tokens, *index).line,
                   tokenVectorPeek(tokens, *index).col);

            return newNode();
        }

        // Collect everything into a buffer
        while (tokenVectorPeek(tokens, *index).type !=
                       KSCRIPT_TOKEN_TYPE_SEMICOLON &&
               !tokenVectorEof(tokens, *index)) {
            tokenVectorPush(buffer, tokenVectorPeek(tokens, *index));
            (*index)++;
        }

        size_t        index_exp = 0;
        expression_t* exp       = astParseExpression(buffer, &index_exp, 0.0f);

        ast_parent_t* node = newNode();
        node->type         = KSCRIPT_AST_NODE_TYPE_VALUE_DEC;
        node->lexeme       = strdup(ident.s);
        node->lexeme_owned = true;

        node->left  = exp;
        node->right = newNode();
        return node;
    }

    // Handle the colon sign
    if (!tokenVectorEof(tokens, *index) &&
        tokenVectorPeek(tokens, *index).type == KSCRIPT_TOKEN_TYPE_COLON) {
        (*index)++;
        if (tokenVectorEof(tokens, *index)) {
            errors_generated++;
            printf("%s:%d:%d: \033[1;31mERROR\033[0m: Incomplete val "
                   "statement, expected "
                   "a type, got EOF\n",
                   source_file,
                   tokenVectorPeek(tokens, *index).line,
                   tokenVectorPeek(tokens, *index).col);

            return newNode();
        }
        if (!parserIsType(tokenVectorPeek(tokens, *index))) {
            errors_generated++;
            printf("%s:%d:%d: \033[1;31mERROR\033[0m: Expected a type, got ",
                   source_file,
                   tokenVectorPeek(tokens, *index).line,
                   tokenVectorPeek(tokens, *index).col);

            deTokenizeTokenKeyword(tokenVectorPeek(tokens, *index));
            printf("\n");

            return newNode();
        }

        token_t type = tokenVectorPeek(tokens, *index);

        (*index)++;

        if (tokenVectorEof(tokens, *index)) {
            errors_generated++;
            printf("%s:%d:%d: \033[1;31mERROR\033[0m: Expected =, got EOF\n",
                   source_file,
                   tokenVectorPeek(tokens, *index).line,
                   tokenVectorPeek(tokens, *index).col);
            return newNode();
        }

        if (!tokenVectorEof(tokens, *index) &&
            tokenVectorPeek(tokens, *index).type != KSCRIPT_TOKEN_TYPE_EQUALS) {
            errors_generated++;
            printf("%s:%d:%d: \033[1;31mERROR\033[0m: Expected =, got ",
                   source_file,
                   tokenVectorPeek(tokens, *index).line,
                   tokenVectorPeek(tokens, *index).col);

            deTokenizeTokenKeyword(tokenVectorPeek(tokens, *index));
            printf("\n");

            return newNode();
        }

        (*index)++;

        token_vector_t* buffer = newTokenVector();

        size_t offset = 0;
        while (tokenVectorPeek(tokens, *index).type !=
                       KSCRIPT_TOKEN_TYPE_SEMICOLON &&
               !tokenVectorEof(tokens, *index)) {
            tokenVectorPush(buffer, tokenVectorPeek(tokens, *index));

            (*index)++;
            offset++;
        }

        size_t        index_exp = 0;
        expression_t* exp       = astParseExpression(buffer, &index_exp, 0.0f);

        ast_parent_t* node = newNode();
        // Type
        node->right = tokenToNode(type);

        node->type         = KSCRIPT_AST_NODE_TYPE_VALUE_DEC;
        node->lexeme       = strdup(ident.s);
        node->lexeme_owned = true;

        node->left = exp;
        return node;
    }

    return newNode();
}

bool parserIsType(token_t token) {
    // Check if its a built-in type
    switch (token.type) {
        case KSCRIPT_TOKEN_TYPE_I16:
            return true;
            break;

        case KSCRIPT_TOKEN_TYPE_I8:
            return true;
            break;

        case KSCRIPT_TOKEN_TYPE_I32:
            return true;
            break;

        case KSCRIPT_TOKEN_TYPE_I64:
            return true;
            break;

        case KSCRIPT_TOKEN_TYPE_U8:
            return true;
            break;

        case KSCRIPT_TOKEN_TYPE_U16:
            return true;
            break;

        case KSCRIPT_TOKEN_TYPE_U32:
            return true;
            break;

        case KSCRIPT_TOKEN_TYPE_U64:
            return true;
            break;

        case KSCRIPT_TOKEN_TYPE_STR:
            return true;
            break;

        case KSCRIPT_TOKEN_TYPE_BOOL:
            return true;

        default:
            return false;
            break;
    }
}

void parserPrintNodeType(ast_node_t* node) {
    switch (node->type) {
        case KSCRIPT_AST_NODE_TYPE_DIV:
            printf("Div");
            break;
        case KSCRIPT_AST_NODE_TYPE_MUL:
            printf("Mul");
            break;
        case KSCRIPT_AST_NODE_TYPE_PLUS:
            printf("Plus");
            break;
        case KSCRIPT_AST_NODE_TYPE_MINUS:
            printf("Minus");
            break;

        case KSCRIPT_AST_NODE_TYPE_LOGICAL_AND:
            printf("LogicalAnd");
            break;
        case KSCRIPT_AST_NODE_TYPE_LOGICAL_OR:
            printf("LogicalOr");
            break;
        case KSCRIPT_AST_NODE_TYPE_LOGICAL_NOT:
            printf("LogicalNot");
            break;

        case KSCRIPT_AST_NODE_TYPE_BWISE_AND:
            printf("BitwiseAnd");
            break;
        case KSCRIPT_AST_NODE_TYPE_BWISE_OR:
            printf("BitwiseOr");
            break;
        case KSCRIPT_AST_NODE_TYPE_BWISE_XOR:
            printf("BitwiseXor");
            break;
        case KSCRIPT_AST_NODE_TYPE_BWISE_NOT:
            printf("BitwiseNot");
            break;

        case KSCRIPT_AST_NODE_TYPE_VARIABLE_DEC:
            printf("VariableDec");
            break;
        case KSCRIPT_AST_NODE_TYPE_VALUE_DEC:
            printf("ValueDec");
            break;
        case KSCRIPT_AST_NODE_TYPE_FUNCTION_DEC:
            printf("FunctionDec");
            break;
        case KSCRIPT_AST_NODE_TYPE_FUNCTION_DEF:
            printf("FunctionDef");
            break;

        case KSCRIPT_AST_NODE_TYPE_LITERAL:
            printf("Literal");
            break;
        case KSCRIPT_AST_NODE_TYPE_BOOL_LITERAL:
            printf("BoolLiteral");
            break;
        case KSCRIPT_AST_NODE_TYPE_STR_LITERAL:
            printf("StrLiteral");
            break;
        case KSCRIPT_AST_NODE_TYPE_INT_LITERAL:
            printf("IntLiteral");
            break;

        case KSCRIPT_AST_NODE_TYPE_STR_TYPE:
            printf("StrType");
            break;
        case KSCRIPT_AST_NODE_TYPE_PTR_TYPE:
            printf("PtrType");
            break;
        case KSCRIPT_AST_NODE_TYPE_BOOL_TYPE:
            printf("BoolType");
            break;

        case KSCRIPT_AST_NODE_TYPE_I64_TYPE:
            printf("i64");
            break;
        case KSCRIPT_AST_NODE_TYPE_I32_TYPE:
            printf("i32");
            break;
        case KSCRIPT_AST_NODE_TYPE_I16_TYPE:
            printf("i16");
            break;
        case KSCRIPT_AST_NODE_TYPE_I8_TYPE:
            printf("i8");
            break;

        case KSCRIPT_AST_NODE_TYPE_U64_TYPE:
            printf("u64");
            break;
        case KSCRIPT_AST_NODE_TYPE_U32_TYPE:
            printf("u32");
            break;
        case KSCRIPT_AST_NODE_TYPE_U16_TYPE:
            printf("u16");
            break;
        case KSCRIPT_AST_NODE_TYPE_U8_TYPE:
            printf("u8");
            break;

        case KSCRIPT_AST_NODE_TYPE_F64_TYPE:
            printf("f64");
            break;
        case KSCRIPT_AST_NODE_TYPE_F32_TYPE:
            printf("f32");
            break;

        case KSCRIPT_AST_NODE_TYPE_NONE:
            printf("None");
            break;
        case KSCRIPT_AST_NODE_TYPE_EOF:
            printf("EOF");
            break;

        default:
            printf("???");
            break;
    }
}

void parserDumpNode(ast_parent_t* parent, int depth) {
    if (parent == NULL) return;

    for (int i = 0; i < depth; i++)
        printf("    ");

    printf("Node: ");
    parserPrintNodeType(parent);
    printf("\n");

    for (int i = 0; i < depth; i++)
        printf("    ");
    printf("    - col: %d\n", parent->col);

    for (int i = 0; i < depth; i++)
        printf("    ");
    printf("    - lexeme: %s\n", parent->lexeme);

    for (int i = 0; i < depth; i++)
        printf("    ");
    printf("    - lexeme_owned: %s\n", parent->lexeme_owned ? "true" : "false");

    for (int i = 0; i < depth; i++)
        printf("    ");
    printf("    - line: %d\n", parent->line);

    parserDumpNode(parent->left, depth + 1);
    parserDumpNode(parent->right, depth + 1);
}