import sys, os, re

if len(sys.argv) < 2:
    print ("Usage:", sys.argv[0], "<ORTI file name>")
    exit(1)
print ("Adding crosscore ISR to", sys.argv[1], "...")

orti_path = os.path.splitext(sys.argv[1])
orti_src  = open(sys.argv[1], 'r')
orti_dest_name = orti_path[0] + "_ccisr" + orti_path[1]
orti_dest = open(orti_dest_name, 'w')

line = orti_src.readline()
while line:
    if (('"NO_ISR"' in line) and (line.rstrip()[-1] != ",")):
        indent = line[0:re.search("\S", line).start()]
        orti_dest.write (line.rstrip() + ",\n")
        orti_dest.write (indent + '"CROSSCORE_ISR" = "1"\n')
    else:
        orti_dest.write (line)
    line = orti_src.readline()

orti_src.close()
orti_dest.close()
print ("Generated", orti_dest_name, ".")
