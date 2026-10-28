#ifndef LIST_H
#define LIST_H

/*
    Name: List.h
    Description: 用 C++ class 实现的 Python list 语义容器（模板类，值语义）。

    与 Python list 的对应关系：
        len(l)          -> l.size()
        l[i]            -> l[i]           支持负数下标（l[-1] 是最后一个）
        l[i] = v        -> l[i] = v
        del l[i]        -> l.erase(i)
        l.append(v)     -> l.append(v)
        l.extend(other) -> l.extend(other)
        l.insert(i, v)  -> l.insert(i, v)
        l.remove(v)     -> l.remove(v)
        l.pop()         -> l.pop()         默认弹出最后一个并返回它
        l.pop(i)        -> l.pop(i)
        l.clear()       -> l.clear()
        l.copy()        -> l.copy()
        l.count(v)      -> l.count(v)
        l.index(v)      -> l.index(v)
        v in l          -> l.contains(v)
        l.reverse()     -> l.reverse()
        l.sort()        -> l.sort()        稳定排序，与 Python 一致
        l[1:3]          -> l.slice(1, 3)
        l[::2]          -> l.slice(0, l.size(), 2)
        l1 + l2         -> l1 + l2
        print(l)        -> std::cout << l

    异常约定（对齐 Python 的两类异常）：
        IndexError -> std::out_of_range       下标越界 / 对空列表 pop
        ValueError -> std::invalid_argument   元素不存在

    标准：C++11，可在 Dev-C++ 5.11（MinGW g++ 4.8.1）下直接编译。
*/

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <ostream>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <vector>

namespace list_detail
{

// void_t 探测：判断 T 是否具备迭代器特征
template <typename... Ts>
struct make_void
{
    typedef void type;
};

template <typename... Ts>
using void_t = typename make_void<Ts...>::type;

template <typename T, typename = void>
struct is_iterator : std::false_type
{
};

template <typename T>
struct is_iterator<T, void_t<typename std::iterator_traits<T>::iterator_category> >
    : std::true_type
{
};

} // namespace list_detail

template <typename T>
class List
{
public:
    typedef T value_type;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef typename std::vector<T>::reference reference;
    typedef typename std::vector<T>::const_reference const_reference;
    typedef typename std::vector<T>::iterator iterator;
    typedef typename std::vector<T>::const_iterator const_iterator;

    // ---------- 构造 ----------
    List() : data_() {}

    List(std::initializer_list<T> init) : data_(init) {}

    explicit List(size_type count) : data_(count) {}

    List(size_type count, const T& value) : data_(count, value) {}

    // 迭代器区间构造。SFINAE 限制 InputIt 必须是真正的迭代器：
    // 既避免它抢占拷贝构造，也避免它抢占 (个数, 值) 构造。
    template <typename InputIt,
              typename = typename std::enable_if<
                  !std::is_same<typename std::decay<InputIt>::type, List>::value &&
                  list_detail::is_iterator<InputIt>::value>::type>
    List(InputIt first, InputIt last) : data_(first, last) {}

    // 拷贝/移动构造与赋值由编译器按值语义自动生成（Rule of Zero）

    // ---------- 容量与元素访问 ----------
    size_type size() const { return data_.size(); }
    bool empty() const { return data_.empty(); }
    size_type capacity() const { return data_.capacity(); }

    void reserve(size_type n) { data_.reserve(n); }
    void resize(size_type n) { data_.resize(n); }
    void resize(size_type n, const T& value) { data_.resize(n, value); }
    void clear() { data_.clear(); }
    void swap(List& other) { data_.swap(other.data_); }

    // Python 风格下标：负数从末尾计数，越界抛 std::out_of_range
    reference operator[](difference_type index)
    {
        return data_[resolveIndex(index, data_.size())];
    }

    const_reference operator[](difference_type index) const
    {
        return data_[resolveIndex(index, data_.size())];
    }

    // 显式命名的边界检查版本，语义与 operator[] 相同
    reference at(difference_type index)
    {
        return data_[resolveIndex(index, data_.size())];
    }

    const_reference at(difference_type index) const
    {
        return data_[resolveIndex(index, data_.size())];
    }

    // 与 std::vector 一致：空列表调用是未定义行为
    reference front() { return data_.front(); }
    const_reference front() const { return data_.front(); }
    reference back() { return data_.back(); }
    const_reference back() const { return data_.back(); }

    // ---------- 增删改 ----------
    void append(const T& value) { data_.push_back(value); }
    void append(T&& value) { data_.push_back(std::move(value)); }

    template <typename... Args>
    reference emplace_back(Args&&... args)
    {
        return data_.emplace_back(std::forward<Args>(args)...);
    }

    void extend(const List& other)
    {
        data_.insert(data_.end(), other.data_.begin(), other.data_.end());
    }

    void extend(std::initializer_list<T> values)
    {
        data_.insert(data_.end(), values.begin(), values.end());
    }

    // Python 语义：负数下标从末尾算，越界则钳到两端
    void insert(difference_type index, const T& value)
    {
        const size_type pos = clampInsertIndex(index);
        data_.insert(data_.begin() + pos, value);
    }

    template <typename... Args>
    void emplace(difference_type index, Args&&... args)
    {
        const size_type pos = clampInsertIndex(index);
        data_.emplace(data_.begin() + pos, std::forward<Args>(args)...);
    }

    // 删除第一个等于 value 的元素；不存在则抛 std::invalid_argument
    void remove(const T& value)
    {
        iterator it = std::find(data_.begin(), data_.end(), value);
        if (it == data_.end())
        {
            throw std::invalid_argument("List.remove: value not in list");
        }
        data_.erase(it);
    }

    // 删除指定位置的元素（等价 del l[i]）
    void erase(difference_type index)
    {
        const size_type pos = resolveIndex(index, data_.size());
        data_.erase(data_.begin() + pos);
    }

    // 弹出并返回元素，默认最后一个（等价 l.pop()）
    T pop(difference_type index = -1)
    {
        if (data_.empty())
        {
            throw std::out_of_range("List.pop: index out of range (list is empty)");
        }
        const size_type pos = resolveIndex(index, data_.size());
        T value = std::move(data_[pos]);
        data_.erase(data_.begin() + pos);
        return value;
    }

    // ---------- 查询 ----------
    size_type count(const T& value) const
    {
        return static_cast<size_type>(
            std::count(data_.begin(), data_.end(), value));
    }

    // 首个等于 value 的下标；不存在则抛 std::invalid_argument
    size_type index(const T& value) const
    {
        const_iterator it = std::find(data_.begin(), data_.end(), value);
        if (it == data_.end())
        {
            throw std::invalid_argument("List.index: value not in list");
        }
        return static_cast<size_type>(it - data_.begin());
    }

    bool contains(const T& value) const
    {
        return std::find(data_.begin(), data_.end(), value) != data_.end();
    }

    iterator find(const T& value)
    {
        return std::find(data_.begin(), data_.end(), value);
    }

    const_iterator find(const T& value) const
    {
        return std::find(data_.begin(), data_.end(), value);
    }

    // ---------- 排序与反转 ----------
    void reverse() { std::reverse(data_.begin(), data_.end()); }

    // 稳定排序，与 Python 的 list.sort() 行为一致
    void sort() { std::stable_sort(data_.begin(), data_.end()); }

    template <typename Compare>
    void sort(Compare comp)
    {
        std::stable_sort(data_.begin(), data_.end(), comp);
    }

    List copy() const { return List(*this); }

    // ---------- 切片（l[start:stop] / l[start:stop:step]） ----------
    List slice(difference_type start, difference_type stop) const
    {
        return slice(start, stop, 1);
    }

    List slice(difference_type start, difference_type stop, difference_type step) const
    {
        if (step == 0)
        {
            throw std::invalid_argument("List.slice: step cannot be zero");
        }

        const difference_type length = static_cast<difference_type>(data_.size());

        if (step > 0)
        {
            if (start < 0) start += length;
            if (start < 0) start = 0;
            if (start > length) start = length;

            if (stop < 0) stop += length;
            if (stop < 0) stop = 0;
            if (stop > length) stop = length;
        }
        else
        {
            if (start < 0) start += length;
            if (start < 0) start = -1;
            if (start >= length) start = length - 1;

            if (stop < 0) stop += length;
            if (stop < 0) stop = -1;
            if (stop >= length) stop = length - 1;
        }

        List result;
        if (step > 0)
        {
            for (difference_type i = start; i < stop; i += step)
            {
                result.append(data_[static_cast<size_type>(i)]);
            }
        }
        else
        {
            for (difference_type i = start; i > stop; i += step)
            {
                result.append(data_[static_cast<size_type>(i)]);
            }
        }
        return result;
    }

    // ---------- 运算符 ----------
    List& operator+=(const List& other)
    {
        data_.insert(data_.end(), other.data_.begin(), other.data_.end());
        return *this;
    }

    List operator+(const List& other) const
    {
        List result(*this);
        result += other;
        return result;
    }

    bool operator==(const List& other) const { return data_ == other.data_; }
    bool operator!=(const List& other) const { return !(*this == other); }

    // ---------- 迭代器 ----------
    iterator begin() { return data_.begin(); }
    iterator end() { return data_.end(); }
    const_iterator begin() const { return data_.begin(); }
    const_iterator end() const { return data_.end(); }
    const_iterator cbegin() const { return data_.cbegin(); }
    const_iterator cend() const { return data_.cend(); }

private:
    std::vector<T> data_;

    // 把 Python 风格下标（允许负数）转成合法下标，越界抛 std::out_of_range
    static size_type resolveIndex(difference_type index, size_type size)
    {
        if (index < 0)
        {
            index += static_cast<difference_type>(size);
        }
        if (index < 0 || index >= static_cast<difference_type>(size))
        {
            throw std::out_of_range("List: index out of range");
        }
        return static_cast<size_type>(index);
    }

    // insert 的下标：负数从末尾算，超出范围则钳到 [0, size]
    size_type clampInsertIndex(difference_type index) const
    {
        const difference_type length = static_cast<difference_type>(data_.size());
        if (index < 0)
        {
            index += length;
            if (index < 0) index = 0;
        }
        else if (index > length)
        {
            index = length;
        }
        return static_cast<size_type>(index);
    }
};

// 打印成 Python 风格的 [a, b, c]
template <typename T>
std::ostream& operator<<(std::ostream& os, const List<T>& list)
{
    os << "[";
    for (std::size_t i = 0; i < list.size(); ++i)
    {
        if (i != 0) os << ", ";
        os << list[static_cast<std::ptrdiff_t>(i)];
    }
    os << "]";
    return os;
}

#endif // LIST_H
