import re
f = open("D:\\PROGRAMOWANIE\\C\\Judy\\src\\c\\fileIO.c", "r")
openedFiles = 0;
pat = re.compile("//")
for line in f:
	# print(str(line.startswith("int")))
	if line.find("fopen") != -1 and not line.startswith("//"):
		pat.match("int")
		openedFiles += 1
print(openedFiles)