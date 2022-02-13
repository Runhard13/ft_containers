#include <iostream>
#include <vector>
#include "../src/containers/vector.hpp"
#include "../src/containers/stack.hpp"
//#include "../src/containers/map.hpp"

int main ()
{
	ft::vector<int> ft_vector;

	ft_vector.push_back(5);
	ft_vector.push_back(5);
	ft_vector.push_back(5);
	ft_vector.push_back(5);
	std::cout << ft_vector.size() << std::endl;

	int range_array[] = { 87, 92, -5, 8984, 96 };
	ft::vector<int>::const_iterator ft_iterator(&(range_array[0]));
	ft::vector<int> ft_range_vector(ft_iterator, ft_iterator + 5);
	if (ft_iterator == ft_range_vector.begin())
		{ std::cout << "==" << std::endl; }
	
	if (ft_iterator != ft_range_vector.begin())
		{ std::cout << "!=" << std::endl; }

	if (ft_iterator > ft_range_vector.begin())
		{ std::cout << ">" << std::endl; }

	if (ft_iterator >= ft_range_vector.begin())
		{ std::cout << ">=" << std::endl; }

	if (ft_iterator < ft_range_vector.begin())
		{ std::cout << "<" << std::endl; }

	if (ft_iterator <= ft_range_vector.begin())
		{ std::cout << "<=" << std::endl; }

	//ft_iterator = ft_range_vector.begin();
		
	return (0);
}