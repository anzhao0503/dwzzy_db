sw = open('test.txt', 'w+')
for i in range(256):
    sw.writelines(str(i+1)+'\n')
sw.close()
