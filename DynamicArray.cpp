#include <iostream>

#include <stdlib.h>
#include "DynamicArray.h"

template<typename T>
Array<T>::Array() {
	capacity_ = 8;
	buf_ = (T*)malloc(capacity_ * sizeof(T));
}
template<typename T>
Array<T>::Array(int capacity) {
	capacity_ = capacity;
	buf_ = (T*)malloc(capacity_ * sizeof(T));
}



template<typename T>
void Array<T>::Debug() {
	std::cout << capacity_ << std::endl;
	std::cout << sizeof(T) * capacity_ << std::endl;
}