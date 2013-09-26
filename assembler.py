#!/usr/bin/env python2

import sys
import binascii

filename = sys.argv[1]
fileobj = open(filename, 'r')
code = fileobj.read()
instructions = []
lines = []
for y in code.split("\n"):
    lines.append(y)
for y in lines:
    for new in y.split(" "):
        instructions.append(new)
print instructions
for x in instructions:
    x.strip("\n")

bytelist = ["00"]

x = 0
print bytelist
while x < len(instructions):
    instr = instructions[x]
    if instr.lower() == "mov":
        bytelist.append('00')
        bytelist.append("%0.2X" %int(instructions[x +1]))
        x = x + 1
    elif instr.lower() == "bac":
        bytelist.append('01')
        bytelist.append("%0.2X" %int(instructions[x +1]))
        x = x + 1
    elif instr.lower() == "add":
        bytelist.append('02')
        bytelist.append("%0.2X" %int(instructions[x +1]))
        x = x + 1
    elif instr.lower() == "sub":
        bytelist.append('03')
        bytelist.append("%0.2X" %int(instructions[x +1]))
        x = x + 1
    elif instr.lower() == "prt":
        bytelist.append('04')
    elif instr.lower() == "get":
        bytelist.append('05')
    elif instr.lower() == "loop":
        bytelist.append('06')
    elif instr.lower() == "endl":
        bytelist.append('07')
    x = x + 1

print bytelist

output = sys.argv[2]
output_file = open(output, 'wb')

bytes = binascii.a2b_hex(''.join(bytelist))
output_file.write(bytes)













