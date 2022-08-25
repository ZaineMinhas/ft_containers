#include "vector.hpp"
#include "red_black_tree.hpp"
#include "map.hpp"

int		main(void)
{
	ft::map<int, char> map;

	// std::cout << map.insert(ft::make_pair(5, 65)).second << std::endl;
	// std::cout << map.insert(ft::make_pair(5, 66)).second << std::endl;
	// std::cout << map.insert(ft::make_pair(5, 67)).second << std::endl;
	// std::cout << map.insert(ft::make_pair(5, 68)).second << std::endl;
	// std::cout << map.insert(ft::make_pair(6, 65)).second << std::endl;

	// std::cout << "----------------------------------------------------" << std::endl;

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

	map.aff_tree();

	// std::cout << "----------------------------------------------------" << std::endl;

	// std::cout << map.begin()->first;
	// std::cout << map.end()->first;
	// for (ft::map<const int, char>::iterator it = map.begin(); it != map.end(); --it)
	// 	map.aff_node(it);

	// std::cout << "----------------------------------------------------" << std::endl;

	// ft::map<const int, char>::iterator it = map.begin();
	// map.aff_node(it);
	// it++;
	// map.aff_node(++it);
	// map.aff_node(++it);

	// std::cout << "del : " << map.erase(6) << std::endl;
	// map.aff_tree();
	// std::cout << "del : " << map.erase(5) << std::endl;
	// map.aff_tree();
	// std::cout << "del : " << map.erase(1) << std::endl;
	// map.aff_tree();
	// std::cout << "del : " << map.erase(84) << std::endl;
	// map.aff_tree();
	// std::cout << "del : " << map.erase(19) << std::endl;
	// map.aff_tree();
	// std::cout << "del : " << map.erase(101) << std::endl;
	// map.aff_tree();
	// std::cout << "del : " << map.erase(1000) << std::endl;
	// map.aff_tree();
	// std::cout << "del : " << map.erase(420) << std::endl;
	// map.aff_tree();
	// std::cout << "del : " << map.erase(84) << std::endl;
	// map.aff_tree();
	// std::cout << "del : " << map.erase(8) << std::endl;
	// map.aff_tree();
	// std::cout << "del : " << map.erase(42) << std::endl;
	// map.aff_tree();
	// std::cout << "del : " << map.erase(69) << std::endl;
	// map.aff_tree();
	// std::cout << "del : " << map.erase(18) << std::endl;
	// map.aff_tree();
	// std::cout << "del : " << map.erase(7) << std::endl;
	// map.aff_tree();
	// std::cout << "del : " << map.erase(2) << std::endl;
	// map.aff_tree();
	// std::cout << "del : " << map.erase(-4) << std::endl;
	// map.aff_tree();
	// std::cout << "del : " << map.erase(2) << std::endl;
	// map.aff_tree();
	// std::cout << "del : " << map.erase(666) << std::endl;
	// map.aff_tree();

	// std::cout << "----------------------------------------------------" << std::endl;


	std::cout << "--- STOP ---\n";
	// map.aff_tree();
	std::cout << "size : " << map.size() << std::endl;
	std::cout << "empty : " << map.empty() << std::endl;

	return (0);
}

/*int	main(void)
{
	ft::rb_tree<const int, int>	tree;
	
	tree.insert(ft::make_pair(5, 65));
	tree.insert(ft::make_pair(6, 65));
	tree.insert(ft::make_pair(7, 65));
	tree.insert(ft::make_pair(8, 65));
	tree.insert(ft::make_pair(18, 65));
	tree.insert(ft::make_pair(1, 65));
	tree.insert(ft::make_pair(-4, 65));
	tree.insert(ft::make_pair(1000, 65));
	tree.insert(ft::make_pair(2, 65));
	tree.insert(ft::make_pair(84, 65));
	tree.insert(ft::make_pair(69, 65));
	tree.insert(ft::make_pair(420, 65));
	tree.insert(ft::make_pair(42, 65));
	tree.insert(ft::make_pair(19, 65));
	tree.insert(ft::make_pair(101, 65));

	std::cout << "----------------------------------------------------------------------------------------" << std::endl;
	tree.aff_tree();
	std::cout << "----------------------------------------------------------------------------------------" << std::endl;

	tree.del_node(ft::make_pair(6, 65));
	tree.aff_tree();
	std::cout << "----------------------------------------------------------------------------------------" << std::endl;
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

	// tree.aff_tree();
	return (0);
}*/

// clear && c++ main.cpp && ./a.out
