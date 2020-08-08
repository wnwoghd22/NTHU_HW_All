import random

class Matrix:
    def __init__(self, data):
        self._mat = data

    def row(self, r):
        return self._mat[r]

    def column(self, c):
        return [i[c] for i in self._mat]

    @property
    def nrow(self):
        return len(self._mat)

    @property
    def ncolumn(self):
        return len(self._mat[0])

    def transpose(self):
        return Matrix([list(i) for i in zip(*self._mat)])

    def randomize(self):
        _ls = []
        for i in self._mat:
            _ls.extend(i)
        random.shuffle(_ls)
        for i in range(self.nrow):
            self._mat[i] = _ls[i*self.ncolumn:i*self.ncolumn+self.ncolumn]
