#ifndef OPCODESTREAM_H
#define OPCODESTREAM_H

typedef enum OpcodeType
{
    //dyadic instructions
    MOV0,
    MOV1,
    LDB0,
    LDB1,
    LDW0,
    LDW1,
    STB0,
    STW0,
    ADD0,
    ADD1,
    SUB0,
    SUB1,
    MUL0,
    MUL1,
    DIV0,
    DIV1,
    CMP0,
    CMP1,
    // monadic instructions
    CAL0,
    INC0,
    DEC0,
    JMP0,
    JMP1,
    JLT0,
    JLT1,
    JGT0,
    JGT1,
    JEQ0,
    JEQ1,
    JNE0,
    JNE1,
    PSH0,
    PSH1,
    POP0,
    POP1,
    // 0 operand instructions
    HLT0,
    RET0,
    MSF0
    
} OpcodeType;

typedef struct OpcodeNode
{
    OpcodeType m_opcode;
    struct OpcodeNode* m_next;
    struct OpcodeNode* m_prev;
} OpcodeNode;

typedef struct OpcodeStream
{
    OpcodeNode* m_node;
    OpcodeNode* m_end;
    OpcodeNode* m_start;
    long m_index;
} OpcodeStream;

OpcodeStream* OSCreate();
void OSInsert(OpcodeStream* os, OpcodeType opt);
void OSStep(OpcodeStream* os);
int OSHasNext(OpcodeStream* os);
void OSClear(OpcodeStream* os);
void OSDestroy(OpcodeStream* os);

#endif
