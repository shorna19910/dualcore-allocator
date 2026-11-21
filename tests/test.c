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

    printf("\n%d passed, %d failed\n", passed, failed);
    return failed;
}
