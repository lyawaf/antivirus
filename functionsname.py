#! /usr/bin/env python
# -*- coding: utf-8 -*-
import subprocess
import re
from subprocess import Popen, PIPE

class NameAdress(object):
    def __init__(self, name=None,  adress=None):
        self.name = name
        self.adress = adress
    def show(self):
        print self.name, " ", self.adress

class Funtcions(object):
    def __init__(self, name=None,  adress=None):
        self.name = name
        self.adress = adress
    def show(self):
        print self.name, " ", self.adress

def start():
    p = Popen(['objdump', '-x', 'nlbig'], stdin=PIPE, stdout=PIPE, stderr=PIPE)
    output, err = p.communicate(b"input data that is passed to subprocess' stdin")
    
    lines = output.split('\n')
    n = 0
    for line in lines:
        #print line
        n = n + 1
    #print n

    a = "Sections:"
    i = 0
    for line in lines:
        if a in line:
            sect = i # sect - номер секции Sections:
            break
        i = i + 1
    #print sect

    i=0
    b = "SYMBOL TABLE:"
    for line in lines:
        if b in line:
            symb = i # symb - номер секции SYMBOL TABLE:
        i = i + 1
    #print symb

    name = []
    adress = []

    for i in range(sect + 2, symb, 2):#symb
        #print lines[i]
        words = lines[i].split(' ')


        j=0
        index = []
        for word in words:
            if word.strip():
                #print j, " ", word, "nostrip"
                index.append(j)
            j = j+1
        #print index

        index.reverse()
        index.pop()
        a=index.pop()
        #print a
        name.append(words[a])

        index.pop()
        b=index.pop()
        #print b
        adress.append(words[b])
    #print name, adress, "\n"

    neednumber=0
    i=0
    c = "*ABS*"
    for line in lines:
        if c in line:
            abs = i # abs - номер секции SYMBOL TABLE:
        i = i + 1
    #print abs

    functions = []
    f_adress = []
#print abs, n
    for i in range(abs, n-3):#n-3
        #print lines[i]
        if lines[i].find("*ABS*") != -1:
            #print "fuck ABS"
            continue
        if lines[i].find("*UND*") != -1:
            #print "fuck UND"
            continue
        words = lines[i].split(' ')
        trash = []
        for word in words:
            trash.append(word)
            if word.find(".") != -1:
                word = re.sub(r"\d+", "", word, flags=re.UNICODE)
                k = 0
                for names in name:
                    if names == word:
                        neednumber = k
                    #print k
                    k = k+1
        functions.append(trash.pop())
        trash.reverse()
        a=trash.pop()
        a=int(a,16)-int(adress[neednumber],16)
        f_adress.append(a)

    print f_adress, functions

start()


