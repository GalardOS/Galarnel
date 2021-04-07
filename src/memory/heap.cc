#include "heap.hh"

#include "libsteel/common.hh"

struct meta_block {
    uint32 next_meta_in;
    uint32 status;
} __attribute__((packed));

constexpr uint32 STATUS_FREE = 0;
constexpr uint32 STATUS_OCCUPIED = 1;

static uint64* buffer_start;
static uint32 buffer_element_count;

namespace heap {
    void __initialize() {
        // Setup the buffer start and size
        buffer_start = (uint64*)0x0;
        buffer_element_count = 0x4000 / sizeof(uint64);

        // Setup the first block as free and refering to the whole buffer,
        // this block is expecting a meta block refering to the end of the 
        // buffer 
        ((meta_block*)(&buffer_start[0]))->status = STATUS_FREE;
        ((meta_block*)(&buffer_start[0]))->next_meta_in = buffer_element_count - 1;

        // Meta block refering to the end of the buffer. This block should not be 
        // used to follow the finding empty blocks
        ((meta_block*)(&buffer_start[buffer_element_count - 1]))->status = STATUS_OCCUPIED;
        ((meta_block*)(&buffer_start[buffer_element_count - 1]))->next_meta_in = 0;
    }

    static uint32 find_empty_block_with_size(uint32 size) {
        uint32 index = 0;

        // Loop until a the allocation fits or the buffer index has
        // reached the maximum
        while(index < buffer_element_count) {
            meta_block* meta = (meta_block*)&buffer_start[index];
            const uint32 available_size = meta->next_meta_in - 1; 
            
            // If there is enough available space to fit the allocation return that index,
            // if not, advance to the next meta block
            if(meta->status == STATUS_FREE && available_size >= size) {
                return index;
            } else {
                index += meta->next_meta_in;
            }
        }

        return -1;
    }

    void* allocate(uint32 size) {
        const uint32 size_in_blocks = size / sizeof(uint64);

        // Block should be the free block with enough size, if the block is -1
        // no block has been found, so nullptr should be returned
        const uint32 block = find_empty_block_with_size(size_in_blocks);
        if(block == -1)
            return nullptr;

        const uint32 next_meta_in = ((meta_block*)(&buffer_start[block]))->next_meta_in;

        /// TODO: create the meta block only if the block created has not size = 0
        // Create the new next empty block. 
        const uint32 new_empty_idx = block + size_in_blocks + 1;
        ((meta_block*)(&buffer_start[new_empty_idx]))->next_meta_in = next_meta_in - size_in_blocks + 1;
        ((meta_block*)(&buffer_start[new_empty_idx]))->status = STATUS_FREE;

        // Update the allocated meta block to be occupied
        ((meta_block*)(&buffer_start[block]))->next_meta_in = size_in_blocks + 1;
        ((meta_block*)(&buffer_start[block]))->status = STATUS_OCCUPIED;

        return buffer_start + block + 1; 
    }

    void deallocate(void* ptr) {
        // Get the meta block of the pointer, which is the previous 64 bits of the given pointer 
        meta_block* meta_of_ptr = (meta_block*)(ptr);
        meta_of_ptr--;

        // Set the new status as free. 
        meta_of_ptr->status = STATUS_FREE;

        meta_block* next_meta = meta_of_ptr + meta_of_ptr->next_meta_in;

        // Check if the next meta block is also free, if so, create unify both into one large free
        // space. This should help avoid fragmentation.
        bool is_last_meta = (next_meta->status == STATUS_OCCUPIED) && 
                            (next_meta->next_meta_in = 0);
        if(!is_last_meta && next_meta->status == STATUS_FREE) {
            meta_of_ptr->next_meta_in += next_meta->next_meta_in;
        }
    }
}