#include "HashAraay.h"
#include <assert.h>

int main() {
	HashArray<int, int> curr;
	curr.insert(0, 0);
	curr.insert(100, 100);
	curr.insert(1000, 1000);
	curr.insert(1,1);
	curr.insert(2,2);
	curr.insert(3,3);
	curr.insert(4,4);
	curr.insert(5,5);
	int return_val = curr.insert(1, 1);
	assert(return_val == -1);
	curr.insert(2, 2);
	curr.insert(3, 3);
	curr.insert(4, 4);
	curr.insert(5, 5);
	int array[10] = { 10,9,8,7,6,5,4,3,2,1 };
	HashArray<int, int> curr_2(10,array,array);
	Node<int, int>** arr = curr.getArr();
	Node<int, int>** arr_2 = curr_2.getArr();
	for (int i = 0; i < 1000000; i++)
	{
		int k = rand();
		curr.insert(k, k);
		curr_2.insert(k, k);
	}
	for (int i = 0; i < 100; i++)
	{
		arr++;
		arr_2++;
	}

	return 0;
}