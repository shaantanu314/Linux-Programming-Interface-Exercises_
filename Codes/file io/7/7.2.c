#define _DEFAULT_SOURCE
#define _BSD_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef struct block_header{

    int block_length;
    int is_free;
    struct block_header* next_chunk;
    struct block_header* prev_chunk;

}block_header_t;

static block_header_t *ll_head = NULL;

void* my_malloc(size_t size)
{
    block_header_t *current_header=NULL,*previous_header=NULL,*new_free_header;

    
    current_header = ll_head;
    
    const size_t memory_needed = sizeof(block_header_t)+size;
    //printf("recieved request\n");
    
    while(current_header)
    {
        if(current_header->block_length >=memory_needed && current_header->is_free==1)
        {
            
            
            new_free_header = (block_header_t*)((unsigned long long int)current_header + memory_needed);
            new_free_header->prev_chunk = current_header;
            new_free_header->next_chunk = current_header->next_chunk;
            new_free_header->is_free = 1;
            new_free_header->block_length = current_header->block_length - memory_needed;

            current_header->is_free = 0;
            current_header->next_chunk = new_free_header;
            current_header->prev_chunk = previous_header;
            current_header->block_length = memory_needed;

            block_header_t* memory_ptr = ((void *)((unsigned long)current_header + sizeof(block_header_t)));
            return memory_ptr;
        }
        else
        {
            previous_header = current_header;
            current_header = current_header->next_chunk;
        }
        

    }
    //printf("expansion needed \n");
    
    block_header_t* new_header = (block_header_t*)sbrk(memory_needed);  
    //offsets the pointer to from where the memory starts
    block_header_t* memory_ptr = ((void *)((unsigned long)new_header + sizeof(block_header_t)));
    
    new_header->prev_chunk = previous_header;
    new_header->next_chunk = NULL;
    new_header->block_length = memory_needed;
    new_header->is_free = 0;
    if(previous_header!=NULL)
        previous_header->next_chunk = new_header;
    


    // handling condition if the ll_head isnt pointing to the first head
    if(!ll_head)
    {
        //printf("updated\n");
        ll_head = new_header;
    }

    return memory_ptr;
    
}
 


int main()
{

    char *buf;
    char *buf_[13];
    for(int i=10;i>=1;i--)
    {
        printf("head : %p\n",ll_head);
        buf = (char*)my_malloc(i);
        buf_[i]= buf;
        printf("%p\n",buf);
    }

}