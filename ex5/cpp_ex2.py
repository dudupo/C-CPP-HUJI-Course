#########################################
############ TEST CPP - EX2 #############
#########################################
# If you found a bug in the test you can always send an email to me:
# amit.david@mail.huji.ac.il
#
# HOW TO RUN
# 1) Place all of the project files in './in' folder
# 2) Run in terminal using 'python3 cpp_ex.2' or 'python3 cpp_ex.2 --no-valgrind'
# 3) Results will be shown in terminal
#
# All .cmp file generated from school solution
#########################################
import difflib
import os
import subprocess

import sys

PYTHON_VER = f"If you see this error message, you are using python 2.x instead of 3.7"

PROGRAM_NAME = "FractalDrawer"

# If you want to force using valgrind change this to variable to True
USE_VALGRIND = sys.platform.startswith("linux")

USE_SCHOOL_SOLUTION = False

# File types
IN = "in"
CSV = "csv"
OUT = "out"
CMP = "cmp"
VAL = "val"

INVALID_ARGS = ['',
                'csv/valid-carpet1.csv csv/valid-carpet1.csv',
                'csv/valid-carpet1.csv csv/valid-carpet1.csv csv/valid-carpet1.csv'
                ]

total = 0
counter = 0


#########################################

def convert_file_name(name, loc):
    return f"{loc}/{name}.{loc}"


def cmp_files(cmp_file, out_file):
    global counter
    global total
    total += 1

    with open(cmp_file, 'r') as fCmp:
        with open(out_file, 'r') as fOut:
            diff = difflib.ndiff(fOut.readlines(), fCmp.readlines())

            for i, line in enumerate(diff):
                if line.startswith("- ") or line.startswith("+ ") or line.startswith("? "):
                    print("\tOutput test - FAIL")
                    print("\tDifference found in '" + out_file + "' at line " + str(i))
                    return

    counter += 1
    print("\tOutput test - PASS")


def check_valgrind_file(val_file):
    global counter
    global total
    total += 1

    check_lines = -1

    with open(val_file, 'r') as fVal:
        for line in fVal.readlines():
            if "LEAK SUMMARY:" in line:
                check_lines = 0

            elif 0 <= check_lines < 3:
                check_lines += 1
                if ": 0 bytes in 0 blocks" not in line:
                    print("\tValgrind test - FAIL")
                    print("\tMemory leak found, more info in '" + val_file + "'\n")
                    return

            if "ERROR SUMMARY:" in line and "ERROR SUMMARY: 0 errors from" not in line:
                print("\tValgrind test - FAIL")
                print("\tError found, more info in '" + val_file + "'")
                return

    counter += 1
    print("\tValgrind test - PASS")


def t_valid(file_name):
    csv_file = os.path.abspath(convert_file_name(file_name, CSV))
    out_file = convert_file_name(file_name, OUT)
    cmp_file = convert_file_name(file_name, CMP)
    val_file = convert_file_name(file_name, VAL)

    with open(out_file, 'w') as fOut:
        try:
            if USE_SCHOOL_SOLUTION:
                program = f'~labcc/www/cpp_ex2/school_solution/FractalDrawer "{csv_file}"'

            elif USE_VALGRIND:
                program = f'valgrind --leak-check=full --log-file={val_file} in/{PROGRAM_NAME} "{csv_file}"'

            else:
                program = f'in/{PROGRAM_NAME} "{csv_file}"'

            subprocess.run(program, stdout=fOut, stderr=subprocess.STDOUT, shell=True, timeout=5)

        except subprocess.TimeoutExpired:
            print("\tTest - FAIL")
            print("\tTIMEOUT Reached")
            return

    cmp_files(cmp_file, out_file)
    if not USE_SCHOOL_SOLUTION and USE_VALGRIND:
        check_valgrind_file(val_file)


def t_invalid(file_name):
    global counter
    global total
    total += 1

    csv_file = os.path.abspath(convert_file_name(file_name, CSV))
    val_file = convert_file_name(file_name, VAL)

    try:
        if USE_SCHOOL_SOLUTION:
            program = f'~labcc/www/cpp_ex2/school_solution/FractalDrawer "{csv_file}"'

        elif USE_VALGRIND:
            program = f'valgrind --leak-check=full --log-file={val_file} in/{PROGRAM_NAME} "{csv_file}"'

        else:
            program = f'in/{PROGRAM_NAME} "{csv_file}"'

        return_code, line = subprocess.getstatusoutput(program)

        if line != "Invalid input" or return_code != 1:
            print("\tOutput test - FAIL")
            print("\tExpected: 'Invalid input' and exit code 1")
            print("\tGot: exit code " + str(return_code) + " and output:")
            print((line[:75] + '...') if len(line) > 75 else line)
        else:
            counter += 1
            print("\tOutput test - PASS")

    except subprocess.TimeoutExpired:
        print("\tTest - FAIL")
        print("\tTIMEOUT Reached")
        return

    if not USE_SCHOOL_SOLUTION and USE_VALGRIND:
        check_valgrind_file(val_file)


def t_invalid_args(args, i):
    global counter
    global total
    total += 1

    val_file = convert_file_name("args" + str(i), VAL)

    try:
        if USE_SCHOOL_SOLUTION:
            program = f'~labcc/www/cpp_ex2/school_solution/FractalDrawer {args}'

        elif USE_VALGRIND:
            program = f'valgrind --leak-check=full --log-file={val_file} in/{PROGRAM_NAME} {args}'

        else:
            program = f'in/{PROGRAM_NAME} {args}'

        return_code, line = subprocess.getstatusoutput(program)

        if line != "Usage: FractalDrawer <file path>" or return_code != 1:
            print("\tOutput test - FAIL")
            print("\tExpected: 'Usage: FractalDrawer <file path>' and exit code 1")
            print("\tGot: exit code " + str(return_code) + " and output:")
            print((line[:75] + '...') if len(line) > 75 else line)
        else:
            counter += 1
            print("\tOutput test - PASS")

    except subprocess.TimeoutExpired:
        print("\tTest - FAIL")
        print("\tTIMEOUT Reached")
        return

    if not USE_SCHOOL_SOLUTION and USE_VALGRIND:
        check_valgrind_file(val_file)


#########################################
if __name__ == "__main__":
    if "--no-valgrind" in sys.argv:
        USE_VALGRIND = False

    print("\n------- COMPILATION START -------")

    gcc_program = "(cd in; make)"
    compiled = subprocess.run(gcc_program, text=True, shell=True)

    print("------- COMPILATION END - The section above should have no warnings nor errors -------")

    if compiled.returncode != 0:
        print("\nProgram failed compiling")
    else:
        print("\nProgram compiled successfully")

        print("\n------- TEST START -------")
        # Invalid args
        for i, arg in enumerate(INVALID_ARGS):
            print("Test args '" + arg + "':")
            t_invalid_args(arg, i)
            print()

        # Files in csv
        print()
        print("Test fileWhichDoesntExist:")
        t_invalid("fileWhichDoesntExist")
        print()
        for csv_file_name in sorted(os.listdir('./csv')):
            print("Test " + csv_file_name + ":")
            if csv_file_name.startswith('valid'):
                t_valid(csv_file_name[:-4])
            else:  # start with invalid
                t_invalid(csv_file_name[:-4])
            print()

        print("------- TEST END -------")
        print(f'\nTEST SUMMERY: Passed {counter} out of {total}')

        if counter == total:
            print("Good job! :)")
