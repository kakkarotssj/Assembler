#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "tokenstream.h"
#include "opcodestream.h"

typedef struct Parser
{
    Lexer* m_lex;
    Token m_errorToken;
    OpcodeStream* m_os;
    char* m_contents;
    long m_errorIns;
} Parser;

Parser* createParser(char* contents,int debug);
void parseOPCode(Parser* p,char* output);
char* parserError(Parser* p,long* line, long* pos,long* ins);
void tokenize(Parser* p);
void createParserError(Parser* p, Token t);
int parserContainsError(Parser* p);
void destroyParser(Parser* p);
#endif
