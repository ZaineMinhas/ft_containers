#include "vector.hpp"
#include "red_black_tree.hpp"


int	main(void)
{
	ft::rb_tree<const int, int>	tree;
	
	tree.insert(ft::make_pair(50, 0));
	tree.insert(ft::make_pair(55, 2));
	tree.insert(ft::make_pair(35, 4));
	tree.insert(ft::make_pair(40, 4));
	tree.insert(ft::make_pair(20, 4));
	tree.insert(ft::make_pair(10, 4));
	tree.insert(ft::make_pair(5, 4));
	tree.insert(ft::make_pair(25, 4));
	tree.insert(ft::make_pair(17, 4));
	tree.insert(ft::make_pair(40, 4));
	tree.insert(ft::make_pair(40, 4));
	tree.insert(ft::make_pair(40, 4));
	tree.insert(ft::make_pair(40, 4));

	std::cout << "----------------------------------------------------------------------------------------" << std::endl;
	tree.aff_tree(tree.get_root(), 0);
	std::cout << "----------------------------------------------------------------------------------------" << std::endl;

	tree.del_node(ft::make_pair(35, 4));
	tree.aff_tree(tree.get_root(), 0);
	std::cout << "----------------------------------------------------------------------------------------" << std::endl;
	tree.del_node(ft::make_pair(35, 4));
	tree.aff_tree(tree.get_root(), 0);
	std::cout << "----------------------------------------------------------------------------------------" << std::endl;
	tree.del_node(ft::make_pair(35, 4));
	tree.aff_tree(tree.get_root(), 0);
	std::cout << "----------------------------------------------------------------------------------------" << std::endl;
	tree.del_node(ft::make_pair(35, 4));
	tree.aff_tree(tree.get_root(), 0);
	std::cout << "----------------------------------------------------------------------------------------" << std::endl;
	tree.del_node(ft::make_pair(35, 4));
	tree.aff_tree(tree.get_root(), 0);
	std::cout << "----------------------------------------------------------------------------------------" << std::endl;

	tree.aff_tree(tree.get_root(), 0);
	return (0);
}

// clear && c++ red_black_tree.hpp main.cpp && ./a.out
