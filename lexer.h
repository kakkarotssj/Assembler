#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include "tokenstream.h"

typedef struct Lexer
{
    TokenStream* m_tokenStream;
    int m_currPos;
    int m_contentSize;
} Lexer;

#endif
