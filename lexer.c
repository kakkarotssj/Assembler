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
    lex->m_line = 0;
    lex->m_pos = 0;
    lex->m_contentSize = strlen(contents);
    return lex;
}

void lexerClose(Lexer* lex)
{
    TSDestroy(lex->m_tokenStream);
    free(lex);
}

Token lexerNextTokenKind(Lexer* lex)
{
    Token t;
    t.kind = ENDOFFILE;
    char *it = &(lex->m_contents[lex->m_currPos]);
    
    if(lex->m_currPos == lex->m_contentSize)
    {
        t.kind = INVALID;
        return t;
    }
    if(*it == '\0')
    {
        lex->m_currPos++;
        return t;
    }
    
    while(*it == '\n')
    {
        it = it+1;
        lex->m_line++;
        lex->m_currPos++;
        lex->m_pos = 0;
        if(lex->m_currPos > lex->m_contentSize)
            return t;
    }
    
    while(*it == ' ')
    {
        it = it+1;
        lex->m_currPos++;
        lex->m_pos++;
        if(lex->m_currPos > lex->m_contentSize)
            return t;
    }
    
    long lineno = lex->m_line;
    long pos = lex->m_pos;
        
    if(lex->m_currPos + 2 < lex->m_contentSize && t.kind == ENDOFFILE)
    {
        // Dyadic Operations
        if(*it == 'A'&& *(it+1) == 'D' && *(it+2) == 'D')
        {
            t.kind = ADD;
            t.start = pos;
            t.end = t.start + 2;
            t.lineno = lineno;
            strcpy(t.name,"ADD");
        }
        
        else if(*it == 'C' && *(it+1) == 'M' && *(it+2) == 'P')
        {
            t.kind = CMP;
            t.start = pos;
            t.end = t.start + 2;
            t.lineno = lineno;
            strcpy(t.name,"CMP");
        }
        
        else if(*it == 'D' && *(it+1) == 'I' && *(it+2) == 'V')
        {
            t.kind = DIV;
            t.start = pos;
            t.end = t.start + 2;
            t.lineno = lineno;
            strcpy(t.name,"DIV");
        }
        
        else if(*it == 'L' && *(it+1) == 'D' && *(it+2) == 'B')
        {
            t.kind = LDB;
            t.start = pos;
            t.end = t.start + 2;
            t.lineno = lineno;
            strcpy(t.name,"LDB");
        }
        
        else if(*it == 'L' && *(it+1) == 'D' && *(it+2) == 'W')
        {
            t.kind = LDW;
            t.start = pos;
            t.end = t.start + 2;
            t.lineno = lineno;
            strcpy(t.name,"LDW");
        }
        
        else if(*it == 'M'&& *(it+1) == 'O' && *(it+2) == 'V')
        {
            t.kind = MOV;
            t.start = pos;
            t.end = t.start + 2;
            t.lineno = lineno;
            strcpy(t.name,"MOV");
        }
        
        else if(*it == 'M' && *(it+1) == 'U' && *(it+2) == 'L')
        {
            t.kind = MUL;
            t.start = pos;
            t.end = t.start + 2;
            t.lineno = lineno;
            strcpy(t.name,"MUL");
        }
        
        else if(*it == 'S' && *(it+1) == 'T' && *(it+2) == 'B')
        {
            t.kind = STB;
            t.start = pos;
            t.end = t.start + 2;
            t.lineno = lineno;
            strcpy(t.name,"STB");
        }
        
        else if(*it == 'S' && *(it+1) == 'T' && *(it+2) == 'W')
        {
            t.kind = STW;
            t.start = pos;
            t.end = t.start + 2;
            t.lineno = lineno;
            strcpy(t.name,"STW");
        }
        
        else if(*it == 'S' && *(it+1) == 'U' && *(it+2) == 'B')
        {
            t.kind = SUB;
            t.start = pos;
            t.end = t.start + 2;
            t.lineno = lineno;
            strcpy(t.name,"SUB");
        }
        
        // monadic operations
        
        else if(*it == 'C'&& *(it+1) == 'A' && *(it+2) == 'L')
        {
            t.kind = CAL;
            t.start = pos;
            t.end = t.start + 2;
            t.lineno = lineno;
            strcpy(t.name,"CAL");
        }
        
        else if(*it == 'D' && *(it+1) == 'E' && *(it+2) == 'C')
        {
            t.kind = DEC;
            t.start = pos;
            t.end = t.start + 2;
            t.lineno = lineno;
            strcpy(t.name,"DEC");
        }
        
        else if(*it == 'I' && *(it+1) == 'N' && *(it+2) == 'C')
        {
            t.kind = INC;
            t.start = pos;
            t.end = t.start + 2;
            t.lineno = lineno;
            strcpy(t.name,"INC");
        }
        
        else if(*it == 'J' && *(it+1) == 'M' && *(it+2) == 'P')
        {
            t.kind = JMP;
            t.start = pos;
            t.end = t.start + 2;
            t.lineno = lineno;
            strcpy(t.name,"JMP");
        }
        
        else if(*it == 'J' && *(it+1) == 'E' && *(it+2) == 'Q')
        {
            t.kind = JEQ;
            t.start = pos;
            t.end = t.start + 2;
            t.lineno = lineno;
            strcpy(t.name,"JEQ");
        }
        
        else if(*it == 'J'&& *(it+1) == 'N' && *(it+2) == 'E')
        {
            t.kind = JNE;
            t.start = pos;
            t.end = t.start + 2;
            t.lineno = lineno;
            strcpy(t.name,"JNE");
        }
        
        else if(*it == 'J' && *(it+1) == 'G' && *(it+2) == 'T')
        {
            t.kind = JGT;
            t.start = pos;
            t.end = t.start + 2;
            t.lineno = lineno;
            strcpy(t.name,"JGT");
        }
        
        else if(*it == 'J' && *(it+1) == 'L' && *(it+2) == 'T')
        {
            t.kind = JLT;
            t.start = pos;
            t.end = t.start + 2;
            t.lineno = lineno;
            strcpy(t.name,"JLT");
        }
        
        else if(*it == 'P' && *(it+1) == 'O' && *(it+2) == 'P')
        {
            t.kind = POP;
            t.start = pos;
            t.end = t.start + 2;
            t.lineno = lineno;
            strcpy(t.name,"POP");
        }
        
        else if(*it == 'P' && *(it+1) == 'S' && *(it+2) == 'H')
        {
            t.kind = PSH;
            t.start = pos;
            t.end = t.start + 2;
            t.lineno = lineno;
            strcpy(t.name,"PSH");
        }
        
        // 0 operands instructions
        
        else if(*it == 'H' && *(it+1) == 'L' && *(it+2) == 'T')
        {
            t.kind = HLT;
            t.start = pos;
            t.end = t.start + 2;
            t.lineno = lineno;
            strcpy(t.name,"HLT");
        }
        
        else if(*it == 'M' && *(it+1) == 'S' && *(it+2) == 'F')
        {
            t.kind = MSF;
            t.start = pos;
            t.end = t.start + 2;
            t.lineno = lineno;
            strcpy(t.name,"MSF");
        }
        
        else if(*it == 'R' && *(it+1) == 'E' && *(it+2) == 'T')
        {
            t.kind = RET;
            t.start = pos;
            t.end = t.start + 2;
            t.lineno = lineno;
            strcpy(t.name,"RET");
        }
        
        // Registers
        
        else if(*it == 'R' && *(it+1) == '1' && *(it+2) == '0')
        {
            t.kind = R10;
            t.start = pos;
            t.end = t.start + 2;
            t.lineno = lineno;
            strcpy(t.name,"R10");
        }
        
        else if(*it == 'R' && *(it+1) == '1' && *(it+2) == '1')
        {
            t.kind = R11;
            t.start = pos;
            t.end = t.start + 2;
            t.lineno = lineno;
            strcpy(t.name,"R11");
        }
        
        else if(*it == 'R' && *(it+1) == '1' && *(it+2) == '2')
        {
            t.kind = R12;
            t.start = pos;
            t.end = t.start + 2;
            t.lineno = lineno;
            strcpy(t.name,"R12");
        }
        
        else if(*it == 'R' && *(it+1) == '1' && *(it+2) == '3')
        {
            t.kind = R13;
            t.start = pos;
            t.end = t.start + 2;
            t.lineno = lineno;
            strcpy(t.name,"R13");
        }
        
        else if(*it == 'R' && *(it+1) == '1' && *(it+2) == '4')
        {
            t.kind = R14;
            t.start = pos;
            t.end = t.start + 2;
            t.lineno = lineno;
            strcpy(t.name,"R14");
        }
        
        else if(*it == 'R' && *(it+1) == '1' && *(it+2) == '5')
        {
            t.kind = R15;
            t.start = pos;
            t.end = t.start + 2;
            t.lineno = lineno;
            strcpy(t.name,"R15");
        }
        
        else if(*it == 'C' && *(it+1) == 'L' && *(it+2) == 'K')
        {
            t.kind = CLK;
            t.start = pos;
            t.end = t.start + 2;
            t.lineno = lineno;
            strcpy(t.name,"CLK");
        }
        
        else if(*it == 'M' && *(it+1) == 'K' && *(it+2) == 'Y')
        {
            t.kind = MKY;
            t.start = pos;
            t.end = t.start + 2;
            t.lineno = lineno;
            strcpy(t.name,"MKY");
        }
        
        else if(*it == 'F' && *(it+1) == 'L' && *(it+2) == 'G')
        {
            t.kind = FLG;
            t.start = pos;
            t.end = t.start + 2;
            t.lineno = lineno;
            strcpy(t.name,"FLG");
        }
    
    }
    
    if(lex->m_currPos + 1 < lex->m_contentSize && t.kind == ENDOFFILE)
    {
        // registers
        
        if(*it == 'R' && *(it+1) == '0')
        {
            t.kind = R0;
            t.start = pos;
            t.end = t.start + 1;
            t.lineno = lineno;
            strcpy(t.name,"R0");
        }
        
        else if(*it == 'R' && *(it+1) == '1')
        {
            t.kind = R1;
            t.start = pos;
            t.end = t.start + 1;
            t.lineno = lineno;
            strcpy(t.name,"R1");
        }
        
        else if(*it == 'R' && *(it+1) == '2')
        {
            t.kind = R2;
            t.start = pos;
            t.end = t.start + 1;
            t.lineno = lineno;
            strcpy(t.name,"R2");
        }
        
        else if(*it == 'R' && *(it+1) == '3')
        {
            t.kind = R3;
            t.start = pos;
            t.end = t.start + 1;
            t.lineno = lineno;
            strcpy(t.name,"R3");
        }
        
         else if(*it == 'R' && *(it+1) == '4')
        {
            t.kind = R4;
            t.start = pos;
            t.end = t.start + 1;
            t.lineno = lineno;
            strcpy(t.name,"R4");
        }
        
        else if(*it == 'R' && *(it+1) == '5')
        {
            t.kind = R5;
            t.start = pos;
            t.end = t.start + 1;
            t.lineno = lineno;
            strcpy(t.name,"R5");
        }
        
        else if(*it == 'R' && *(it+1) == '6')
        {
            t.kind = R6;
            t.start = pos;
            t.end = t.start + 1;
            t.lineno = lineno;
            strcpy(t.name,"R6");
        }
        
         else if(*it == 'R' && *(it+1) == '7')
        {
            t.kind = R7;
            t.start = pos;
            t.end = t.start + 1;
            t.lineno = lineno;
            strcpy(t.name,"R7");
        }
        
        else if(*it == 'R' && *(it+1) == '8')
        {
            t.kind = R8;
            t.start = pos;
            t.end = t.start + 1;
            t.lineno = lineno;
            strcpy(t.name,"R8");
        }
        
        else if(*it == 'R' && *(it+1) == '9')
        {
            t.kind = R9;
            t.start = pos;
            t.end = t.start + 1;
            t.lineno = lineno;
            strcpy(t.name,"R9");
        }
        
    }
    
    if(lex->m_currPos < lex->m_contentSize && t.kind == ENDOFFILE)
    {
        if(*it == '#')
        {
            t.kind = HASH;
            t.start = pos;
            t.end = t.start + 1;
            t.lineno = lineno;
            strcpy(t.name,"HASH");
        }
        
        else if(*it == '@')
        {
            t.kind = AT;
            t.start = pos;
            t.end = t.start;
            t.lineno = lineno;
            strcpy(t.name,"@");
        }
        
        else if(*it == ',')
        {
            t.kind = COMMA;
            t.start = pos;
            t.end = t.start;
            t.lineno = lineno;
            strcpy(t.name,",");
        }
    }
    
    if(t.kind == ENDOFFILE)
    {
        int counter = 0;
        char ch[10];
        
        t.start = pos;
        while(*it != ' ' || *it != '\n' || *it != '\0')
        {
            if(counter == 9)
                break;
            ch[counter++] = *it;
            it = it+1;
            pos++;
        }
        
        ch[counter] = '\0';
        
        t.kind = STRING;
        t.end = t.start + counter-1;
        t.lineno = lineno;
        strcpy(t.name,ch);
    }
    
    lex->m_pos = pos;
    lex->m_line = lineno;
    
    return t;
}
