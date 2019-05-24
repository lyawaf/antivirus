import binwalk
import re
# save directory /_filename.extracted with all elf, mach-o, pe extracted files to /dirpath

def select_executable(filepath, dirpath):
#req = re.compile(r'\b(ELF)|(Mach-O)|(PE)\b', flags=re.IGNORECASE)
    try:
        binwalk.scan(filepath, quiet=True,
                               signature=True,
                               extract=True,
                               matryoshka=True,
                               directory=dirpath,
                               dd='\b{0,1}(elf)|(mach-o)|(pe)\b')

    except binwalk.ModuleException as e:
        print("Critical failure:", e)

select_executable("hello/new2.jpg","hello")

