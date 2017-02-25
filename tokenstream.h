#ifndef TOKENSTREAM_H
#define TOKENSTREAM_H

#include "tokentype.h"

typedef struct Token
{
    long kind;
    long start;
    long end;
} Token;

typedef struct ListNode
{
    Token m_token;
    struct ListNode* m_next;
    struct ListNode* m_prev;
} ListNode;

typedef struct TokenStream
{
    ListNode* m_node;
    long m_index;
    long m_size;
} TokenStream;

void TSInsert(TokenStream* ts, Token token);
TokenType TSLA(TokenStream* ts, int i);
TokenType TSNext(TokenStream* ts);
long TSIndex(TokenStream* ts);

#endif
