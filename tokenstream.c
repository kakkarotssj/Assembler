#include "tokenstream.h"
#include "tokentype.h"
#include <stdlib.h>

TokenStream* TSCreate()
{
    TokenStream* ts = malloc(sizeof(TokenStream));
    ts->m_index = -1;
    ts->m_size = 0;
    ts->m_indexNode = NULL;
    return ts;
}

void TSInsert(TokenStream* ts, Token token)
{
    if(ts->m_size == 0)
    {
        ListNode* nn = malloc(sizeof(ListNode));
        nn->m_next = NULL;
        nn->m_prev = NULL;
        nn->m_token.kind = token.kind;
        nn->m_token.end = token.end;
        nn->m_token.start = token.start;
        ts->m_start = nn;
        ts->m_end = nn;
        ts->m_size++;
    }
    else
    {
        ListNode* end = ts->m_end;
        ListNode* nn = malloc(sizeof(ListNode));
        nn->m_next = NULL;
        nn->m_prev = end;
        nn->m_token.kind = token.kind;
        nn->m_token.end = token.end;
        nn->m_token.start = token.start;
        end->m_next = nn;
        ts->m_end = nn;
        ts->m_size++;
    }
}

TokenType TSLA(TokenStream* ts, int i)
{
    if(ts->m_index+i >= ts->m_size)
        return INVALID;
    else
    {
        ListNode* cur = ts->m_indexNode;
        if(cur == NULL)
        {
            ListNode* itr = ts->m_start;
            if(itr == NULL)
                return INVALID;
            for(;i>0;i++)
            {
                i--;
                itr = itr->next;
                if(itr == NULL && i>0)
                    return INVALID;
            }
            
            if(itr == NULL)
                return INVALID;
            
            return itr->m_token.kind;
            
        }
    }
}

TokenType TSNext(TokenStream* ts)
{
    if(ts->m_index == -1)
    {
        ts->m_index++;
        ts->m_indexNode = ts->m_start;
    }
    else
    {
        if(ts->m_index == ts->m_size-1)
            return INVALID;
        
        ts->m_index++;
        ts->m_indexNode = ts->m_indexNode->m_next;
    }
    return ts->m_indexNode->m_token.kind;
}

long TSIndex(TokenStream* ts)
{
    return ts->m_index;
}

void TSClear(TokenStream* ts)
{
    ListNode* itr = ts->m_start;
    ts->m_start = NULL;
    ts->m_end = NULL;
    
    if(itr == NULL)
        return;
    for(;itr!=NULL;itr = itr->m_next)
    {
        free(itr); 
    }
}
