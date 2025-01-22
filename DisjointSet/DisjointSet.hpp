#ifndef DISJOINTSET_HPP
#define DISJOINTSET_HPP
#include "../HashMap/HashMap.hpp"

/*
DisjointSet:

Time Complexity:
- find, union: O(\alpha(n)) ~ O(1) thanks to optimizations.

Optimizations:
- path compression: Flatten tree depth into width, access root worst case O(n) -> O(1)
    - Before: 1 → 2 → 3 → 4
    - After: 1 → 4
             2 → 4
             3 → 4
    - takes place in find operation.
    - Path compression does not immediately flatten all trees into a two-level tree, as not all nodes participate so not all will be compressed.
        - in the limit of "every node in the data structure has been accessed at least once", it approaches a two-level tree and thus O(1).
    - Before: 1 → 2 → 3 → 4
    - After: 1 → 4
             2 → 4
             3 → 4

- union by rank: a balancing measure, ensures that the tree with the smaller rank is attached to the root of the tree with the larger rank.
Prevents tall trees from forming, keeping the structure shallow.
*/


template <typename T>
class DisjointSet   {
private:
    HashMap<T, T> parent; // map to the root in the group
    HashMap<T, size_t> rank; // each root's tree height
public:
    void make_set(const T& input);
    T find_set(const T& input);
    void union_set(const T& elem1, const T& elem2);
};


template <typename T>
void DisjointSet<T>::make_set(const T& input)    {
    if (!parent.contains(input))    {
        parent[input] = input;
        rank[input] = 0;
    }
}

template <typename T>
T DisjointSet<T>::find_set(const T& input)    {
    if (parent[input] != input) {
        parent[input] = find_set(parent[input]); // if input is not root, go up to check if its parent is.
    }
    return parent[input]; // return root
}

template <typename T>
void DisjointSet<T>::union_set(const T& elem1, const T& elem2)   {
    if (rank[elem1] > rank[elem2])  {
        parent[elem2] = elem1; // append shallower tree to taller tree root
    }   else if (rank[elem2] > elem[1]) {
        parent[elem1] = elem2;
    }   else    {
        parent[elem1] = elem2;
        ++rank[elem2];
    }
    
}


#endif // DISJOINTSET_HPP