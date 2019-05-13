Simple calling convention determiner
==================================

## What is it?

CCPtool is an instrument used to determine calling conventions of c-like
functions in binary files. It's simple to use and simple to embed as a part
chain of commands or as a part of other code.

## Requirements

Capstone version >= 3.0.1

gcc version >= 4.8.5 supporting -std=c++1y

## Installation

    cd CCPtool && make && make install

## Usage

Run ```CCPtool --help``` to get internal help.

CCPtool uses virtual addresses of functions provided to it to seek to
functions in file to analyse.

    CCPtool filename vaddr1 [vaddr2, ...]

For each address supplied it will print to stdout a line containing a word
standing for the function's calling convention type.
