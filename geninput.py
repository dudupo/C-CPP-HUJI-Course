import random
import string

def random_key(length):
	key = ''
	for i in range(length):
		key += random.choice(string.ascii_letters)
	return key

if __name__ == '__main__':
	size = 40
	length = 7
	for i in range(size):
		print( '{0}\t{1}\t{2} {3}\t{4}\t{5}\t{6}'.format(random.randint(10**9 , 10**10),
		random_key(length), random_key(length), random.randint(1,100) ,  random.randint(18,80) ,random_key(length), random_key(length)))
	print('q')
