
#include <cstdint>
#include <cstddef>
#include <stdlib.h>
#include <stdexcept>

template <typename T, size_t CAPACITY>
class StaticVectSimple
{
    public:
        StaticVectSimple():
            _size(0)
        {}

        StaticVectSimple(const StaticVectSimple& other):
            _size(other._size)
        {
            for (size_t i = 0; i < other.size(); i++)
            {
                _elems[i] = other[i];
            }
        }

        ~StaticVectSimple()
        {
            clear();
        }

        void push_back(T& item)
        {
            if (!is_full())
            {
                _elems[_size] = item;
            }
            else
            {
                throw std::out_of_range("Static vector is full");
            }
        }

        T& pop()
        {
            if (!is_empty())
            {
                T* ret = _elems[_size-1];
                _size--;
                return *T;
            }
            else
            {
                throw std::out_of_range("Static vector is empty");
            }
        }

        const T& operator[](const size_t idx) const
        {
            if (idx < _size)
            {
                return _elems[idx];
            }
            else
            {
                throw std::out_of_range("Index is out of range")
            }
        }

        T& operator[](const size_t idx)
        {
            if (idx < _size)
            {
                return _elems[idx];
            }
            else
            {
                throw std::out_of_range("Index is out of range")
            }
        }

        size_t size() const { return _size; }

        constexpr size_t capcity() const { return CAPACITY; }

        bool is_full() const { return _size == CAPACITY; }

        bool is_empty() const { return _size == 0; }

        void clear() { _size = 0; }

        T& begin() { return _elems[0]; }
        const T& begin() const { return _elems[0]; }
        T& end() { return _elems[_size-1]; }
        const T& end() const { return _elems[_size-1]; }

    private:
        alignas(sizeof(T)) T _elems[CAPACITY];
        size_t _size;
};


#include <cstddef>
#include <stdexcept>
#include <new>        // placement new
#include <utility>    // std::move
#include <type_traits>

template<typename T, std::size_t Capacity>
class StaticVectAdvanced {
public:
    StaticVectAdvanced() : size_(0) {}

    // Copy constructor
    StaticVectAdvanced(const StaticVectAdvanced& other) : size_(0) {
        for (std::size_t i = 0; i < other.size_; ++i) {
            new (&data_[i]) T(other[i]);
        }
        size_ = other.size_;
    }

    // Move constructor
    StaticVectAdvanced(StaticVectAdvanced&& other) noexcept : size_(0) {
        for (std::size_t i = 0; i < other.size_; ++i) {
            new (&data_[i]) T(std::move(other[i]));
        }
        size_ = other.size_;
        other.clear();
    }

    // Copy assignment
    StaticVectAdvanced& operator=(const StaticVectAdvanced& other) {
        if (this != &other) {
            clear();
            for (std::size_t i = 0; i < other.size_; ++i) {
                new (&data_[i]) T(other[i]);
            }
            size_ = other.size_;
        }
        return *this;
    }

    // Move assignment
    StaticVectAdvanced& operator=(StaticVectAdvanced&& other) noexcept {
        if (this != &other) {
            clear();
            for (std::size_t i = 0; i < other.size_; ++i) {
                new (&data_[i]) T(std::move(other[i]));
            }
            size_ = other.size_;
            other.clear();
        }
        return *this;
    }

    // Destructor
    ~StaticVectAdvanced() {
        clear();
    }

    // Element access
    T& operator[](std::size_t index) {
        return *reinterpret_cast<T*>(&data_[index]);
    }

    const T& operator[](std::size_t index) const {
        return *reinterpret_cast<const T*>(&data_[index]);
    }

    T& at(std::size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return (*this)[index];
    }

    const T& at(std::size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return (*this)[index];
    }

    // Modifiers
    void push_back(const T& value) {
        if (size_ >= Capacity) {
            throw std::overflow_error("Capacity exceeded");
        }
        new (&data_[size_]) T(value);
        ++size_;
    }

    void push_back(T&& value) {
        if (size_ >= Capacity) {
            throw std::overflow_error("Capacity exceeded");
        }
        new (&data_[size_]) T(std::move(value));
        ++size_;
    }

    void pop_back() {
        if (size_ == 0) {
            throw std::underflow_error("Empty");
        }
        --size_;
        reinterpret_cast<T*>(&data_[size_])->~T();
    }

    void clear() {
        for (std::size_t i = 0; i < size_; ++i) {
            reinterpret_cast<T*>(&data_[i])->~T();
        }
        size_ = 0;
    }

    // Capacity
    std::size_t size() const { return size_; }
    constexpr std::size_t capacity() const { return Capacity; }
    bool empty() const { return size_ == 0; }

private:
    // Raw, uninitialized storage
    typename std::aligned_storage<sizeof(T), alignof(T)>::type data_[Capacity];
    std::size_t size_;
};
