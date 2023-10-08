#pragma once
#include <pthread.h>
#include <stdbool.h>

#define INT_CAST(value) (*((int*)(value)))
#define CHAR_CAST(value) (*((char*)(value)))

#define initialization() { .buffer_init = cb_init, \
                           .add_item = cb_insert, \
                           .remove_item = cb_remove \
                        }


typedef enum {Int , Char , Float , Double} types;



typedef void NO_RETURN;
typedef void* GENERIC_TYPE;



typedef struct {
   /* private data*/
   int             __add_index;
   int             __remove_index;
   GENERIC_TYPE    __buffer;
   types           __type;
   pthread_mutex_t __mutx;

   /*public data*/
   unsigned int    size;
   unsigned int    remaining;

   /* public function pointers*/
   NO_RETURN (*buffer_init)(void* self , types type , unsigned int size);
   GENERIC_TYPE (*add_item)(void* self , GENERIC_TYPE value);
   GENERIC_TYPE (*remove_item)(void* self);

} circular_buffer_t;


/*Methods declaration*/
NO_RETURN cb_init(void* self , types type , unsigned int size);
GENERIC_TYPE cb_insert(void* self , GENERIC_TYPE value);
GENERIC_TYPE cb_remove(void* self);

/*utility function*/
void print_function(void*);



