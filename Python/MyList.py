class MyList(list):
    def __repr__(self):
        return self.__class__.__name__+'('+super().__repr__()+')'
#if __name__=='__main__':
#    L = MyList([1,2,3])
#    P = MyList([7.4, MyList([2,(5,'a','z'),[4,[9,7],'b']]), 2, 'world', 'bye'])
    
    def find(self, val):
        def rec_find(L, val):
            if isinstance(L, list) or isinstance(L, tuple):
                for i,v in enumerate(L):
                    p = rec_find(v, val)
                    if p == True:
                        return (i,)
                    if p != False:
                        return (i,)+p
            return L == val
        return rec_find(self, val)

    def sort(self, key=None, reverse=False):
        D = {'NoneType':0, 'int':1, 'float':1, 'str':2, 'tuple':3, 'list':4}
        return super().sort(key=lambda x:(D.get(type(x).__name__, 5), \
                key(x) if key is not None else x), reverse=reverse)
