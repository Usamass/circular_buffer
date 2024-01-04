#include <stdio.h>
#include <inttypes.h>
#include <pthread.h>
#include "src/circular_buffer.h"


int main (int argc , char* argv[]) 
{
	int values[10] = {1 , 2, 5 , 9 , 85 , 27 , 38 , 49 , 45 , 10};
	char c_values[10] = "helloworld";
	int single_value = 199;
	/* initializing 2 buffers one for int and the other for char */
	circular_buffer_t cb1 = initialization();
	circular_buffer_t cb2 = initialization();

	cb1.buffer_init(&cb1 , Int , 5);
	cb2.buffer_init(&cb2 , Char , 5);


	size_t i = 0;
	/*filling the (int)integer buffer*/
	while (cb1.remaining != 0) {
		cb1.add_item(&cb1 , &single_value);
		i++;
	}
	printf("Integer buffer is full now!\n");

	printf("removing items from the integer buffer...\n");

    /*removing the items from the buffer*/
	while (cb1.remaining != cb1.size -1) {
		printf("items %d\n" , INT_CAST(cb1.remove_item(&cb1)));
	}


	i = 0;
	/*filling the (char)character buffer*/

	while (cb2.remaining != 0) {
		cb2.add_item(&cb2 , &c_values[i]);
		i++;
	}
	printf("character buffer is full now!\n");


	printf("removing items from the character buffer...\n");


	/*removing the items from the buffer*/
	while (cb2.remaining != cb2.size -1) {
		printf("items %c\n" , CHAR_CAST(cb2.remove_item(&cb2)));
	}


	return 0;
}

