def long_multiply(multiplier, multiplicand):
    result = multiplier * multiplicand
    width = len(str(result))+1

    listOfStrings = [' '*(width-len(str(multiplier)))+str(multiplier), \
                'X)'+' '*(width-len(str(multiplicand))-2)+str(multiplicand), \
                    '-'*width]

    for i,val in enumerate(reversed(str(multiplicand))):
        factor = str(multiplier*int(val))
        listOfStrings.append(' '*(width-i-len(factor))+factor)

    listOfStrings.extend(['-'*width,' '+str(result)])

    print('\n'.join(listOfStrings))
