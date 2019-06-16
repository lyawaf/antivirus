# -*- coding: utf-8 -*-
import subprocess
import re
from subprocess import Popen, PIPE

def start(filename):
    p = Popen(['objdump', '-x', filename], stdout=PIPE, stderr=PIPE)
    output, err = p.communicate(b"input data that is passed to subprocess' stdin")
    
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

    functions = []
    f_adress = []

    for i in range(abs, n-3):
        if lines[i].find(name) != -1:
            words = lines[i].split(' ')
            trash = []
            for word in words:
                trash.append(word)
                if word.find(".") != -1:
                    word = re.sub(r"\d+", "", word, flags=re.UNICODE)
            functions.append(trash.pop())
            f_adress.append(int(words[0],16)-int(adress,16))

    print (f_adress, functions)

if __name__ == "__main__":
    filename="nlbig"
    start(filename)


