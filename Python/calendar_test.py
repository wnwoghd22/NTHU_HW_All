import tkinter
from operator import add, sub
root = tkinter.Tk()
f = tkinter.Frame(root, borderwidth = 5)

import datetime
today = datetime.date.today()
current_year, current_month = today.year, today.month
import calendar
cal = calendar.TextCalendar(6)

calstr = tkinter.StringVar()
calstr.set(cal.formatmonth(current_year, current_month))

l =tkinter.Label(f,textvariable=calstr,justify=tkinter.LEFT,font=('Courier',12))
b = tkinter.Button(f,text='Quit',command=root.destroy)

def shift_month(add_or_sub):
    global current_year, current_month
    current_month = add_or_sub(current_month,1)
    if current_month == 0:
        current_month = 12
        current_year -= 1
    if current_month == 13:
        current_month = 1
        current_year += 1
    calstr.set(cal.formatmonth(current_year, current_month))

pm = tkinter.Button(f, text='Prev', command=lambda:shift_month(sub))
nm = tkinter.Button(f, text='Next', command=lambda:shift_month(add))

f.grid(row=0, column=0)
l.grid(row=0, column=0, columnspan=3)
[w.grid(row=1,column=i) for i, w in enumerate([pm,b,nm])]

f.mainloop()
