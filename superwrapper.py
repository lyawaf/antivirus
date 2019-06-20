#!/usr/bin/env python3

from extract import extract
from functionsname import get_functions_addresses
from invoke_layer import invoke
from os import listdir
from os.path import isfile, join

def scan_file(filename, log):
    log('Scanning {}'.format(filename))
    try:
        functions_addresses = [addrs for (name, addrs) in get_functions_addresses(filename)]
        log('Found {} functions in file'.format(len(functions_addresses)))
        is_dangerous = invoke(filename, functions_addresses)
        return (filename, is_dangerous)
    except Exception as exc:
        return (filename, True)

def scan(filepath, dirpath, log):
    extract(filepath, dirpath)
    extracted_dirpath = dirpath + '/_' + filepath.split('/')[-1] + '.extracted'
    files = listdir(extracted_dirpath)
    binary_files = [join(extracted_dirpath, f) for f in files if isfile(join(extracted_dirpath, f))]
    log('Found {} embedded files in {}'.format(len(binary_files), filepath))

    return [scan_file(f, log) for f in binary_files]


if __name__ == '__main__':
    print(scan('elf_32_simple.bin', './CCPTool/tests', print))
