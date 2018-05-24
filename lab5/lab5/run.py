import subprocess



print "Starting run ...\n"


subprocess.call(["make", "all"])

for i in range(1,121,1):
    subprocess.call(["./main", str(i)])

print "Finished. Cleaning up ...\n"    
subprocess.call(["make", "clean"])