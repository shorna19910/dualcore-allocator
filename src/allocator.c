#include <stdio.h>
#include <unistd.h>
#include <stddef.h>

struct block {
    size_t size;
    int free;
    struct block *next;
};

enum { FIRST_FIT = 0, BEST_FIT = 1, WORST_FIT = 2 };

static struct block *head = NULL;
static struct block *tail = NULL;
static int strategy = FIRST_FIT;

void set_strategy(int s) {
    strategy = s;
}

void allocator_reset(void) {
    head = NULL;
    tail = NULL;
}

size_t align8(size_t size) {
    return (size + 7) & ~(size_t)7;
}

struct block *find_free_block(size_t size) {
    struct block *cur = head;
    struct block *chosen = NULL;
    while (cur != NULL) {
        if (cur->free && cur->size >= size) {
            if (strategy == FIRST_FIT) {
                return cur;
            }
            if (chosen == NULL ||
                (strategy == BEST_FIT && cur->size < chosen->size) ||
                (strategy == WORST_FIT && cur->size > chosen->size)) {
                chosen = cur;
            }
        }
        cur = cur->next;
    }
    return chosen;
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

static void out(const char *s, int n) {
    ssize_t r = write(1, s, n);
    (void)r;
}

void dump_map(void) {
    char buf[200];
    int n = snprintf(buf, sizeof(buf), "--- Memory map ---\n");
    out(buf, n);
    struct block *cur = head;
    int i = 0;
    while (cur != NULL) {
        n = snprintf(buf, sizeof(buf), "Block %d: addr=%p size=%zu bytes %s\n",
                     i, (void *)cur, cur->size, cur->free ? "FREE" : "USED");
        out(buf, n);
        cur = cur->next;
        i++;
    }
}

void dump_stats(void) {
    char buf[200];
    size_t total_free = 0;
    size_t largest = 0;
    int free_blocks = 0;
    struct block *cur = head;
    while (cur != NULL) {
        if (cur->free) {
            free_blocks++;
            total_free += cur->size;
            if (cur->size > largest) {
                largest = cur->size;
            }
        }
        cur = cur->next;
    }
    int n = snprintf(buf, sizeof(buf),
                     "Free blocks: %d, total free: %zu bytes, largest free block: %zu bytes\n",
                     free_blocks, total_free, largest);
    out(buf, n);
}
