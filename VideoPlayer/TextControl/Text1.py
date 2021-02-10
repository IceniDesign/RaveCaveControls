
#https://pythonbasics.org/tkinter-label/#:~:text=The%20tkinter%20label%20widgets%20can,multiple%20times%20in%20a%20window).


from tkinter import *

class Window(Frame):
    def __init__(self, master=None):
        Frame.__init__(self, master)
        self.master = master
        self.pack(fill=BOTH, expand=1)
        
        text = Label(self, text="Just do it")
        text.place(x=70,y=90)
        #text.pack()
        
root = Tk()
app = Window(root)
root.wm_title("Tkinter window")
root.geometry("200x200")
root.mainloop()