#include "opcodestream.h"
#include <stdlib.h>
OpcodeStream* OSCreate()
{
    OpcodeStream * os = malloc(sizeof(OpcodeStream));
    os->m_index = -1;
    os->m_node = NULL;
    return os;
}


void OSInsert(OpcodeStream* os, OpcodeType opc)
{
    if(os->m_index < 0)
    {
        OpcodeNode* nn = malloc(sizeof(OpcodeNode));
        nn->m_next = NULL;
        nn->m_prev = NULL;
        nn->m_opcode = opc;
        os->m_node = nn;
        os->m_end = nn;
        os->m_start = nn;
    }
    else
    {
        OpcodeNode* end = os->m_end;
        OpcodeNode* nn = malloc(sizeof(OpcodeNode));
        nn->m_next = NULL;
        nn->m_prev = end;
        nn->m_opcode = opc;
        end->m_next = nn;
        os->m_end = nn;
    }
}

void OSStep(OpcodeStream* os)
{
    os->m_node = os->m_node->m_next;
}

int OSHasNext(OpcodeStream* os)
{
    if(os->m_node != NULL)
        return 1;
    return 0;
}

void OSClear(OpcodeStream* os)
{
    OpcodeNode* itr = os->m_start;
    os->m_start = NULL;
    os->m_end = NULL;
    
    if(itr == NULL)
        return;
    for(;itr!=NULL;itr = itr->m_next)
    {
        free(itr); 
    }
}

void OSDestroy(OpcodeStream* os)
{
    OSClear(os);
    free(os);
}
