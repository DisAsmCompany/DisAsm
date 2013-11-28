import os
import sys
extensions = {
'.exe' : 'EXE : EXEcutable', 
'.dll' : 'DLL : Dynamic Link Library', 
'.acm' : 'ACM : Audio Compression Manager',
'.ax'  : 'AX  : ActiveX (DirectShow Filter)',
'.drv' : 'DRV : Device DRiVer',
'.ocx' : 'OCX : OLE Control eXtension',
'.vbx' : 'VBX : Visual Basic eXtension',
'.cpl' : 'CPL : Control PaneL',
'.scr' : 'SCR : Screen Saver',
'.sys' : 'SYS : SYStem File',
'.fon' : 'FON : FONt',
'.efi' : 'EFI : Extensible Firmware Interface',
'.icl' : 'ICL : Icon Library',
'.vxd' : 'VXD : Virtual XXX Driver',
'.386' : '386 : i386 Executable',
};
disasm = 'windows32\debug\DisAsmSample.exe'
sysroot = os.environ['SYSTEMROOT'] + '\System32';
for root, dirs, files in os.walk(sysroot):
	while len(dirs) > 0:
		dirs.pop();
	for file in files:
		for ext in extensions:
			if file.endswith(ext):
				print(file);
				sys.stderr.write(file);
				sys.stderr.flush();
				os.system(disasm + ' ' + file + ' > ' + 'out\\' + file + '.txt')
