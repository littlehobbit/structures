#ifndef SET_H
#define SET_H

#include <rb_tree.h>

namespace btl
{
    template<typename Key, typename Container = btl::rb_tree<Key>>
    class set
    {
    public:
        set() = default;



    private:
        Container _container;
    };
} // namespace btl


#endif // SET_H
