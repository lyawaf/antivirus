import binwalk
# dig for elf, mach-o, pe extracted files and if exists save it to /dirpath/_filename.extracted/

def extract(filepath, dirpath):
    binwalk.scan('-D', 'elf::',
                 '-D', 'microsoft executable:exe:',
                 '-D', 'mach-o:o:',
                 filepath, quiet=True,
                           signature=True,
                           extract=True,
                           matryoshka=True,
                           directory=dirpath)

