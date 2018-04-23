import sys
import numpy as np
import os
import scipy
from scipy import ndimage
import lmdb

def processOptions(options):
	for i in range(1, len(sys.argv)):
		arg = sys.argv[i]
		_arg = arg.split('=')
		opt = _arg[0][1:]
		
		if opt[0] == '-':
			opt = opt[1:]
		
		options[opt] = _arg[1]

	if 'i' not in options.keys():
		print("Please provide video file name by using -i=<intput folder name>")
		quit()

	if 'o' not in options.keys():
		print("Please provide db output folder using -o=<output folder name>")
		quit()
		
	if 'f' not in options.keys():
		print("Please provide db name using -f=<output db name>")
		quit()

	if not os.path.exists(options['i']):
		print("Please enter an input directory that exists.")

	print("looking for data in", options['i'])

	if not os.path.exists(options['o']):
		os.makedirs(options['o'])

def readFiles(t_count):
	files = [f for f in os.listdir(options['i']) if os.path.isfile(os.path.join(options['i'], f))]
	for f in files:
		f_name = os.path.join(options['i'], f)
		print("Processing ...", f)
		dna = scipy.misc.imread(f_name)
		dnaf = ndimage.gaussian_filter(dna, 3)
		T = 25
		labeled, nr_objects = ndimage.label(dnaf > T)
		fnum = f.strip().split()[0]
		t_count[fnum] = str(nr_objects)


def createDB(fname, t_count):
	print("Creating database .....")
	lmdb_env = lmdb.open(fname, map_size=int(1e9))
	for key, value in t_count.items():
		with lmdb_env.begin(write=True) as lmdb_txn:
			lmdb_txn.put(key.encode('utf-8'), value.encode('utf-8'))
	
	print("Database created in", fname)

def readDB(fname):
	dc = {}
	lmdb_env = lmdb.open(fname)
	lmdb_txn = lmdb_env.begin()
	lmdb_cursor = lmdb_txn.cursor()
	for key, value in lmdb_cursor:
		print("Read:", key.decode("utf-8") , ":", value.decode("utf-8"))
		dc[int(key.decode("utf-8"))] = int(value.decode("utf-8"))
	return dc

options = {}
processOptions(options)
t_count = dict()
readFiles(t_count)

fname = os.path.join(options['o'], options['f'])
createDB(fname, t_count)
#print(readDB(fname))
