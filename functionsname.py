#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import re
from subprocess import Popen, PIPE

def start(filename):
    p = Popen(['objdump', '-x', filename], stdout=PIPE, stderr=PIPE)
    output, err = p.communicate()
    
    lines = output.decode('utf8').split('\n')
    
    n = len(lines)

    sect=lines.index("Sections:")
    symb=lines.index("SYMBOL TABLE:")

    name = ".text"

    for i in range(sect + 2, symb, 2):
        words = lines[i].split(' ')
        j=0
        index = []
        for word in words:
            if word.strip():
                index.append(j)
            j = j+1
        if words[index[1]]==name:
            adress=words[index[3]]

    i=0
    for line in lines:
        if "*ABS*" in line:
            abs = i # abs - номер секции *ABS* в SYMBOL TABLE, отсюда начинаем разбирать функции:
        i = i + 1

    funcnames = []
    funcadress = []

    for i in range(abs, n-3):
        if lines[i].find(name) != -1:
            words = lines[i].split(' ')
            for word in words:
                lastworld = word
            funcnames.append(lastworld)
            funcadress.append(int(words[0],16)-int(adress,16))

    print (funcadress, funcnames)

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: {} file".format(sys.argv[0]))
        sys.exit(1)
    start(sys.argv[1])

