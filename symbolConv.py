# Symbol converter for Base modules

import sys

if(len(sys.argv) < 3):
    print("Not enough args!")
    exit(0)

file = sys.argv[1]
output = sys.argv[2]

print(f"Converting {file} to {output}")

with open(file, "r") as o:
    oLines = o.readlines()
    prog = len(oLines)
    count = 0
    with open(output, "w") as w:
        for line in oLines:
            print(f"Converting... {(count / prog) * 100}% done...")

            line = line.replace("\t", " ")
            stuff = line.split(' ')

            if(len(stuff) > 2):
                if(stuff[1] == 'g'):
                    addr = stuff[0]
                    size = stuff[8]
                    name = stuff[9]
                    w.write(f"{addr} {size} {name}")

            count += 1
        pass
print("")