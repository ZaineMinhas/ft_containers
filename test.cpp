#include <iostream>
#include <vector>
#include "vector.hpp"

int main(void)
{
	ft::vector<int> vec, vec2, vec3, vec4;
	for (int i = 0; i < 10000; i++)
		vec.push_back(rand() % 100000);

	vec.reserve(100000000);
	vec.resize(10);
	vec.resize(1000000, -5);
	vec2 = vec;
	vec3 = vec2;
	vec2.clear();
	vec3.swap(vec4);

	std::cout << vec.size() << std::endl;
	std::cout << vec2.size() << std::endl;
	std::cout << vec3.size() << std::endl;
	std::cout << vec4.size() << std::endl;
	std::cout << vec.empty() << std::endl;
	std::cout << vec2.empty() << std::endl;
	std::cout << vec3.empty() << std::endl;
	std::cout << vec4.empty() << std::endl;
	std::cout << vec.capacity() << std::endl;
	std::cout << vec2.capacity() << std::endl;
	std::cout << vec3.capacity() << std::endl;
	std::cout << vec4.capacity() << std::endl;
	return 0;
}
