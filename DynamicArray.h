#pragma once
#include <iostream>
#include <stdlib.h>
#include <iterator>
#include <vector>

template<typename T>
class Array final {
public:
    Array();
    Array(int capacity);
	~Array();

	int insert(const T& value);
	int insert(int index, const T& value);
	void remove(int index);
	int size() const;
	Iterator iterator();
	ConstIterarto iterator() const;

	const T& operator[](int index) const;
	T& operator[](int index);

    void Debug();

private:
	void deleteBuf();
private:
    T* buf_;
    int capacity_;
	int length_;
	const float kExp = 1.6;
};

using namespace std;

template<typename T>
Array<T>::Array() {
	capacity_ = 8;
	length_ = 0;
	buf_ = (T*)malloc(capacity_ * sizeof(T));
}
template<typename T>
Array<T>::Array(int capacity) {
	capacity_ = capacity;
	length_ = 0;
	buf_ = (T*)malloc(capacity_ * sizeof(T));
}
template<typename T>
Array<T>::~Array() {
	deleteBuf();
}

template<typename T>
int Array<T>::insert(const T& value) {
	return insert(length_, value);
}
template<typename T>
int Array<T>::insert(int index, const T& value) {
	length_++;
	if (length_ > capacity_) {
		T* old_buf = buf_;
		capacity_ *= kExp;
		buf_ = (T*)malloc(capacity_ * sizeof(T));

		for (int i = 0; i < index; i++) {
			buf_[i] = move(old_buf[i]);
			delete (old_buf[i]);
		}

		new (buf_[index]) T(value);

		for (int i = index + 1; i < length_; i++) {
			buf_[i] = move(old_buf[i]);
			delete (old_buf[i]);
		}
	}

	else
	{
		for (int i = length_; i > index; i--) {
			buf_[i] = move(buf_[i - 1]);
		}
		new (buf_[index]) T(value);
	}
}
template<typename T>
void Array<T>::remove(int index) {
	for (int i = index; i < length_ - 1; i++) {
		buf_[i] = move(buf_[i + 1]);
	}
	length_--;
}
template<typename T>
int Array<T>::size() const {
	return length_;
}
template<typename T>
Iterator Array<T>::iterator() {
}


template<typename T>
const T& Array<T>::operator[](int index) const {
	return buf_[index];
}
template<typename T>
T& Array<T>::operator[](int index) {
	return buf_[index];
}

template<typename T>
void Array<T>::deleteBuf() {
	for (int i = 0; i < length_; i++) {
		delete (buf_ + 1);
	}
	free(buf_);
}

template<typename T>
void Array<T>::Debug() {
	std::cout << capacity_ << std::endl;
	std::cout << sizeof(T) * capacity_ << std::endl;
}