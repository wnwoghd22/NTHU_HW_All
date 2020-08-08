import operator
class Polynomial:
    def __init__(self, *coeff):
        self._coeff = list(coeff)
    def evaluate(self, xvalue):
        idx = 0
        result = 0
        for i in self._coeff:
            result += i*(xvalue**idx)
            idx += 1
        return result
    __call__ = evaluate
    def __add__(self, RHS):
        result = []
        for i in self._coeff:
            result.append(i)
        for i in range(min(len(self._coeff), len(RHS._coeff))):
            result[i] += RHS._coeff[i]
        if len(result) < len(RHS._coeff):
            result.extend(RHS._coeff[len(result):])
        return Polynomial(*result)
    def __sub__(self, RHS):
        for i in RHS._coeff:
            sublist = [-x for x in RHS._coeff]
        return self.__add__(Polynomial(*sublist))
    def __imul__(self, other):
        for i in range(len(self._coeff)):
            self._coeff[i] *= other
        return self
    def __repr__(self):
        coefflist = tuple(self._coeff)
        return f'{self.__class__.__name__}{coefflist}'
    def change_coeff(self, idx, coeff):
        self._coeff[idx] = coeff
