#pragma once
#include <iostream>

template<typename T>
class Array final {
public:
	class Iterator {
	public:
		Iterator(Array<T>* arr, int delta)
			: arr_(arr),
			index_(0),
			delta_(delta)
		{};

		const T& get() const;
		void set(const T& value);
		void next();
		bool hasNext() const;
	private:
		Array<T>* arr_;
		int index_;
		int delta_;
	};

	Array();
	explicit Array(int capacity);
	~Array();

	int insert(const T& value);
	int insert(int index, const T& value);
	int insert(T&& value);
	int insert(int index, T&& value);
	void remove(int index);
	int size() const;
	Iterator iterator();
	Iterator reverseIterator();
	//ConstIterarto iterator() const;

	const T& operator[](int index) const;
	T& operator[](int index);
private:
	T* buf_;
	int capacity_;
	int length_;
	const float kExp = 1.6f;
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
	for (int i = 0; i < length_; i++) {
		buf_[i].~T();
	}
	free(buf_);
}


template<typename T>
int Array<T>::insert(const T& value) {
	return insert(length_, value);
}
template<typename T>
int Array<T>::insert(int index, const T& value) {
	if (length_ == capacity_) {
		T* oldBuf = buf_;
		capacity_ *= kExp;
		length_ += 1;
		buf_ = (T*)malloc(capacity_ * sizeof(T));
		for (int i = 0; i < index; i++) {
			new (buf_ + i) T(move(oldBuf[i]));
		}

		new (buf_ + index) T(value);

		for (int i = index + 1; i < length_; i++) {
			new (buf_ + i) T(move(oldBuf[i - 1]));
		}

		for (int i = 0; i < length_ - 1; i++) {
			oldBuf[i].~T();
		}
	}

	else
	{
		for (int i = length_; i > index; i--) {
			new (buf_ + i) T(move(buf_[i - 1]));
			buf_[i - 1].~T();
		}
		length_ += 1;
		new (buf_ + index) T(value);
	}
	return index;
}
template<typename T>
int Array<T>::insert(T&& value) {
	return insert(length_, value);
}
template<typename T>
int Array<T>::insert(int index, T&& value) {
	if (length_ == capacity_) {
		T* oldBuf = buf_;
		capacity_ *= kExp;
		length_ += 1;
		buf_ = (T*)malloc(capacity_ * sizeof(T));
		for (int i = 0; i < index; i++) {
			new (buf_ + i) T(move(oldBuf[i]));
		}

		new (buf_ + index) T(move(value));

		for (int i = index + 1; i < length_; i++) {
			new (buf_ + i) T(move(oldBuf[i - 1]));
		}

		for (int i = 0; i < length_ - 1; i++) {
			oldBuf[i].~T();
		}
	}

	else
	{
		for (int i = length_; i > index; i--) {
			new (buf_ + i) T(move(buf_[i - 1]));
			buf_[i - 1].~T();
		}
		length_ += 1;
		new (buf_ + index) T(move(value));
	}
	return index;
}


template<typename T>
void Array<T>::remove(int index) {
	buf_[index].~T();
	for (int i = index; i < length_ - 1; i++) {
		new (buf_ + i) T(move(buf_[i + 1]));
		buf_[i + 1].~T();
	}
	length_ -= 1;
}
template<typename T>
int Array<T>::size() const {
	return length_;
}
template<typename T>
typename Array<T>::Iterator Array<T>::iterator() {
	return *(new Iterator{ this, 1 });
}
template<typename T>
typename Array<T>::Iterator Array<T>::reverseIterator() {
	return *(new Iterator{ this, -1 });
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
const T& Array<T>::Iterator::get() const {
	return arr_->buf_[index_];
}
template<typename T>
void Array<T>::Iterator::set(const T& value) {
	arr_->buf_[index_](value);
}
template<typename T>
void Array<T>::Iterator::next() {
	index_ += delta_;
}
template<typename T>
bool Array<T>::Iterator::hasNext() const {
	if (index_ + delta_ < arr_->length_ && index_ + delta_ >= 0) return true;
	else return false;
}