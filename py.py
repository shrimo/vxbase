class A(object):
    def __init__(self, x):
        self.x = x
        self.z = x * x

    def mult(self):
    	return self.z * self.x 

    def __del__(self):
    	print 'exit'

a = A(5.222)
print a.x, a.z
print a.mult()
