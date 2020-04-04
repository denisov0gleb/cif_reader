# Simple CIF (Crystallographic Information File) parser to create reports

## ToDO:
* Find where max 2 theta values are stored
* Change Space Group: *'P 1 21/c 1'* to *P21/c*
* Change Syngony: *'monoclinic'* to *Monoclinic*
* Change coefficient mu from cm-1 to mm-1: *0.105* to *1.05*
* Append min diffraction density to max: *0.317 and -0.280* to *0.317 / -0.280*


## Install:
1. __make__
2. Add folder with *cif_reader.exe* to your *PATH*


## Usage for Windows:
1. Call from command line
		__cif_reader.exe your_file.cif__
		or drag&drop *your_file.cif* on *cif_reader.exe*
2. Copy data from *cif_result.txt* from folder with *your_file.cif* to your report
