#include <stdlib.h>
#include <string.h>

#include "phonebook_rbtree.h"

static entry *nil = NULL;

entry *left_rotate(entry *pHead, entry *x)
{
    if (x->pRight != nil) {
        entry *y = x->pRight;

        x->pRight = y->pLeft;
        if (y->pLeft != nil)
            y->pLeft->pParent = x;
        y->pParent = x->pParent;

        if (x->pParent != nil) {
            if (x->pParent->pLeft == x)
                x->pParent->pLeft = y;
            else
                x->pParent->pRight = y;
        }

        y->pLeft = x;

        if (x->pParent == nil) {
            x->pParent = y;
            return y;
        } else {
            x->pParent = y;
        }
    }

    return pHead;
}

entry *right_rotate(entry *pHead, entry *x)
{
    if (x->pLeft != nil) {
        entry *y = x->pLeft;

        x->pLeft = y->pRight;
        if (y->pRight != nil)
            y->pRight->pParent = x;
        y->pParent = x->pParent;

        if (x->pParent != nil) {
            if (x->pParent->pLeft == x)
                x->pParent->pLeft = y;
            else
                x->pParent->pRight = y;
        }

        y->pRight = x;

        if (x->pParent == nil) {
            x->pParent = y;
            return y;
        } else {
            x->pParent = y;
        }
    }

    return pHead;
}

entry *fix_after_append(entry *pHead, entry *x)
{
    entry *y = NULL;

    while(x->pParent->color == RED) {
        if (x->pParent == x->pParent->pParent->pLeft) {
            y = x->pParent->pParent->pRight;
            if (y->color == RED) {
                y->color = BLACK;
                x->pParent->color = BLACK;
                x->pParent->pParent->color = RED;
                x = x->pParent->pParent;
            } else {
                if (x->pParent->pRight == x) {
                    x = x->pParent;
                    pHead = left_rotate(pHead, x);
                }

                x->pParent->color = BLACK;
                x->pParent->pParent->color = RED;
                pHead = right_rotate(pHead, x->pParent->pParent);
            }
        } else {
            y = x->pParent->pParent->pLeft;
            if (y->color == RED) {
                y->color = BLACK;
                x->pParent->color = BLACK;
                x->pParent->pParent->color = RED;
                x = x->pParent->pParent;
            } else {
                if (x->pParent->pLeft == x) {
                    x = x->pParent;
                    pHead = right_rotate(pHead, x);
                }

                x->pParent->color = BLACK;
                x->pParent->pParent->color = RED;
                pHead = left_rotate(pHead, x->pParent->pParent);
            }
        }
    }

    pHead->color = BLACK;

    return pHead;
}

/* FILL YOUR OWN IMPLEMENTATION HERE! */
entry *findName(char lastname[], entry *pHead)
{
    int cmp_result = 0;
    while(pHead != nil) {
        cmp_result = strcasecmp(pHead->lastName, lastname);

        if (cmp_result < 0 && pHead->pLeft != nil)
            pHead = pHead->pLeft;
        else if (cmp_result > 0 && pHead->pRight != nil)
            pHead = pHead->pRight;
        else
            break;
    }

    if (pHead == nil)
        return NULL;

    return pHead;
}

entry *append(char lastName[], entry *pHead)
{
    if (pHead == NULL) {
        nil = (entry *) malloc(sizeof(entry));
        nil->color = BLACK;

        entry *new_node = (entry *) malloc(sizeof(entry));
        strcpy(new_node->lastName, lastName);
        new_node->color = BLACK;
        new_node->pParent = new_node->pLeft = new_node->pRight = nil;
        return new_node;
    }

    entry *current = pHead, *parent = nil;
    int cmp_result = 0;
    while(current != nil) {
        cmp_result = strcasecmp(current->lastName, lastName);

        parent = current;
        if (cmp_result < 0)
            current = current->pLeft;
        else if (cmp_result > 0)
            current = current->pRight;
        else
            return pHead;
    }

    entry *new_node = (entry *) malloc(sizeof(entry));
    strcpy(new_node->lastName, lastName);
    new_node->pLeft = new_node->pRight = nil;
    new_node->pParent = parent;
    new_node->color = RED;
    if (cmp_result < 0)
        parent->pLeft = new_node;
    else
        parent->pRight = new_node;

    pHead = fix_after_append(pHead, new_node);

    return pHead;
}

void free_rbtree(entry *pHead)
{
    if (pHead == nil)
        return;

    free_rbtree(pHead->pLeft);
    free_rbtree(pHead->pRight);
    free(pHead);
}
