#! /usr/bin/env python3
import subprocess
from invoke_exceptions import *

def invoke(filename, function_addresses):
    input_addresses = [str(address) for address in function_addresses]

    command = ['./CCPTool/main', filename]

    try:
        process = subprocess.run(command + input_addresses, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    except Exception as exc:
        NoMainException(exc)
        print (exc)
        return

    output = process.stdout.decode()
    errors = process.stderr.decode()

    if errors != '':
        raise BadData(errors)
        return

    return (output, errors)
