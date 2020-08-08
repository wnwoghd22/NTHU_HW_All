import time

while true:
    t = time.localtime()
    print('\r%02d%02d%02d', %t.time_hour, t.time_min, t.time_sec), end = ' ')
    time.sleep(1)
