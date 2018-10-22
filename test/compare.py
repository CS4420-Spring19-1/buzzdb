import subprocess
import os
import shutil


if not os.path.exists('./results'):
	os.mkdir('./results')
else:
	shutil.rmtree('./results')
	os.mkdir('./results')

for i in range(1,4):
	filePath = './results'
	range=10000
	max_range=10*range
	os.mkdir('./results/Algorithm'+str(i))
	filePath = filePath + "/Algorithm" + str(i)
	while range <= max_range:
		join_selectivity = 0.1;
		max_selectivity = 1;
		command = ["../build/test/emerald"];
		command.append("-r " + str(range))
		file = open(filePath+"/r" + str(range) + ".txt", 'w');
		while join_selectivity <= max_selectivity:
				ps = subprocess.call(command+["-j " + str(join_selectivity)]+["-a" + str(i)], stdout=file)
				join_selectivity+=0.1;
		range = range + 10000
		file.close()
	i=i+1
