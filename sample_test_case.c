#include "memory.h"
#include <assert.h>
#include <string.h>

// test case 1: test allocate two blocks
int test_case_1() {
    Memory memory;
    init_memory(&memory, 1024);
    void *block1 = allocate_memory(&memory, 200);
    void *block2 = allocate_memory(&memory, 300);

    assert(block1 == memory.head->address);
    assert(block2 == block1 + 200);

    char output[1000];
    display_memory_sizes(&memory, output);
    assert(strcmp(output, "200 -> 300 -> 524 -> ") == 0);
    display_memory_status(&memory, output);
    assert(strcmp(output, "No -> No -> Yes -> ") == 0);

    assert(check_link(&memory) == 1);
    return 0;
}

// test case 2: test allocate three blocks with total size larger than the memory pool
int test_case_2() {
    Memory memory;
    init_memory(&memory, 1024);
    void *block1 = allocate_memory(&memory, 200);
    void *block2 = allocate_memory(&memory, 300);
    void *block3 = allocate_memory(&memory, 700);

    assert(block1 == memory.head->address);
    assert(block2 == block1 + 200);
    assert(block3 == NULL);

    char output[1000];
    display_memory_sizes(&memory, output);
    assert(strcmp(output, "200 -> 300 -> 524 -> ") == 0);
    display_memory_status(&memory, output);
    assert(strcmp(output, "No -> No -> Yes -> ") == 0);
    assert(check_link(&memory) == 1);
    return 0;
}

// test case 3: test allocate three blocks and free last block
int test_case_3() {
    Memory memory;
    init_memory(&memory, 1024);
    void *block1 = allocate_memory(&memory, 200);
    void *block2 = allocate_memory(&memory, 300);
    void *block3 = allocate_memory(&memory, 500);

    free_memory(&memory, block3);

    assert(block1 == memory.head->address);
    assert(block2 == block1 + 200);
    assert(block3 == block2 + 300);

    char output[1000];
    display_memory_sizes(&memory, output);
    assert(strcmp(output, "200 -> 300 -> 524 -> ") == 0);
    display_memory_status(&memory, output);
    assert(strcmp(output, "No -> No -> Yes -> ") == 0);
    assert(check_link(&memory) == 1);
    return 0;
}

int main() {
    test_case_1();
    test_case_2();
    test_case_3();
    return 0;
}