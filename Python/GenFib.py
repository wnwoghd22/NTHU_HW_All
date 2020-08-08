def fib():
    yield 0
    yield 1
    fn_2 = 0
    fn_1 = 1
    while True:
        fn = fn_2 + fn_1
        yield fn
        fn_2, fn_1 = fn_1, fn
