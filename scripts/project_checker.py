import os
import re
from builtins import print
from pathlib import Path
PROJECT_ROOT = "D:\\PROGRAMOWANIE\\C\\Judy"
###############################################
#                 Functions
###############################################

#Recursively runs through directories
def scanFolder(path, depth):
	offset = depth*"   "
	print(offset+"Now scanning "+path)
	for item in os.scandir(path):
		if(item.is_dir()):
			scanFolder(item.path, depth+1)
		else:
			print(offset+"FILE: "+item.name)
			file = open(item.path, "r")
			#Test calls
			checkFileAccess(file)
			checkMemAlloc(file)

#Checks if after 'fopen()' appears 'fclose()' within a function
def checkFileAccess(sourceFile):
	openedFiles = 0
	closedFiles = 0
	re_fopen = re.compile("[^//]*fopen.*")
	re_close = re.compile("[^//]*fclose.*")
	for line in sourceFile:
		if re.search(re_fopen, line):
			openedFiles += 1
		if re.search(re_close, line):
			closedFiles += 1
	if openedFiles != closedFiles:
		print("    CHECK FILE ACCESS: MISMATCH BETWEEN OPENED FILES["+str(openedFiles)+"] AND CLOSED FILES["+str(closedFiles)+"]")
	

#Checks if after 'malloc()' appears 'free()' within a function	
def checkMemAlloc(sourceFile):	
	memAllocs = 0
	memFree = 0
	for line in sourceFile:
		if line.find("malloc") != -1 and not line.startswith("//"):
			memAllocs += 1
		if line.find("free") != -1:
			memFree += 1
	if memAllocs != memFree:
		print("    CHECK MEM ALLOC: MISMATCH BETWEEN ALLOCS["+str(memAllocs)+"] AND FREE["+str(memFree)+"]")

###############################################
#                 Config data
###############################################
os.system("cls")
print("Accessing config data..")
configFile = open(PROJECT_ROOT+"\\src\\h\\config.h", "r")
configData = {}
#parse config data into dictionary
for line in configFile:
	splitLine = line.split(" ")
	if(splitLine[0] == "#define" and len(splitLine) == 3 ):
		configData[splitLine[1]] = splitLine[2]

#print config data
for x in configData:	
	print(x+" - "+configData[x])
print("Config data acquired")
configFile.close()

###############################################
#Run checks on files
###############################################
scanFolder(PROJECT_ROOT+"\\src", 0)
#os.system("pause")