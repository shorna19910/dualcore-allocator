#include "../src/allocator.c"

int main() {
    void *a = my_malloc(50);
    void *b = my_malloc(50);
    void *c = my_malloc(50);
    (void)c;
    my_free(a);
    my_free(b);
    dump_map();

    printf("\nNow asking for 100 bytes:\n");
    void *d = my_malloc(100);
    (void)d;
    dump_map();
    return 0;
}
