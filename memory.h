#ifndef MEMORY_H  
#define MEMORY_H  

#include <stddef.h> // For size_t  

// Define the Block structure  
typedef struct Block {  
    size_t size;          // Size of the block  
    int is_free;          // 1 if free, 0 if allocated  
    void *address;        // Address of the memory block  
    struct Block *prev;   // Pointer to the previous block  
    struct Block *next;   // Pointer to the next block  
} Block;  

// Define the Memory structure  
typedef struct Memory {  
    Block *head;          // Head of the block list  
} Memory;  

// Function declarations  
void init_memory(Memory *memory, size_t total_size);  
void *allocate_memory(Memory *memory, size_t size);  
void free_memory(Memory *memory, void *ptr);  
void display_memory(Memory *memory);  
void display_memory_sizes(Memory *memory, char *output); // Add this declaration  
void display_memory_status(Memory *memory, char *output); // Add this declaration  
int check_link(Memory *memory);  
#endif // MEMORY_H