#ifndef _QUEUE_H
#define _QUEUE_H

#include <iostream>
using namespace std;

template<typename Type>
struct Node{
    Type val;
    Node *nptr;
    Node *pptr;
};


template<typename Type>
class Queue{
    public:
    Queue();
    Queue(const Queue &src);
    ~Queue();

    void enqueue(Type n);
    void dequeue();
    void print();
    bool isEmpty();

    Queue &operator=(const Queue &src);

    private:
    Node<Type> *sptr;
    Node<Type> *eptr;
};

#endif