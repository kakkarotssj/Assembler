#include "lexer.h"
#include "tokenstream.h"
#include <stdlib.h>
#include <string.h>

Lexer* lexerOpen(TokenStream* ts, char* contents)
{
    Lexer* lex = malloc(sizeof(Lexer));
    lex->m_tokenStream = ts;
    lex->m_contents = contents;
    lex->m_currPos = 0;
    lex->m_contentSize = strlen(contents);
    return lex;
}

void lexerClose(Lexer* lex)
{
    TSDestroy(lex->m_tokenStream);
    free(lex);
}

TokenType lexerNextTokenKind(Lexer* lex)
{
    return INVALID;
}
