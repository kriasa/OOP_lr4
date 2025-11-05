#pragma once
#include <iostream>
#include <concepts>
#include <memory>
#include <cassert>
#include <algorithm>
#include <type_traits>

template <class T>
concept Arrayable = std::is_default_constructible_v<T>;

template <Arrayable T>
class Array {
public:
    Array() : _size(0), _capacity(0), _array(nullptr) {
        std::cout << "Default constructor" << std::endl;
    }

    Array(const std::initializer_list<T> &t) {
        std::cout << "Initializer list constructor" << std::endl;
        _size = t.size();
        _capacity = _size;
        _array = std::shared_ptr<T[]>(new T[_capacity]);
        size_t i{0};
        for (const auto &c : t) _array[i++] = c;
    }

    Array(const Array &other) {
        std::cout << "Copy constructor" << std::endl;
        _size = other._size;
        _capacity = other._capacity;
        _array = std::shared_ptr<T[]>(new T[_capacity]);
        for (size_t i{0}; i < _size; ++i) _array[i] = other._array[i];
    }

    Array(Array &&other) noexcept {
        std::cout << "Move constructor" << std::endl;
        _size = other._size;
        _capacity = other._capacity;
        _array = std::move(other._array);
        other._size = 0;
        other._capacity = 0;
        other._array = nullptr;
    }

    Array& operator=(const Array& other) {
        if (this != &other) {
            Array temp(other);
            *this = std::move(temp);
        }
        return *this;
    }

    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            _size = other._size;
            _capacity = other._capacity;
            _array = std::move(other._array);
            other._size = 0;
            other._capacity = 0;
            other._array = nullptr;
        }
        return *this;
    }

    T& operator[](size_t index) {
        assert(index < _size);
        return _array[index];
    }

    const T& operator[](size_t index) const {
        assert(index < _size);
        return _array[index];
    }

    size_t size() const {
        return _size;
    }

    void push_back(const T& value) {
        if (_size >= _capacity)
            resize(_capacity == 0 ? 1 : _capacity * 2);
        _array[_size++] = value;
    }

    void push_back(T&& value) {
        if (_size >= _capacity)
            resize(_capacity == 0 ? 1 : _capacity * 2);
        _array[_size++] = std::move(value);
    }

    void erase(size_t index) {
        assert(index < _size);
        for (size_t i = index; i + 1 < _size; ++i) {
            _array[i] = std::move(_array[i + 1]);
        }
        --_size;
    }

    template <typename U>
    static constexpr bool has_arrow = requires(const U& u) { u->area(); };

    double totalArea() const {
        double total = 0.0;
        for (size_t i = 0; i < _size; ++i) {
            if constexpr (std::is_pointer_v<T>) {
                if (_array[i]) {
                    total += _array[i]->area();
                }
            } else if constexpr (has_arrow<T>) {
                if (_array[i]) {
                    total += _array[i]->area();
                }
            } else {
                total += _array[i].area();
            }
        }
        return total;
    }

    ~Array() noexcept {
        std::cout << "destructor: size=" << _size << std::endl;
    }

private:
    void resize(size_t new_capacity) {
        std::cout << "Resizing from " << _capacity << " to " << new_capacity << std::endl;
        auto new_array = std::shared_ptr<T[]>(new T[new_capacity]);
        for (size_t i = 0; i < _size; ++i) {
            new_array[i] = std::move(_array[i]);
        }
        _array = std::move(new_array);
        _capacity = new_capacity;
    }

    size_t _size;
    size_t _capacity;
    std::shared_ptr<T[]> _array;
};
