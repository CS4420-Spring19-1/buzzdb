import subprocess
import os
import shutil


if not os.path.exists('./results'):
	os.mkdir('./results')
else:
	shutil.rmtree('./results')
	os.mkdir('./results')

for range in [10000, 100000]:
	os.mkdir('./results/range_'+str(range))
	for i in [2,4]:
		filePath = "./results/range_"+str(range)
		os.mkdir(filePath+ '/Algorithm'+str(i))
		filePath = filePath + "/Algorithm" + str(i)
		command = ["../build/test/emerald"];
		command.append("-r " + str(range))
		file = open(filePath+"/r" + str(range) + ".txt", 'w');
		for column_1_size in [10000, 100000]:
			for size_factor in [0.2, 2]:
				for join_selectivity in [0.1, 0.3, 0.5, 0.9]:
						ps = subprocess.call(command+["-j " + str(join_selectivity)]+["-a " + str(i)] + ["-o " + str(column_1_size)] + ["-s " + str(size_factor)], stdout=file)
		file.close()
