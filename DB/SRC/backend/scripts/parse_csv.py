import sys
import pandas as pd
filename = sys.argv[1]
attrs = sys.argv[2].split(',');
types = sys.argv[3].split(',');
df = pd.read_csv('upload/' + filename)

column_valid = True
for a1, a2 in zip(attrs, df.columns):
	if a1 != a2:
		column_valid = False
		break
if column_valid:
	print(0)
else:
	print(1)

type_valid = True
for t1, t2 in zip(types, df.dtypes):
	if (t1[:3] == 'int' or t1[:6] == 'bigint') and str(t2)[:3] != 'int':
		type_valid = False
	if t1[:5] == 'float' and (str(t2)[:5] != 'float' and str(t2)[:3] != 'int'):
		type_valid = False
	if t1[:4] == 'date' and str(t2)[:4] != 'date':
		type_valid = False
if type_valid:
	print(0)
else:
	print(1)

#df[df.isnull()]='NULL'

for i, r in df.iterrows():
	for rr in r:
		print(rr)
	