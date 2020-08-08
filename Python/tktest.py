import tkinter

root = tkinter.Tk()
f = tkinter.frame(root)
f.pack()
l = tkinter.label(f, text = 'hello world')
l.pack()
b = tkinter.button(f, text = 'quit', command = root.destroy())
b.pack()
