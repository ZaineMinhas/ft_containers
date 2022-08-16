#include "vector.hpp"
#include "bbt_tree.hpp"


int	main(void)
{
	ft::rb_tree<const int, int>	tree;
	
	tree.insert(ft::make_pair(1, 0));
	tree.insert(ft::make_pair(2, 2));
	tree.insert(ft::make_pair(-2, 3));
	tree.insert(ft::make_pair(10, 4));
	tree.insert(ft::make_pair(11, 4));
	tree.insert(ft::make_pair(12, 4));
	tree.insert(ft::make_pair(13, 4));
	tree.insert(ft::make_pair(-3, 4));
	tree.insert(ft::make_pair(-4, 4));
	tree.insert(ft::make_pair(11, 4));


	// std::cout << "ROOT = " << tree.get_root()->data.first << std::endl;
	// tree.aff_node(tree.get_root()->right);
	tree.aff_tree(tree.get_root(), 0);
	return (0);
}

// clear && c++ bbt_tree.hpp main.cpp && ./a.out
