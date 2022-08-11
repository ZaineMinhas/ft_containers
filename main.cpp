#include "vector.hpp"
#include "bbt_tree.hpp"


int	main(void)
{
	ft::rb_tree<const int, int>	tree;
	
	tree.insert(ft::make_pair(0, 0));
	return (0);
}

// c++ main.cpp && clear && ./a.out
