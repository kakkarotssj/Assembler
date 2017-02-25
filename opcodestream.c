#include "opcodestream.h"
#include <stdlib.h>
OpcodeStream* OSCreate()
{
    OpcodeStream * os = malloc(sizeof(OpcodeStream));
    os->m_index = -1;
    os->m_node = NULL;
    return os;
}
