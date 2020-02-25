#ifndef WORDCOUNT_QUEUE_H
#define WORDCOUNT_QUEUE_H

#include <vector>

// TODO: implement Queue<T>
template<typename T>
class Queue {
public:
    T pop() {}
    void push(const T&) {}
private:
    std::vector<T> queue;
};

#endif //WORDCOUNT_QUEUE_H
