clang++ test/*.cpp -o start -Wall -Wextra -Werror -std=c++98
./start > test_result.txt
cat test_result.txt