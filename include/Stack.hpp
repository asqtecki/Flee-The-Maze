#pragma once

#include <stdexcept>

template <typename T>
class Stack {
    T* arr;
    int capacity;
    int size;
    int topIdx;
    void resize(int s) {
        T* temp = new T[s];
        for (int i=0;i<capacity;i++) temp[i] = arr[i];
        delete[] arr;
        capacity = s;
        arr = temp;
    }
    public:
        Stack(int s = 10) {
            capacity = s;
            size = 0;
            arr = new T[capacity];
            topIdx = -1;
        }
        void push(const T& val) {
            if (isFull()) resize(capacity * 2);
            size++;
            arr[++topIdx] = val;
        }
        T pop() {
            if (isEmpty()) throw std::underflow_error("Stack underflow");
            size--;
            return arr[topIdx--];
        }
        T& top() const {
            if (isEmpty()) throw std::underflow_error("Stack underflow");
            return arr[topIdx];
        }
        int getSize() const { return size; }
        bool isEmpty() const { return size == 0; }
        bool isFull() const { return size == capacity; }
        ~Stack() {
            delete[] arr;
        }
};