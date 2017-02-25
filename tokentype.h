#ifndef TOKENTYPE_H
#define TOKENTYPE_H

typedef enum TokenType{
    INVALID,
    // dyadic operations
    ADD,
    CMP,
    MOV,
    // monadic operations
    JMP,
    // 0 address operations
    HLT
} TokenType;

char* tokenText(TokenType t)
{
    // for dyadic Operations
    if(t == ADD)
        return "ADD";
    else if(t == CMP)
        return "CMP";
    else if(t == MOV)
        return "MOV";
    // for monadic Operations
    else if(t == JMP)
        return "JMP";
    //for 0 address Operations
    else if(t == HLT)
        return "HLT";
    else
        return "INVALID";
}

#endif
