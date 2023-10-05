#pragma once

template<typename T>
class Array final {
public:
    Array();
    Array(int capacity);

    void Debug();
private:
    T* buf_;
    int capacity_;
};