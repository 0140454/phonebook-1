#include <stdlib.h>
#include <string.h>

#include "phonebook_opt.h"
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
    while (pHead != NULL) {
        if (strcasecmp(lastName, pHead->lastName) == 0)
            return pHead;
        pHead = pHead->pNext;
    }
    return NULL;
}

entry *append(char lastName[], entry *e)
{
    e->pNext = (entry *) pool_alloc(pool, sizeof(entry));
    e = e->pNext;
    strcpy(e->lastName, lastName);
    e->pNext = NULL;
    e->pDetail = NULL;

    return e;
}

unsigned int hashfunction(char *str)
{
    unsigned int hash = 5381;

    while (*str) {
        hash += (hash << 5) + (*str++);
    }

    return (hash & 0x7FFFFFFF);
}
