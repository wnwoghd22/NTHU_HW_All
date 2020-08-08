def default_function(_L, _prefix):
    _s = ' '*4*(len(_prefix)-1) + '.'.join(map(str,_prefix)) + '. '+_L
    print(_s)
def my_outline_format_function(_L, _prefix):
    D = {1:'I',2:'II',3:'III',4:'IV',5:'V'\
            ,6:'VI',7:'VII',8:'VIII',9:'IX',10:'X'}
    _s = ' '*2*(len(_prefix)-1)
    if len(_prefix) == 1:
        _s += D.get(_prefix[0])
    elif len(_prefix) == 2:
        _s += chr(ord('A')-1+_prefix[1])
    else:
        _s += str(_prefix[-1])
    _s += '. '+_L
    print(_s)
def my_thesis_format_function(_L, _prefix):
    _s = ' '*2*(len(_prefix)-1)
    if len(_prefix) == 1:
        _s += 'Chapter'
    elif len(_prefix) == 2:
        _s += 'Section'
    _s += '.'.join(map(str,_prefix)) + '. '+_L
    print(_s)
def my_simple_format_function(_L, _prefix):
    _s = ' '*2*(len(_prefix)-1)
    _s += str(_prefix[-1])
    if len(_prefix)%3 == 1:
        _s += '. '
    elif len(_prefix)%3 == 2:
        _s += ') '
    else:
        _s += ' - '
    _s += _L
    print(_s)
def number_outline(L, F = default_function, prefix = ()):
    if type(L) in {list, tuple}:
        i = 0
        for v in L:
            if type(v) not in {list, tuple}:
                i += 1
            number_outline(v, F, prefix+(i,)) #if v is int then F(v, prefix)
    else:
        F(L, prefix) #type(L) is int, print the line
