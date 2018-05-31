import subprocess as proc
import os
import time
import sys
import configparser

printResults = 0
storeResults = 0
useThreads = 0
fileName = ""

def initialise():
	global printResults
	global storeResults
	global fileName
	global useThreads

	if os.name != 'posix':
		print"\nScript only for POSIX systems. Exiting."
		return False

	config = configparser.ConfigParser()
	config.read('config.ini')

	if 'Test' in config:
		if 'print' in config['Test']:
			printResults = config['Test']['print']
		else:
			print "\nRequired configuration key 'print' missing! Exiting ..."
			return False
		if 'use_threads' in config['Test']:
			useThreads = config['Test']['use_threads']
		else:
			print "\nRequired configuration key 'use_threads' missing! Exiting ..."
			return False

		if 'store' in config['Test']:
			storeResults = config['Test']['store']
			
			if storeResults == '1':
				if 'results_file_name' in config['Test']:
					fileName = config['Test']['results_file_name']
				else:
					print "\nRequired configuration key 'results_file_name' missing! Exiting ..."
					return False
			else:
				fileName = "none"
		else:
			print "\nRequired configuration key 'store' missing! Exiting ..."
			return False

		print "\nConfigurations parsed successfully!"
		if useThreads == '1':
			print "\tUse Threads: Yes"
		else:
			print "\tUse Threads: No"

		if printResults == '1':
			print "\tPrint Schedule: Yes"
		else:
			print "\tPrint Schedule: No"

		if storeResults == '1':
			print "\tStore Results: Yes"
			print "\tResults Filename: ", fileName, "\n"
		else:
			print "\tStore Results: No\n"
	else:
		print "\nRequired configuration group 'Test' missing! Exiting ..."
		return False

	if not os.path.isfile("main"):
		print "No executable found. Rebuilding ..."
		code = callSub(['make', '-s', '-j3', 'all'], "Make failed! Exiting.")
		callSub(['make', '-s', 'removeObjects'], "")
		if code:
			print "Rebuild Successful!"
		return code
	
	return True

def mainMenu():
	var = ""
	while var != "1" and var != "2" and var != "Q" and var != "q" and var != "QQ" and var != "Qq" and var != "qQ" and var != "qq" and var != "(Q_Q)":
		print "\nPleas enter choice: "
		print "   1: Run all"
		print "   2: Run specific"
		print "   Q: Quit"
		print "  QQ: Quit and Clean"

		try:
			var = raw_input("Choice: ")
		except:
			print "\nPlease enter 1 or 2 to run, or [Q | QQ] to quit."
			var = "-1"
	return var

def callSub(args, errorMsg):
	try:	
		proc.check_call(args)
		return True
	except proc.CalledProcessError:
		print errorMsg
		proc.call(["make", '-s', "clean"])
		return False

def getNumber():
	num = -1
	while not (num >= 1 and num <= 120):
		print "\nWhich problem? (1-120): "
		try:
			num = input("Choice: ")
		except:
			print "\nPlease enter an integer in the range [1,120]."
			num = -1
	return num

def main():
	global stopAsking
	if not initialise():
		return 1

	var = "d"

	while var != "Q" and var != "q":	
		var = mainMenu()

		if var == "1":
			var = "-1"
			print "Starting run ..."
			print "To stop early, use CTRL+C\n"
			time.sleep(2)

			for i in range(1,121,1):
				try:
					if not callSub(["./main", str(i), str(useThreads), str(printResults), str(storeResults), str(fileName)], "\nRun failed! Exiting."):
						return 1
				except KeyboardInterrupt:
					print "\nStopped!"
					break

		elif var == "2":
			var = "-1"

			print "\nStarting run ...\n"
			if not callSub(["./main", str(getNumber()), str(useThreads), str(printResults), str(storeResults), str(fileName)], "\nRun failed! Exiting."):
				return 1
				
		elif var == "QQ" or var == "Qq" or var == "qQ" or var == "qq" or var == "(Q_Q)":
			print "\nCleaning up ..." 
			callSub(["make", '-s', "clean"], "Clean failed!")  
			break

		else:
			print ""

	print "Finished.\n"

if __name__ == '__main__':
	main()







