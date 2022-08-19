#include "vector.hpp"
#include "red_black_tree.hpp"
#include "map.hpp"


/*int	main(void)
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
	tree.insert(ft::make_pair(45, 4));
	tree.insert(ft::make_pair(46, 4));
	tree.insert(ft::make_pair(47, 4));
	tree.insert(ft::make_pair(48, 4));
	tree.insert(ft::make_pair(49, 4));
	tree.insert(ft::make_pair(51, 4));
	tree.insert(ft::make_pair(52, 4));

	// std::cout << "----------------------------------------------------------------------------------------" << std::endl;
	// tree.aff_tree();
	// std::cout << "----------------------------------------------------------------------------------------" << std::endl;

	// tree.del_node(ft::make_pair(35, 4));
	// tree.aff_tree();
	// std::cout << "----------------------------------------------------------------------------------------" << std::endl;
	// tree.del_node(ft::make_pair(35, 4));
	// tree.aff_tree();
	// std::cout << "----------------------------------------------------------------------------------------" << std::endl;
	// tree.del_node(ft::make_pair(35, 4));
	// tree.aff_tree();
	// std::cout << "----------------------------------------------------------------------------------------" << std::endl;
	// tree.del_node(ft::make_pair(35, 4));
	// tree.aff_tree();
	// std::cout << "----------------------------------------------------------------------------------------" << std::endl;
	// tree.del_node(ft::make_pair(35, 4));
	// tree.aff_tree();
	// std::cout << "----------------------------------------------------------------------------------------" << std::endl;

	tree.aff_tree();
	return (0);
}*/

int		main(void)
{
	ft::map<const int, char> map;

	// std::cout << map.insert(ft::make_pair(5, 65)).first->second << std::endl;
	// std::cout << map.insert(ft::make_pair(5, 65)).second << std::endl;
	map.insert(ft::make_pair(5, 65));
	map.insert(ft::make_pair(6, 65));
	map.insert(ft::make_pair(7, 65));
	map.insert(ft::make_pair(8, 65));
	map.insert(ft::make_pair(18, 65));
	map.insert(ft::make_pair(1, 65));
	map.insert(ft::make_pair(-4, 65));
	map.insert(ft::make_pair(1000, 65));
	map.insert(ft::make_pair(2, 65));
	map.insert(ft::make_pair(84, 65));
	map.insert(ft::make_pair(69, 65));
	map.insert(ft::make_pair(420, 65));
	map.insert(ft::make_pair(42, 65));
	map.insert(ft::make_pair(19, 65));
	map.insert(ft::make_pair(101, 65));
	// std::cout << map.begin()->first;
	// std::cout << map.end()->first;
	for (ft::map<const int, char>::iterator it = map.begin(); it != map.end(); --it)
		map.aff_node(it);

	// ft::map<const int, char>::iterator it = map.begin();
	// map.aff_node(it);
	// it++;
	// map.aff_node(++it);
	// map.aff_node(++it);

	std::cout << "----------------------------------------------------" << std::endl;

	map.aff_tree();

	// std::cout << map.empty() << std::endl;

	return (0);
}



// clear && c++ main.cpp && ./a.out
