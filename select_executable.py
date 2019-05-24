import binwalk
# save directory /_filename.extracted with all elf, mach-o, pe extracted files to /dirpath

def select_executable(filepath, dirpath):
    try:
        binwalk.scan(filepath, quiet=True,
                               signature=True,
                               extract=True,
                               matryoshka=True,
                               directory=dirpath,
                               dd='[(,\b{0,1}](elf)|(mach-o)|(pe)[\b,)]')

    except binwalk.ModuleException as e:
        print("Critical failure:", e)

