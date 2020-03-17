import csv
import random

#The name of your name list
modname = "Jaspiri"
#Name of derived file
filename = "jaspiri.csv"


#==NAMES==#
#Set to 1 to have a first and a last name; 0 creates full names
firstlast = 1

#Set to 1 to enable differing criteria for male vs female names
femmasc = 1

#Set to number of possible female endings; 0 does not differentiate.
endfem = 3

endfemale1 = "e"
endfemale2 = "a"
endfemale3 = "i"

startfemale1 = "j"
startfemale2 = "a"
startfemale3 = "h"

#set to number of possible male endings; 0 does not differentiate.
masc = 0

endmale1 = "o"
endmale2 = "a"
endmale3 = "r"

starmale1 = "j"
starmale2 = "a"
starmale3 = "s"

#set to 1 to have two first names: e.g. "Pepi Gora," etc.
townames = 0

#Set to 1 to have different names for royalty
regnal = 0

#Army Suffixes
army = "Knights"
xeno = "Aliens"
gene = "Heroes"

#Fleet Suffix
fleet = "Grand Fleet"


#Not Alterable

final = modname + ".txt"



with open(filename, newline='') as csvfile:
	vulgar = csv.reader(csvfile, delimiter=',', quotechar='|')
	
	names = []
	next(vulgar)
	for row in vulgar:
		if row[0].title() not in names:
			names.append(row[0].title())
			
	#random.shuffle(names)
	
	print(names)
	
with open(filename, newline='') as csvfile:
	vulgar = csv.reader(csvfile, delimiter=',', quotechar='|')

	femnames = []
	next(vulgar)
	for row in vulgar:
		if startfem == 0 and endfem == 0:
			if row[0].title() not in femnames:
				femnames.append(row[0].title())
				
		if startfem == 1 and endfem == 0:
			if row[0].startswith(startfemale1):
					if row[0] not in femnames:
						femnames.append(row[0].title())
						
		if startfem == 2 and endfem == 0:
			if row[0].startswith(startfemale1) or row[0].startswith(startfemale2):
				if row[0] not in femnames:
					femnames.append(row[0].title())
					
		if startfem == 3 and endfem == 0:
			if row[0].startswith(startfemale1) or row[0].startswith(startfemale2) or row[0].startswith(startfemale3):
				if row[0] not in femnames:
					femnames.append(row[0].title())
					
#Endfem 1
		if startfem == 0 and endfem == 1:
			if row[0].endsswith(endfemale1):
				if row[0] not in femnames:
					femnames.append(row[0].title())
				
		if startfem == 1 and endfem == 1:
			if row[0].startswith(startfemale1) and row[0].endswith(endfemale1):
					if row[0] not in femnames:
						femnames.append(row[0].title())
						
		if startfem == 2 and endfem == 1:
			if (row[0].startswith(startfemale1) or row[0].startswith(startfemale2)) and row[0].endswith(endfemale1):
				if row[0] not in femnames:
					femnames.append(row[0].title())
					
		if startfem == 3 and endfem == 1:
			if (row[0].startswith(startfemale1) or row[0].startswith(startfemale2) or row[0].startswith(startfemale3)) and row[0].endswith(endfemale1):
				if row[0] not in femnames:
					femnames.append(row[0].title())

#Endfem 2
		if startfem == 0 and endfem == 2:
			if row[0].endswith(endfemale1) or row[0].endswith(endfemale2):
				if row[0] not in femnames:
					femnames.append(row[0].title())
				
		if startfem == 1 and endfem == 2:
			if row[0].startswith(startfemale1) and (row[0].endswith(endfemale1) or row[0].endswith(endfemale2)):
					if row[0] not in femnames:
						femnames.append(row[0].title())
						
		if startfem == 2 and endfem == 2:
			if (row[0].startswith(startfemale1) or row[0].startswith(startfemale2)) and (row[0].endswith(endfemale1) or row[0].endswith(endfemale2)):
				if row[0] not in femnames:
					femnames.append(row[0].title())
					
		if startfem == 3 and endfem == 2:
			if (row[0].startswith(startfemale1) or row[0].startswith(startfemale2) or row[0].startswith(startfemale3)) and (row[0].endswith(endfemale1) or row[0].endswith(endfemale2)):
				if row[0] not in femnames:
					femnames.append(row[0].title())

#Endfem 3
		if startfem == 0 and endfem == 3:
			if row[0].endswith(endfemale1) or row[0].endswith(endfemale2) or row[0].endswith(endfemale3):
				if row[0] not in femnames:
					femnames.append(row[0].title())
				
		if startfem == 1 and endfem == 3:
			if row[0].startswith(startfemale1) and (row[0].endswith(endfemale1) or row[0].endswith(endfemale2) or row[0].endswith(endfemale3)):
					if row[0] not in femnames:
						femnames.append(row[0].title())
						
		if startfem == 2 and endfem == 3:
			if (row[0].startswith(startfemale1) or row[0].startswith(startfemale2)) and (row[0].endswith(endfemale1) or row[0].endswith(endfemale2) or row[0].endswith(endfemale3)):
				if row[0] not in femnames:
					femnames.append(row[0].title())
					
		if startfem == 3 and endfem == 3:
			if (row[0].startswith(startfemale1) or row[0].startswith(startfemale2) or row[0].startswith(startfemale3)) and (row[0].endswith(endfemale1) or row[0].endswith(endfemale2) or row[0].endswith(endfemale3)):
				if row[0] not in femnames:
					femnames.append(row[0].title())


with open(filename, newline='') as csvfile:
	vulgar = csv.reader(csvfile, delimiter=',', quotechar='|')

	mascnames = []
	next(vulgar)
	for row in vulgar:
		if row[0] not in mascnames:
			if startmasc == 0 and endmasc == 0:
				mascnames.append(row[0].title())

			if startmasc == 1 and endmasc == 0:
				if row[0].startswith(startmale1):
					mascnames.append(row[0].title())

			if startmasc == 2 and endmasc == 0:
				if row[0].startswith(startmale1) or row[0].startswith(startmale2):
					mascnames.append(row[0].title())

			if startmasc == 3 and endmasc == 0:
				if row[0].startswith(startmale1) or row[0].startswith(startmale2) or row[0].startswith(startmale3):
					mascnames.append(row[0].title())
						
#endmasc 1
			if startmasc == 0 and endmasc == 1:
				if row[0].endsswith(endmale1):
					mascnames.append(row[0].title())

			if startmasc == 1 and endmasc == 1:
				if row[0].startswith(startmale1) and row[0].endswith(endmale1):
					mascnames.append(row[0].title())

			if startmasc == 2 and endmasc == 1:
				if (row[0].startswith(startmale1) or row[0].startswith(startmale2)) and row[0].endswith(endmale1):
					mascnames.append(row[0].title())
						
			if startmasc == 3 and endmasc == 1:
				if (row[0].startswith(startmale1) or row[0].startswith(startmale2) or row[0].startswith(startmale3)) and row[0].endswith(endmale1):
					mascnames.append(row[0].title())

#endmasc 2
			if startmasc == 0 and endmasc == 2:
				if row[0].endswith(endmale1) or row[0].endswith(endmale2):
					mascnames.append(row[0].title())
					
			if startmasc == 1 and endmasc == 2:
				if row[0].startswith(startmale1) and (row[0].endswith(endmale1) or row[0].endswith(endmale2)):
					mascnames.append(row[0].title())
	
			if startmasc == 2 and endmasc == 2:
				if (row[0].startswith(startmale1) or row[0].startswith(startmale2)) and (row[0].endswith(endmale1) or row[0].endswith(endmale2)):
					mascnames.append(row[0].title())
						
			if startmasc == 3 and endmasc == 2:
				if (row[0].startswith(startmale1) or row[0].startswith(startmale2) or row[0].startswith(startmale3)) and (row[0].endswith(endmale1) or row[0].endswith(endmale2)):
					mascnames.append(row[0].title())

#endmasc 3
			if startmasc == 0 and endmasc == 3:
				if row[0].endswith(endmale1) or row[0].endswith(endmale2) or row[0].endswith(endmale3):
					mascnames.append(row[0].title())
	
			if startmasc == 1 and endmasc == 3:
				if row[0].startswith(startmale1) and (row[0].endswith(endmale1) or row[0].endswith(endmale2) or row[0].endswith(endmale3)):
					mascnames.append(row[0].title())
		
			if startmasc == 2 and endmasc == 3:
				if (row[0].startswith(startmale1) or row[0].startswith(startmale2)) and (row[0].endswith(endmale1) or row[0].endswith(endmale2) or row[0].endswith(endmale3)):
					mascnames.append(row[0].title())
	
			if startmasc == 3 and endmasc == 3:
				if (row[0].startswith(startmale1) or row[0].startswith(startmale2) or row[0].startswith(startmale3)) and (row[0].endswith(endmale1) or row[0].endswith(endmale2) or row[0].endswith(endmale3)):
					mascnames.append(row[0].title())
	
#print("FEMALE NAMES")
#print(femnames)
#print("MALE NAMES")
#print(mascnames)
	
#Document Creation
	f = open(final,"w+")
	f.write(
	"###" + modname + "\n"
	"" + modname + " = {\n"
	
	"\t###SHIPS\n"
	"\n"
	"\tship_names = {\n"
	"\n"
	"\t\tgeneric = {\n"
	"\t\t\t" + " ".join(names[1:51]) + "\n"
	"\t\t}\n"
	"\t\tcorvette = {\n"
	"\t\t\t" + " ".join(names[52:77]) + "\n"
	"\t\t}\n"
	"\n"
	"\t\tdestroyer = {\n"
	"\t\t\t" + " ".join(names[78:103]) + "\n"
	"\t\t}\n"
	"\n"
	"\t\tcruiser = {\n"
	"\t\t\t" + " ".join(names[104:155]) + "\n"
	"\t\t}\n"
	"\n"
	"\t\tbattleship = {\n"
	"\t\t\t" + " ".join(names[156:181]) + "\n"
	"\t\t}\n"
	"\n"
	"\t\ttitan = {\n"
	"\t\t\t" + " ".join(names[182:192]) + "\n"
	"\t\t}\n"
	"\n"
	"\t\tcolossus = {\n"
	"\t\t\t" + " ".join(names[193:196]) + "\n"
	"\t\t}\n"
	"\n"
	"\t\tscience = {\n"
	"\t\t\t" + " ".join(names[222:248]) + "\n"
	"\t\t}\n"
	"\n"
	"\t\tcolonizer = {\n"
	"\t\t\t" + " ".join(names[249:274]) + "\n"
	"\t\t}\n"
	"\n"
	"\t\tconstructor = {\n"
	"\t\t\t" + " ".join(names[275:300]) + "\n"
	"\t\t}\n"
	"\n"
	"\t\ttransport = {\n"
	"\t\t\t" + " ".join(names[301:352]) + "\n"
	"\t\t}\n"
	"\n"
	"\t\tmilitary_station_small = {\n"
	"\t\t\t" + " ".join(names[353:368]) + "\n"
	"\t\t}\n"
	"\n"
	"\t\tion_cannon = {\n"
	"\t\t\t" + " ".join(names[369:384]) + "\n"
	"\t\t}\n"
	"\n"
	"\t}\n"
	"\n"
	
	"\tfleet_names = {\n"
	"\t\trandom_names = {\n"
	"\t\t\t\"" + "".join(names[385]) +  " " + fleet + "\" " + "\"" + "".join(names[1097]) +  " " + fleet + "\" " + "\"" + "".join(names[1098]) +  " " + fleet + "\" " + "\"" + "".join(names[1099]) +  " " + fleet + "\" " + "\"" + "".join(names[1100]) +  " " + fleet + "\" " + "\"" + "".join(names[1101]) +  " " + fleet + "\" " + "\"" + "".join(names[1102]) +  " " + fleet + "\" " + "\"" + "".join(names[1103]) +  " " + fleet + "\" " + "\"" + "".join(names[1104]) +  " " + fleet + "\" " + "\"" + "".join(names[1105]) +  " " + fleet + "\" " + "\"" + "".join(names[1106]) +  " " + fleet + "\" " + "\"" + "".join(names[1107]) +  " " + fleet + "\" " + "\"" + "".join(names[1108]) +  " " + fleet + "\" " + "\"" + "".join(names[1109]) +  " " + fleet + "\" " + "\"" + "".join(names[1110]) +  " " + fleet + "\" " + "\"" + "".join(names[1111]) +  " " + fleet + "\"\n"
	"\t\t}\n"
	"\t}\n"
	"\n"
	
	"\t###ARMIES\n"
	"\tarmy_names = {\n"
	"\n"
	"\t\tdefense_army = {\n"
	"\t\t\tsequential name = \"%O% " + "".join(names[386]) + " " + army + "\"\n"
	"\t\t}\n"
	"\n"
	"\t\tassault_army = {\n"
	"\t\t\tsequential name = \"%O% " + "".join(names[387]) + " " + army + "\"\n"
	"\t\t}\n"
	"\n"
	"\t\tslave_army = {\n"
	"\t\t\tsequential name = \"%O% " + "".join(names[388]) + " " + army + "\"\n"
	"\t\t}\n"
	"\n"
	"\t\tclone_army = {\n"
	"\t\t\tsequential name = \"%O% " + "".join(names[389]) + " " + army + "\"\n"
	"\t\t}\n"
	"\n"
	"\t\trobotic_army = {\n"
	"\t\t\tsequential name = \"%O% " + "".join(names[390]) + " " + army + "\"\n"
	"\t\t}\n"
	"\n"
	"\t\trandroid_army = {\n"
	"\t\t\tsequential name = \"%O% " + "".join(names[391]) + " " + army + "\"\n"
	"\t\t}\n"
	"\n"
	"\t\tpsionic_army = {\n"
	"\t\t\tsequential name = \"%O% " + "".join(names[392]) + " " + army + "\"\n"
	"\t\t}\n"
	"\n"
	"\t\txenomorph_army = {\n"
	"\t\t\tsequential name = \"%O% " + "".join(names[393]) + " " + xeno + "\"\n"
	"\t\t}\n"
	"\n"
	"\t\tgene_warrior_army = {\n"
	"\t\t\tsequential name = \"%O% " + "".join(names[394]) + " " + gene + "\"\n"
	"\t\t}\n"
	"\t}\n"
	"\n"
	
	"\t### PLANETS\n"
	"\n"
	"\tplanet_names = {\n"
	"\n"
	"\t\tgeneric = {\n"
	"\t\t\tnames = {\n"
	"\t\t\t\t" + " ".join(names[395:595]) + "\n"
	"\t\t\t}\n"
	"\t\t}\n"
	"\n"
	"\t\tpc_desert = {\n"
	"\t\t\tnames = {\n"
	"\t\t\t}\n"
	"\t\t}\n"
	"\n"
	"\t\tpc_tropical = {\n"
	"\t\t\tnames = {\n"
	"\t\t\t}\n"
	"\t\t}\n"
	"\n"
	"\t\tpc_arid = {\n"
	"\t\t\tnames = {\n"
	"\t\t\t}\n"
	"\t\t}\n"
	"\n"
	"\t\tpc_continental = {\n"
	"\t\t\tnames = {\n"
	"\t\t\t}\n"
	"\t\t}\n"
	"\n"
	"\t\tpc_ocean = {\n"
	"\t\t\tnames = {\n"
	"\t\t\t}\n"
	"\t\t}\n"
	"\n"
	"\t\tpc_tundra = {\n"
	"\t\t\tnames = {\n"
	"\t\t\t}\n"
	"\t\t}\n"
	"\n"
	"\t\tpc_alpine = {\n"
	"\t\t\tnames = {\n"
	"\t\t\t}\n"
	"\t\t}\n"
	"\n"
	"\t\tpc_arctic = {\n"
	"\t\t\tnames = {\n"
	"\t\t\t}\n"
	"\t\t}\n"
	"\n"
	"\t}\n"
	"\n"
	"\t### CHARACTERS\n"
	"\n"
	)
	f.close
	
	if firstlast == 0:
	
		f = open(final,"a")
		f.write(
		"\tcharacter_names={\n"
		"\t\tdefault = {\n"
		"\t\t\tfull_names ={\n"
		"\t\t\t" + " ".join(names[596:1096]) + "\n"
		"\t\t\t}\n"
		"\n"
		"\t\t\t#Always combined with a second name\n"
		"\t\t\tfirst_names_male ={\n"
		"\t\t\t}\n"
		"\n"
		"\t\t\tfirst_names_female ={\n"
		"\t\t\t}\n"
		"\n"
		"\t\t\t# Always combined with a first name\n"
		"\t\t\tsecond_names ={\n"
		"\t\t\t}\n"
		"\n"
		)
		f.close
		
	if firstlast == 1:
		if femmmasc == 0:
			f = open(final,"a")
			f.write(
			"\tcharacter_names={\n"
			"\t\tdefault = {\n"
			"\t\t\tfull_names ={\n"
			"\t\t\t}\n"
			"\n"
			"\t\t\t#Always combined with a second name\n"
			"\t\t\tfirst_names_male ={\n"
			"\t\t\t" + " ".join(names[596:846]) + "\n"
			"\t\t\t}\n"
			"\n"
			"\t\t\tfirst_names_female ={\n"
			"\t\t\t" + " ".join(names[847:1107]) + "\n"
			"\n"
			"\t\t\t# Always combined with a first name\n"
			"\t\t\t" + " ".join(names[1108:1308]) + "\n"
			"\t\t\t}\n"
			"\n"
			)
			f.close
		if femmasc == 1:
			f = open(final,"a")
			f.write(
			"\tcharacter_names={\n"
			"\t\tdefault = {\n"
			"\t\t\tfull_names ={\n"
			"\t\t\t}\n"
			"\n"
			"\t\t\t#Always combined with a second name\n"
			"\t\t\tfirst_names_male ={\n"
			"\t\t\t" + " ".join(mascnames[1:50]) + "\n"
			"\t\t\t}\n"
			"\n"
			"\t\t\tfirst_names_female ={\n"
			"\t\t\t" + " ".join(femnames[1:50]) + "\n"
			"\n"
			"\t\t\t# Always combined with a first name\n"
			"\t\t\t" + " ".join(names[1108:1308]) + "\n"|
			"\t\t\t}\n"
			"\n"
			)
			f.close
	if regnal == 0:
	
		f = open(final,"a")
		f.write(
		"\t\t\tregnal_first_names_male ={\n"
		"\t\t\t}\n"
		"\n"
		"\t\t\tregnal_first_names_female ={\n"
		"\t\t\t}\n"
		"\n"
		"\t\t\tregnal_second_names ={\n"
		"\t\t\t}\n"
		"\t\t}\n"
		"\t}\n"
		"}"
		)
		f.close
		
	if regnal == 1:
	
		f = open(final,"a")
		f.write(
		"\t\t\tregnal_first_names_male ={\n"
		"\t\t\t" + " ".join(names[1101:1308]) + "\n"
		"\t\t\t}\n"
		"\n"|||||||
		"\t\t\tregnal_first_names_female ={\n"
		"\t\t\t" + " ".join(names[1108:1308]) + "\n"
		"\t\t\t}\n"
		"\n"
		"\t\t\tregnal_second_names ={\n"
		"\t\t\t" + " ".join(names[1108:1308]) + "\n"
		"\t\t\t}\n"
		"\t\t}\n"
		"\t}\n"
		"}"
		)
		f.close
		

def readcsv(file):
	with open(file, newline='') as csvfile:
	vulgar = csv.reader(csvfile, delimiter=',', quotechar='|')
	
	names = []
	next(vulgar)
	for row in vulgar:
		if row[0].title() not in names:
			names.append(row[0].title())
			
	random.shuffle(names)
	
	return names
	
def main()
	filename = "jaspiri.csv"
	namelist = readcsv(filename)
	print(namelist)

if __name__ == '__main__' :
    main()