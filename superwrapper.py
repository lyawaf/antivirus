#!/usr/bin/env python3

from extract import extract
from functionsname import get_functions_addresses
from invoke_layer import invoke
from os import listdir
from os.path import isfile, join

def scan_file(filename):
    functions_addresses = get_functions_addresses(filename)
    return (filename, invoke(filename, [addrs for (name, addrs) in functions_addresses]))

def scan(filepath, dirpath):
    extract(filepath, dirpath)
    extracted_dirpath = filepath + '.extracted'
    files = [join(extracted_dirpath, f) for f in listdir(extracted_dirpath) if isfile(join(extracted_dirpath, f))]
    return list(map(scan_file, files))


if __name__ == '__main__':
    scan('elf_32_simple.bin', './CCPTool/tests')
