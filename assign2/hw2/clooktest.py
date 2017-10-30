import random
import os

current_directory = os.getcwd()
final_directory = os.path.join(current_directory, r'clooktest')
if not os.path.exists(final_directory):
   os.makedirs(final_directory)

#Create the three files and write a string of 10 random characters + endline
for i in range (0,5):
    file = open('clooktest/file.%d' % (i), 'w')
    valid_letters = 'abcdefghijklmnopqrstuvwxyz'
    rand_string = ''.join((random.choice(valid_letters) for j in xrange(10)))
    file.write(rand_string)
    file.write("\n")
    file.close()

for i in range (0,5):
    file = open('clooktest/file.%d' % (i), 'r')
    file.readline()
    file.close()
