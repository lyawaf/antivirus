#! /usr/bin/env python3
import subprocess
from invoke_exceptions import *

def parse(output):
    result = output.split("\n")

    for strings in result:
        if strings.find("virus") != -1:
            print ("!!! VIRUS !!!")
            return
    print("NOT VIRUS")

def invoke(filename, function_addresses):
    input_addresses = [str(address) for address in function_addresses]

    command = ['./CCPTool/main', filename]

    try:
        process = subprocess.run(command + input_addresses, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    except Exception as exc:
        NoMainException(exc)
        print(exc)
        return

    output = process.stdout.decode()
    errors = process.stderr.decode()

    if errors != '':
        raise BadData(errors)

    parse(output)

    return (output)
