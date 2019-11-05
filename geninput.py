import random
import string

def random_key(length):
	key = ''
	for i in range(length):
		key += random.choice(string.ascii_letters)
	return key

if __name__ == '__main__':
	size = 8
	length = 20
	for i in range(size):
		print( '{0}\t{1}\t{2}\t{3}\t{4}\t{5}'.format(random.randint(1 , 10*7),
		random_key(length), random.randint(1,100) ,  random.randint(1,30) ,random_key(length), random_key(length)))
	print('q')
