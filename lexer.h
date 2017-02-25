#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include "opcodestream.h"
#include "tokenstream.h"
#include "tokentype.h"

typedef struct Lexer
{
    TokenStream* m_tokenStream;
    char* m_contents;
    int m_currPos;
    int m_contentSize;
} Lexer;

Lexer* lexerOpen(TokenStream* ts, char* contents);
void lexerClose(Lexer* lex);
TokenType lexerNextTokenKind(Lexer* lex);

#endif
