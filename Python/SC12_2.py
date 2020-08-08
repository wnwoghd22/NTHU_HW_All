class DaysInYear:
    def __init__(self, year):
        self._days = []
        def leapyear(y):
            return 29 if y%1000==0 or y%4==0 and y%100!=0 else 28
        def convert_str(yy,mm,dd):
            return '.'.join((str(yy), '0'*(2-len(str(mm)))+str(mm),\
                                     '0'*(2-len(str(dd)))+str(dd)))
        for i in range(12):
            if i + 1 in (1,3,5,7,8,10,12):
                for j in range(31):
                    self._days.append(convert_str(year, i+1, j+1))
            if i + 1 in (4,6,9,11):
                for j in range(30):
                    self._days.append(convert_str(year, i+1, j+1))
            if i + 1 is 2:
                for j in range(leapyear(year)):
                    self._days.append(convert_str(year, i+1, j+1))
    def __getitem__(self, index):
        return self._days[index]
