#include <iostream>
#include <string>
#include <deque>
#if 1 //CREATE A REAL STL EXAMPLE
#include <map>
#include <stack>
#include <vector>
namespace ft = std;
#else
#include <src/map.hpp>
#include <src/stack.hpp>
#include <src/vector.hpp>
#endif

#include <stdlib.h>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
  int idx;
  char buff[BUFFER_SIZE];
};

#define COUNT (MAX_RAM / (int)sizeof(Buffer))

void test_vector();
void test_stack();
void test_map();

int main()
{


  //test_stack();
  //test_map();
  //test_vector();
  return (0);
}
