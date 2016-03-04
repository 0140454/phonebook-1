#include <stdlib.h>
#include <string.h>

#include "phonebook_trie.h"

/* FILL YOUR OWN IMPLEMENTATION HERE! */
entry *findName(char lastname[], entry *pHead)
{
    int i, alpha, len = strlen(lastname);

    for (i = 0; i <= len && pHead; ++i) {
        if (lastname[i] >= 'a')
            alpha = lastname[i] - 'a';
        else if (lastname[i] >= 'A')
            alpha = lastname[i] - 'A';
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
            pHead->pChild[alpha] = (entry *) calloc(1, sizeof(entry));
            pHead->pChild[alpha]->ch = lastName[i];
        }

        pHead = pHead->pChild[alpha];
    }
}

void free_trie(entry *pHead)
{
    if (pHead == NULL)
        return;

    int i;
    for (i = 0; i < 27; ++i)
        free_trie(pHead->pChild[i]);
    free(pHead);
}
