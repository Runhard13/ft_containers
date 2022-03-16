cmake_minimum_required(VERSION 3.17)
project(ft_containers)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")

add_executable(ft_containers
        test/main.cpp

        test/test_vector.cpp
        test/test_stack.cpp
        test/test_map.cpp
		)

add_executable(performance
		test/performance_test.cpp
		)