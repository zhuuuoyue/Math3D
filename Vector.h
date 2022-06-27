#ifndef _VECTOR_H_INCLUDED_
#define _VECTOR_H_INCLUDED_

#include "ArrayStorage.h"
#include "Defs.h"

#include <iostream>

M3D_BEGIN

enum VectorType {
    ROW,
    COLUMN
};

template<typename T, size_t S, int VT = VectorType::ROW>
class Vector {
private:

    enum {
        ROWS = VectorType::COLUMN == VT ? S : 1,
        COLUMNS = VectorType::ROW == VT ? S : 1,
        SIZE = ROWS * COLUMNS,
    };

public:

    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = size_t;
    using index_type = size_t;
    using data_storage = ArrayStorage<T, ROWS, COLUMNS>; // debug

    Vector() = default;

    constexpr size_type length() const { return SIZE; }

    const_reference operator()(index_type index) const {
        return m_storage(index);
    }

    reference operator()(index_type index) {
        return m_storage(index);
    }

    // debug
    const data_storage* data() const { return &m_storage; }

private:

    data_storage m_storage;

};

template<typename T, int VT>
class Vector<T, 0, VT> {
public:

    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = size_t;
    using index_type = size_t;
    using data_storage = ArrayStorage<T, 1, 1>; // debug

    Vector() = default;

    constexpr size_type length() const { return 0; }

    const_reference operator()(index_type index) const {
        return m_storage(0);
    }

    reference operator()(index_type index) {
        return m_storage(0);
    }

    // debug
    const data_storage* data() const { return nullptr; }

private:

    data_storage m_storage;

};

template<typename T, size_t S>
using RowVector = Vector<T, S, VectorType::ROW>;

template<typename T, size_t S>
using ColumnVector = Vector<T, S, VectorType::COLUMN>;

#define SPECIALIZE_VECTOR(VALUE_TYPE, LENGTH, SUFFIX) \
using Vector##LENGTH##SUFFIX = Vector<VALUE_TYPE, LENGTH, VectorType::ROW>;

SPECIALIZE_VECTOR(int, 2, i)
SPECIALIZE_VECTOR(int, 3, i)
SPECIALIZE_VECTOR(int, 4, i)
SPECIALIZE_VECTOR(float, 2, f)
SPECIALIZE_VECTOR(float, 3, f)
SPECIALIZE_VECTOR(float, 4, f)
SPECIALIZE_VECTOR(double, 2, d)
SPECIALIZE_VECTOR(double, 3, d)
SPECIALIZE_VECTOR(double, 4, d)

#undef SPECIALIZE_VECTOR

M3D_END

#endif // _VECTOR_H_INCLUDED_
