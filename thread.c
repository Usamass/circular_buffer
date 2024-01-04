#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>
#include "src/circular_buffer.h"

void* producer_thread(void* arg);
void* consumer_thread(void* arg);

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutx = PTHREAD_MUTEX_INITIALIZER;


int values[10] = {1 , 2, 5 , 9 , 85 , 27 , 38 , 49 , 45 , 10};


int main (int argc , char* argv[]) 
{

	circular_buffer_t cb1 = initialization();
    cb1.buffer_init(&cb1 , Int , 5);

    pthread_t prod_thread;
    pthread_t consm_thread;
    pthread_attr_t t_attr;

    pthread_cond_init(&cond , NULL);



    pthread_attr_init(&t_attr); 

    pthread_create(&prod_thread , &t_attr , (void*)producer_thread , &cb1);
    
    pthread_create(&consm_thread , &t_attr , (void*)consumer_thread , &cb1);

    /*Making program wait for the threads to finish*/
    pthread_join(prod_thread , NULL);
    pthread_join(consm_thread , NULL);

    return 0;
}


void* producer_thread(void* arg) 
{
    circular_buffer_t* buf = (circular_buffer_t*)arg;
    unsigned int buf_size = buf->size;
    int i = 0;

    while (1) {
        pthread_mutex_lock(&mutx);

        if (buf->remaining == 0) {
            printf("producer thread is on wait!\n");
            pthread_cond_wait(&cond , &mutx);
        } 

        buf->add_item(buf , &values[i%buf_size]);
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutx);

        printf("inside producer thread!\n");
        i++;

        sleep(1);
       


               
    }

    
    



       
    



}

void* consumer_thread(void* arg) 
{
    circular_buffer_t* buf = (circular_buffer_t*)arg;
    unsigned int buf_size = buf->size;
    while (1) {
        pthread_mutex_lock(&mutx);

        if (buf->remaining == buf_size -1) {
            pthread_cond_wait(&cond , &mutx);
        }

        printf("items %d\n" , INT_CAST(buf->remove_item(buf)));

        pthread_mutex_unlock(&mutx);
        pthread_cond_signal(&cond);


        sleep(5);
 
       
    }

}