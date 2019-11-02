#pragma once
#include <atomic>
#include <cstdio>

template <typename T>
class SharedPtr {
private:
    T* pointer = nullptr;
    std::atomic_uint* use_counter = nullptr;
public:
    SharedPtr();
    SharedPtr(T* ptr) noexcept;
    SharedPtr(const SharedPtr& r);
    SharedPtr(SharedPtr&& r);
    ~SharedPtr();

    SharedPtr<T>& operator = (const SharedPtr& r);SharedPtr<T>& operator = (SharedPtr&& r);
    operator bool() const;
    T& operator*() const;
    T* operator->() const;

    auto get()->T*;
    void reset();
    void reset(T* ptr);
    void swap(SharedPtr& r);

    std::atomic_uint* use_count() const;
};

template <typename T>
SharedPtr<T>::SharedPtr()
{
    pointer = nullptr;
    use_counter = new std::atomic_uint{0};
}

template <typename T>
SharedPtr<T>::SharedPtr(T* ptr) noexcept
{
    pointer = ptr;
    use_counter = new std::atomic_uint{ 1 };
}

template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr& r)
{
    this = r;
}

template <typename T>
SharedPtr<T>::SharedPtr(SharedPtr&& r)
{
    this = std::move(r);
}

template <typename T>
SharedPtr<T>::~SharedPtr()
{
    if (use_counter != nullptr)
        if (*use_counter)
        {
            delete pointer;
            delete use_counter;
        }

}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator = (const SharedPtr& r)
{
    pointer = r.pointer;
    return this;
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator = (SharedPtr&& r)
{
    pointer = r.pointer;
    use_counter = r.use_count();

    r.pointer = nullptr;
    r.use_counter = nullptr;

    return *this;
}

template <typename T>
SharedPtr<T>::operator bool() const
{
    return pointer != nullptr;
}

template <typename T>
T& SharedPtr<T>::operator*() const
{
    return *pointer;
}

template <typename T>
T* SharedPtr<T>::operator->() const
{
    return pointer;
}

template <typename T>
auto SharedPtr<T>::get()->T*
{
    return pointer;
}

template <typename T>
void SharedPtr<T>::reset()
{
    *this = SharedPtr();
}

template <typename T>
void SharedPtr<T>::reset(T* ptr)
{
    *this = SharedPtr(ptr);
}

template <typename T>
void SharedPtr<T>::swap(SharedPtr& r)
{
    std::swap(pointer, r.pointer);
    std::swap(use_counter, r.use_counter);
}

template <typename T>
std::atomic_uint* SharedPtr<T>::use_count() const
{
    return use_counter;
}