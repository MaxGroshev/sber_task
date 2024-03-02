import subprocess
import argparse
import os
import sys
from   subprocess import Popen, PIPE, STDOUT

# -----------------------------------------------------------------------------------------

class TERMINAL_COLORS:
        PURPLE    = '\033[95m'
        OKBLUE    = '\033[94m'
        OKCYAN    = '\033[96m'
        OKGREEN   = '\033[92m'
        YELLOW    = '\033[33m'
        BLUE      = '\033[36m'
        GREEN     = '\033[32m'

        WARNING   = '\033[93m'
        ERROR     = '\033[91m'
        RED       = '\033[91m'
        DEFAULT   = '\033[0m'
        BOLD      = '\033[1m'
        UNDERLINE = '\033[4m'

test_dir = os.path.dirname(os.path.abspath(__file__)) + "/my_test_dat/"
test_data = {
    (test_dir + "1.dat") :  [42, 420],
    (test_dir + "2.dat") :  [69],
    (test_dir + "3.dat") :  [1, 2, 4],
    (test_dir + "4.dat") :  [336, 1, 0],
    (test_dir + "8.dat") :  [9, 8, 7, 6, 5, 5],
    (test_dir + "9.dat") :  [2, 3],
    (test_dir + "10.dat") : [0],
    (test_dir + "11.dat") : [5, 25],
    (test_dir + "12.dat") : [11],
    (test_dir + "15.dat") : [42],
    (test_dir + "16.dat") : [],
    (test_dir + "101.dat") : [5, 4, 3, 2],
    (test_dir + "107.dat") : [1],
    (test_dir + "108.dat") : [42, 12],
    (test_dir + "109.dat") : [2, 4, 0],
    (test_dir + "110.dat") : [0],
    (test_dir + "factorial.dat") : [3628800],
    (test_dir + "fibonacci.dat") : [55],
}

data_files_names = []

# -----------------------------------------------------------------------------------------

def check_output_data(n_of_test, stdout_data, correct_res, name_of_testing_prog):
    try:
        if stdout_data == correct_res:
            print(TERMINAL_COLORS.GREEN            + \
                f"Test {n_of_test} IS PASSED:\n"   + \
                f"Prog output = {stdout_data}"     + \
            TERMINAL_COLORS.DEFAULT
            )
            print('—————————————————————————END_OF_TEST————————————————————————\n\n')
            return True
        else:
            print(TERMINAL_COLORS.ERROR            + \
                f"Test {n_of_test} IS FAILED:\n"   + \
                f"Prog output   = {stdout_data}\n" + \
                f"Expected      = {correct_res}"   + \
            TERMINAL_COLORS.DEFAULT
            )
            print('————————————————————————END_OF_TEST—————————————————————————\n\n')
            return False
    except:
        print(TERMINAL_COLORS.WARNING                   + \
            f"Test {n_of_test} fall. Prog output:\n"    + \
            stdout_data + "'"                           + \
        TERMINAL_COLORS.DEFAULT
        )
        return False



def show_total_test_stat(n_of_test, passed_test):
    print('===========TOTAL==============')
    print(TERMINAL_COLORS.OKBLUE                          + \
            f"Total num of tests = {n_of_test + 1}\n"+ \
            f"Num of passed      = {passed_test}"         + \
    TERMINAL_COLORS.DEFAULT
    )
    print('==============================')

# -----------------------------------------------------------------------------------------

def parse_test_data(test_case):
    with open(test_case) as dat_file:
        correct_res = 0
        res_is_reached = False
        data = ""
        for item in dat_file:
            data = item

    start = data.find('(')
    end   = data.find(')')

    try:
        correct_res = data[start + 1:end]
        data = data[start + 1:end]
    except:
        correct_res = 0

    correct_numbers = ''.join(c if c.isdigit() else ' ' for c in correct_res).split()
    return correct_numbers

# -----------------------------------------------------------------------------------------

def run_test(name_of_testing_prog, test_case):
    pipe = Popen([name_of_testing_prog, test_case], stdout = PIPE)

    stdout_data = (pipe.communicate())
    string_data = (stdout_data[0].decode())
    conver_output = string_data.split()

    conver_output = [int(n) for n in conver_output]

    return conver_output


def run_test_data(name_of_testing_prog, test_dat):
    n_of_elems_in_range = 0

    passed_test = 0
    n_of_test   = 0
    for (test_case, n_of_test) in zip(test_dat, range(len(test_dat))):
        print('————————————————————————START_OF_TEST———————————————————————')
        n_of_trians = run_test(name_of_testing_prog, test_case)
        if (check_output_data(n_of_test + 1, n_of_trians, test_dat[test_case], name_of_testing_prog)):
            passed_test += 1
    show_total_test_stat(n_of_test, passed_test)


# -----------------------------------------------------------------------------------------

if __name__ == "__main__":
    run_test_data("./compiler", test_data)
