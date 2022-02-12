#include <iostream>
#include "../src/containers/vector.hpp"
#include "../src/containers/stack.hpp"
#include "../src/containers/map.hpp"

int main ()
{
	ft::vector<int> ft_vector;

	ft_vector.push_back(5);
	ft_vector.push_back(5);
	ft_vector.push_back(5);
	ft_vector.push_back(5);

	std::cout << ft_vector.size() << std::endl;

	return (0);
}