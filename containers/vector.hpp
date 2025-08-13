#pragma once

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <limits>
#include <memory>
#include <type_traits>

namespace ownstl {

template <class T>
class contiguos_iterator;

template <class T, class Allocator = std::allocator<T>>
class vector
{
public:
    // Member types
    using value_type = T;
    using allocator_type = Allocator;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = std::allocator_traits<Allocator>::pointer;
    using const_pointer = std::allocator_traits<Allocator>::const_pointer;
    using iterator = contiguos_iterator<value_type>;
    using const_iterator = contiguos_iterator<const value_type>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    // Constructors and destructor
    constexpr vector() noexcept(noexcept(Allocator())) : vector(Allocator()) {}
    constexpr explicit vector(const Allocator& alloc);
    constexpr explicit vector(size_type count,
                              const Allocator& alloc = Allocator());
    constexpr vector(size_type count, const T& value,
                     const Allocator& alloc = Allocator());
    template <class InputIt>
    constexpr vector(InputIt first, InputIt last,
                     const Allocator& alloc = Allocator());
    constexpr vector(const vector& other);
    constexpr vector(vector&& other) noexcept;
    constexpr vector(const vector& other, const Allocator& alloc);
    constexpr vector(vector&& other, const Allocator& alloc);
    vector(std::initializer_list<T> init, const Allocator& alloc = Allocator());

    constexpr ~vector();

    // Operator =
    constexpr vector& operator=(const vector& other);
    constexpr vector& operator=(vector&& other) noexcept(
        std::allocator_traits<
            Allocator>::propagate_on_container_move_assignment::value ||
        std::allocator_traits<Allocator>::is_always_equal::value);
    constexpr vector& operator=(std::initializer_list<value_type> ilist);

    // Assign methods
    constexpr void assign(size_type count, const T& value);
    template <class InputIt>
    constexpr void assign(InputIt first, InputIt last);
    constexpr void assign(std::initializer_list<T> ilist);

    constexpr allocator_type get_allocator() const noexcept { return alloc_; }

    // ELement access
    constexpr reference at(size_type pos);
    constexpr const_reference at(size_type pos) const;

    constexpr reference operator[](size_type pos) { return begin_[pos]; }
    constexpr const_reference operator[](size_type pos) const
    {
        return begin_[pos];
    }

    constexpr reference front() { return *begin_; }
    constexpr const_reference front() const { return *begin_; }

    constexpr reference back() { return *(end_ - 1); }
    constexpr const_reference back() const { return *(end_ - 1); }

    constexpr pointer data() noexcept { return begin_; }
    constexpr const_pointer data() const noexcept { return begin_; }

    // Iterators
    constexpr iterator begin() noexcept { return iterator(begin_); }
    constexpr const_iterator begin() const noexcept
    {
        return const_iterator(begin_);
    }
    constexpr const_iterator cbegin() const noexcept
    {
        return const_iterator(begin_);
    }

    constexpr iterator end() noexcept { return iterator(end_); }
    constexpr const_iterator end() const noexcept
    {
        return const_iterator(end_);
    }
    constexpr const_iterator cend() const noexcept
    {
        return const_iterator(end_);
    }

    constexpr reverse_iterator rbegin() noexcept
    {
        return reverse_iterator(end());
    }
    constexpr const_reverse_iterator rbegin() const noexcept
    {
        return const_reverse_iterator(end());
    }
    constexpr const_reverse_iterator crbegin() const noexcept
    {
        return const_reverse_iterator(cend());
    }

    constexpr reverse_iterator rend() noexcept
    {
        return reverse_iterator(begin());
    }
    constexpr const_reverse_iterator rend() const noexcept
    {
        return const_reverse_iterator(begin());
    }
    constexpr const_reverse_iterator crend() const noexcept
    {
        return const_reverse_iterator(cbegin());
    }

    // Capacity
    constexpr bool empty() const noexcept { return begin_ == nullptr; }
    constexpr size_type size() const noexcept { return end_ - begin_; }
    constexpr size_type max_size() const noexcept
    {
        return std::numeric_limits<difference_type>::max();
    }
    constexpr void reserve(size_type new_cap);
    constexpr size_type capacity() const noexcept { return end_cap_ - begin_; }
    constexpr void shrink_to_fit();

    // Modifiers
    constexpr void clear() noexcept;

    constexpr iterator insert(const_iterator pos, const T& value);
    constexpr iterator insert(const_iterator pos, T&& value);
    constexpr iterator insert(const_iterator pos, size_type count,
                              const T& value);
    template <class InputIt>
    constexpr iterator insert(const_iterator pos, InputIt first, InputIt last);
    constexpr iterator insert(const_iterator pos,
                              std::initializer_list<T> ilist);

    template <class... Args>
    constexpr iterator emplace(const_iterator pos, Args&&... args);

    constexpr iterator erase(const_iterator pos);
    constexpr iterator erase(const_iterator first, const_iterator last);

    constexpr void push_back(const T& value);
    constexpr void push_back(T&& value);

    template <class... Args>
    constexpr reference emplace_back(Args&&... args);

    constexpr void pop_back();

    constexpr void resize(size_type count);
    constexpr void resize(size_type count, const value_type& value);

    constexpr void swap(vector& other) noexcept(
        std::allocator_traits<Allocator>::propagate_on_container_swap::value ||
        std::allocator_traits<Allocator>::is_always_equal::value);

    constexpr void printAll()
    {
        for (auto* it = begin_; it != end_; ++it)
            std::cout << *it << ' ';
        std::cout << '\n';
    }

private:
    pointer begin_ = nullptr;
    pointer end_ = nullptr;
    pointer end_cap_ = nullptr;
    [[no_unique_address]] Allocator alloc_{};
};

template <class T, class Allocator>
constexpr vector<T, Allocator>::vector(const Allocator& alloc) : alloc_(alloc)
{}

template <class T, class Allocator>
constexpr vector<T, Allocator>::vector(size_type count, const Allocator& alloc)
    : alloc_(alloc)
{
    using traits = std::allocator_traits<Allocator>;

    if (count > 0)
    {
        pointer allocated_ptr = nullptr;
        try
        {
            allocated_ptr = traits::allocate(alloc_, count);
            pointer current = allocated_ptr;

            try
            {
                for (; current != allocated_ptr + count; ++current)
                    traits::construct(alloc_, current);
            }
            catch (...)
            {
                for (auto* it = allocated_ptr; it != current; ++it)
                    traits::destroy(alloc_, it);

                throw;
            }

            begin_ = allocated_ptr;
            end_ = end_cap_ = allocated_ptr + count;
        }

        catch (...)
        {
            traits::deallocate(alloc_, allocated_ptr, count);

            throw;
        }
    }

    else
        begin_ = end_ = end_cap_ = nullptr;
}

template <class T, class Allocator>
constexpr vector<T, Allocator>::vector(size_type count, const T& value,
                                       const Allocator& alloc)
    : alloc_(alloc)
{
    using traits = std::allocator_traits<Allocator>;

    if (count > 0)
    {
        pointer allocated_ptr = nullptr;
        try
        {
            allocated_ptr = traits::allocate(alloc_, count);
            pointer current = allocated_ptr;

            try
            {
                for (; current != allocated_ptr + count; ++current)
                    traits::construct(alloc_, current, value);
            }
            catch (...)
            {
                for (auto* it = allocated_ptr; it != current; ++it)
                    traits::destroy(alloc_, it);

                throw;
            }

            begin_ = allocated_ptr;
            end_ = end_cap_ = allocated_ptr + count;
        }

        catch (...)
        {
            traits::deallocate(alloc_, allocated_ptr, count);

            throw;
        }
    }

    else
        begin_ = end_ = end_cap_ = nullptr;
}

template <class T, class Allocator>
template <class InputIt>
constexpr vector<T, Allocator>::vector(InputIt first, InputIt last,
                                       const Allocator& alloc)
    : alloc_(alloc)
{

    using traits = std::allocator_traits<Allocator>;

    if constexpr (std::is_base_of_v<std::forward_iterator_tag,
                                    typename std::iterator_traits<
                                        InputIt>::iterator_category>)
    {
        const size_type count = std::distance(first, last);
        if (count > 0)
        {
            pointer allocated_ptr = nullptr;
            try
            {
                allocated_ptr = traits::allocate(alloc_, count);
                pointer current = allocated_ptr;

                try
                {
                    for (; first != last; ++current, ++first)
                        traits::construct(alloc_, current, *first);
                }
                catch (...)
                {
                    for (auto* it = allocated_ptr; it != current; ++it)
                        traits::destroy(alloc_, it);

                    throw;
                }

                begin_ = allocated_ptr;
                end_ = end_cap_ = allocated_ptr + count;
            }
            catch (...)
            {
                traits::deallocate(alloc_, allocated_ptr, count);

                throw;
            }
        }
        else
            begin_ = end_ = end_cap_ = nullptr;
    }
    else
    {
        try
        {
            while (first != last)
            {
                if (end_ == end_cap_)
                {
                    const size_type new_cap =
                        (capacity() == 0) ? 1 : capacity() * 2;
                    reserve(new_cap);
                }

                traits::construct(alloc_, end_, *first);
                ++end_;
                ++first;
            }
        }
        catch (...)
        {
            for (auto* it = begin_; it != end_; ++it)
                traits::destroy(alloc_, it);

            if (begin_)
                traits::deallocate(alloc_, begin_, capacity());

            throw;
        }
    }
}

template <class T, class Allocator>
constexpr vector<T, Allocator>::vector(const vector& other)
    : alloc_(std::allocator_traits<Allocator>::
                 select_on_container_copy_construction(other.get_allocator()))
{
    using traits = std::allocator_traits<Allocator>;

    pointer allocated_ptr = nullptr;
    try
    {
        allocated_ptr = traits::allocate(alloc_, other.capacity());
        pointer current = allocated_ptr;

        try
        {
            for (; current != allocated_ptr + other.size();
                 ++current, ++other.begin_)
                traits::construct(alloc_, current, *other.begin_);
        }
        catch (...)
        {
            for (auto* it = allocated_ptr; it != current; ++it)
                traits::destroy(alloc_, it);

            throw;
        }

        begin_ = allocated_ptr;
        end_ = end_cap_ = allocated_ptr + other.capacity();
    }
    catch (...)
    {
        traits::deallocate(alloc_, allocated_ptr, other.capacity());

        throw;
    }
}

template <class T, class Allocator>
constexpr vector<T, Allocator>::vector(vector&& other) noexcept
    : alloc_(std::move(other.get_allocator()))
{
    begin_ = other.begin_;
    end_ = other.end_;
    end_cap_ = other.end_cap_;

    other.begin_ = other.end_ = other.end_cap_ = nullptr;
}

template <class T, class Allocator>
constexpr vector<T, Allocator>::vector(const vector& other,
                                       const Allocator& alloc)
    : alloc_(alloc)
{
    using traits = std::allocator_traits<Allocator>;

    pointer allocated_ptr = nullptr;
    try
    {
        allocated_ptr = traits::allocate(alloc_, other.capacity());
        pointer current = allocated_ptr;

        try
        {
            for (; current != allocated_ptr + other.size();
                 ++current, ++other.begin_)
                traits::construct(alloc_, current, *other.begin_);
        }
        catch (...)
        {
            for (auto* it = allocated_ptr; it != current; ++it)
                traits::destroy(alloc_, it);

            throw;
        }

        begin_ = allocated_ptr;
        end_ = end_cap_ = allocated_ptr + other.capacity();
    }
    catch (...)
    {
        traits::deallocate(alloc_, allocated_ptr, other.capacity());

        throw;
    }
}

template <class T, class Allocator>
constexpr vector<T, Allocator>::vector(vector&& other, const Allocator& alloc)
    : alloc_(alloc)
{
    if (alloc_ == other.get_allocator())
    {
        begin_ = other.begin_;
        end_ = other.end_;
        end_cap_ = other.end_cap_;

        other.begin_ = other.end_ = other.end_cap_ = nullptr;
    }
    else
    {
        reserve(other.size());

        for (auto item : other)
            emplace_back(std::move(item));
    }
}

template <class T, class Allocator>
vector<T, Allocator>::vector(std::initializer_list<T> init,
                             const Allocator& alloc)
    : alloc_(alloc)
{
    using traits = std::allocator_traits<Allocator>;

    const size_type count = std::distance(init.begin(), init.end());

    pointer allocated_ptr = nullptr;
    try
    {
        allocated_ptr = traits::allocate(alloc_, count);
        pointer current = allocated_ptr;

        try
        {
            for (auto it = init.begin(); it != init.end(); ++it, ++current)
                traits::construct(alloc_, current, *it);
        }
        catch (...)
        {
            for (auto* it = allocated_ptr; it != current; ++it)
                traits::destroy(alloc_, it);

            throw;
        }

        begin_ = allocated_ptr;
        end_ = end_cap_ = begin_ + count;
    }
    catch (...)
    {
        traits::deallocate(alloc_, allocated_ptr, count);

        throw;
    }
}

template <class T, class Allocator>
constexpr vector<T, Allocator>::~vector()
{
    using traits = std::allocator_traits<Allocator>;

    if (begin_)
    {
        for (auto* it = begin_; it != end_; ++it)
            traits::destroy(alloc_, it);

        traits::deallocate(alloc_, begin_, end_cap_ - begin_);
    }
}

template <class T, class Allocator>
constexpr vector<T, Allocator>&
vector<T, Allocator>::operator=(const vector& other)
{}
} // namespace ownstl
