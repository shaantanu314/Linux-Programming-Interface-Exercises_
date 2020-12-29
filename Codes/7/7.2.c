/*

An implementation of malloc() and free() using sbrk()

shaantanu kulkarni 
shaantanu.kulkarni@students.iiit.ac.in

*/

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
            
            
            new_free_header = (block_header_t*)((unsigned long)current_header + memory_needed);
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
    /*
    If we fail to find a block which is of size more than the required size of the block requested
    we need to expand the heap size, so we use the sbrk() to do so.
    */
    printf("expansion needed \n");
    
    block_header_t* new_header = (block_header_t*)sbrk(memory_needed);  
    /*
    Since we want to return the pointer to the location form where the memory can be used ,ie, after the block header,
    we need to offsets the pointer 
    */
    void *memory_ptr = ((void *)((unsigned long)new_header + sizeof(block_header_t)));
    
    
    if(previous_header!=NULL)
        previous_header->next_chunk = new_header;
    new_header->prev_chunk = previous_header;
    new_header->next_chunk = NULL;
    new_header->block_length = memory_needed;
    new_header->is_free = 0;
    


    /*
    handling condition if the ll_head the first head yet
    */
    if(!ll_head)
    {
        ll_head = new_header;
    }

    block_header_t* header_ptr = (block_header_t *)((unsigned long)memory_ptr - sizeof(block_header_t));
    //printf("ptr: %p\n",header_ptr);

    return memory_ptr;
}

void my_free(void *ptr)
{
    block_header_t* header_ptr = ((block_header_t *)((unsigned long)ptr - sizeof(block_header_t)));
    header_ptr->is_free=1;
    if(header_ptr->next_chunk != NULL)
    {
        if(header_ptr->next_chunk->is_free==1)
        {
            
            header_ptr->block_length = header_ptr->block_length + header_ptr->next_chunk->block_length ;
            if(header_ptr->next_chunk->next_chunk)
                header_ptr->next_chunk->next_chunk->prev_chunk = header_ptr;

            header_ptr->next_chunk=header_ptr->next_chunk->next_chunk;            
        }
    }

    if(header_ptr->prev_chunk != NULL)
    {
        if(header_ptr->prev_chunk->is_free==1)
        {
            
            header_ptr->prev_chunk->block_length += header_ptr->block_length;
            header_ptr->prev_chunk->next_chunk = header_ptr->next_chunk;
            if(header_ptr->next_chunk)
                header_ptr->next_chunk->prev_chunk = header_ptr->prev_chunk;
        }
    }


}
 


int main()
{

    char *buf;
    char *buf_[103];

    // test case:
    for(int i=100;i>=1;i--)
    {
        //printf("head : %p\n",ll_head);
        buf = (char*)my_malloc(i);
        buf_[i]= buf;

        // printf("ptr : %p\n",buf);
        // block_header_t* header_ptr = ((block_header_t *)((unsigned long)buf - sizeof(block_header_t)));
        //printf("ptr : %p\n",header_ptr);
        
        if(i%2)
        {
            printf("attempting to free()\n");
            my_free(buf);
        }
        //printf("\n\n\n");
    }




}