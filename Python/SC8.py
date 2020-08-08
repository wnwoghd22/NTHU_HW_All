import operator, copy
def postcalc(*_ls, stack = []):
    _stack = copy.deepcopy(stack)
    #inner function
    def _add(a, b): _stack.append(a.__add__(b))
    def _sub(a, b): _stack.append(a.__sub__(b))
    def _mul(a, b): _stack.append(a.__mul__(b))
    def _swap(a, b): _stack.extend([a,b])
    def unkown(a, b):
        print("Unkown operator has been found!")
        _stack.extend([b,a])
    D = {'_add':_add,'_sub':_sub,'_mul':_mul,'_swap':_swap}

    for i in _ls:
        if type(i) in {int, float}:
            _stack.append(i)
        if type(i) is str:
            D.get('_'+i, unkown)(_stack.pop(),_stack.pop()) #_(dict_name)(a,b)
    print(_stack)
