#pragma once

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <stdexcept>
#include <limits>
#include <type_traits>

namespace ownstl 
{

template<class T, std::size_t N> 
struct array
{
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using iterator = pointer;
    using const_iterator = const_pointer;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    constexpr array() = default;
    constexpr array(std::initializer_list<T> ilist);
    constexpr ~array() = default;

    constexpr reference at(size_type pos);
    constexpr const_reference at(size_type pos) const;

    constexpr reference operator[](size_type pos);
    constexpr const_reference operator[](size_type pos) const;

    constexpr reference front();
    constexpr const_reference front() const;

    constexpr reference back();
    constexpr const_reference back() const;

    constexpr pointer data() noexcept;
    constexpr const_pointer data() const noexcept;

    constexpr iterator begin() noexcept;
    constexpr const_iterator begin() const noexcept;
    constexpr const_iterator cbegin() const noexcept;
    
    constexpr iterator end() noexcept;
    constexpr const_iterator end() const noexcept;
    constexpr const_iterator cend() const noexcept; 

    constexpr reverse_iterator rbegin() noexcept;
    constexpr const_reverse_iterator rbegin() const noexcept;
    constexpr const_reverse_iterator crbegin() const noexcept;

    constexpr reverse_iterator rend() noexcept;
    constexpr const_reverse_iterator rend() const noexcept;
    constexpr const_reverse_iterator crend() const noexcept;

    constexpr bool empty() const noexcept;
    constexpr size_type size() const noexcept;
    constexpr size_type max_size() const noexcept;

    constexpr void fill(const T& value);
    constexpr void swap(array& other) noexcept(std::is_nothrow_swappable_v<T>);
    
private:
    T m_data[N];
};

template<class T, std::size_t N>
constexpr array<T, N>::array(std::initializer_list<T> ilist)
{
    if (ilist.size() > N) 
        throw std::length_error("Initializer list size exceeds array capacity");
    
    std::copy(ilist.begin(), ilist.end(), m_data);
}

template<class T, std::size_t N> 
constexpr typename array<T, N>::reference array<T, N>::at(size_type pos)
{
    if (pos >= N)
        throw std::out_of_range("out of range");
    return m_data[pos];
}

template<class T, std::size_t N> 
constexpr typename array<T, N>::const_reference array<T, N>::at(size_type pos) const
{
    if (pos >= N)
        throw std::out_of_range("out of range");
    return m_data[pos];
}

template<class T, std::size_t N> 
constexpr typename array<T, N>::reference array<T, N>::operator[](size_type pos)
{
    return m_data[pos];
}

template<class T, std::size_t N> 
constexpr typename array<T, N>::const_reference array<T, N>::operator[](size_type pos) const
{
    return m_data[pos];
}

template<class T, std::size_t N> 
constexpr typename array<T, N>::reference array<T, N>::front()
{
    if (N == 0) 
        throw std::out_of_range("Cannot access front of empty array");
    
    return m_data[0];
}

template<class T, std::size_t N> 
constexpr typename array<T, N>::const_reference array<T, N>::front() const
{
    if (N == 0) 
        throw std::out_of_range("Cannot access front of empty array");
    
    return m_data[0];
}

template<class T, std::size_t N> 
constexpr typename array<T, N>::reference array<T, N>::back()
{
    if (N == 0) 
        throw std::out_of_range("Cannot access back of empty array");
    
    return m_data[N - 1];
}

template<class T, std::size_t N> 
constexpr typename array<T, N>::const_reference array<T, N>::back() const
{
    if (N == 0) 
        throw std::out_of_range("Cannot access back of empty array");
    
    return m_data[N - 1];
}

template<class T, std::size_t N> 
constexpr typename array<T, N>::pointer array<T, N>::data() noexcept
{
    return N == 0 ? nullptr : &m_data[0];
}

template<class T, std::size_t N> 
constexpr typename array<T, N>::const_pointer array<T, N>::data() const noexcept
{
    return N == 0 ? nullptr : &m_data[0];
}

template<class T, std::size_t N>
constexpr typename array<T, N>::iterator array<T, N>::begin() noexcept
{
    return N == 0 ? nullptr : &m_data[0];
}

template<class T, std::size_t N>
constexpr typename array<T, N>::const_iterator array<T, N>::begin() const noexcept
{
    return N == 0 ? nullptr : &m_data[0];
}

template<class T, std::size_t N>
constexpr typename array<T, N>::const_iterator array<T, N>::cbegin() const noexcept
{
    return N == 0 ? nullptr : &m_data[0];
}

template<class T, std::size_t N>
constexpr typename array<T, N>::iterator array<T, N>::end() noexcept
{
    return N == 0 ? nullptr : &m_data[N];
}

template<class T, std::size_t N>
constexpr typename array<T, N>::const_iterator array<T, N>::end() const noexcept
{
    return N == 0 ? nullptr : &m_data[N];
}

template<class T, std::size_t N>
constexpr typename array<T, N>::const_iterator array<T, N>::cend() const noexcept
{
    return N == 0 ? nullptr : &m_data[N];
}

template<class T, std::size_t N>
constexpr typename array<T, N>::reverse_iterator array<T, N>::rbegin() noexcept
{
    return reverse_iterator(end());
}

template<class T, std::size_t N>
constexpr typename array<T, N>::const_reverse_iterator array<T, N>::rbegin() const noexcept
{
    return const_reverse_iterator(end());
}

template<class T, std::size_t N>
constexpr typename array<T, N>::const_reverse_iterator array<T, N>::crbegin() const noexcept
{
    return const_reverse_iterator(cend());
}

template<class T, std::size_t N>
constexpr typename array<T, N>::reverse_iterator array<T, N>::rend() noexcept
{
    return reverse_iterator(begin());
}

template<class T, std::size_t N>
constexpr typename array<T, N>::const_reverse_iterator array<T, N>::rend() const noexcept
{
    return const_reverse_iterator(begin());
}

template<class T, std::size_t N>
constexpr typename array<T, N>::const_reverse_iterator array<T, N>::crend() const noexcept
{
    return const_reverse_iterator(cbegin());
}

template<class T, std::size_t N>
constexpr bool array<T, N>::empty() const noexcept
{
    return size() == 0;
}

template<class T, std::size_t N>
constexpr typename array<T, N>::size_type array<T, N>::size() const noexcept
{
    return N;
}

template<class T, std::size_t N>
constexpr typename array<T, N>::size_type array<T, N>::max_size() const noexcept
{
    return N;
}

template<class T, std::size_t N>
constexpr void array<T, N>::fill(const T& value)
{
    for (size_type i = 0; i < N; i++)
        m_data[i] = value;
}

template<class T, std::size_t N>
constexpr void array<T, N>::swap(array<T, N>& other) noexcept(std::is_nothrow_swappable_v<T>)
{
    for (std::size_t i = 0; i < N; ++i) 
    {
        using std::swap;
        swap(this->m_data[i], other.m_data[i]);
    }
}

// Специализация для N == 0
template<class T>
struct array<T, 0>
{
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using iterator = pointer;
    using const_iterator = const_pointer;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    constexpr array() = default;
    constexpr array(std::initializer_list<T> ilist) 
    {
        if (ilist.size() > 0) 
        {
            throw std::length_error("Initializer list size exceeds array capacity");
        }
    }
    constexpr ~array() = default;

    constexpr reference at(size_type) 
    {
        throw std::out_of_range("Cannot access element in empty array");
    }
    constexpr const_reference at(size_type) const 
    {
        throw std::out_of_range("Cannot access element in empty array");
    }

    constexpr reference operator[](size_type) 
    {
        throw std::out_of_range("Cannot access element in empty array");
    }
    constexpr const_reference operator[](size_type) const 
    {
        throw std::out_of_range("Cannot access element in empty array");
    }

    constexpr reference front() 
    {
        throw std::out_of_range("Cannot access front of empty array");
    }

    constexpr const_reference front() const 
    {
        throw std::out_of_range("Cannot access front of empty array");
    }

    constexpr reference back() 
    {
        throw std::out_of_range("Cannot access back of empty array");
    }
    constexpr const_reference back() const 
    {
        throw std::out_of_range("Cannot access back of empty array");
    }

    constexpr pointer data() noexcept { return nullptr; }
    constexpr const_pointer data() const noexcept { return nullptr; }

    constexpr iterator begin() noexcept { return nullptr; }
    constexpr const_iterator begin() const noexcept { return nullptr; }
    constexpr const_iterator cbegin() const noexcept { return nullptr; }

    constexpr iterator end() noexcept { return nullptr; }
    constexpr const_iterator end() const noexcept { return nullptr; }
    constexpr const_iterator cend() const noexcept { return nullptr; }

    constexpr reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
    constexpr const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
    constexpr const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(cend()); }

    constexpr reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
    constexpr const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }
    constexpr const_reverse_iterator crend() const noexcept { return const_reverse_iterator(cbegin()); }

    constexpr bool empty() const noexcept { return true; }
    constexpr size_type size() const noexcept { return 0; }
    constexpr size_type max_size() const noexcept { return 0; }

    constexpr void fill(const T&) {}
    constexpr void swap(array&) noexcept {}
};

} // namespace ownstl