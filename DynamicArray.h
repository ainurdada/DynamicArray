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

	const T& operator[](int index) const;
	T& operator[](int index);
private:
	T* buf_;
	int capacity_;
	int length_;
	const float kExp = 1.6f;
};

#include "DynamicArray.hpp"