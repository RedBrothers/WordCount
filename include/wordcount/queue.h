#ifndef WORDCOUNT_QUEUE_H
#define WORDCOUNT_QUEUE_H

#include <deque>
#include <mutex>
#include <condition_variable>

// TODO: implement Queue<T>
/*
 * Thread-Safe Deque implementation
 */
template<typename T>
class Deque {
public:
    void push_front(const T&);
    void push_front(T&&);
    void push_back(const T&);
    void push_back(T&&);
    T pop_front();
    T pop_back();

    [[nodiscard]] size_t size() const;
private:
    std::deque<T> queue_;
    std::mutex m_;
    std::condition_variable cond_;
};


template<typename T>
void Deque<T>::push_front(const T& el) {
    std::unique_lock lock{ m_ };
    queue_.push(el);
    lock.unlock();
}

template<typename T>
void Deque<T>::push_front(T&& el) {
    std::unique_lock lock{ m_ };
    queue_.push(std::move(el));
    lock.unlock();
}

template<typename T>
void Deque<T>::push_back(const T& el) {
    std::unique_lock lock{ m_ };
    queue_.push(el);
    lock.unlock();
}

template<typename T>
void Deque<T>::push_back(T&& el) {
    std::unique_lock lock{ m_ };
    queue_.push(std::move(el));
    lock.unlock();
}

template<typename T>
T Deque<T>::pop_front() {
    std::unique_lock lock{ m_ };
    auto el = queue_.back();
    queue_.pop();
    lock.unlock();
    return el;
}

template<typename T>
T Deque<T>::pop_back() {
    std::unique_lock lock{ m_ };
    auto el = queue_.back();
    queue_.pop();
    lock.unlock();
    return el;
}

template<typename T>
size_t Deque<T>::size() const {
    std::lock_guard lock{ m_ };
    return queue_.size();
}

#endif //WORDCOUNT_QUEUE_H
