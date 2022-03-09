#include "../src/vector.hpp"
#include <vector>
#include <iostream>
#include <iomanip>

template<class T>
std::string
is_equal(const T &t1, const T &t2) { return t1 == t2 ? "ok" : "not ok"; }

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
		ft_it++;
	}
	return ("EQUAL");
}

template<class T>
void
printValues(
	std::vector<T> &stl_vector,
	ft::vector<T> &ft_vector, std::string testName
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

	std::cout << std::setfill('*') << std::setw(70) << std::left << testName << std::endl;
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
	else
		std::cout << "\33[1;32m" << "TOTAL: OK" << "\33[1;0m" << std::endl;
	std::cout << "**********************************************************************" << std::endl;
}

template<class T>
void
printVectors(
	std::vector<T> &stl_vector,
	ft::vector<T> &ft_vector
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
		std::cout << *stl_it;
		stl_it++;
		if (stl_it != stl_vector.end())
			std::cout << ", ";
	}
	std::cout << "\n";

	//печать FT
	std::cout << "FT Vector content: ";
	while (ft_it != ft_vector.end())
	{
		std::cout << *ft_it;
		ft_it++;
		if (ft_it != ft_vector.end())
			std::cout << ", ";
	}
	std::cout << "\n";
	std::cout << "**********************************************************************" << std::endl;
	std::cout << "\n\n";
}

void
test_vector()
{
	std::string testName;
	std::vector<int> myvector;
	for (int i=1; i<=5; i++) myvector.push_back(i);

	{
		testName = "DEFAULT INT VECTOR";

		std::vector<int> stl_vector_default_int;
		ft::vector<int> ft_vector_default_int;

		printValues(stl_vector_default_int, ft_vector_default_int, testName);
		printVectors(stl_vector_default_int, ft_vector_default_int);
	}

	{
		testName = "DEFAULT STRING VECTOR";

		std::vector<std::string> stl_vector_default_string;
		ft::vector<std::string> ft_vector_default_string;

		printValues(stl_vector_default_string, ft_vector_default_string, testName);
		printVectors(stl_vector_default_string, ft_vector_default_string);

	}

	{
		testName = "FILL CONSTRUCTOR";

		std::vector<int> stl_fill_vector(11);
		ft::vector<int> ft_fill_vector(11);

		printValues(stl_fill_vector, ft_fill_vector, testName);
		printVectors(stl_fill_vector, ft_fill_vector);

		testName = "FILL CONSTRUCTOR WITH VALUE";

		std::vector<int> stl_fill_vector_with_value(11, 22);
		ft::vector<int> ft_fill_vector_with_value(11, 22);

		printValues(stl_fill_vector_with_value, ft_fill_vector_with_value, testName);
		printVectors(stl_fill_vector_with_value, ft_fill_vector_with_value);
	}

	{
		testName = "RANGE CONSTRUCTOR";

		std::vector<int> stl_range_vector(myvector.begin(), myvector.end());
		ft::vector<int> ft_range_vector(myvector.begin(), myvector.end());

		printValues(stl_range_vector, ft_range_vector, testName);
		printVectors(stl_range_vector, ft_range_vector);
	}

	{
		testName = "ASSIGN";

		std::vector<int> stl_range_vector(myvector.begin(), myvector.end());
		ft::vector<int> ft_range_vector(myvector.begin(), myvector.end());

		std::vector<int> stl_assign_vector = stl_range_vector;
		ft::vector<int> ft_assign_vector = ft_range_vector;

		printValues(stl_assign_vector, ft_assign_vector, testName);
		printVectors(stl_assign_vector, ft_assign_vector);
	}

	{
		testName = "ITER BEGIN() and END()";


		std::vector<int> stl_range_vector(myvector.begin(), myvector.end());
		ft::vector<int> ft_range_vector(myvector.begin(), myvector.end());

		int from_stl = *(stl_range_vector.begin());
		int from_ft = *(ft_range_vector.begin());
		int from_stl_end = *(stl_range_vector.end() - 1);
		int from_ft_end = *(ft_range_vector.end() - 1);

		printValues(stl_range_vector, ft_range_vector, testName);
		std::cout << ".begin() from STL — " << from_stl << std::endl;
		std::cout << ".end() from STL — " << from_stl_end << std::endl;
		std::cout << "\n";
		std::cout << ".begin() from FT — " << from_ft << std::endl;
		std::cout << ".end() from FT — " << from_ft_end << std::endl;
		std::cout << "\n";
		printVectors(stl_range_vector, ft_range_vector);

	}

	{
		testName = "CONST ITER BEGIN() and END()";

		std::vector<int> stl_range_vector(myvector.begin(), myvector.end());
		ft::vector<int> ft_range_vector(myvector.begin(), myvector.end());

		int from_stl = *(stl_range_vector.begin());
		int from_ft = *(ft_range_vector.begin());
		int from_stl_end = *(stl_range_vector.end() - 1);
		int from_ft_end = *(ft_range_vector.end() - 1);

		printValues(stl_range_vector, ft_range_vector, testName);
		std::cout << ".const_begin() from STL — " << from_stl << std::endl;
		std::cout << ".const_end() from STL — " << from_stl_end << std::endl;
		std::cout << "\n";
		std::cout << ".const_begin() from FT — " << from_ft << std::endl;
		std::cout << ".const_end() from FT — " << from_ft_end << std::endl;
		std::cout << "\n";
		printVectors(stl_range_vector, ft_range_vector);

	}

	{
		//TODO: reverse итератор не работает -___-
		testName = "REVERSE ITER BEGIN() and END()";

		std::vector<int> stl_range_vector(myvector.begin(), myvector.end());
		ft::vector<int> ft_range_vector(myvector.begin(), myvector.end());

		int from_stl = *(stl_range_vector.rbegin());
		int from_ft = *(ft_range_vector.rbegin());
		int from_stl_end = *(stl_range_vector.rend() - 1);
		int from_ft_end = *(ft_range_vector.rend() - 1);

		printValues(stl_range_vector, ft_range_vector, testName);
		std::cout << ".rbegin() from STL — " << from_stl << std::endl;
		std::cout << ".rend() from STL — " << from_stl_end << std::endl;
		std::cout << "\n";
		std::cout << ".rbegin() from FT — " << from_ft << std::endl;
		std::cout << ".rend() from FT — " << from_ft_end << std::endl;
		std::cout << "\n";
		printVectors(stl_range_vector, ft_range_vector);

	}
	{
		testName = "CONST REV ITER";

		std::vector<int> stl_range_vector(myvector.begin(), myvector.end());
		ft::vector<int> ft_range_vector(myvector.begin(), myvector.end());

		int from_stl = *(stl_range_vector.rbegin());
		int from_ft = *(ft_range_vector.rbegin());
		int from_stl_end = *(stl_range_vector.rend() - 1);
		int from_ft_end = *(ft_range_vector.rend() - 1);

		printValues(stl_range_vector, ft_range_vector, testName);
		std::cout << ".const_rbegin() from STL — " << from_stl << std::endl;
		std::cout << ".const_rend() from STL — " << from_stl_end << std::endl;
		std::cout << "\n";
		std::cout << ".const_rbegin() from FT — " << from_ft << std::endl;
		std::cout << ".const_rend() from FT — " << from_ft_end << std::endl;
		std::cout << "\n";
		printVectors(stl_range_vector, ft_range_vector);
	}

	{
		testName = "SIZE MANITULATIONS";
		std::vector<int> stl_vector(1);
		ft::vector<int> ft_vector(1);

		stl_vector.resize(2);
		ft_vector.resize(2);

		stl_vector.push_back(11);
		ft_vector.push_back(11);
		stl_vector.push_back(14444444);
		ft_vector.push_back(14444444);

		stl_vector.reserve(1);
		ft_vector.reserve(1);

		stl_vector.push_back(11);
		ft_vector.push_back(11);
		stl_vector.push_back(11);
		ft_vector.push_back(11);
		stl_vector.push_back(11);
		ft_vector.push_back(11);

		stl_vector.reserve(100);
		ft_vector.reserve(100);

		stl_vector.push_back(345);
		ft_vector.push_back(345);

		printValues(stl_vector, ft_vector, testName);
		printVectors(stl_vector, ft_vector);
	}

	{
		testName = "OPERATOR[]";

		std::vector<int> stl_vector(10);
		ft::vector<int> ft_vector(10);

		unsigned i = 0;
		while (i++ < 4)
			stl_vector[i] = i;

		i = 0;
		while (i++ < 4)
			ft_vector[i] = i;

		printValues(stl_vector, ft_vector, testName);
		printVectors(stl_vector, ft_vector);
	}

	{
		testName = "OPERATOR AT.  VALID";
		std::vector<int> stl_vector(3);
		ft::vector<int> ft_vector(3);

		stl_vector.push_back(11);
		ft_vector.push_back(11);
		stl_vector.push_back(22);
		ft_vector.push_back(22);
		stl_vector.push_back(33);
		ft_vector.push_back(33);

		int ft = ft_vector.at(3);
		int stl = stl_vector.at(3);

		std::cout << "STL operator at(3) = " << stl << std::endl;
		std::cout << "FT operator at(3) = " << ft << std::endl;
	
		printValues(stl_vector, ft_vector, testName);
		printVectors(stl_vector, ft_vector);
	}

	{
	    testName = "OPERATOR AT. OUT OF RANGE";

	    ft::vector<int> ft_vector(3);

	    ft_vector.push_back(11);
	    ft_vector.push_back(22);
	    ft_vector.push_back(33);

	    try
	    {
	        ft_vector.at(3333333) = 50;
	    }
	    catch (const std::out_of_range& e)
	    {
	        std::cerr <<  "Error: "  << e.what() << std::endl;
	    }
	}

}