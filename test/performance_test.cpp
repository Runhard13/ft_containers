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

void vector_perform() {
  std::vector<int> stl_vector;
  ft::vector<int> ft_vector;

  time_t start, end;
  double time_taken, total_stl, total_ft;

  //STL VECTOR PERFOMANCE TEST************

  // вставка
  start = clock();
  for (int i = 0; i < 5000; i++)
	stl_vector.push_back(i);
  end = clock();

  time_taken = end - start;
  total_stl = time_taken;
  std::cout << "STL Insertion time is " << time_taken << " ms" << std::endl;

  //поиск
  srand(time(0));
  int value = rand() % 5000;

  start = clock();
  for (int i = 0; i < 5000; i++)
	stl_vector[value] = 4;
  end = clock();

  time_taken = end - start;
  total_stl += time_taken;
  std::cout << "STL find time is " << time_taken << " ms" << std::endl;

  //удаление
  start = clock();
  stl_vector.erase(stl_vector.begin(), stl_vector.begin() + 200);
  end = clock();

  time_taken = end - start;
  total_stl += time_taken;
  std::cout << "STL deletion time is " << time_taken << " ms" << std::endl;
  std::cout << "\n";
  std::cout << "STL total time is " << total_stl << " ms" << std::endl;
  std::cout << "\n";

  //FT VECTOR PERFOMANCE TEST************

  //вставка
  start = clock();
  for (int i = 0; i < 5000; i++)
	ft_vector.push_back(i);
  end = clock();

  time_taken = end - start;
  total_ft = time_taken;
  std::cout << "FT Insertion time is " << time_taken << " ms" << std::endl;

  //поиск
  start = clock();
  for (int i = 0; i < 5000; i++)
	ft_vector[value] = 4;
  end = clock();

  time_taken = end - start;
  total_ft += time_taken;
  std::cout << "FT find time is " << time_taken << " ms" << std::endl;

  //удаление
  start = clock();
  ft_vector.erase(ft_vector.begin(), ft_vector.begin() + 200);
  end = clock();

  time_taken = end - start;
  total_ft += time_taken;
  std::cout << "FT deletion time is " << time_taken << " ms" << std::endl;
  std::cout << "FT total time is " << total_ft << " ms" << std::endl;
  std::cout << "\n";

  if (total_ft / total_stl > 1)
	std::cout << "FT vector slower in " << total_ft / total_stl << " times";
  else
	std::cout << "FT vector faster in " << total_stl / total_ft << " times";

}

void map_perform() {
  time_t start, end;
  double time_taken, total_stl, total_ft;

  srand(time(0));
  std::map<int, int> stl_map;
  ft::map<int, int> ft_map;

  int value1 = rand();
  int value2 = rand();

  //STL MAP PERFOMANCE TEST************

  //вставка
  start = clock();
  for (int i = 0; i < 5000; i++)
	stl_map.insert(std::make_pair(value1, value2));
  end = clock();

  time_taken = end - start;
  total_stl = time_taken;
  std::cout << "STL Insertion time is " << time_taken << " ms" << std::endl;

  //поиск
  value1 = rand() % 4900;
  start = clock();
  for (int i = 0; i < 3000; i++)
	stl_map.find(value1);
  end = clock();

  time_taken = end - start;
  total_stl += time_taken;
  std::cout << "STL find time is " << time_taken << " ms" << std::endl;

  //удаление
  value1 = rand() % 4900;
  start = clock();
  for (int i = 0; i < 3000; i++)
	stl_map.erase(value1);
  end = clock();

  time_taken = end - start;
  total_stl += time_taken;

  std::cout << "STL deletion time is " << time_taken << " ms" << std::endl;
  std::cout << "\n";

  std::cout << "STL total time is " << total_stl << " ms" << std::endl;
  std::cout << "\n";

  //FT MAP PERFOMANCE TEST************

  //вставка
  start = clock();
  for (int i = 0; i < 5000; i++)
	ft_map.insert(ft::make_pair(value1, value2));
  end = clock();

  time_taken = end - start;
  total_ft = time_taken;
  std::cout << "FT Insertion time is " << time_taken << " ms" << std::endl;

  //поиск
  value1 = rand() % 4900;
  start = clock();
  for (int i = 0; i < 3000; i++)
	ft_map.find(value1);
  end = clock();

  time_taken = end - start;
  total_ft += time_taken;
  std::cout << "FT find time is " << time_taken << " ms" << std::endl;

  //удаление
  value1 = rand() % 4900;
  start = clock();
  for (int i = 0; i < 3000; i++)
	ft_map.erase(value1);
  end = clock();

  time_taken = end - start;
  total_ft += time_taken;
  std::cout << "FT deletion time is " << time_taken << " ms" << std::endl;
  std::cout << "\n";
  std::cout << "FT total time is " << total_ft << " ms" << std::endl;
  std::cout << "\n";

  if (total_ft / total_stl > 1)
	std::cout << "FT map slower in " << total_ft / total_stl << " times";
  else
	std::cout << "FT map faster in " << total_stl / total_ft << " times";
}

void stack_perform() {
  std::stack<int> stl_stack;
  ft::stack<int> ft_stack;
}

int main() {
  std::cout << std::setfill('*') << std::setw(70) << std::left << "VECTOR PERFORMANCE" << std::endl;
  vector_perform();
  std::cout << "\n";
  std::cout << "\n";
  std::cout << std::setfill('*') << std::setw(70) << std::left << "MAP PERFORMANCE" << std::endl;
  map_perform();
  std::cout << "\n";
}


