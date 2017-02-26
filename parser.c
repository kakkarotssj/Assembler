#include "parser.h"
#include "lexer.h"
#include "opcodestream.h"
#include "tokenstream.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parserdebug = 1;

int isGPRegister(TokenType t)
{
    if(t == R0 || t == R1 || t == R2 || t == R3 || t == R4
        || t == R5 || t == R6 || t == R7 || t == R8 || t == R9 
        || t == R10 || t == R11 || t == R12 || t == R13 
        || t == R14 || t == R15)
        return 1;
    return 0;
}
int isSPRegister(TokenType t)
{
    if(t == FLG || t == CLK || t == MKY )
        return 1;
    return 0;
}

OpcodeType OTForReg(TokenType t)
{
    if(t == R0)
        return GPR0;
    if(t == R1)
        return GPR1;
    if(t == R2)
        return GPR2;
    if(t == R3)
        return GPR3;
    if(t == R4)
        return GPR4;
    if(t == R5)
        return GPR5;
    if(t == R6)
        return GPR6;
    if(t == R7)
        return GPR7;
    if(t == R8)
        return GPR8;
    if(t == R9)
        return GPR9;
    if(t == R10)
        return GPR10;
    if(t == R12)
        return GPR12;
    if(t == R13)
        return GPR13;
    if(t == R14)
        return GPR14;
    if(t == R15)
        return GPR15;
    if(t == CLK)
        return SPCLK;
    if(t == MKY)
        return SPMKY;
    if(t == FLG)
        return SPFLG;

    else return STRINGVAL;
}

int isInteger(char* arr)
{
    int len = strlen(arr);
    int i = 0;
    for(;i<len;i++)
    {
        if(arr[i] < 48 || arr[i] > 57)
            return 0;
    }
    return 1;
}

int _P_parse_(Parser* p,TokenStream* ts,OpcodeStream* os)
{
    if (TSSize(ts) == 0)
    {
        createParserError(p,p->m_errorToken);
        return 0;
    }
    TokenType token = TSStep(ts);
    long ins = 0;
    while(token != ENDOFFILE)
    {
        ins++;
        
        // dyadic instaructions
        if(token == INVALID)
            break;
        if(token == ADD)
        {
            if(isGPRegister(TSLA(ts,1)) && TSLA(ts,2) == COMMA && TSLA(ts,3) == HASH && TSLA(ts,4) == STRING )
                OSInsert(os,ADD0,TSToken(ts).name);
            else if(isGPRegister(TSLA(ts,1)) && TSLA(ts,2) == COMMA && ( isGPRegister(TSLA(ts,3)) || isSPRegister(TSLA(ts,3))))
                OSInsert(os,ADD1,TSToken(ts).name);
            else
                p->m_errorIns = ins;
            token = TSStep(ts);
            if(isGPRegister(token))
            {
                OSInsert(os,OTForReg(token),TSToken(ts).name);
                token = TSStep(ts);
                if(token == COMMA)
                {
                    token = TSStep(ts);
                    if(isGPRegister(token))
                    {
                        OSInsert(os,OTForReg(token),TSToken(ts).name);
                    }
                    else if(isSPRegister(token))
                    {
                        OSInsert(os,OTForReg(token),TSToken(ts).name);
                    }
                    else if(token == HASH)
                    {
                        token = TSStep(ts);
                        if(token == STRING)
                        {
                            if(isInteger(TSToken(ts).name))
                                OSInsert(os,INTEGER,TSToken(ts).name);
                            else
                            {
                                createParserError(p,TSToken(ts));
                                return 0;
                            }
                        }
                        else
                        {
                            createParserError(p,TSToken(ts));
                            return 0;
                        }
                    }
                    else
                    {
                        createParserError(p,TSToken(ts));
                        return 0;
                    }
                }
                else
                {
                    createParserError(p,TSToken(ts));
                    return 0;
                }
            }
            else
            {
                createParserError(p,TSToken(ts));
                return 0;
            }
        }
        else if(token == CMP)
        {
            if(isGPRegister(TSLA(ts,1)) && TSLA(ts,2) == COMMA && TSLA(ts,3) == HASH && TSLA(ts,4) == STRING)
                OSInsert(os,CMP0,TSToken(ts).name);
            else if(isGPRegister(TSLA(ts,1)) && TSLA(ts,2) == COMMA && ( isGPRegister(TSLA(ts,3)) || isSPRegister(TSLA(ts,3))))
                OSInsert(os,CMP1,TSToken(ts).name);
            else
                p->m_errorIns = ins;
            token = TSStep(ts);
            if(isGPRegister(token))
            {
                OSInsert(os,OTForReg(token),TSToken(ts).name);
                token = TSStep(ts);
                if(token == COMMA)
                {
                    token = TSStep(ts);
                    if(isGPRegister(token))
                    {
                        OSInsert(os,OTForReg(token),TSToken(ts).name);
                    }
                    else if(isSPRegister(token))
                    {
                        OSInsert(os,OTForReg(token),TSToken(ts).name);
                    }
                    else if(token == HASH)
                    {
                        token = TSStep(ts);
                        if(token == STRING)
                        {
                            if(isInteger(TSToken(ts).name))
                                OSInsert(os,INTEGER,TSToken(ts).name);
                            else
                            {
                                p->m_errorIns = ins;
                                createParserError(p,TSToken(ts));
                                return 0;
                            }
                        }
                        else
                        {
                            createParserError(p,TSToken(ts));
                            return 0;
                        }
                    }
                    else
                    {
                        createParserError(p,TSToken(ts));
                        return 0;
                    }
                }
                else
                {
                    createParserError(p,TSToken(ts));
                    return 0;
                }
            }
            else
            {
                createParserError(p,TSToken(ts));
                return 0;
            }
        }
        else if(token == DIV)
        {
            if(isGPRegister(TSLA(ts,1)) && TSLA(ts,2) == COMMA && TSLA(ts,3) == HASH && TSLA(ts,4) == STRING)
                OSInsert(os,DIV0,TSToken(ts).name);
            else if(isGPRegister(TSLA(ts,1)) && TSLA(ts,2) == COMMA && ( isGPRegister(TSLA(ts,3)) || isSPRegister(TSLA(ts,3))))
                OSInsert(os,DIV1,TSToken(ts).name);
            else
                p->m_errorIns = ins;
            token = TSStep(ts);
            if(isGPRegister(token))
            {
                OSInsert(os,OTForReg(token),TSToken(ts).name);
                token = TSStep(ts);
                if(token == COMMA)
                {
                    token = TSStep(ts);
                    if(isGPRegister(token))
                    {
                        OSInsert(os,OTForReg(token),TSToken(ts).name);
                    }
                    else if(isSPRegister(token))
                    {
                        OSInsert(os,OTForReg(token),TSToken(ts).name);
                    }
                    else if(token == HASH)
                    {
                        token = TSStep(ts);
                        if(token == STRING)
                        {
                            if(isInteger(TSToken(ts).name))
                                OSInsert(os,INTEGER,TSToken(ts).name);
                            else
                            {
                                p->m_errorIns = ins;
                                createParserError(p,TSToken(ts));
                                return 0;
                            }
                        }
                        else
                        {
                            createParserError(p,TSToken(ts));
                            return 0;
                        }
                    }
                    else
                    {
                        createParserError(p,TSToken(ts));
                        return 0;
                    }
                }
                else
                {
                    createParserError(p,TSToken(ts));
                    return 0;
                }
            }
            else
            {
                createParserError(p,TSToken(ts));
                return 0;
            }
        }
        else if(token == LDB)
        {
            if(isGPRegister(TSLA(ts,1)) && TSLA(ts,2) == COMMA && TSLA(ts,3) == STRING)
                OSInsert(os,LDB0,TSToken(ts).name);
            else if(isGPRegister(TSLA(ts,1)) && TSLA(ts,2) == COMMA && TSLA(ts,3) == AT && ( isGPRegister(TSLA(ts,4)) || isSPRegister(TSLA(ts,4))))
                OSInsert(os,LDB1,TSToken(ts).name);
            else
                p->m_errorIns = ins;
            token = TSStep(ts);
            if(isGPRegister(token))
            {
                OSInsert(os,OTForReg(token),TSToken(ts).name);
                token = TSStep(ts);
                if(token == COMMA)
                {
                    token = TSStep(ts);
                    if(token == STRING)
                    {
                        if(isInteger(TSToken(ts).name))
                            OSInsert(os,INTEGER,TSToken(ts).name);
                        else
                        {
                            p->m_errorIns = ins;
                            createParserError(p,TSToken(ts));
                            return 0;
                        }
                    }
                    else if(token == AT)
                    {
                        token = TSStep(ts);
                        if(isGPRegister(token))
                        {
                            OSInsert(os,OTForReg(token),TSToken(ts).name);
                        }
                        else if(isSPRegister(token))
                        {
                            OSInsert(os,OTForReg(token),TSToken(ts).name);
                        }
                        else
                        {
                            createParserError(p,TSToken(ts));
                            return 0;
                        }
                    }
                    else
                    {
                        createParserError(p,TSToken(ts));
                        return 0;
                    }
                }
                else
                {
                    createParserError(p,TSToken(ts));
                    return 0;
                }
            }
            else
            {
                createParserError(p,TSToken(ts));
                return 0;
            }
        }
        else if(token == LDW)
        {
            if(isGPRegister(TSLA(ts,1)) && TSLA(ts,2) == COMMA && TSLA(ts,3) == STRING)
                OSInsert(os,LDW0,TSToken(ts).name);
            else if(isGPRegister(TSLA(ts,1)) && TSLA(ts,2) == COMMA && TSLA(ts,3) == AT && ( isGPRegister(TSLA(ts,4)) || isSPRegister(TSLA(ts,4))))
                OSInsert(os,LDW1,TSToken(ts).name);
            else
                p->m_errorIns = ins;
            token = TSStep(ts);
            if(isGPRegister(token))
            {
                OSInsert(os,OTForReg(token),TSToken(ts).name);
                token = TSStep(ts);
                if(token == COMMA)
                {
                    token = TSStep(ts);
                    if(token == STRING)
                    {
                        if(isInteger(TSToken(ts).name))
                            OSInsert(os,INTEGER,TSToken(ts).name);
                        else
                        {
                            p->m_errorIns = ins;
                            createParserError(p,TSToken(ts));
                            return 0;
                        }
                    }
                    else if(token == AT)
                    {
                        token = TSStep(ts);
                        if(isGPRegister(token))
                        {
                            OSInsert(os,OTForReg(token),TSToken(ts).name);
                        }
                        else if(isSPRegister(token))
                        {
                            OSInsert(os,OTForReg(token),TSToken(ts).name);
                        }
                        else
                        {
                            createParserError(p,TSToken(ts));
                            return 0;
                        }
                    }
                    else
                    {
                        createParserError(p,TSToken(ts));
                        return 0;
                    }
                }
                else
                {
                    createParserError(p,TSToken(ts));
                    return 0;
                }
            }
            else
            {
                createParserError(p,TSToken(ts));
                return 0;
            }
        }
        else if(token == MOV)
        {
            if(isGPRegister(TSLA(ts,1)) && TSLA(ts,2) == COMMA && TSLA(ts,3) == HASH && TSLA(ts,4) == STRING)
                OSInsert(os,MOV0,TSToken(ts).name);
            else if(isGPRegister(TSLA(ts,1)) && TSLA(ts,2) == COMMA && ( isGPRegister(TSLA(ts,3)) || isSPRegister(TSLA(ts,3))))
                OSInsert(os,MOV1,TSToken(ts).name);
            else
                p->m_errorIns = ins;
            token = TSStep(ts);
            if(isGPRegister(token))
            {
                OSInsert(os,OTForReg(token),TSToken(ts).name);
                token = TSStep(ts);
                if(token == COMMA)
                {
                    token = TSStep(ts);
                    if(isGPRegister(token))
                    {
                        OSInsert(os,OTForReg(token),TSToken(ts).name);
                    }
                    else if(isSPRegister(token))
                    {
                        OSInsert(os,OTForReg(token),TSToken(ts).name);
                    }
                    else if(token == HASH)
                    {
                        token = TSStep(ts);
                        if(token == STRING)
                        {
                            if(isInteger(TSToken(ts).name))
                                OSInsert(os,INTEGER,TSToken(ts).name);
                            else
                            {
                                p->m_errorIns = ins;
                                createParserError(p,TSToken(ts));
                                return 0;
                            }
                        }
                        else
                        {
                            createParserError(p,TSToken(ts));
                            return 0;
                        }
                    }
                    else
                    {
                        createParserError(p,TSToken(ts));
                        return 0;
                    }
                }
                else
                {
                    createParserError(p,TSToken(ts));
                    return 0;
                }
            }
            else
            {
                createParserError(p,TSToken(ts));
                return 0;
            }
        }
        else if(token == MUL)
        {
            if(isGPRegister(TSLA(ts,1)) && TSLA(ts,2) == COMMA && TSLA(ts,3) == HASH && TSLA(ts,4) == STRING)
                OSInsert(os,MUL0,TSToken(ts).name);
            else if(isGPRegister(TSLA(ts,1)) && TSLA(ts,2) == COMMA && ( isGPRegister(TSLA(ts,3)) || isSPRegister(TSLA(ts,3))))
                OSInsert(os,MUL1,TSToken(ts).name);
            else
                p->m_errorIns = ins;
            token = TSStep(ts);
            if(isGPRegister(token))
            {
                OSInsert(os,OTForReg(token),TSToken(ts).name);
                token = TSStep(ts);
                if(token == COMMA)
                {
                    token = TSStep(ts);
                    if(isGPRegister(token))
                    {
                        OSInsert(os,OTForReg(token),TSToken(ts).name);
                    }
                    else if(isSPRegister(token))
                    {
                        OSInsert(os,OTForReg(token),TSToken(ts).name);
                    }
                    else if(token == HASH)
                    {
                        token = TSStep(ts);
                        if(token == STRING)
                        {
                            if(isInteger(TSToken(ts).name))
                                OSInsert(os,INTEGER,TSToken(ts).name);
                            else
                            {
                                p->m_errorIns = ins;
                                createParserError(p,TSToken(ts));
                                return 0;
                            }
                        }
                        else
                        {
                            createParserError(p,TSToken(ts));
                            return 0;
                        }
                    }
                    else
                    {
                        createParserError(p,TSToken(ts));
                        return 0;
                    }
                }
                else
                {
                    createParserError(p,TSToken(ts));
                    return 0;
                }
            }
            else
            {
                createParserError(p,TSToken(ts));
                return 0;
            }
        }
        else if(token == STB)
        {
            if(TSLA(ts,1) == STRING && TSLA(ts,2) == COMMA && ( isGPRegister(TSLA(ts,3)) || isSPRegister(TSLA(ts,3))))
                OSInsert(os,STB0,TSToken(ts).name);
            else if(TSLA(ts,1) == AT && ( isGPRegister(TSLA(ts,2)) || isSPRegister(TSLA(ts,2))) && TSLA(ts,3) == COMMA && ( isGPRegister(TSLA(ts,4)) || isSPRegister(TSLA(ts,4))) )
                OSInsert(os,STB1,TSToken(ts).name);
            else
                p->m_errorIns = ins;
            token = TSStep(ts);
            if(token == STRING)
            {
                if(isInteger(TSToken(ts).name))
                {
                    token = TSStep(ts);
                    OSInsert(os,INTEGER,TSToken(ts).name);
                    if(token == COMMA)
                    {
                        token = TSStep(ts);
                        if(isGPRegister(token))
                        {
                            OSInsert(os,OTForReg(token),TSToken(ts).name);
                        }
                        else if(isSPRegister(token))
                        {
                            OSInsert(os,OTForReg(token),TSToken(ts).name);
                        }
                        else
                        {
                            createParserError(p,TSToken(ts));
                            return 0;
                        }
                    }
                    else
                    {
                        createParserError(p,TSToken(ts));
                        return 0;
                    }
                }
                else
                {
                    p->m_errorIns = ins;
                    createParserError(p,TSToken(ts));
                    return 0;
                }
            }
            else if(token == AT)
            {
                token = TSStep(ts);
                    if(isGPRegister(token))
                    {
                        OSInsert(os,OTForReg(token),TSToken(ts).name);
                        token = TSStep(ts);
                        if(token == COMMA)
                        {
                            token = TSStep(ts);
                            if(isGPRegister(token))
                            {
                                OSInsert(os,OTForReg(token),TSToken(ts).name);
                            }
                            else if(isSPRegister(token))
                            {
                                OSInsert(os,OTForReg(token),TSToken(ts).name);
                            }
                            else
                            {
                                createParserError(p,TSToken(ts));
                                return 0;
                            }
                        }
                        else
                        {
                            createParserError(p,TSToken(ts));
                            return 0;
                        }
                    }
                    else if(isSPRegister(token))
                    {
                        OSInsert(os,OTForReg(token),TSToken(ts).name);
                        token = TSStep(ts);
                        if(token == COMMA)
                        {
                            token = TSStep(ts);
                            if(isGPRegister(token))
                            {
                                OSInsert(os,OTForReg(token),TSToken(ts).name);
                            }
                            else if(isSPRegister(token))
                            {
                                OSInsert(os,OTForReg(token),TSToken(ts).name);
                            }
                            else
                            {
                                createParserError(p,TSToken(ts));
                                return 0;
                            }
                        }
                        else
                        {
                            createParserError(p,TSToken(ts));
                            return 0;
                        }
                    }
                    else
                    {
                        createParserError(p,TSToken(ts));
                        return 0;
                    }
            }
            else
            {
                createParserError(p,TSToken(ts));
                return 0;
            }
        }
        else if(token == STW)
        {
            if(TSLA(ts,1) == STRING && TSLA(ts,2) == COMMA && ( isGPRegister(TSLA(ts,3)) || isSPRegister(TSLA(ts,3))))
                OSInsert(os,STW0,TSToken(ts).name);
            else if(TSLA(ts,1) == AT && ( isGPRegister(TSLA(ts,2)) || isSPRegister(TSLA(ts,2))) && TSLA(ts,3) == COMMA && ( isGPRegister(TSLA(ts,4)) || isSPRegister(TSLA(ts,4))) )
                OSInsert(os,STW1,TSToken(ts).name);
            else
                p->m_errorIns = ins;
            token = TSStep(ts);
            if(token == STRING)
            {
                if(isInteger(TSToken(ts).name))
                {
                    token = TSStep(ts);
                    OSInsert(os,INTEGER,TSToken(ts).name);
                    if(token == COMMA)
                    {
                        token = TSStep(ts);
                        if(isGPRegister(token))
                        {
                            OSInsert(os,OTForReg(token),TSToken(ts).name);
                        }
                        else if(isSPRegister(token))
                        {
                            OSInsert(os,OTForReg(token),TSToken(ts).name);
                        }
                        else
                        {
                            createParserError(p,TSToken(ts));
                            return 0;
                        }
                    }
                    else
                    {
                        createParserError(p,TSToken(ts));
                        return 0;
                    }
                }
                else
                {
                    p->m_errorIns = ins;
                    createParserError(p,TSToken(ts));
                    return 0;
                }
            }
            else if(token == AT)
            {
                token = TSStep(ts);
                    if(isGPRegister(token))
                    {
                        OSInsert(os,OTForReg(token),TSToken(ts).name);
                        token = TSStep(ts);
                        if(token == COMMA)
                        {
                            token = TSStep(ts);
                            if(isGPRegister(token))
                            {
                                OSInsert(os,OTForReg(token),TSToken(ts).name);
                            }
                            else if(isSPRegister(token))
                            {
                                OSInsert(os,OTForReg(token),TSToken(ts).name);
                            }
                            else
                            {
                                createParserError(p,TSToken(ts));
                                return 0;
                            }
                        }
                        else
                        {
                            createParserError(p,TSToken(ts));
                            return 0;
                        }
                    }
                    else if(isSPRegister(token))
                    {
                        OSInsert(os,OTForReg(token),TSToken(ts).name);
                        token = TSStep(ts);
                        if(token == COMMA)
                        {
                            token = TSStep(ts);
                            if(isGPRegister(token))
                            {
                                OSInsert(os,OTForReg(token),TSToken(ts).name);
                            }
                            else if(isSPRegister(token))
                            {
                                OSInsert(os,OTForReg(token),TSToken(ts).name);
                            }
                            else
                            {
                                createParserError(p,TSToken(ts));
                                return 0;
                            }
                        }
                        else
                        {
                            createParserError(p,TSToken(ts));
                            return 0;
                        }
                    }
                    else
                    {
                        createParserError(p,TSToken(ts));
                        return 0;
                    }
            }
            else
            {
                createParserError(p,TSToken(ts));
                return 0;
            }
        }
        else if(token == SUB)
        {
            if(isGPRegister(TSLA(ts,1)) && TSLA(ts,2) == COMMA && TSLA(ts,3) == HASH && TSLA(ts,4) == STRING)
                OSInsert(os,SUB0,TSToken(ts).name);
            else if(isGPRegister(TSLA(ts,1)) && TSLA(ts,2) == COMMA && ( isGPRegister(TSLA(ts,3)) || isSPRegister(TSLA(ts,3))))
                OSInsert(os,SUB1,TSToken(ts).name);
            else
                p->m_errorIns = ins;
            token = TSStep(ts);
            if(isGPRegister(token))
            {
                OSInsert(os,OTForReg(token),TSToken(ts).name);
                token = TSStep(ts);
                if(token == COMMA)
                {
                    token = TSStep(ts);
                    if(isGPRegister(token))
                    {
                        OSInsert(os,OTForReg(token),TSToken(ts).name);
                    }
                    else if(isSPRegister(token))
                    {
                        OSInsert(os,OTForReg(token),TSToken(ts).name);
                    }
                    else if(token == HASH)
                    {
                        token = TSStep(ts);
                        if(token == STRING)
                        {
                            if(isInteger(TSToken(ts).name))
                                OSInsert(os,INTEGER,TSToken(ts).name);
                            else
                            {
                                p->m_errorIns = ins;
                                createParserError(p,TSToken(ts));
                                return 0;
                            }
                        }
                        else
                        {
                            createParserError(p,TSToken(ts));
                            return 0;
                        }
                    }
                    else
                    {
                        createParserError(p,TSToken(ts));
                        return 0;
                    }
                }
                else
                {
                    createParserError(p,TSToken(ts));
                    return 0;
                }
            }
            else
            {
                createParserError(p,TSToken(ts));
                return 0;
            }
        }
        
        // monadic instructions
        
        else if(token == CAL)
        {
            OSInsert(os,CAL0,TSToken(ts).name);
            token = TSStep(ts);
            if(token == STRING)
            {
                if(isInteger(TSToken(ts).name))
                {
                    OSInsert(os,INTEGER,TSToken(ts).name);
                }
                else
                {
                    p->m_errorIns = ins;
                    createParserError(p,TSToken(ts));
                    return 0;
                }
            }
            else
            {
                createParserError(p,TSToken(ts));
                return 0;
            }
        }
        else if(token == DEC)
        {
            OSInsert(os,DEC0,TSToken(ts).name);
            token = TSStep(ts);
            if(isGPRegister(token))
            {
                OSInsert(os,OTForReg(token),TSToken(ts).name);
            }
            else
            {
                createParserError(p,TSToken(ts));
                return 0;
            }
        }
        else if(token == INC)
        {
            OSInsert(os,INC0,TSToken(ts).name);
            token = TSStep(ts);
            if(isGPRegister(token))
            {
                OSInsert(os,OTForReg(token),TSToken(ts).name);
            }
            else
            {
                createParserError(p,TSToken(ts));
                return 0;
            }
        }
        else if(token == JMP)
        {
            if(TSLA(ts,1) == STRING)
                OSInsert(os,JMP0,TSToken(ts).name);
            else if(isGPRegister(TSLA(ts,1)))
                OSInsert(os,JMP1,TSToken(ts).name);
            else
                p->m_errorIns = ins;
            
            token = TSStep(ts);
            if(token == STRING)
            {
                if(isInteger(TSToken(ts).name))
                {
                    OSInsert(os,INTEGER,TSToken(ts).name);
                }
                else
                {
                    p->m_errorIns = ins;
                    createParserError(p,TSToken(ts));
                    return 0;
                }
            }
            else if(isGPRegister(token))
            {
                OSInsert(os,OTForReg(token),TSToken(ts).name);
            }
            else
            {
                createParserError(p,TSToken(ts));
                return 0;
            }
        }
        else if(token == JEQ)
        {
            if(TSLA(ts,1) == STRING)
                OSInsert(os,JEQ0,TSToken(ts).name);
            else if(isGPRegister(TSLA(ts,1)))
                OSInsert(os,JEQ1,TSToken(ts).name);
            else
                p->m_errorIns = ins;
            
            token = TSStep(ts);
            if(token == STRING)
            {
                if(isInteger(TSToken(ts).name))
                {
                    OSInsert(os,INTEGER,TSToken(ts).name);
                }
                else
                {
                    p->m_errorIns = ins;
                    createParserError(p,TSToken(ts));
                    return 0;
                }
            }
            else if(isGPRegister(token))
            {
                OSInsert(os,OTForReg(token),TSToken(ts).name);
            }
            else
            {
                createParserError(p,TSToken(ts));
                return 0;
            }
        }
        else if(token == JNE)
        {
            if(TSLA(ts,1) == STRING)
                OSInsert(os,JNE0,TSToken(ts).name);
            else if(isGPRegister(TSLA(ts,1)))
                OSInsert(os,JNE1,TSToken(ts).name);
            else
                p->m_errorIns = ins;
            
            token = TSStep(ts);
            if(token == STRING)
            {
                if(isInteger(TSToken(ts).name))
                {
                    OSInsert(os,INTEGER,TSToken(ts).name);
                }
                else
                {
                    p->m_errorIns = ins;
                    createParserError(p,TSToken(ts));
                    return 0;
                }
            }
            else if(isGPRegister(token))
            {
                OSInsert(os,OTForReg(token),TSToken(ts).name);
            }
            else
            {
                createParserError(p,TSToken(ts));
                return 0;
            }
        }
        else if(token == JLT)
        {
            if(TSLA(ts,1) == STRING)
                OSInsert(os,JLT0,TSToken(ts).name);
            else if(isGPRegister(TSLA(ts,1)))
                OSInsert(os,JLT1,TSToken(ts).name);
            else
                p->m_errorIns = ins;
            
            token = TSStep(ts);
            if(token == STRING)
            {
                if(isInteger(TSToken(ts).name))
                {
                    OSInsert(os,INTEGER,TSToken(ts).name);
                }
                else
                {
                    p->m_errorIns = ins;
                    createParserError(p,TSToken(ts));
                    return 0;
                }
            }
            else if(isGPRegister(token))
            {
                OSInsert(os,OTForReg(token),TSToken(ts).name);
            }
            else
            {
                createParserError(p,TSToken(ts));
                return 0;
            }
        }
        else if(token == JGT)
        {
            if(TSLA(ts,1) == STRING)
                OSInsert(os,JGT0,TSToken(ts).name);
            else if(isGPRegister(TSLA(ts,1)))
                OSInsert(os,JGT1,TSToken(ts).name);
            else
                p->m_errorIns = ins;
            
            token = TSStep(ts);
            if(token == STRING)
            {
                if(isInteger(TSToken(ts).name))
                {
                    OSInsert(os,INTEGER,TSToken(ts).name);
                }
                else
                {
                    p->m_errorIns = ins;
                    createParserError(p,TSToken(ts));
                    return 0;
                }
            }
            else if(isGPRegister(token))
            {
                OSInsert(os,OTForReg(token),TSToken(ts).name);
            }
            else
            {
                createParserError(p,TSToken(ts));
                return 0;
            }
        }
        else if(token == POP)
        {
            if(TSLA(ts,1) == STRING)
                OSInsert(os,POP0,TSToken(ts).name);
            else if(isGPRegister(TSLA(ts,1)))
                OSInsert(os,POP1,TSToken(ts).name);
            else
                p->m_errorIns = ins;
            
            token = TSStep(ts);
            if(token == STRING)
            {
                if(isInteger(TSToken(ts).name))
                {
                    OSInsert(os,INTEGER,TSToken(ts).name);
                }
                else
                {
                    p->m_errorIns = ins;
                    createParserError(p,TSToken(ts));
                    return 0;
                }
            }
            else if(isGPRegister(token))
            {
                OSInsert(os,OTForReg(token),TSToken(ts).name);
            }
            else
            {
                createParserError(p,TSToken(ts));
                return 0;
            }
        }
        else if(token == PSH)
        {
            if(TSLA(ts,1) == STRING)
                OSInsert(os,PSH0,TSToken(ts).name);
            else if(isGPRegister(TSLA(ts,1)))
                OSInsert(os,PSH1,TSToken(ts).name);
            else
                p->m_errorIns = ins;
            
            token = TSStep(ts);
            if(token == STRING)
            {
                if(isInteger(TSToken(ts).name))
                {
                    OSInsert(os,INTEGER,TSToken(ts).name);
                }
                else
                {
                    p->m_errorIns = ins;
                    createParserError(p,TSToken(ts));
                    return 0;
                }
            }
            else if(isGPRegister(token))
            {
                OSInsert(os,OTForReg(token),TSToken(ts).name);
            }
            else
            {
                createParserError(p,TSToken(ts));
                return 0;
            }
        }
        
        // 0 operand instructions
        
        else if(token == HLT)
        {
            OSInsert(os,HLT0,TSToken(ts).name);
        }
        else if(token == RET)
        {
            OSInsert(os,RET0,TSToken(ts).name);
        }
        else if(token == MSF)
        {
            OSInsert(os,MSF0,TSToken(ts).name);
        }
        
        token = TSStep(ts);
    }
    
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
    t.lineno = 0;
    t.start = 0;
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
    if(parserdebug)
        printf("\nParsing Start");
    char * output = malloc(20);
    strcat(output,"Parse Succesfull");
    if(parserdebug)
        printf("\nStarting Tokenizing");
    tokenize(p);
    TokenStream* ts = p->m_lex->m_tokenStream;
    OpcodeStream* os = OSCreate();
    if(!_P_parse_(p,ts,os))
        return "Parse Eroor";
    
    // convert to bin using opcodeconvertor
    // output = opcodeConvertor(os);
    return output;
}

void createParserError(Parser* p, Token t)
{
    p->m_errorToken = t;
}

char* parserError(Parser* p,long* line, long* pos, long* ins)
{
    Token tok = p->m_errorToken;
    
    if(tok.end == ENDOFFILE || tok.end == INVALID)
    {
        *ins = p->m_errorIns;
        *line = tok.lineno;
        *pos = tok.start;   
        return "Empty File";
    }
    char* ch = malloc(20);
    strcpy(ch,"");
    
    strcat(ch,"Syntax Error : ");
    strcat(ch,tok.name);
    *ins = p->m_errorIns;
    *line = tok.lineno;
    *pos = tok.start;  
    return ch;
}

int parserHasError(Parser* p)
{
    if(p->m_errorToken.end != ENDOFFILE)
        return 1;
    return 0;
}
