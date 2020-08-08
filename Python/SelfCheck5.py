x = list(input("string: "))
y = list(input("prohibited string: "))

z = [x[i] for i in range(len(x)) if x[i] not in y]

print(x)
print(y)
print(z)

