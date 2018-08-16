#!/usr/bin/env python
#!/usr/bin/env python
import os, timeit, math

code = '''
for x in range(100):
   name = '/files/file_' + str(x).zfill(4) + '.txt'
   os.path.exists(name)
'''
print('#%*s%*s%*s%*s%*s' % (10, "Runs x100k", 11, "TIME(s)", 22, "TOTAL(s)", 25, "AVG TIME(s)", 23, "SIGMA"))
count = 1
while count <= 1024:

   sumnums = 0.0
   nums = []
   for i in range(count):
      temp = timeit.timeit(setup = 'import os', stmt = code, number = 1000)
      sumnums += temp
      nums.append(temp)
   avg = sumnums/count
   sigma = 0.0
   for c in range(len(nums)):
      sigma += math.pow(nums[c]-avg, 2)
   sigma = sigma / len(nums)
   sigma = math.sqrt(sigma)
   time = nums[0]
   print(' %*i%*f%*f%*f%*f' % (10, count, 11, time, 22, sumnums, 25, avg, 23, sigma))
   count = count * 2
