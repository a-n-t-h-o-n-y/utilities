#!/usr/bin/python
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

def make_class():
    if len(sys.argv) == 1:
        print(bcolors.FAIL + "Error:" + bcolors.ENDC + " Provide class name as"
                + " argument.")
        return
    make_header()
    if len(sys.argv) == 2:
        make_source()
    return

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

def make_source():
    class_name = sys.argv[1]
    source_file = open(class_name.lower() + '.cpp', "w")
    source_contents = (
            r'#include "' + class_name.lower() + '.hpp"'
            )
    source_file.write(source_contents)
    source_file.close()
    return

if __name__ == '__main__':
    make_class()
