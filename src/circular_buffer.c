#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "circular_buffer.h"

NO_RETURN cb_init(void* self, types type, unsigned int size)
{
    circular_buffer_t* cb = (circular_buffer_t*)self;
    cb->size = size;
    cb->__type = type;
    cb->remaining = (cb->size - abs(cb->__add_index - cb->__remove_index));

    switch (type)
    {
    case Int:
        cb->__buffer = (int*)malloc(sizeof(int) * size); 
        cb->__add_index = 0;
        cb->__remove_index = 0;
        break;
    case Char:
        cb->__buffer = (char*)malloc(sizeof(char) * size);
        cb->__add_index = 0;
        cb->__remove_index = 0;
        break;
    
    default:

        fprintf(stderr , "ERROR: unknown data type\n");
        break;
    }   
    
}

GENERIC_TYPE cb_insert(void* self , GENERIC_TYPE value)
{
    circular_buffer_t* cb = (circular_buffer_t*)self;
    unsigned int buf_size = cb->size;
    unsigned int remaining_space;

    switch (cb->__type)
    {
        case Int:
            int* int_ptr = (int*)cb->__buffer;

        // printf("remaining space: %d\n" , cb->remaining);
            int_ptr[cb->__add_index % buf_size] = *((int*)value);
            cb->__add_index++;  
            cb->remaining = (buf_size - abs(cb->__add_index - cb->__remove_index));
        break;

        case Char:
            char* char_ptr = (char*)cb->__buffer;

        // printf("remaining space: %d\n" , cb->remaining);
            char_ptr[cb->__add_index % buf_size] = *((char*)value);
            cb->__add_index++;  
            cb->remaining = (buf_size - abs(cb->__add_index - cb->__remove_index));
        
        break;
        
        default:

            fprintf(stderr , "ERROR: unknown date type\n");
            break;
    } 


    
}
GENERIC_TYPE cb_remove(void *self)
{
    circular_buffer_t* cb = (circular_buffer_t*)self;
    unsigned int buf_size = cb->size;
    cb->remaining = (buf_size - abs(cb->__add_index - cb->__remove_index));
    GENERIC_TYPE ret;
    

    // printf("add_index: %d \t remove_index: %d\n" , cb->__add_index , cb->__remove_index);
    switch (cb->__type)
    {
        case Int:
            int* int_ptr = (int*)cb->__buffer;

            // printf("remaining space: %d\n" , cb->remaining);
            ret = &int_ptr[cb->__remove_index % buf_size];
            cb->__remove_index++;
            return ret;

            
            
        break;

        case Char:
            char* char_ptr = (char*)cb->__buffer;

            // printf("remaining space: %d\n" , cb->remaining);
            ret = &char_ptr[cb->__remove_index % buf_size];
            cb->__remove_index++;
            return ret;
 
       
        
    }  
}

void print_function (void* self) 
{
    circular_buffer_t* cb = (circular_buffer_t*)self;

    int* ptr = (int*)cb->__buffer;

    for (int i = 0 ; i < cb->size ; i++) {
        printf("values: %d\n" , ptr[i]);
    }






}
