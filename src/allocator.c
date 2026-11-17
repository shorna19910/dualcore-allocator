#include <stdio.h>
#include <unistd.h>
#include <stddef.h>

struct block {
    size_t size;
    int free;
    struct block *next;
};

static struct block *head = NULL;
static struct block *tail = NULL;

size_t align8(size_t size) {
    return (size + 7) & ~(size_t)7;
}

struct block *find_free_block(size_t size) {
    struct block *cur = head;
    while (cur != NULL) {
        if (cur->free && cur->size >= size) {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

void split_block(struct block *blk, size_t size) {
    if (blk->size >= size + sizeof(struct block) + 8) {
        struct block *newb = (struct block *)((char *)(blk + 1) + size);
        newb->size = blk->size - size - sizeof(struct block);
        newb->free = 1;
        newb->next = blk->next;
        blk->size = size;
        blk->next = newb;
        if (tail == blk) {
            tail = newb;
        }
    }
}

void coalesce(void) {
    struct block *cur = head;
    while (cur != NULL && cur->next != NULL) {
        char *end = (char *)(cur + 1) + cur->size;
        if (cur->free && cur->next->free && end == (char *)cur->next) {
            if (tail == cur->next) {
                tail = cur;
            }
            cur->size += sizeof(struct block) + cur->next->size;
            cur->next = cur->next->next;
        } else {
            cur = cur->next;
        }
    }
}

void *my_malloc(size_t size) {
    if (size == 0) {
        return NULL;
    }
    size = align8(size);

    struct block *found = find_free_block(size);
    if (found != NULL) {
        split_block(found, size);
        found->free = 0;
        return (void *)(found + 1);
    }

    struct block *blk = sbrk(sizeof(struct block) + size);
    if (blk == (void *)-1) {
        return NULL;
    }
    blk->size = size;
    blk->free = 0;
    blk->next = NULL;

    if (head == NULL) {
        head = blk;
    } else {
        tail->next = blk;
    }
    tail = blk;

    return (void *)(blk + 1);
}

void my_free(void *ptr) {
    if (ptr == NULL) {
        return;
    }
    struct block *blk = (struct block *)ptr - 1;
    blk->free = 1;
    coalesce();
}

void dump_map(void) {
    struct block *cur = head;
    int i = 0;
    printf("--- Memory map ---\n");
    while (cur != NULL) {
        printf("Block %d: addr=%p size=%zu bytes %s\n", i, (void *)cur,
               cur->size, cur->free ? "FREE" : "USED");
        cur = cur->next;
        i++;
    }
}
