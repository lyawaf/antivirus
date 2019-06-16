import subprocess

def invoke(filename, function_addresses):
    input_addresses = [str(address) for address in function_addresses]

    command = ['./main', filename]
    process = subprocess.run(command + input_addresses, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    output = process.stdout.decode()
    errors = process.stderr.decode()
    return(output,errors)
