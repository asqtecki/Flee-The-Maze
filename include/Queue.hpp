#pragma once

#include <stdexcept>

template <typename T>
class Queue {
    struct node {
        T value;
        node* next;
        node(T val) : value(val), next(nullptr) {}
    };
    node* front;
    node* rear;
    int size;
    public:
        Queue() : size(0) {
            front = rear = nullptr;
        }
        Queue(const Queue<T>& q) : size(0) {
            front = rear = nullptr;
            node* temp = q.front;
            while (temp) {
                enqueue(temp->value);
                temp = temp->next;
            }
        }
        Queue<T>& operator = (const Queue<T>& q) {
            if (this==&q) return *this;
            clear();
            node* temp = q.front;
            while (temp) {
                enqueue(temp->value);
                temp = temp->next;
            }
            return *this;
        }
        bool isEmpty() const {
            return size == 0;
        }
        void enqueue(T val) {
            node* temp = new node{val};
            if (rear==nullptr) front = rear = temp;
            else {
                rear->next = temp;
                rear = temp;
            }
            size++;
        }
        T dequeue() {
            if (isEmpty()) throw std::runtime_error("Queue is empty!");
            node* temp = front;
            T val = temp->value;
            front = front->next;
            if (front==nullptr) rear = nullptr;
            delete temp;
            size--;
            return val;
        }
        T& peek() {
            if (isEmpty()) throw std::runtime_error("Queue is empty!");
            return front->value;
        }
        const T& peek() const {
            if (isEmpty()) throw std::runtime_error("Queue is empty!");
            return front->value;
        }
        int getSize() const {
            return size;
        }
        void clear() {
            while (!isEmpty()) dequeue();
        }

        T& operator [](int idx) {
            if (idx<0 || idx>=size) throw std::out_of_range("Index out of bounds!");
            node* temp = front;
            for (int i=0;i<idx;i++) temp = temp->next;
            return temp->value;
        }
        const T& operator [](int idx) const {
            if (idx<0 || idx>=size) throw std::out_of_range("Index out of bounds!");
            node* temp = front;
            for (int i=0;i<idx;i++) temp = temp->next;
            return temp->value;
        }
        Queue<T>& operator += (const Queue<T>& q) {
            node* temp = q.front;
            while (temp) {
                enqueue(temp->value);
                temp = temp->next;
            }
            return *this;
        }
        //comps based on size
        bool operator == (const Queue<T>& q) const { return size == q.size; }
        bool operator != (const Queue<T>& q) const { return size != q.size; }
        bool operator > (const Queue<T>& q) const { return size > q.size; }

        //iterators
        struct it {
            node* temp;
            it(node* n) : temp(n) {}
            T& operator * () { return temp->value; }
            T* operator -> () { return &temp->value;}
            it& operator ++ () { 
                temp = temp->next;
                return *this;
            }
            bool operator != (const it& i) const { return temp != i.temp; }
        };
        struct const_it {
            node* temp;
            const_it(node* n) : temp(n) {}
            const T& operator * ()  const { return temp->value; }
            const T* operator -> () const { return &temp->value; }
            const_it& operator ++ () { 
                temp = temp->next; 
                return *this;
            }
            bool operator != (const const_it& i) const { return temp != i.temp; }
        };
        it begin() { return it(front); }
        it end()   { return it(nullptr); }
        const_it begin() const { return const_it(front); }
        const_it end() const { return const_it(nullptr); }

        ~Queue() {
            clear();
        }
};