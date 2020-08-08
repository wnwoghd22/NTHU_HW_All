def reverse_list(ls):
    result = []
    for i in reversed(ls):
        if type(i) in {list, tuple}:
            result.append(reverse_list(i))
        else:
            result.append(i)
    return result
