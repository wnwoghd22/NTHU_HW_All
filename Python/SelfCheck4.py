s1 = input('Enter a string:\n')
s2 = input('Enter another string:\n')

if len(s1) == len(s2):
    print('First string: ',s1 , '(length ',len(s1), ')')
    print('Second string: ',s2 , '(length ',len(s2), ')')
elif len(s1) > len(s2):
    print('Shorter string: ', s2, '(length ',len(s2), ')')
    print('Longer string: ', s1, '(length ',len(s1), ')')
else:
    print('Shorter string: ', s1, '(length ', len(s1), ')')
    print('Longer string: ', s2, '(length ', len(s2), ')')
