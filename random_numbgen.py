import random 
  

res = random.sample(range(1, 3000), 100)

with open('listfile.txt', 'w') as filehandle:
    for listitem in res:
        filehandle.write('%s ' % listitem) 