#pragma once
#include <iostream>

template<typename T>
class Array final {
public:
	class Iterator final {
	public:
		Iterator(Array<T>* arr, int delta);

		T& get() const;
		void set(const T& value);
		void next();
		bool hasNext() const;
	private:
		Array<T>* arr_;
		int index_;
		int delta_;
	};

	class ConstIterator final {
	public:
		ConstIterator(Array<T>* arr, int delta);

		const T& get() const;
		void next();
		bool hasNext() const;
	private:
		Iterator it;
	};

	Array();
	explicit Array(int capacity);
	Array(const Array& other);
	Array(Array&& other);
	~Array();

	int insert(const T& value);
	int insert(int index, const T& value);
	int insert(T&& value);
	int insert(int index, T&& value);
	void remove(int index);
	int size() const;
	Iterator iterator();
	Iterator reverseIterator();
	ConstIterator iterator() const;
	ConstIterator reverseIterator() const;

	const T& operator[](int index) const;
	T& operator[](int index);

	Array<T>& operator=(const Array<T>& other);
	Array<T>& operator=(Array<T>&& other);
private:
	void reset();

	T* buf_;
	int capacity_;
	int length_;
	const float kExp = 1.6f;
};

#include "DynamicArray.hpp"