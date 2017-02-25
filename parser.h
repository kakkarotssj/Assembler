#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "tokenstream.h"

typedef struct Parser
{
    Lexer* m_lex;
    Token m_errorToken;
    char* m_contents;
} Parser;

Parser* createParser(char* contents);
char* parse(Parser* p);
char* parserError(Parser* p);
void tokenize(Parser* p);


#endif
