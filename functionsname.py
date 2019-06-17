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

    text_section_literal = ".text"

    for i in range(section_index + 2, symbols_index, 2):
        words = lines[i].split(' ')
        j = 0
        index = []
        for word in words:
            if word.strip():
                index.append(j)
            j = j + 1
        if words[index[1]] == text_section_literal:
            text_section_address = words[index[3]]

    functions_names = []
    functions_address = []

    for i in range(symbols_index + 1, len(lines) - 3):
        if lines[i].find(text_section_literal) != -1:
            words = lines[i].split(' ')
            for word in words:
                last_world = word
            functions_names.append(last_world)
            functions_address.append(int(words[0], 16) - int(text_section_address, 16))

    print (functions_address, functions_names)

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: {} file".format(sys.argv[0]))
        sys.exit(1)
    start(sys.argv[1])
    
