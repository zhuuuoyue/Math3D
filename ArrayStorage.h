#ifndef _ARRAY_STORAGE_H_INCLUDED_
#define _ARRAY_STORAGE_H_INCLUDED_

#include "Defs.h"

#include <algorithm>

M3D_BEGIN

template<typename T, size_t R, size_t C>
class ArrayStorage
{
public:

    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using size_type = size_t;
    using index_type = size_t;

    enum {
        ROWS = R,
        COLUMNS = C,
        SIZE = ROWS * COLUMNS,
    };

    using self = ArrayStorage<T, R, C>;

public:

    ArrayStorage() : m_data{ nullptr } {
        m_data = new value_type[SIZE];
    }

    explicit ArrayStorage(const_reference value) : ArrayStorage{} {
        std::fill_n(m_data, SIZE, value);
    }

    ArrayStorage(const self& other) : ArrayStorage{} {
        std::copy_n(other.m_data, SIZE, m_data);
    }

    ArrayStorage(self&& other) : m_data { nullptr } {
        std::swap(m_data, other.m_data);
    }

    ArrayStorage& operator=(const self& other) {
        if (this != &other) {
            std::copy_n(other.m_data, SIZE, m_data);
        }
        return *this;
    }

    ArrayStorage& operator=(self&& other) {
        if (this != &other) {
            if (m_data) {
                delete[] m_data;
                m_data = nullptr;
            }
            std::swap(other.m_data, m_data);
        }
        return *this;
    }

    ~ArrayStorage() {
        if (m_data) {
            delete[] m_data;
            m_data = nullptr;
        }
    }

    constexpr size_type size() const { return ROWS * COLUMNS; }

    constexpr size_type rows() const { return ROWS; }

    constexpr size_type cols() const { return COLUMNS; }

    pointer data() { return m_data; }

    const_pointer data() const { return m_data; }

    const_reference operator()(index_type row, index_type col) const {
        return operator()(convert_index(row, col));
    }

    reference operator()(index_type row, index_type col) {
        return operator()(convert_index(row, col));
    }

    const_reference operator()(index_type index) const {
        return *(m_data + index);
    }

    reference operator()(index_type index) {
        return *(m_data + index);
    }

private:

    index_type convert_index(index_type row, index_type col) const {
        return COLUMNS * row + col;
    }

private:

    pointer m_data;

};

template<typename T, size_t R, size_t C>
class InvalidArrayStorage
{
public:

    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using size_type = size_t;
    using index_type = size_t;

    enum {
        ROWS = R,
        COLUMNS = C
    };

private:

    value_type m_value;

};

#define DEFINE_BASE_AND_USE_DEFINITIONS(T, R, C) \
public: \
    using Base = InvalidArrayStorage<T, R, C>; \
    using Base::value_type; \
    using Base::reference; \
    using Base::const_reference; \
    using Base::pointer; \
    using Base::const_pointer; \
    using Base::size_type; \
    using Base::index_type; \
    using Base::ROWS; \
    using Base::COLUMNS;

template<typename T, size_t C>
class ArrayStorage<T, 0, C> : public InvalidArrayStorage<T, 0, C>
{
    DEFINE_BASE_AND_USE_DEFINITIONS(T, 0, C)
};

template<typename T, size_t R>
class ArrayStorage<T, R, 0> : public InvalidArrayStorage<T, R, 0>
{
    DEFINE_BASE_AND_USE_DEFINITIONS(T, R, 0)
};

template<typename T>
class ArrayStorage<T, 0, 0> : public InvalidArrayStorage<T, 0, 0>
{
    DEFINE_BASE_AND_USE_DEFINITIONS(T, 0, 0)
};

#undef DEFINE_BASE_AND_USE_DEFINITIONS

M3D_END

#endif // _ARRAY_STORAGE_H_INCLUDED_
