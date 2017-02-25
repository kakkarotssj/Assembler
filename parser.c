#include "parser.h"
#include "lexer.h"
#include "opcodestream.h"
#include "tokenstream.h"
#include <stdio.h>
#include <stdlib.h>


int _P_parse_(TokenStream* ts,OpcodeStream* os)
{
    
    return 0;
}

Parser* createParser(char* contents)
{
    Parser* p = malloc(sizeof(Parser));
    p->m_contents = contents;
    
    TokenStream* tok = TSCreate();
    Lexer* lex = lexerOpen(tok,contents);
    p->m_lex = lex;
    
    Token t;
    t.kind = ENDOFFILE;
    p->m_errorToken = t;
    
    return p;
}

void tokenize(Parser* p)
{
    Token tok;
    Lexer* lexer = p->m_lex;
    do
    {
        tok = lexerNextTokenKind(lexer);
        if(tok.kind != INVALID)
            TSInsert(lexer->m_tokenStream,tok);
    }
    while ( tok.kind != INVALID );
}

char* parse(Parser* p)
{
    char * output;
    tokenize(p);
    TokenStream* ts = p->m_lex->m_tokenStream;
    OpcodeStream* os = OSCreate();
    if(!_P_parse_(ts,os))
        return parserError(p);
    
    // convert to bin using opcodeconvertor
    // output = opcodeConvertor(os);
    return output;
}


