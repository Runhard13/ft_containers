#include "../src/vector.hpp"
#include <vector>
#include <iostream>
#include <iomanip>

template <class T>
std::string is_equal(const T& t1, const T& t2) { return t1 == t2 ? "ok" : "not ok"; }

template<class T>
std::string
is_equal_content(
	 std::vector<T> &stl_vector,
	 ft::vector<T> &ft_vector
)
{
	typename ft::vector<T>::iterator ft_it;
	typename std::vector<T>::iterator stl_it;

	if (ft_vector.size() != stl_vector.size())
		return ("NOT EQUAL");
	stl_it = stl_vector.begin();
	ft_it = ft_vector.begin();
	while (ft_it != ft_vector.end())
	{
		if (*ft_it != *stl_it)
			return ("NOT EQUAL");
		stl_it++;
	}
	return ("EQUAL");
}

template <class T>
void printValues(
	std::vector<T>& stl_vector,
	ft::vector<T>& ft_vector, std::string testName
)
{
	//real vector
	std::string stl_empty = ((stl_vector.empty() == 1) ? "true" : "false");
	size_t stl_size = stl_vector.size();
	size_t stl_max_size = stl_vector.max_size();
	size_t stl_capacity = stl_vector.capacity();

	//ft_vector
	std::string ft_empty = ((ft_vector.empty() == 1) ? "true" : "false");
	size_t ft_size = ft_vector.size();
	size_t ft_max_size = ft_vector.max_size();
	size_t ft_capacity = ft_vector.capacity();

	//сравнение
	std::string empty = is_equal(ft_empty, stl_empty);
	std::string size = is_equal(ft_size, stl_size);
	std::string max_size = is_equal(ft_max_size, stl_max_size);
	std::string capacity = is_equal(ft_capacity, stl_capacity); // в текущей реализации не всегда равны эти параметры
	std::string content = is_equal_content(stl_vector, ft_vector);



	std::cout << std::setfill('*') << std::setw(80) << std::left << testName << std::endl;
	std::cout << std::setfill(' ') << std::setw(20) << std::left << "Attribute";
	std::cout << std::setfill(' ') << std::setw(20) << std::left << "STL Vector";
	std::cout << std::setfill(' ') << std::setw(20) << std::left << "FT Vector";
	std::cout << std::setfill(' ') << std::setw(20) << std::left << "Result" << std::endl;

	std::cout << std::setfill(' ') << std::setw(20) << std::left << "Empty";
	std::cout << std::setfill(' ') << std::setw(20) << std::left << stl_empty;
	std::cout << std::setfill(' ') << std::setw(20) << std::left << ft_empty;
	std::cout << std::setfill(' ') << std::setw(20) << std::left << empty << std::endl;

	std::cout << std::setfill(' ') << std::setw(20) << std::left << "Size";
	std::cout << std::setfill(' ') << std::setw(20) << std::left << stl_size;
	std::cout << std::setfill(' ') << std::setw(20) << std::left << ft_size;
	std::cout << std::setfill(' ') << std::setw(20) << std::left << size << std::endl;

	std::cout << std::setw(20) << std::left << "Capacity";
	std::cout << std::setw(20) << std::left << stl_capacity;
	std::cout << std::setw(20) << std::left << ft_capacity;
	std::cout << std::setw(20) << std::left << capacity << std::endl;

	std::cout << std::setw(20) << std::left << "Max_size";
	std::cout << std::setw(20) << std::left << stl_max_size;
	std::cout << std::setw(20) << std::left << ft_max_size;
	std::cout << std::setw(20) << std::left << max_size << std::endl;
	std::cout << "\n";

	std::cout << std::left << "Result of content comparison: " << content << std::endl;
	if (empty == "not ok" || size == "not ok" || max_size == "not ok" || content == "NOT EQUAL")
		std::cout << "\33[1;31m" << "TOTAL: NOT OK" << "\33[1;0m" << std::endl;
	std::cout << "\33[1;32m" << "TOTAL: OK" << "\33[1;0m" << std::endl;
	std::cout << "**********************************************************************" << std::endl;
}

template <class T>
void printVectors(
	std::vector<T>& stl_vector,
	ft::vector<T>& ft_vector
)
{
	typename std::vector<T>::iterator stl_it;
	typename ft::vector<T>::iterator ft_it;
	stl_it = stl_vector.begin();
	ft_it = ft_vector.begin();

	//печать STL
	std::cout << "STL Vector content: ";
	while (stl_it != stl_vector.end())
	{
		std::cout << *stl_it << ", ";
		stl_it++;
	}
	std::cout << "\n";

	//печать FT
	std::cout << "FT Vector content: ";
	while (ft_it != ft_vector.end())
	{
		std::cout << *ft_it << ", ";
		ft_it++;
	}
	std::cout << "\n";
	std::cout << "**********************************************************************" << std::endl;
}

void
test_vector()
{
	std::string testName;

	testName = "DEFAULT INT VECTOR";
	std::vector<int> stl_vector_default_int;
	ft::vector<int> ft_vector_default_int;
	printValues(stl_vector_default_int, ft_vector_default_int, testName);
	printVectors(stl_vector_default_int, ft_vector_default_int);
	std::cout << "\n\n";

	testName = "DEFAULT STRING VECTOR";
	std::vector<std::string> stl_vector_default_string;
	ft::vector<std::string> ft_vector_default_string;
	printValues(stl_vector_default_string, ft_vector_default_string, testName);
	printVectors(stl_vector_default_string, ft_vector_default_string);
}