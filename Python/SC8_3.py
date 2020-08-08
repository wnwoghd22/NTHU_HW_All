def WhoIsOlder(**Dict):
    age = -1
    name = ''
    if len(Dict) == 0:
        print('None is oldest. \n %d' % age)
    else:
        j = 0
        for i in Dict.values():
            if age < i:
                age = i
                name = list(Dict.keys())[j]
            j = j + 1
        print('%s is oldest. \n %d' % (name, age))
        
WhoIsOlder(Amy = 10, Lisa = 11)
WhoIsOlder()
WhoIsOlder(Sam = 5, Liu = 20, Chao = 15)

