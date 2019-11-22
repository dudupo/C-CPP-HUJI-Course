"""
Tester for C, exercise 2.
"""
import textwrap
from os import listdir
# from os import startfile
from os.path import isfile, join, isdir, exists
from os import path
import subprocess
import tarfile
from sys import stderr
from sys import platform
from difflib import *

DIFFERENCES_EXPLAINER = " 1. Lines prefixed with '-' indicate that they were in the USER output, but not the SCHOOLS output.\n 2. Lines prefixed with + were in the SCHOOLS output, but not the USER output.\n 3. If a line has an incremental difference between versions, an extra line prefixed with '?' is used to highlight the change within the new version.\n 4. If a line has not changed, it is printed with an extra blank space on the left column so that it it lines up with the other lines that may have differences."

END_EXPLAINER = "\n??????????????????????????????????????????????????????????????\n"

START_EXPLAINER = "\n???????????????????-HOW TO READ DIFFERENCE-???????????????????\n"

FAILED_TEST = """
   __      _ _          _   _            _   _ 
  / _|    (_) |        | | | |          | | | |
 | |_ __ _ _| | ___  __| | | |_ ___  ___| |_| |
 |  _/ _` | | |/ _ \/ _` | | __/ _ \/ __| __| |
 | || (_| | | |  __/ (_| | | ||  __/\__ \ |_|_|
 |_| \__,_|_|_|\___|\__,_|  \__\___||___/\__(_)
                                               
"""

SOME_TESTS_FAILED = """
                                                                                                 
 _____ _____ _____ _____    _____ _____ _____ _____ _____    _____ _____ _____ __    _____ ____  
|   __|     |     |   __|  |_   _|   __|   __|_   _|   __|  |   __|  _  |     |  |  |   __|    \ 
|__   |  |  | | | |   __|    | | |   __|__   | | | |__   |  |   __|     |-   -|  |__|   __|  |  |
|_____|_____|_|_|_|_____|    |_| |_____|_____| |_| |_____|  |__|  |__|__|_____|_____|_____|____/ 
                                                                                                 
"""

SUCCESS_BABY = """                                                                       
                                                                                
                     ,--,                                                       
  .--.--.          ,'_ /|                                 .--.--.    .--.--.    
 /  /    '    .--. |  | :    ,---.     ,---.     ,---.   /  /    '  /  /    '   
|  :  /`./  ,'_ /| :  . |   /     \   /     \   /     \ |  :  /`./ |  :  /`./   
|  :  ;_    |  ' | |  . .  /    / '  /    / '  /    /  ||  :  ;_   |  :  ;_     
 \  \    `. |  | ' |  | | .    ' /  .    ' /  .    ' / | \  \    `. \  \    `.  
  `----.   \:  | : ;  ; | '   ; :__ '   ; :__ '   ;   /|  `----.   \ `----.   \ 
 /  /`--'  /'  :  `--'   \'   | '.'|'   | '.'|'   |  / | /  /`--'  //  /`--'  / 
'--'.     / :  ,      .-./|   :    :|   :    :|   :    |'--'.     /'--'.     /  
  `--'---'   `--`----'     \   \  /  \   \  /  \   \  /   `--'---'   `--'---'   
                            `----'    `----'    `----'                          

$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$'               `$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$  
$$$$$$$$$$$$$$$$$$$$$$$$$$$$'                   `$$$$$$$$$$$$$$$$$$$$$$$$$$$$
$$$'`$$$$$$$$$$$$$'`$$$$$$!                       !$$$$$$'`$$$$$$$$$$$$$'`$$$
$$$$  $$$$$$$$$$$  $$$$$$$                         $$$$$$$  $$$$$$$$$$$  $$$$
$$$$. `$' \' \$`  $$$$$$$!                         !$$$$$$$  '$/ `/ `$' .$$$$
$$$$$. !\  i  i .$$$$$$$$                           $$$$$$$$. i  i  /! .$$$$$
$$$$$$   `--`--.$$$$$$$$$                           $$$$$$$$$.--'--'   $$$$$$
$$$$$$L        `$$$$$^^$$                           $$^^$$$$$'        J$$$$$$
$$$$$$$.   .'   ""~   $$$    $.                 .$  $$$   ~""   `.   .$$$$$$$
$$$$$$$$.  ;      .e$$$$$!    $$.             .$$  !$$$$$e,      ;  .$$$$$$$$
$$$$$$$$$   `.$$$$$$$$$$$$     $$$.         .$$$   $$$$$$$$$$$$.'   $$$$$$$$$
$$$$$$$$    .$$$$$$$$$$$$$!     $$`$$$$$$$$'$$    !$$$$$$$$$$$$$.    $$$$$$$$
$JT&yd$     $$$$$$$$$$$$$$$$.    $    $$    $   .$$$$$$$$$$$$$$$$     $by&TL$
                                 $    $$    $
                                 $.   $$   .$
                                 `$        $'
                                  `$$$$$$$$'
"""

STARTING_TESTS = """
===============================================================
===============================================================
      _             _   _               _            _       
     | |           | | (_)             | |          | |      
  ___| |_ __ _ _ __| |_ _ _ __   __ _  | |_ ___  ___| |_ ___ 
 / __| __/ _` | '__| __| | '_ \ / _` | | __/ _ \/ __| __/ __|
 \__ \ || (_| | |  | |_| | | | | (_| | | ||  __/\__ \ |_\__ \

 |___/\__\__,_|_|   \__|_|_| |_|\__, |  \__\___||___/\__|___/
                                 __/ |                       
                                |___/                        
                                               
===============================================================
===============================================================
"""

PATH_TO_USER_FILES = path.join("tests", "user")

PATH_TO_IN_FILES = path.join("tests", "in")

SCHOOL_PATH = path.join("tests", "school")

TESTS_PATH = path.join("tests")

ERR_MOVED_FILES = "Test files were moved \n\t Could not find 'queue.c' or 'queue.h', have your removed them from the test files?"

QUEUE_H_PATH = path.join("YourFilesHere", "queue.h")

QUEUE_C_PATH = path.join("YourFilesHere", "queue.c")

TREE_ANALYZER_PATH = path.join("YourFilesHere", "TreeAnalyzer.c")

ERR_DID_NOT_EXTRACT = "Your c file did not extract properly. \n\t make sure the tar file is well made"

ERR_NO_TAR_FILE = "Could not find tar file. did you name it correctly? should be name 'c_ex2.tar' and should be in 'YourFilesHere' directory"

MSG_TOO_MANY_COMPRESSED = "Tar file should only include 'TreeAnalyzer.c'"

version = 1.0

PATH_TO_TAR_FILE = path.join("YourFilesHere", "c_ex2.tar")


def error_occurred(message):
    stderr.write("ERROR: ")
    stderr.write(message)
    input("\nCould not run tests. Press ENTER to exit.")
    exit(1)


def run_cmd_command(arguments_list):
    """
    runs the given command through the command line and returns information
    about the command.
    :param arguments_list: a list representing the command to run
    :return: A tuple containing the returncode, the output of the command and
    all the errors.
    """
    process = subprocess.Popen(arguments_list, stdin=subprocess.PIPE,
                               stdout=subprocess.PIPE, stderr=subprocess.PIPE,
                               universal_newlines=True)
    output, errors = process.communicate()
    return process.returncode, output, errors


def extract_tar():
    try:
        tar = tarfile.open(PATH_TO_TAR_FILE)
        names = tar.getnames()
        if len(names) != 1:
            tar.close()
            error_occurred(MSG_TOO_MANY_COMPRESSED)
        for name in names:
            if name != "TreeAnalyzer.c":
                tar.close()
                error_occurred(MSG_TOO_MANY_COMPRESSED)
        tar.extractall(path="YourFilesHere")
        tar.close()
    except FileNotFoundError:
        error_occurred(ERR_NO_TAR_FILE)
    print("tar extracted successfully!")


def compile_files():
    if not exists(TREE_ANALYZER_PATH):
        error_occurred(ERR_DID_NOT_EXTRACT)
    if not exists(QUEUE_C_PATH) or not exists(QUEUE_H_PATH):
        error_occurred(ERR_MOVED_FILES)
    compile_command = ["gcc", "-Wextra", "-Wall", "-Wvla", "-lm",
                       "YourFilesHere/TreeAnalyzer.c",
                       "YourFilesHere/queue.c", "YourFilesHere/queue.h", "-o",
                       "TreeAnalyzer"]
    rc, out, err = run_cmd_command(compile_command)
    if rc != 0:
        error_occurred(
            "=======\n" + err + "\n=======" + "\nCould not compile file! error listed above.")
    print("compiled successfully!")


def run_single_test(test_type, test_file_name):
    path_to_in_file = path.join(PATH_TO_IN_FILES, "test_" + test_type,
                                path.join(test_file_name,
                                          test_file_name + ".txt"))

    path_to_in_numbers = path.join(PATH_TO_IN_FILES, "test_" + test_type,
                                   test_file_name, "numbers.txt")

    path_to_school_solution = path.join(SCHOOL_PATH, "test_" + test_type,
                                        test_file_name + ".txt")
    path_to_school_errors = path.join(SCHOOL_PATH, "errors_" + test_type,
                                      test_file_name + ".txt")

    path_to_user_out = path.join(PATH_TO_USER_FILES, "test_" + test_type,
                                 test_file_name + ".txt")
    path_to_user_err = path.join(PATH_TO_USER_FILES, "errors_" + test_type,
                                 test_file_name + ".txt")

    if test_file_name == "no_arguments":
        test_command = ["TreeAnalyzer"]
    else:
        with open(path_to_in_numbers, 'r') as f:
            first_num = f.readline().strip()
            second_num = f.readline().strip()
            f.close()
        test_command = ["TreeAnalyzer", path_to_in_file, first_num,
                        second_num]

        if not first_num.strip():
            test_command = ["TreeAnalyzer", path_to_in_file, second_num]
        elif not second_num.strip():
            test_command = ["TreeAnalyzer", path_to_in_file, first_num]

    rc, out, err = run_cmd_command(test_command)

    with open(path_to_user_out, 'w') as fout:
        fout.write(str(out))

    with open(path_to_user_err, 'w') as ferr:
        ferr.write(str(err))

    # if rc != 0:
    #     error_occurred("while running tests on '" + test_file_name + "' the tester crushed. \n\t please send me a message at the forum so i can fix it!")

    compared_outputs = compare_files(path_to_user_out,
                                     path_to_school_solution)
    compared_errors = compare_files(path_to_user_err, path_to_school_errors)

    if compared_outputs is not None or compared_errors is not None:
        if compared_outputs is not None:
            print_with_indentation("Failed Output Compare, difference was:",
                                   compared_outputs)
        if compared_errors is not None:
            print_with_indentation("Failed Errors compare, difference was:",
                                   compared_errors)
        return False
    print("Test passed!")
    return True


def print_with_indentation(title, to_print):
    """print text in a nice way"""
    print(START_EXPLAINER)
    print(DIFFERENCES_EXPLAINER)
    print(END_EXPLAINER)
    prefix = title + ": "
    wrapper = textwrap.TextWrapper(initial_indent=prefix,
                                   break_long_words=False,
                                   subsequent_indent=' ' * len(prefix))
    print(wrapper.fill(to_print))


def compare_files(file1, file2):
    """
    compare to files with FC (windows file comparer)
    :param file1:
    :param file2:
    :return: the compaction text if there was errors
    """

    with open(file1)as f1:
        first = f1.readlines()
    with open(file2) as f2:
        second = f2.readlines()

    d = Differ()
    diff = d.compare(first, second)
    compared = '\n'.join(diff)
    if '-' in compared or '+' in compared or '?' in compared:
        return compared
    # if platform == "linux" or platform == "linux2":
    #     command_to_compare = ['diff', file1, file2]  # only linux
    # else:
    #     command_to_compare = ['fc', '/N', '/W', file1, file2]  # only windows
    # code, output, errors = run_cmd_command(command_to_compare)
    # if code != 0:  # if code != 0
    #     return output
    # return None


def run_all_static_tests():
    passed_tests_amount = 0
    passed_all = True
    all_tests = listdir(path.join(PATH_TO_IN_FILES, "test_static"))
    tests_amount = len(all_tests)
    failed_tests_list = []
    print(STARTING_TESTS)
    for i, test in enumerate(all_tests):
        print("==============================")
        print("Starting static test number " + str(i + 1))
        print("TYPE: static test on file '" + test + ".txt' ... ")
        print("----------------------")
        if run_single_test("static", test):
            passed_tests_amount += 1
        else:
            failed_tests_list.append(i)
            print(FAILED_TEST)
            passed_all = False
    if passed_all:
        print(SUCCESS_BABY)
        return True
    else:
        print(SOME_TESTS_FAILED)
        print("passed " + str(
            passed_tests_amount) + " static tests out of " + str(
            tests_amount))
        print("FAILED TESTS WERE: ")
        for test_index in failed_tests_list:
            print(str(test_index + 1) + ", ", end="")
        print()
        return False


if __name__ == '__main__':
    if __name__ == "__main__":
        while True:
            print("starting tester for ex2 version", version, '\n')
            # extract_tar()
            compile_files()
            tests_passed = run_all_static_tests()

            if tests_passed:
                input("Press Enter to quit the tester")
                exit(0)
            else:
                ans = input("write r to restart the tester OR any other key to quit")
                if ans == "r":
                    print('\n\n\nRestarting...')
                else:
                    exit(0)

