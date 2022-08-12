#include "vector.hpp"
#include "bbt_tree.hpp"


int	main(void)
{
	ft::rb_tree<const int, int>	tree;
	
	tree.insert(ft::make_pair(1, 0));
	tree.insert(ft::make_pair(2, 2));
	tree.insert(ft::make_pair(-2, 3));
	tree.insert(ft::make_pair(1, 4));

	std::cout << "ROOT = " << tree.get_root()->data.first << std::endl;
	return (0);
}

// clear && c++ bbt_tree.hpp main.cpp && ./a.out
