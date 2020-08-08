class Polynomial:
    def __init__(self, *coeff):
        self.coefflist = coeff
    def evaluate(self, xvalue):
        idx = 0
        x = 0
        for i in self.coefflist:
            x += i*(xvalue**idx)
            idx += 1
        return x
    __call__ = evaluate

f = Polynomial(3,5,4,7,1)
print(f.evaluate(3))
print(f(3))






