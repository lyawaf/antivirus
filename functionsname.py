#! /usr/bin/env python
# -*- coding: utf-8 -*-
import subprocess
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
    rc = p.returncode
    
    lines = output.split('\n')
    n = 0
    for line in lines:
        n = n + 1
    
    words = lines[15].split(' ')
    text = NameAdress(words[3],  words[14])
    text.show()

    words = lines[17].split(' ')
    data = NameAdress(words[3],  words[14])
    data.show()

    massiv = []
    i=29
    while i < n:
        words = lines[i].split(' ')
        func = Funtcions()
        if words[8][0:5] == text.name[0:5]:
            func.adress = int(words[0],16)-int(text.adress,16)
        elif words[8][0:5] == data.name[0:5]:
            func.adress = int(words[0],16)-int(data.adress,16)
        else:
            break
        func.name = words[9]
        massiv.append(func)
        i = i+1

    for i in range(len(massiv)):
            massiv[i].show()

start()


