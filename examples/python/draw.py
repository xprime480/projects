
from Tkinter import Tk,Button,Canvas,LAST,FLAT

class Goofy(Tk) :
    """Goofy widget that knows how to draw:

    - an optional quit button (on creation)
    - a grid of dots
    - various sizes of bullseye logos
    """
    
    def __init__(self, button=True) :
        """Draw a button if requested and a blank canvas"""
        Tk.__init__(self)
        self['bg'] = "white"
        if button : 
            self.b = Button(text="Quit",
                            command=self.destroy,
                            relief=FLAT,
                            bg="white")
            self.b.pack()
        self.c = Canvas(bg="white")
        self.c.pack()

        self.colors = ["red", "yellow", "blue",
                       "green", "purple", "orange",
                       "black", "white", "grey"]


    def make_dot_grid(self, size, spacing) :
        """Make a grid"""

        xcount = 1 + int(self.c.cget("width"))  / spacing
        ycount = 1 + int(self.c.cget("height")) / spacing
        
        for x in xrange(xcount) :
            for y in xrange(ycount) :
                self.c.create_oval(x * spacing,
                                   y * spacing,
                                   x * spacing + size,
                                   y * spacing + size,
                                   fill="black")

    def newcolor(self, *dontmatch) :
        from random import choice
        while True :
            t = choice(self.colors)
            if t not in dontmatch :
                return t
        

    def make_logo(self, ulx, uly, scale, outer=None, inner=None) :
        """Draw a logo at a given position and scale factor."""
        
        width = min(max(1,scale*2), 3)
        if not inner :
            inner = self.newcolor(outer)
        if not outer :
            outer = self.newcolor(inner)
        
        self.c.create_oval(ulx+scale*20, uly+scale*20,
                           ulx+scale*80, uly+scale*140,
                           fill=outer, width=width)
        self.c.create_oval(ulx+scale*40, uly+scale*40,
                           ulx+scale*60, uly+scale*100,
                           fill=inner, width=width)
        self.c.create_line(ulx, uly,
                           ulx+scale*50,
                           uly+scale*80,
                           arrow=LAST, width=width)

    def draw_logos(self) :
        """Draw a number of logos in predefined locations."""
        self.make_logo(0,   0,   1)
        self.make_logo(100, 0,   0.5,   inner="blue")
        self.make_logo(150, 100, 0.333, outer="cyan")
        self.make_logo(200, 0,   1.5,   inner="green", outer="white")

    def t1(self) :
        """Draw a grid under some logos"""
        self.make_dot_grid(2, 10)
        self.draw_logos()
        self.mainloop()

    def t2(self) :
        """Draw a grid over some logos"""
        self.draw_logos()
        self.make_dot_grid(2, 10)
        self.mainloop()

if '__main__' == __name__ :
    """Test"""
    Goofy(button=False).t1()
    Goofy(            ).t2()
