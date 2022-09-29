#pragma once

#include <defines.hpp>

#include <memory>

void add_general_allocation_num(size_t numObjects);
void minus_general_allocation_num(size_t numObjects);

namespace irl
{
    template<typename T>
    IRL_API class general_allocator 
    {
    public:
        using value_type = T;
        using pointer = T *;
        using const_pointer = const T *;
        using size_type = size_t;
    
        template<typename U>
        struct rebind
        {
            typedef general_allocator<U> other;
        };

        pointer allocate(size_type numObjects) 
        {
            add_general_allocation_num(numObjects);
            return static_cast<pointer>(operator new(sizeof(T) * numObjects));
        }
        void deallocate(pointer p, size_t numObjects)
        {
            minus_general_allocation_num(numObjects);
            operator delete(p);
        }

        
    };
    template<typename T>
    T* general_allocate()
    {
        add_general_allocation_num(1);
        return static_cast<T*>(operator new(sizeof(T)));
    }

    template<typename T>
    T* general_allocate(size_t numObjects)
    {
        add_general_allocation_num(numObjects);
        return static_cast<T*>(operator new(sizeof(T) * numObjects));
    }

    template<typename T>
    void general_deallocate(T* p)
    {
        minus_general_allocation_num(1);
        delete p;
    }

    template<typename T>
    void general_deallocate(T* p, size_t numObjects)
    {
        minus_general_allocation_num(numObjects);
        delete[] p;
    }
} // namespace irl

IRL_API size_t get_all_general_allocations();
IRL_API size_t get_general_allocationsNow();