#ifndef CONVERTOR_H
#define CONVERTOR_H

#include "opcodestream.h"

char *binaryOfOpcode(OpcodeStream *OS);
void *convertOPCodes(OpcodeStream *OS,char* output, int debug);

#endif
