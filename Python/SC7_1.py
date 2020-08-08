try:
    a = int(input('Enter A :'))
    b = int(input('Enter B :'))
    c = a / b
    print("There is no exception.")
except ValueError as err:
    print("There is an exception. It is %s." % err)
    c = -1
except ZeroDivisionError as err:
    print("There is an exception. It is %s." % err)
    c = -1
print("quotient = " + str(c))
