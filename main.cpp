#include "vector.hpp"

int	main(void)
{
	ft::vector<int> t(7, 20);
	ft::vector<int> v(t);

	std::cout << "CAPACITY : " << v.capacity() << std::endl;
	std::cout << "SIZE : " << v.size() << std::endl;
	std::cout << "|";
	for (size_t i = 0; i < v.size(); i++)
		std::cout << v[i] << "|";
	std::cout << std::endl;
	
	v.resize(10, 42);

	std::cout << std::endl << "CAPACITY : " << v.capacity() << std::endl;
	std::cout << "SIZE : " << v.size() << std::endl;
	std::cout << "|";
	for (size_t i = 0; i < v.size(); i++)
		std::cout << v[i] << "|";
	std::cout << std::endl;
	return (0);
}

// c++ main.cpp && clear && ./a.out
