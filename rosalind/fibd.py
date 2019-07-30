# http://rosalind.info/problems/fibd/

import six

line = six.moves.input()
tokens = line.split(' ')
n = int(tokens[0])
k = int(tokens[1])

# population[(i + offset) % k] represents the number of rabbits of i months old
offset = 0
population = [0] * k
population[0] = 1

logging = True

num_mature_rabbits = 0
for t in range(0, n - 1):
    if logging:
        print("At time % d" % (t + 1))
        for i in range(0, k):
            index = (i + offset) % k
            print(population[index])
    num_new_born_rabbits = num_mature_rabbits
    # New borns are turning mature
    num_mature_rabbits = num_mature_rabbits + population[offset]    
    # Rotate the array by changing the offset, the +k ensures offset is never negative
    offset = (offset + k - 1) % k
    # After the rotation, the slot for storing the number of newborns are currently storing the number of dying mature rabbits 
    num_mature_rabbits = num_mature_rabbits - population[offset]
    population[offset] = num_new_born_rabbits

print(num_mature_rabbits + population[offset])