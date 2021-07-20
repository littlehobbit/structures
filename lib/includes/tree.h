#ifndef TREE_H
#define TREE_H

#include <tuple>

namespace btl
{
    template<typename Key>
    class bst
    {

    public:
        using key_type = Key;

        bst()
        {
            // make "end" list node
            _list = new _tree_node;
            _list->next = _list->prev = _list;
        }

        // return true if node was inserted
        bool insert(const key_type& key)
        {
            if (!_root) {
                // Make new root
                _root = new _tree_node{nullptr, nullptr, nullptr, key};
                _list->insertAfter(_root);
                _size++;
                return true;
            }

            // insert in tree and list
            return _tree_insert(&_root, nullptr, key);
        }

        // TODO iterator find

        std::size_t count(const key_type &key)
        {
            _tree_node *iter = _root;
            while (iter != nullptr && iter->key != key) {
                if (key < iter->key)
                    iter = iter->left;
                else
                    iter = iter->right;
            }
            return iter != nullptr;
        }

    private:

        struct _tree_node
        {
            // tree structure
            _tree_node *parent = nullptr;
            _tree_node *left = nullptr;
            _tree_node *right = nullptr;
            key_type key;

            // list of tree nodes in non-degreese order
            _tree_node *next = nullptr;
            _tree_node *prev = nullptr;


            void insertAfter(_tree_node *to_ins)
            {
                to_ins->next = this->next;
                to_ins->prev = this;
                to_ins->next->prev = to_ins;
                this->next = to_ins;
            }

        };

        bool _tree_insert(_tree_node **root, _tree_node *parent, const key_type& key)
        {
            if (*root == nullptr) {
                // do tree insert
                _size++;
                *root = new _tree_node{parent, nullptr, nullptr, key};
                _list_insert(parent, *root);
                return true;
            }

            // do tree search
            if ((*root)->key == key) {
                // node with key already exist
                return false;
            } else {
                if (key < (*root)->key) {
                    return _tree_insert(&((*root)->left), *root, key);
                } else {
                    return _tree_insert(&((*root)->right), *root, key);
                }
            }
        }

        void _list_insert(_tree_node *parent, _tree_node *new_node)
        {
            if (new_node->key < parent->key) {
                parent->prev->insertAfter(new_node);
            } else {
                parent->insertAfter(new_node);
            }
        }

        std::size_t _size = 0;
        _tree_node *_root = nullptr;
        _tree_node *_list = nullptr;
    };
}

#endif // TREE_H
