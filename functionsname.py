#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import sys
from errors import *
from subprocess import Popen, PIPE

def get_functions_addresses(filename):
    try:
        process = Popen(['objdump', '-x', filename], stdout=PIPE, stderr=PIPE)
    except Exception as exc:
        raise ObjdumpFailure(exc)

    output, err = process.communicate()
    
    lines = output.decode('utf8').split('\n')

    try:
        section_index = lines.index('Sections:')
    except Exception as exc:
        raise NoSectionError('There is not section with adresses')
    
    try:
        symbols_index = lines.index('SYMBOL TABLE:')
    except Exception as exc:
        raise NoSectionError('No SYMBOL TABLE section')

    text_literal = '.text'

    for line in lines[section_index + 2 : symbols_index : 2]:
        words = line.split()
        if words[1] == text_literal:
            text_section_address = words[3]
            break
    else:
        raise NoSectionError('No .text section')

    functions = []

    for line in lines[symbols_index + 1 : -3]:
        if line.find(text_literal) != -1:
            words = line.split(' ')
            function_address = int(words[0], 16) - int(text_section_address, 16)
            functions.append((words[-1], function_address))

    return functions

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print('Usage: {} file'.format(sys.argv[0]))
        sys.exit(1)
    functions = get_functions_addresses(sys.argv[1])
    print(functions)

