#ifndef _DEBUG_H_INCLUDED_
#define _DEBUG_H_INCLUDED_

#include "ArrayStorage.h"
#include "Vector.h"

#include <iostream>

template<typename T, size_t R, size_t C>
std::ostream& operator<<(std::ostream& os, const M3D ArrayStorage<T, R, C>& storage)
{
    for (int i = 0; i < storage.rows(); ++i) {
        for (int j = 0; j < storage.cols(); ++j) {
            if (0 == j) {
                os << "[ ";
            }
            else {
                os << ", ";
            }
            os << storage(i, j);
            if ((j + 1) == storage.cols()) {
                os << " ]";
            }
        }
        os << "\n";
    }
    return os;
}

template<typename T, size_t S, int VT>
std::ostream& operator<<(std::ostream& os, const M3D Vector<T, S, VT>& vec)
{
    os << *vec.data();
    return os;
}

#endif // _DEBUG_H_INCLUDED_
