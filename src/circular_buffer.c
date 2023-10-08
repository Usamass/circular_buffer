#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <unistd.h>
#include "circular_buffer.h"

#define ERROR_LOG(msg,...) printf("threading ERROR: " msg "\n" , ##__VA_ARGS__)


NO_RETURN cb_init(void* self, types type, unsigned int size)
{
    circular_buffer_t* cb = (circular_buffer_t*)self;
    
    cb->size = size;
    cb->__type = type;
    cb->remaining = (cb->size - abs(cb->__add_index - cb->__remove_index));
    int rc = pthread_mutex_init(&cb->__mutx , NULL);
    if (rc != 0) {
        ERROR_LOG("Mutex initalization failed!\n");
    }
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

    int rc = pthread_mutex_lock(&cb->__mutx);

    if (rc != 0) {
        ERROR_LOG("Mutex locking failed!\n");
    }       
    switch (cb->__type)
    {
        case Int:
            int* int_ptr = (int*)cb->__buffer;

        // printf("remaining space: %d\n" , cb->remaining);
            int_ptr[cb->__add_index % buf_size] = INT_CAST(value);
            cb->__add_index++;  
            cb->remaining = (buf_size - abs(cb->__add_index - cb->__remove_index));
        break;

        case Char:
            char* char_ptr = (char*)cb->__buffer;

        // printf("remaining space: %d\n" , cb->remaining);
            char_ptr[cb->__add_index % buf_size] = CHAR_CAST(value);
            cb->__add_index++;  
            cb->remaining = (buf_size - abs(cb->__add_index - cb->__remove_index));
        
        break;
        
        default:

            fprintf(stderr , "ERROR: unknown date type\n");
            break;
    } 
    rc = pthread_mutex_unlock(&cb->__mutx);
     if (rc != 0) {
        ERROR_LOG("Mutex unlocking failed!\n");
    }


    
}
GENERIC_TYPE cb_remove(void *self)
{
    circular_buffer_t* cb = (circular_buffer_t*)self;
    unsigned int buf_size = cb->size;
    cb->remaining = (buf_size - abs(cb->__add_index - cb->__remove_index));
    GENERIC_TYPE ret;
    
    int rc = pthread_mutex_lock(&cb->__mutx);

    if (rc != 0) {
        ERROR_LOG("Mutex locking failed!\n");
    }
    // printf("add_index: %d \t remove_index: %d\n" , cb->__add_index , cb->__remove_index);
    switch (cb->__type)
    {
        case Int:
            int* int_ptr = (int*)cb->__buffer;

            // printf("remaining space: %d\n" , cb->remaining);
            ret = &int_ptr[cb->__remove_index % buf_size];
            cb->__remove_index++;

            rc = pthread_mutex_unlock(&cb->__mutx);
            if (rc != 0) {
                ERROR_LOG("Mutex unlocking failed!\n");
            }

            return ret;
            
        break;

        case Char:
            char* char_ptr = (char*)cb->__buffer;

            // printf("remaining space: %d\n" , cb->remaining);
            ret = &char_ptr[cb->__remove_index % buf_size];
            cb->__remove_index++;

            rc = pthread_mutex_unlock(&cb->__mutx);
            if (rc != 0) {
                ERROR_LOG("Mutex unlocking failed!\n");
            }
            
            return ret;
        break;
 
       
        
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
