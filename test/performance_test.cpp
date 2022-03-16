//
// Created by ruslan on 16.03.2022.
//

#include "../src/vector.hpp"
#include "../src/map.hpp"
#include "../src/stack.hpp"
#include <vector>
#include <map>
#include <stack>
#include <iostream>
#include <iomanip>
#include "stdlib.h"

void vector_perform ()
{
	std::vector<int> stl_vector;
	ft::vector<int> ft_vector;

	time_t start, end;
	time_t time_taken, total_stl, total_ft;

	// вставка STL
	start = clock();
	for (int i = 0; i < 5000; i++)
	{
		stl_vector.push_back(i);
	}
	end = clock();
	time_taken = end - start;
	total_stl = time_taken;

	std::cout << "STL Insertion time is " << time_taken << " ms" << std::endl;

	//поиск и замена STL
	srand(time(0));
	int value = rand() % 5000;

	start = clock();
	for (int i = 0; i < 1000; i++)
	{
		stl_vector[value] = 4;
	}
	end = clock();

	time_taken = end - start;
	total_stl += time_taken;

	std::cout << "STL find and replace time is " << time_taken << " ms" << std::endl;

	//удаление STL

	start = clock();
	for (int i = 0; i < 1000; i++)
	{
		stl_vector.erase(stl_vector.begin() + value);
	}
	end = clock();

	time_taken = end - start;
	total_stl += time_taken;

	std::cout << "STL deletion time is " << time_taken << " ms" << std::endl;
	std::cout << "STL total time is " << total_stl << " ms" << std::endl;
	std::cout << "\n";

	// вставка FT
	start = clock();
	for (int i = 0; i < 5000; i++)
	{
		ft_vector.push_back(i);
	}
	end = clock();
	time_taken = end - start;
	total_ft = time_taken;

	std::cout << "FT Insertion time is " << time_taken << " sec" << std::endl;

	//поиск и замена FT

	start = clock();
	for (int i = 0; i < 1000; i++)
	{
		ft_vector[value] = 4;
	}
	end = clock();

	time_taken = end - start;
	total_ft += time_taken;

	std::cout << "FT find and replace time is " << time_taken << " ms" << std::endl;

	//удаление FT

	start = clock();
	for (int i = 0; i < 1000; i++)
	{
		ft_vector.erase(ft_vector.begin() + value);
	}
	end = clock();

	time_taken = end - start;
	total_ft += time_taken;

	std::cout << "FT deletion time is " << time_taken << " ms" << std::endl;
	std::cout << "FT total time is " << total_ft << " ms" << std::endl;
	std::cout << "\n";

	if (total_ft / total_stl > 1)
		std::cout << "FT vector slower in " << total_ft / total_stl << " times";
	else
		std::cout << "FT vector faster in" << total_stl / total_ft << " times";

}

void map_perform()
{
	time_t start, end;
	time_t time_taken, total_stl, total_ft;

	srand(time(0));
	std::map<int, int> stl_map;
	ft::map<int, int> ft_map;

	int value1 = rand();
	int value2 = rand();

	//вставка
	start = clock();
	for (int i = 0; i < 5000; i++)
	{
		stl_map.insert(std::make_pair(value1, value2));
	}
	end = clock();
	time_taken = end - start;
	total_stl = time_taken;
	std::cout << "STL Insertion time is " << time_taken << " sec" << std::endl;
}

void stack_perform ()
{
	std::stack<int> stl_stack;
	ft::stack<int> ft_stack;
}

int main ()
{
	std::cout << std::setfill('*') << std::setw(70) << std::left << "VECTOR PERFORMANCE" << std::endl;
	vector_perform();
	std::cout << "\n";
	std::cout << std::setfill('*') << std::setw(70) << std::left << "MAP PERFORMANCE" << std::endl;
	map_perform();
	std::cout << "\n";
	std::cout << std::setfill('*') << std::setw(70) << std::left << "STACK PERFORMANCE" << std::endl;
	stack_perform();
}


