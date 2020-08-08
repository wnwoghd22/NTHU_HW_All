def CharRange(start, end):
    if ord(start) > ord(end):
        for i in range(ord(start)-ord(end)+1):
            yield chr(ord(start)-i)
    else:
        for i in range(ord(end)-ord(start)+1):
            yield chr(ord(start)+i)
