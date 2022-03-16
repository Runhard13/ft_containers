clang++ test/performance_test.cpp -o performance_test -Wall -Wextra -Werror -std=c++98
./performance_test > performance_test_result.txt
cat performance_test_result.txt