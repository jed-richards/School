from sys import argv

if len(argv) < 3:
    print('Usage: python {argv[0]} target file1 file2 .. fileN')
    exit(1)

targetName = argv[1]
sourceNames = argv[2:]

for name in sourceNames:
    try:
        open(name)
    except FileNotFoundError:
        print(name + ' does not exist!')

with open(targetName, 'w') as outf:
    for name in sourceNames:
        with open(name, 'r') as inf:
            outf.write(inf.read())
