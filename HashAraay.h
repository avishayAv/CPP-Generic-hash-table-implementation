#ifndef HASH_ARRAY_H
#define HASH_ARRAY_H

#include <iostream>
#include <ostream>
#include <algorithm>


/*
template V for value
template K for k 
*/
template<class V, class K>

class NodeHash
{

public:

	V val;
	K key;
	NodeHash<V, K>* next;
	NodeHash(V val_1, K key_1, NodeHash<V, K>* next_1 = NULL) : val(val_1), key(key_1), next(next_1){};
	void setNext(NodeHash<V, K>* next_1) { next = next_1; };
	~NodeHash() {};

};

/*
template V for value
template K for k
*/
template<class V, class K>
class HashArray
{
private:
	NodeHash<V, K>** arr;
	int capacity;
	int size;


public:
	/*
	default constuctor for hash array' with capacity 100 for beggining
	*/
	HashArray() : capacity(100), size(0) {
		arr = new NodeHash<V,K>*[capacity];
		for (int i = 0; i < capacity; i++)
		{
			arr[i] = NULL;
		}
	};

	/*
	constuctor for hash array with array of n values to insert 
	note: values nust be different no check will be done
	*/
	HashArray(int n, V* values, K* keys) {
		capacity = n * 11;
		size = n;
		arr = new NodeHash<V, K>*[capacity];
		for (int i = 0; i < capacity; i++)
		{
			arr[i] = NULL;
		}
		for (int i = 0; i < n; i++)
		{
			NodeHash<V, K>* new_NodeHash = new NodeHash<V, K>(values[i], keys[i]);
			int index = keys[i] % capacity;
			new_NodeHash->setNext(arr[index]);
			arr[index] = new_NodeHash;
		}
	};

	/*
	make hash array 4 time bigger
	in order to keep hasharray in O(n) size
	return: -2 for allocation error, 0 for success.
	*/
	int correctSize() {
		if (size / capacity >= 4) {
			capacity *= 4;
			NodeHash<V, K>** new_arr = new NodeHash<V, K>*[capacity];
			if (new_arr == NULL)
			{
				return -2;
			}
			for (int i = 0; i < capacity; i++)
			{
				new_arr[i] = NULL;
			}
			NodeHash<V, K>* temp;
			NodeHash<V, K>* temp_2;
			for (int i = 0; i < capacity / 4; i++)
			{
				temp = arr[i];
				while (temp != NULL) {
					int index = temp->key % capacity;
					temp_2 = temp->next;
					temp->setNext(new_arr[index]);
					new_arr[index] = temp;
					temp = temp_2;
				}
			}
			NodeHash<V, K>** to_delete = this->arr;
			this->arr = new_arr;
			delete[] to_delete;
			
		}
		return 0;
	};

	/*
	input: value to insert and his key
	output: -1 if key already exist, -2 for allocation error, 0 for success.
	*/
	int insert(V value, K key) {
		int index = key % capacity;
		NodeHash<V, K>* temp;
		temp = arr[index];
		while (temp != NULL)
		{
			if (temp->key == key)
			{
				return -1;
			}
			temp = temp->next;
		}
		NodeHash<V, K>* new_NodeHash = new NodeHash<V, K>(value, key);
		if (new_NodeHash == NULL)
		{
			return -2;
		}
		temp = arr[index];
		arr[index] = new_NodeHash;
		new_NodeHash->setNext(temp);
		size++;
		return this->correctSize();
	};
	
	/*
	input: key
	output: null for not found, else return value
	*/
	V* getVal(K key)
	{
		int index = key % capacity;
		NodeHash<V, K>* temp;
		temp = arr[index];
		while (temp != NULL)
		{
			if (temp->key == key)
				return &(temp->val);
			temp = temp->next;
		}
		return NULL;
	};

	NodeHash<V, K>** getArr() {
		return this->arr;
	}

	void getPtrArr(V** arr_ptr){
		NodeHash<V, K>* temp;
		int index = 0;
		for (int i = 0; i < capacity; i++)
		{
			temp = arr[i];
			while (temp != NULL) {
				arr_ptr[index] = &(temp->val);
				index++;
				temp = temp->next;
			}
		}
	}
	int getSize() {
		return this->size;
	}
	~HashArray() {
		/*NodeHash<V, K>* temp;
		NodeHash<V, K>* temp_2;
		for (int i = 0; i < capacity; i++)
		{
			temp = arr[i];
			while (temp != NULL) {
				temp_2 = temp->next;
				delete temp;
				temp = temp_2;
			}
		}*/
		delete[] this->arr;
	};
};
#endif