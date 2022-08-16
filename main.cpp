#include "vector.hpp"
#include "red_black_tree.hpp"


int	main(void)
{
	ft::rb_tree<const int, int>	tree;
	
	tree.insert(ft::make_pair(50, 0));
	tree.insert(ft::make_pair(55, 2));
	tree.insert(ft::make_pair(35, 3));
	tree.insert(ft::make_pair(40, 4));
	tree.insert(ft::make_pair(20, 4));
	tree.insert(ft::make_pair(10, 4));
	tree.insert(ft::make_pair(5, 4));
	std::cout << "----------------------------------------------------------------------------------------" << std::endl;
	tree.insert(ft::make_pair(25, 4));
	tree.insert(ft::make_pair(17, 4));
	tree.insert(ft::make_pair(40, 4));


	// std::cout << "ROOT = " << tree.get_root()->data.first << std::endl;
	// tree.aff_node(tree.get_root()->right);
	tree.aff_tree(tree.get_root(), 0);
	return (0);
}

/*int main(void) {
	ft::rb_tree<const int, char>	binaryTree;
	// ft::rb_tree<const int, char>	*node = binaryTree.new_node(ft::make_pair(0, 0), false, NULL);

	binaryTree.insert(ft::make_pair(50, 65));
	binaryTree.insert(ft::make_pair(55, 65));
	binaryTree.insert(ft::make_pair(35, 65));
	binaryTree.insert(ft::make_pair(40, 65));
	binaryTree.insert(ft::make_pair(20, 65));
	binaryTree.insert(ft::make_pair(10, 65));
	binaryTree.insert(ft::make_pair(5, 65));
	binaryTree.insert(ft::make_pair(25, 65));
	binaryTree.insert(ft::make_pair(17, 65));

	binaryTree.aff_tree(binaryTree.get_root(), 0);

	std::cout << std::endl << "----------------------------------------------------------------------" << std::endl;
	return (0);
}*/

// clear && c++ red_black_tree.hpp main.cpp && ./a.out
