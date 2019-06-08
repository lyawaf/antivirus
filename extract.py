#!/usr/bin/env python3

# Dig for elf, mach-o, pe extracted files and if exists save it to /dirpath/_filename.extracted/
# May throw only binwalk.ModuleException exceptions

import binwalk

def extract(filepath, dirpath):
    binwalk.scan('-D', 'elf::',
                 '-D', 'microsoft executable:exe:',
                 '-D', 'mach-o:o:',
                 filepath, quiet=True,
                           signature=True,
                           extract=True,
                           matryoshka=True,
                           directory=dirpath)

