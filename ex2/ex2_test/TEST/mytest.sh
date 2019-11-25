#!/bin/bash
pathtest=/c/Users/davidponar/workspace/c_cpp/ex2/ex2_test/TEST/tests/in/test_static
./TreeAnalyzer.exe $pathtest/normal/normal.txt 4 3 > $pathtest/normal/log
# ./TreeAnalyzer.exe $pathtest/bad_first_number/bad_first_number.txt 10 3 2>&1 | tee -a $pathtest/bad_first_number/log
# ./TreeAnalyzer.exe $pathtest/bad_second_number/bad_second_number.txt 4 10 2>&1 | tee -a $pathtest/bad_second_number/log
# ./TreeAnalyzer.exe $pathtest/double_in_line/double_in_line.txt 0 4 2>&1 | tee -a $pathtest/double_in_line/log
# ./TreeAnalyzer.exe $pathtest/file_doesnt_exist/file_doesnt_exist.txt 4 3 2>&1 | tee -a $pathtest/file_doesnt_exist/log
# ./TreeAnalyzer.exe $pathtest/file_is_empty/file_is_empty.txt 4 3 2>&1 | tee -a $pathtest/file_is_empty/log
# ./TreeAnalyzer.exe $pathtest/long_one_sided/long_one_sided.txt 4 3 2>&1 | tee -a $pathtest/long_one_sided/log
# ./TreeAnalyzer.exe $pathtest/long_one_sided_big_range/long_one_sided_big_range.txt 0 99 2>&1 | tee -a $pathtest/long_one_sided_big_range/log
# ./TreeAnalyzer.exe $pathtest/long_one_sided_opposite_big_range/long_one_sided_opposite_big_range.txt 99 0 2>&1 | tee -a $pathtest/long_one_sided_opposite_big_range/log
# ./TreeAnalyzer.exe $pathtest/long_tree/long_tree.txt 4 3 2>&1 | tee -a $pathtest/long_tree/log
# ./TreeAnalyzer.exe $pathtest/n_too_big/n_too_big.txt 4 3 2>&1 | tee -a $pathtest/n_too_big/log
# ./TreeAnalyzer.exe $pathtest/n_too_small/n_too_small.txt 4 3 2>&1 | tee -a $pathtest/n_too_small/log
# ./TreeAnalyzer.exe $pathtest/no_arguments/no_arguments.txt 2>&1 | tee -a $pathtest/no_arguments/log
# ./TreeAnalyzer.exe $pathtest/no_first_number/no_first_number.txt 3 2>&1 | tee -a $pathtest/no_first_number/log
# ./TreeAnalyzer.exe $pathtest/no_second_number/no_second_number.txt 4 2>&1 | tee -a $pathtest/no_second_number/log
# ./TreeAnalyzer.exe $pathtest/same_node_route/same_node_route.txt 0 0 2>&1 | tee -a $pathtest/same_node_route/log
# ./TreeAnalyzer.exe $pathtest/small_tree/small_tree.txt 0 0 2>&1 | tee -a $pathtest/small_tree/log
# ./TreeAnalyzer.exe $pathtest/zero_vertices/zero_vertices.txt 0 0 2>&1 | tee -a $pathtest/zero_vertices/log
