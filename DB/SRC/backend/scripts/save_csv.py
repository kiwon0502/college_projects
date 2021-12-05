import sys
import pandas as pd

taskname = sys.argv[1]
params = sys.argv[2].split(',')
rows = int(params[0])
cols = int(params[1])
attrs = sys.argv[3].split(',')
types = sys.argv[4].split(',')

result = []
for i  in range(rows):
	rr = []
	for j in range(cols):
		attr = attrs[j]
		val = params[2+i*cols+j]
		if val == 'NULL':
			rr.append(None)
		elif (attr[:3] == 'int' or attr[:6] == 'bigint' or attr[:5] == 'float'):
			rr.append(int(val))
		else:
			rr.append(val)
	result.append(rr)

df = pd.DataFrame(result, columns = attrs)
df.to_csv('upload/'+taskname+'.csv', index = False)
	