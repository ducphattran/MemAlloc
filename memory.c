#include "memory.h"  
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  

/*   
 * Initializes the memory pool.   
 */  
void init_memory(Memory *memory, size_t total_size) {  
    memory->head = (Block *)malloc(sizeof(Block));  
    if (!memory->head) {  
        fprintf(stderr, "Failed to allocate memory for the head block.\n");  
        exit(EXIT_FAILURE);  
    }  

    void *pool_address = malloc(total_size);  
    if (!pool_address) {  
        fprintf(stderr, "Failed to allocate the memory pool.\n");  
        free(memory->head);  
        exit(EXIT_FAILURE);  
    }  

    memory->head->size = total_size;  
    memory->head->is_free = 1;  
    memory->head->address = pool_address;  
    memory->head->prev = NULL;  
    memory->head->next = NULL;  
}  

/*   
 * Allocates a block of 'size' bytes.   
 */  
void *allocate_memory(Memory *memory, size_t size) {  
    Block *current = memory->head;  
    while (current != NULL) {  
        if (current->is_free && current->size >= size) {  
            if (current->size == size) {  
                current->is_free = 0;  
                return current->address;  
            } else {  
                Block *new_block = (Block *)malloc(sizeof(Block));  
                if (!new_block) {  
                    fprintf(stderr, "Failed to allocate new block.\n");  
                    return NULL;  
                }  

                new_block->size = current->size - size;  
                new_block->is_free = 1;  
                new_block->address = (char *)current->address + size;  
                new_block->prev = current;  
                new_block->next = current->next;  

                if (current->next) {  
                    current->next->prev = new_block;  
                }  

                current->size = size;  
                current->is_free = 0;  
                current->next = new_block;  

                return current->address;  
            }  
        }  
        current = current->next;  
    }  
    return NULL;  
}  

/*   
 * Frees a block and merges adjacent free blocks.   
 */  
void free_memory(Memory *memory, void *ptr) {  
    Block *current = memory->head;  
    while (current != NULL) {  
        if (current->address == ptr) {  
            current->is_free = 1;  

            if (current->next && current->next->is_free) {  
                current->size += current->next->size;  
                Block *to_free = current->next;  
                current->next = to_free->next;  
                if (to_free->next) {  
                    to_free->next->prev = current;  
                }  
                free(to_free);  
            }  

            if (current->prev && current->prev->is_free) {  
                current->prev->size += current->size;  
                current->prev->next = current->next;  
                if (current->next) {  
                    current->next->prev = current->prev;  
                }  
                free(current);  
            }  
            return;  
        }  
        current = current->next;  
    }  
}  

/*   
 * Displays the memory blocks.   
 */  
void display_memory(Memory *memory) {  
    Block *current = memory->head;  
    printf("\nMemory Blocks:\n");  
    while (current != NULL) {  
        printf("Block at %p: Size: %zu, Free: %s, Address: %p\n",  
               (void *)current, current->size,  
               current->is_free ? "Yes" : "No", current->address);  
        current = current->next;  
    }  
} 

/*   
 * Displays block sizes.   
 */  
void display_memory_sizes(Memory *memory, char *output) {  
    sprintf(output, "%s", "");  
    Block *current = memory->head;  
    while (current != NULL) {  
        char buffer[64];  
        sprintf(buffer, "%llu -> ", (unsigned long long)current->size);
        strcat(output, buffer);  
        current = current->next;  
    }  
}  

/*   
 * Displays block statuses.   
 */  
void display_memory_status(Memory *memory, char *output) {  
    sprintf(output, "%s", "");  
    Block *current = memory->head;  
    while (current != NULL) {  
        char buffer[64];  
        sprintf(buffer, "%s -> ", current->is_free ? "Yes" : "No");  
        strcat(output, buffer);  
        current = current->next;  
    }  
}  

/*   
 * Checks the integrity of the linked list.   
 */  
int check_link(Memory *memory) {  
    Block *current = memory->head;  
    while (current != NULL) {  
        if (current->next && current->next->prev != current) {  
            return 0;  
        }  
        current = current->next;  
    }  
    return 1;  
}  