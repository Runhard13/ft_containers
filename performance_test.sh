clang++ test/main.cpp test/test_map.cpp test/test_stack.cpp test/test_vector.cpp -o main_test -Wall -Wextra -Werror -std=c++98
./main_test > main_test_result.txt
cat main_test_result.txt