#include "../src/allocator.c"

static int passed = 0;
static int failed = 0;

static void check(int ok, const char *name) {
    printf("%s: %s\n", ok ? "PASS" : "FAIL", name);
    if (ok) {
        passed++;
    } else {
        failed++;
    }
}

int main() {
    allocator_reset();
    void *p = my_malloc(50);
    check(p != NULL, "1. malloc(50) returns a pointer");

    allocator_reset();
    check(my_malloc(0) == NULL, "2. malloc(0) returns NULL");

    allocator_reset();
p = my_malloc(13);
check(((size_t)p % 8) == 0, "3. address is 8-byte aligned");

    allocator_reset();
p = my_malloc(10);
((char *)p)[0] = 'H';
((char *)p)[1] = 'i';
check(((char *)p)[0] == 'H' && ((char *)p)[1] == 'i', "4. data written to a block can be read back");

    allocator_reset();
p = my_malloc(40);
void *q = my_malloc(40);
check((char *)q >= (char *)p + 40, "5. two blocks do not overlap");

allocator_reset();
p = my_malloc(64);
my_free(p);
q = my_malloc(64);
check(p == q, "6. freed block is reused for the same size");

    printf("\n%d passed, %d failed\n", passed, failed);
    return failed;
}
