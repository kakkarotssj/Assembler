#ifndef OPCODESTREAM_H
#define OPCODESTREAM_H

typedef enum OpcodeType
{
    ADD1,
    ADD2,
    MOV1,
    MOV2,
    CMP0,
    JMP0,
} OpcodeType;

typedef struct OpcodeNode
{
    OpcodeType m_opcode;
    struct ListNode* m_next;
    struct ListNode* m_prev;
} OpcodeNode;

typedef struct OpcodeStream
{
    OpcodeNode* m_node;
    long m_index;
    long m_size;
} OpcodeStream;

void OSInsert(OpcodeStream* os, OpcodeType opt);
OpcodeType OSNext(OpcodeStream* os);
int OSHasNext(OpcodeStream* os);


#endif
