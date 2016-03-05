#include <stdlib.h>
#include <string.h>

#include "phonebook_trie.h"
#include "memory_pool.h"

static memory_pool *pool = NULL;

/* FILL YOUR OWN IMPLEMENTATION HERE! */
void init_memory_pool(int size)
{
    pool = pool_init(size);
}

void free_memory_pool(void)
{
    pool_free(pool);
}

entry *findName(char lastName[], entry *pHead)
{
    int i, alpha, len = strlen(lastName);

    for (i = 0; i <= len && pHead; ++i) {
        if (lastName[i] >= 'a')
            alpha = lastName[i] - 'a';
        else if (lastName[i] >= 'A')
            alpha = lastName[i] - 'A';
        else
            alpha = 26;

        pHead = pHead->pChild[alpha];
    }

    return pHead;
}

void append(char lastName[], entry *pHead)
{
    int i, alpha, len = strlen(lastName);

    for (i = 0; i <= len; ++i) {
        if (lastName[i] >= 'a')
            alpha = lastName[i] - 'a';
        else if (lastName[i] >= 'A')
            alpha = lastName[i] - 'A';
        else
            alpha = 26;

        if (pHead->pChild[alpha] == NULL) {
            pHead->pChild[alpha] = (entry *) pool_alloc(pool, sizeof(entry));
            pHead->pChild[alpha]->ch = lastName[i];
        }

        pHead = pHead->pChild[alpha];
    }
}
