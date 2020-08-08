#!/usr/bin/env python3.7
import sys
print(sys.argv)
numberOfArgs = len(sys.argv)
if numberOfArgs != 2:
    sys.stderr.write('Usage: %s inputFile\n' % sys.argv[0])
    sys.exit(1)
try:
    fh = open(sys.argv[1], 'r')
except:
    sys.stderr.write('Cannot open the file %s' % sys.argv[1])
    sys.exit(2)
for line in fh.readlines():
    print(line, end = '')
fh.close()
