#ifndef LIST_H
#define LIST_H

#include <cstddef>
#include <iterator>

namespace btl
{

    template <typename T>
    class list
    {
        struct _list_node;

        template <typename data_type>
        class _iterator;

    public:
        using value_type = T;
        using reference = value_type&;
        using const_reference = const value_type&;


        using iterator = _iterator<_list_node>;
        using const_iterator = _iterator<const _list_node>;

        // Constructers
        list()
         : _tail(new _list_node)
        {
            _tail->next = _tail->prev = _tail;
        }

        list(std::size_t size, const value_type& value)
         : list()
        {
            for (size_t i = 0; i < size; i++) {
                this->push_back(value);
            }
        }

        ~list()
        {
            // break the cicle
            _tail->prev->next = nullptr;

            // delete elements one by one
            _list_node *iter = _tail;
            while (iter != nullptr) {
                _list_node *tmp = iter;
                iter = iter->next;
                delete tmp;
            }
        }

        void push_back(const T& value)
        {
            _size++;
            _list_node *new_node = new _list_node(_tail, _tail->prev, value);
            _tail->prev->next = new_node;
            _tail->prev = new_node;
        }

        // TODO: insert
        std::size_t count(const_reference value)
        {
            std::size_t count = 0;
            auto iter = this->cbegin(), end = this->cend();
            while (iter != end) {
                if (*iter == value)
                    count++;
            }
            return count;
        }

        /* Для соответсвия сигнатуре вставки у деревьев и хэш-таблицы, чтобы можно было
         * использовать как словарь.
         */
        bool insert(const_reference value)
        {
            // Check if value already in list
            if (this->count(value)) {
                return false;
            }

            // Insert by default in end of list
            this->push_back(value);
            return true;
        }

        iterator begin() const
        {
            return _tail->next;
        }

        iterator end() const
        {
            return _tail;
        }

        const_iterator cbegin() const
        {
            return _tail->next;
        }

        const_iterator cend() const
        {
            return _tail;
        }

    private:
        std::size_t _size = 0;

        /* TODO
         *  comments
         *  object placement: stack or heap
         */

        _list_node *_tail;
    };

    template <typename T>
    template <typename data_type>
    class list<T>::_iterator
    {
    public:
        // TODO usings
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;


        _iterator(data_type* node)
            : _ptr(node)
        {}

        _iterator(const iterator& lhs)
            : _ptr(lhs._ptr)
        {};

        _iterator& operator++()
        {
            _ptr = _ptr->next;
            return *this;
        }

        _iterator operator++(int)
        {
            auto tmp = *this;
            _ptr = _ptr->next;
            return tmp;
        }

        auto& operator*()
        {
            return _ptr->data;
        }

        bool operator==(const _iterator& rhs) const
        {
            return _ptr == rhs._ptr;
        }

        bool operator!=(const _iterator& rhs) const
        {
            return _ptr != rhs._ptr;
        }

    private:
        data_type *_ptr = nullptr;

    };

    template <typename T>
    struct list<T>::_list_node
    {
        _list_node() = default;

        _list_node(
            _list_node *next,
            _list_node *prev,
            const_reference data
        )
            : next(next), prev(prev), data(data)
        {}

        _list_node *next = nullptr;
        _list_node *prev = nullptr;
        value_type data = value_type();
    };

} // namespace btl

#endif // LIST_H
