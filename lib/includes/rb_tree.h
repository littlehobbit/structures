#ifndef RB_TREE_H
#define RB_TREE_H

#include <cstddef>

namespace btl
{

    template<typename  Key>
    class rb_tree
    {
        /*  Свойства красно-черного дерева:
         *      1. Узел красный либо черный и имеет два потомка
         *      2. Корень - черный (для поддеревьев не всегда)
         *      3. Все листься без данных - черные
         *      4. Оба потомка каждого красного узла - черные
         *      5. Любой путь от вершины до листьев имеет одинаковое
         *         количество черных вершин
         */

    public:
        using key_type = Key;

        rb_tree() = default;

        ~rb_tree()
        {
            delete_tree(_root);
        }

        bool insert(const key_type& value)
        {
            if (!_root) {
                _root = new _tree_node {nullptr, BLACK, value};
                return true;
            }

            _tree_node *parent = _root, *iter = _root;
            while (iter != nullptr) {
                parent = iter;
                if (value < iter->key)
                    iter = iter->left;
                else if (value > iter->key)
                    iter = iter->right;
                else
                    return false;
            }

            _tree_node *new_node = new _tree_node {parent, RED, value};

            if (value < parent->key) {
                parent->left = new_node;
            } else {
                parent->right = new_node;
            }

            fix_balance(new_node);
            return true;
        }

        std::size_t count(const key_type& value)
        {
            _tree_node *iter = _root;
            while (iter != nullptr && iter->key != value) {
                if (value < iter->key)
                    iter = iter->left;
                else
                    iter = iter->right;
            }
            return iter != nullptr;
        }

    private:
        enum Colour {
            RED,
            BLACK
        };

        struct _tree_node
        {
            _tree_node *parent = nullptr;
            Colour colour;
            key_type key;

            _tree_node *left = nullptr;
            _tree_node *right = nullptr;

            // TODO iterator
        };


        /* Отношения в дереве:
         *  g - деда
         *  u - дядя
         *  p - родитель
         *  n - дочер. эл
         *       g
         *      / \
         *     u   p
         *        / \
         *      ...  n
         */
        _tree_node* grandparent(_tree_node *node)
        {
            if (node != nullptr && node->parent != nullptr)
                return node->parent->parent;
            else        // TODO: избавиться от повтора кода
                return nullptr;
        }

        _tree_node* uncle(_tree_node *node)
        {
            _tree_node *grandpa = grandparent(node);
            if (!grandpa) return nullptr;

            if (grandpa->left == node->parent)
                return grandpa->right;
            else
                return grandpa->left;
        }

        void rotate_left(_tree_node *node)
        {
            _tree_node *new_root = node->right;

            node->right = new_root->left;
            new_root->left = node;
            if (node->right)
                node->right->parent = node;

            if (node->parent) {
                if (node->key < node->parent->key)
                    node->parent->left = new_root;
                else
                    node->parent->right = new_root;
            } else {
                _root = new_root;
            }

            new_root->parent = node->parent;
            node->parent = new_root;
        }

        void rotate_right(_tree_node *node)
        {
            _tree_node *new_root = node->left;

            node->left = new_root->right;
            new_root->right = node;
            if (node->left)
                node->left->parent = node;

            if (node->parent) {
                if (node->key < node->parent->key)
                    node->parent->left = new_root;
                else
                    node->parent->right = new_root;
            } else {
                _root = new_root;
            }

            new_root->parent = node->parent;
            node->parent = new_root;
        }

        void fix_balance(_tree_node *node)
        {
            while (node != _root && node->parent->colour == RED) {
                _tree_node *uncle_node = uncle(node);
                _tree_node *grandpa_node = grandparent(node);
                if (uncle_node && uncle_node->colour == RED) {
                    // If "uncle" is red, set parent and grandfather colours
                    uncle_node->colour = BLACK;
                    node->parent->colour = BLACK;
                    grandpa_node->colour = RED;
                    node = grandpa_node;
                } else {
                    if (node->parent == grandpa_node->left) {
                        // parent is left child

                        if (node == node->parent->right) {
                            // node is right child
                            node = node->parent;
                            rotate_left(node);
                        }

                        node->parent->colour = BLACK;
                        node->parent->parent->colour = RED;
                        rotate_right(node->parent->parent);

                    } else {
                        // parent is right child

                        if (node == node->parent->left) {
                            // node is left child
                            node = node->parent;
                            rotate_right(node);
                        }

                        node->parent->colour = BLACK;
                        node->parent->parent->colour = RED;
                        rotate_left(node->parent->parent);
                    }
                }
            }

            _root->colour = BLACK;
        }

        // TODO: избавиться от повтора кода
        void delete_tree(_tree_node *node)
        {
            if (node == nullptr)
                return;

            if (node->left != nullptr)
                delete_tree(node->left);

            if (node->right != nullptr)
                delete_tree(node->right);

            delete node;
        }

        _tree_node *_root = nullptr;
    };

} // namespace btl

#endif // RB_TREE_H
