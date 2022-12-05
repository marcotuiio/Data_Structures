import os
import subprocess
import time
import datetime

# BED = input("Path BED (pasta de testes do e-vandro):") 
BED = '/home/marcotuiio/Data_Structures/T4/inputs'

# BSD = input("Path de saída:")
BSD = '/home/marcotuiio/Data_Structures/T4/outputs'

# src = input("Path da pasta SRC:")
src = '/home/marcotuiio/Data_Structures/T4/src'


ini = datetime.datetime.now()

os.chdir(src)
subprocess.call(["make", "clear"])
subprocess.call(["make", "t2"])
print("\n")

geo = [] 
via = []
files = []
subdir = []
for (dirpath, dirnames, filenames) in os.walk(BED):
    #geo.extend(filenames)
    files.extend(filenames)
    subdir.extend(dirnames)
    break

geo = [ fi for fi in files if fi.endswith(".geo") ]
via = [ fi for fi in files if fi.endswith(".via") ]

subqry = []
for i in subdir:
    subsubqry = []
    for (dirpath, dirnames, filenames) in os.walk(BED + "/" + i):
        subsubqry.extend(filenames)
        subqry.append(subsubqry)
        break

geo.sort()
via.sort()
subdir.sort()

count = 0
for files_in_subqry in subqry:
    for j in files_in_subqry:
        # print(f"./t2 -e {BED} -o {BSD} -f {geo[count]} -v {via[count]} -q {subdir[count] + '/' + j}")
        # print("\n")
        subprocess.call(["./t2", "-e", BED, "-o", BSD, "-f", geo[count], "-v", via[count], "-q", subdir[count] + "/" + j])
        

    count += 1 


fin = datetime.datetime.now()

print(f"Tempo para rodar:\n{str(fin - ini)}")