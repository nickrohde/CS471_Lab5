import subprocess
import os


var = "-1"

if not os.path.isfile("main"):
	subprocess.call(["make", "all"])
if not os.path.isfile("main"):
	print "Make failed! Terminating ..."
	subprocess.call(["make", "clean"])
	sys.exit()


while var != "Q" and var != "q":
	while var != "1" and var != "2" and var != "Q" and var != "q":
		print "Pleas enter choice: "
		print "1: Run all"
		print "2: Run specific"
		print "Q: Quit"

		try:
			var = raw_input("Choice: ")
		except:
			print "Please enter 1, 2, or Q/q."
			var = "-1"

	if var == "1":
		var = "-1"
		print "Starting run ...\n"

		for i in range(1,121,1):
			subprocess.call(["./main", str(i)])

	elif var == "2":
		var = "-1"
		var2 = -1
		while not (var2 >= 1 and var2 <= 120):
			print "Which problem? (1-120): "
			try:
				var2 = input("Choice: ")
			except:
				print "Please enter an integer in the range [1,120]."
				var2 = -1

		print "Starting run ...\n"		
		subprocess.call(["./main", str(var2)])

print "Cleaning up ...\n"    

subprocess.call(["make", "clean"])

print "Finished."
