#!/usr/bin/python

# make-header file_name [path] [--benchmark | -b]
# Creates a header and test file, and optionally a benchmark file.
# header is created in current directory or in provided relative/absolute path.
# Path must exist already.
# test created under tests/ in project directory.
# benchmark created under benchmarks/ in project directory.
# Creates a private header if called from under the src/ tree.
# Creates a public header if called from under the include/ tree.

import sys

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

def driver():
    if len(sys.argv) < 2:
        print(bcolors.FAIL + "Error:" + bcolors.ENDC + " Provide file stem as"
                + " argument.")
        return
    # Change this to parse actual arguments
    make_header()
    if len(sys.argv) == 2:
        make_source()
    return

# Haven't modified this yet.
def make_header():
    class_name = sys.argv[1]
    is_template = False
    template_args = ''
    if len(sys.argv) > 3 and sys.argv[2] == '-t':
        is_template = True
        template_args = sys.argv[3:]
     
    header = open(class_name.lower() + ".hpp", "w")
    define = class_name.upper() + "_HPP"
    header_contents = (
            r'#ifndef ' + define + '\n'
            r'#define ' + define + '\n\n'
            )

    if is_template:
        header_contents += 'template <'
        for param in template_args:
            header_contents += 'typename ' + param + ', '
        header_contents = header_contents[:-2]
        header_contents += '>\n'

    header_contents += (
            r'class ' + class_name + ' {\n'
            r'   public:''\n\t\n'
            r'   private:''\n\t\n'
            r'};''\n\n'
            r'#endif''\t'r'// ' + define
            )

    header.write(header_contents)
    header.close()
    return
