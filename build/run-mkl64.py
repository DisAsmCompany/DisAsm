import os
import sys

disasm = 'windows32-msvc2005\\release\\DisAsmSample.exe'
sysroot = os.environ['INTEL_MKL_HOME'] + '\\intel64\\';
for root, dirs, files in os.walk(sysroot):
	while len(dirs) > 0:
		dirs.pop();
	for file in files:
		if file.endswith('.lib'):
			print(file);
			sys.stderr.write(file + '\n');
			sys.stderr.flush();
			os.system(disasm + ' -p ' + sysroot + file + ' > ' + 'out\\' + file + '.txt');
