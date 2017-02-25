#ifndef TOKENSTREAM_H
#define TOKENSTREAM_H

typedef struct Token
{
    int kind;
    int start;
    int end;
} Token;

typedef struct ListNode
{
    Token m_token;
    struct ListNode* next;
    struct ListNode* prev;
} ListNode;

typedef struct TokenStream
{
    ListNode* node;
    int m_index;
    int m_size;
} TokenStream;

#endif
