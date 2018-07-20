/*
 *  ap_array - array container for Xilinx Vivado HLS
 *  Copyright (C) 2018  Bernhard Arnold <bernhard.arnold@cern.ch>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#ifndef ap_array_h
#define ap_array_h

#include <cstddef>
#include <cassert>

template<typename T, std::size_t N>
struct ap_array
{
    typedef T value_type;
    typedef std::size_t size_type;
    typedef T& reference;
    typedef const value_type& const_reference;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;

    value_type data_[N];

    reference at(size_type pos) { assert(pos < size()); return data_[pos]; }
    const_reference at(size_type pos) const { assert(pos < size()); return data_[pos]; }
    reference operator[](size_type pos) { return data_[pos]; }
    const_reference operator[](size_type pos) const { return data_[pos]; }
    reference front() { return data_[0]; }
    const_reference front() const { return data_[0]; }
    reference back() { return data_[N - 1]; }
    const_reference back() const { return data_[N - 1]; }
    pointer data() const { return data_; }
    constexpr bool empty() const { return not N; }
    constexpr size_type size() const { return N; }
    void fill(const T& value);
};

template<typename T, std::size_t N>
void ap_array<T, N>::fill(const_reference value)
{
#pragma HLS ARRAY_PARTITION variable=data_ complete dim=1
    for (size_type i = 0; i < size(); ++i)
    {
#pragma HLS UNROLL
        data_[i] = value;
    }
}

#endif
