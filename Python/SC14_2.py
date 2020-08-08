import tkinter
import random

ROCK,SCISSORS,PAPER = (chr(0x270a),chr(0x270c),chr(0x270b))
D = {0:ROCK,1:SCISSORS,2:PAPER}

computers_hand = ' '
players_hand = ' '
_status = ' '
_flag = True

root = tkinter.Tk()
f = tkinter.Frame(root, borderwidth = 7)

l0_str = tkinter.StringVar()
l1_str = tkinter.StringVar()
l2_str = tkinter.StringVar()

def play_game(_p):
    global computers_hand, players_hand, _flag
    if _flag:
        _flag = False
        _c = random.randint(0,2)
        players_hand = 'you clicked '+D[_p]
        l0_str.set(players_hand)
        computers_hand = D[_c]
        l1_str.set(computers_hand)
        if _c == _p:
            _status = 'Tied!'
        elif (_c==0 and _p==1)or(_c==1 and _p==2)or(_c==2 and _p==0):
            _status = 'Computer Wins'
        else:
            _status = 'User Wins'
        l2_str.set(_status)

def retry():
    global _flag
    l0_str.set(' ')
    l1_str.set(' ')
    l2_str.set(' ')
    _flag = True

l0 = tkinter.Label(f, text = 'Your Hand : ', font = ('Courier', 25))
l0_r = tkinter.Label(f, textvariable = l0_str, font = ('Courier', 25))
l1 = tkinter.Label(f, text = 'Computer\'s hand : ', font = ('Courier', 25))
l1_r = tkinter.Label(f, textvariable = l1_str, font = ('Courier', 25))
l2 = tkinter.Label(f, text = 'Status : ', font = ('Courier', 25))
l2_r = tkinter.Label(f, textvariable = l2_str, font = ('Courier', 25))

b0 = tkinter.Button(f, text = ROCK, command=lambda:play_game(0), \
        font = ('Courier', 25))
b1 = tkinter.Button(f, text = SCISSORS, command=lambda:play_game(1), \
        font = ('Courier', 25))
b2 = tkinter.Button(f, text = PAPER, command=lambda:play_game(2), \
        font = ('Courier', 25))

retry_b = tkinter.Button(f, text = 'Retry', command=retry, \
        font = ('Courier',25))
quit_b = tkinter.Button(f, text = 'Quit', command=root.destroy, \
        font = ('Courier', 25))

f.grid(row=0, column=0)
[w.grid(row=i, column=0) for i,w in enumerate([l0,l1,l2])]
[w.grid(row=0, column=i+1) for i,w in enumerate([b0,b1,b2])]
l0_r.grid(row=0,column=4)
l1_r.grid(row=1,column=1)
l2_r.grid(row=2,column=1)
retry_b.grid(row=2,column=3)
quit_b.grid(row=2, column=4)

f.mainloop()
