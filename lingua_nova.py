import csv
import random

#Alterable
language = "Rokbobahadmahak"
filename = "rok_name.csv"
final = "RokFinal.txt"

#Not Alterable
with open(filename, newline='') as csvfile:
	vulgar = csv.reader(csvfile, delimiter=',', quotechar='|')
	
	names = []
	next(vulgar)
	for row in vulgar:
		if row[0] not in names:
			names.append(row[0])
			
	random.shuffle(names)
	
	#Removes brackets, apostrophes, commas, and capitalizes everything.
	names_string = ' '.join(names).title()
	
	f = open(final,"w+")
	f.write(
	"###" + language + "\n"
	"" + language + " = {\n"
	"\t###SHIPS\n"
	"\n"
	"\tship_names = {\n"
	"\n"
	"\tgeneric = {\n"
	"\t\t\t"
	)
	f.close