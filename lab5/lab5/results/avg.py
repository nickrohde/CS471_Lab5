import numpy as np


def calcAverages(values):
	values = values.transpose()

	averages = []
	averages.append(sum(values[0]) / len(values[0]))
	averages.append(sum(values[1]) / len(values[1]))
	averages.append(sum(values[2]) / len(values[2]))
	averages.append(sum(values[3]) / len(values[3]))
	averages.append(sum(values[4]) / len(values[4]))
	averages.append(sum(values[5]) / len(values[5]))
	averages.append(sum(values[6]) / len(values[6]))
	averages.append(sum(values[7]) / len(values[7]))
	averages.append(sum(values[8]) / len(values[8]))

	values = values.transpose()	

	return averages
			

def makeTable(in_filename, out_filename):
	values = np.genfromtxt(in_filename, delimiter=",")
	averages = calcAverages(values)

	table = open(out_filename, "a")
		
	for i in range(len(values)):
		for j in range(len(values[i])):	
			table.write(str(values[i][j]))
			if (j+1) == len(values[i]):
				table.write("\n")
			else:
				table.write(" & ")

	for i in range(len(averages)):
		table.write(str(averages[i]))
		if (i+1) == len(averages):
			table.write("\n")
		else:
			table.write(" & ")
	table.close()

	print 'Average time FSS: ', averages[1]
	print 'Average time FSSB: ', averages[4]
	print 'Average time FSSNW: ', averages[7]

def main():
	makeTable("results_fast_math.csv","table_fast_math.txt")
	makeTable("results_no_sse3.csv","table_no_sse3.txt")
	makeTable("results_O2.csv","table_O2.txt")
	makeTable("results_O3.csv","table_O3.txt")
	makeTable("results_ofast.csv","table_ofast.txt")


main()



	
