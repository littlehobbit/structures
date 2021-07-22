#ifndef RB_TREE_H
#define RB_TREE_H

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

        bool insert(const key_type& value)
        {
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

            // TODO: balancing
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
            else
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

        void rotateLeft(_tree_node *node)
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
            }

            new_root->parent = node->parent;
            node->parent = new_root;
        }

        void rotateRight(_tree_node *node)
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
            }

            new_root->parent = node->parent;
            node->parent = new_root;
        }

        _tree_node *_root = nullptr;
    };

} // namespace btl

#endif // RB_TREE_H
