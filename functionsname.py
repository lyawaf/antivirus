#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import re
import sys
from subprocess import Popen, PIPE

def start(filename):
    p = Popen(['objdump', '-x', filename], stdout=PIPE, stderr=PIPE)
    output, err = p.communicate()
    
    lines = output.decode('utf8').split('\n')

    section_index = lines.index("Sections:")
    symbols_index = lines.index("SYMBOL TABLE:")

    text_literal = ".text"

    for i in range(section_index + 2, symbols_index, 2):
        words = lines[i].split()
        if words[1] == text_literal:
            text_section_address = words[3]

    functions = []

    for i in range(symbols_index + 1, len(lines) - 3):
        if lines[i].find(text_literal) != -1:
            words = lines[i].split(' ')
            function_address = int(words[0], 16) - int(text_section_address, 16)
            functions.append((words[-1], function_address))

    return (functions)

if __name__ == "__main__":
   
    if len(sys.argv) < 2:
        print("Usage: {} file".format(sys.argv[0]))
        sys.exit(1)
    functions = start(sys.argv[1])
    print (functions)

