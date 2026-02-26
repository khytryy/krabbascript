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
            node->type         = KSCRIPT_AST_NODE_TYPE_EOF;
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

ast_parent_t astParseTokens(token_vector_t* tokens) {
    // TODO
    ast_parent_t parent;
    size_t       index;

    ast_node_t* nodes;

    if (tokenVectorEof(tokens, 0))
        return (ast_parent_t){.type = KSCRIPT_AST_NODE_TYPE_EOF};

    if (!tokenVectorEof(tokens, 1) &&
        tokenVectorPeek(tokens, 1).type == KSCRIPT_TOKEN_TYPE_VAL) {

        index++;
        parserHandleVal(tokens, nodes, &index);
    }

    return parent;
}

symbol_table_t* createSymbolTableFromTokens(token_vector_t* tokens) {
    (void)tokens;
    symbol_table_t* t = {0};

    // TODO
    return t;
}

void parserHandleVal(token_vector_t* tokens,
                     ast_parent_t*   nodes,
                     size_t*         index) {
    if (tokenVectorEof(tokens, *index)) {
        errors_generated++;
        printf("%s:%d:%d: \033[1;31mSYNTAX ERROR\033[0m: Incomplete val "
               "statement. Expected a literal, got EOF\n");

        return;
    }

    if (tokenVectorPeek(tokens, *index).type != KSCRIPT_TOKEN_TYPE_LITERAL) {
        errors_generated++;
        printf("%s:%d:%d: \033[1;31mSYNTAX ERROR\033[0m: Expected a literal, "
               "got ");
        deTokenizeTokenKeyword(tokenVectorPeek(tokens, *index));
        printf("\n");

        return;
    }

    *index++;

    if (tokenVectorEof(tokens, *index)) {
        errors_generated++;
        printf("%s:%d:%d: \033[1;31mSYNTAX ERROR\033[0m: Incomplete val "
               "statement. Expected = or :, got EOF\n");

        return;
    }

    if (tokenVectorPeek(tokens, *index).type != KSCRIPT_TOKEN_TYPE_EQUALS ||
        KSCRIPT_TOKEN_TYPE_COLON) {

        errors_generated++;
        printf("%s:%d:%d: \033[1;31mSYNTAX ERROR\033[0m: Expected = or :, "
               "got ");

        deTokenizeTokenKeyword(tokenVectorPeek(tokens, *index));
        printf("\n");

        return;
    }

    // Handle the equals sign
    if (tokenVectorPeek(tokens, *index).type == KSCRIPT_TOKEN_TYPE_EQUALS) {
        index++;
        token_vector_t* buffer = newTokenVector();

        // Collect everything into a buffer
        while (tokenVectorPeek(tokens, *index).type != KSCRIPT_TOKEN_TYPE_SEMICOLON) {
            tokenVectorPush(buffer, tokenVectorPeek(tokens, *index));
            *index++;
        }

        size_t index_exp = 0;
        expression_t* exp = astParseExpression(buffer, &index_exp, 0.0f);

        ast_parent_t* node = newNode();
        

    }
}