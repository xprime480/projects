#!/usr/bin/python

import Cell

class BoardException(Exception) :
    def __init__(self, msg) :
        self.msg = msg

class Board(object) :
    def __init__(self, order) :
        self.board = []
        self.order = order
        self.size  = order * order
        for r in range(self.size) :
            row = []
            for c in range(self.size) :
                row.append(Cell.Cell(self.size))
            self.board.append(row)
            
    def is_done(self) :
        for row in self.board :
            for cell in row :
                if not cell.is_set() :
                    return False
        return True
        
    def show(self) :
        self.print_horz_border()
        r = 0
        for row in self.board :
            print '||',
            c = 0
            for cell in row :
                self.show_cell(cell)
                c = c + 1
                if (c%self.order) == 0 :
                    print '||',
            print
            r = r + 1
            if (r%self.order) == 0 :
                self.print_horz_border()

    def show_cell(self, cell) :
        if cell.is_set() :
            print '%2d' % cell.get_value(),
        else :
            print '__',

    def print_horz_border(self) :
        count = 5 + 3 * (self.size + self.order - 1)
        print count * '='

    def set_cell(self, r, c, v) :
        self.set_cell_without_update(r, c, v)
        self.update(r, c, v)

    def update(self, r, c, v) :
        self.__propagate(r, c, v)
        self.__check_all()

    def set_cell_without_update(self, r, c, v) :
        self.board[r-1][c-1].set(v)

    def get_cell(self, r, c) :
        return self.board[r-1][c-1].get()

    def __propagate(self, r, c, v) :
        self.__remove_from_row(r, v)
        self.__remove_from_col(c, v)
        self.__remove_from_block(r, c, v)

    def __remove_from_row(self, r, v) :
        for c in range(1,self.size+1) :
            self.__probe(r, c, v)
            
    def __remove_from_col(self, c, v) :
        for r in range(1,self.size+1) :
            self.__probe(r, c, v)

    def __remove_from_block(self, r, c, v) :
        rlo = 1+self.order*int((r-1)/self.order)
        rhi = self.order+rlo
        clo = 1+self.order*int((c-1)/self.order)
        chi = self.order+clo

        for rr in range(rlo, rhi) :
            for cc in range(clo, chi) :
                self.__probe(rr, cc, v)

    def __probe(self, r, c, v) :
        cell = self.board[r-1][c-1]
        if not cell.is_set() :
            if cell.remove([v]) :
                self.__propagate(r, c, cell.get_value())

    def __check_all(self) :
        in_progress = True
        while in_progress :
            in_progress = False

            for r in range(1,self.order+1) :
                in_progress = in_progress or self.__check_row(r)

            for c in range(1,self.order+1) :
                in_progress = in_progress or self.__check_col(c)

            for r in range(1,self.size+1,self.order) :
                for c in range(1,self.size+1,self.order) :
                    in_progress = in_progress or self.__check_block(r, c)

    def __check_row(self, r) :
        cells = [(r,c) for c in range(1,self.size+1)]
        return self.__check_cell_group(cells)

    def __check_col(self, c) :
        cells = [(r,c) for r in range(1,self.size+1)]
        return self.__check_cell_group(cells)

    def __check_block(self, r, c) :
        cells = [(rr,cc) for rr in range(r,r+self.order) 
                 for cc in range(c,c+self.order)]
        return self.__check_cell_group(cells)

    def __check_cell_group(self, group) :
        cells = [self.board[r-1][c-1] for r,c in group]
        free_indexes = [(r,c) for r,c in group 
                        if not self.board[r-1][c-1].is_set()]
        if len(free_indexes) == 0 :
            return False
        
        set_values = [c.get_value() for c in cells if c.is_set()]
        unset_values = set(range(1,self.size+1)).difference(set_values)
        del(cells, set_values)

        for v in unset_values :
            n = 0
            p = None
            for r,c in free_indexes :
                if v in self.board[r-1][c-1].get() :
                    n = n + 1
                    p = (r,c)

            if n == 1 :
                self.set_cell(p[0], p[1], v)
                return True

        return False

def execute(data, order=3) :
    b2 = Board(order)
    for d in data :
        b2.set_cell(*d)
    print
    print
    b2.show()


def test() :
    # simple test data to prove points
    #
    b1_data = [
        (2,1,1),
        (3,4,1),
        (4,7,1),
        (7,8,1),
        (7,1,2),
        (7,2,3),
        (7,3,4),
        (8,1,5),
        (8,2,6),
        (8,3,7),
        (9,3,1),
        (9,2,8)
    ]

    execute(b1_data)

    # An "easy" mode Sudoku from websudoku.com
    #
    b2_data = [
        (1,2,5),
        (1,4,9),
        (1,6,4),
        (1,8,1),
        (1,9,8),
        (2,5,2),
        (2,7,9),
        (3,1,4),
        (3,4,7),
        (3,6,8),
        (3,7,2),
        (3,9,5),
        (4,1,5),
        (4,7,3),
        (4,9,9),
        (5,2,4),
        (5,4,1),
        (5,6,3),
        (5,8,6),
        (6,1,2),
        (6,3,7),
        (6,9,1),
        (7,1,1),
        (7,3,9),
        (7,4,4),
        (7,6,6),
        (7,9,3),
        (8,3,5),
        (8,5,1),
        (9,1,3),
        (9,2,7),
        (9,4,2),
        (9,6,9),
        (9,8,5)
    ]

    execute(b2_data)

    # Can't set a cell twice
    #
    b3_data = [(1,1,1), (1,1,2)]
    try :
        execute(b3_data)
        print "Expected an exception"
    except :
        pass

    # Try a different order
    #
    b4_data = [
        (1,1,1),
        (1,4,3),
        (2,2,2),
        (3,3,3),
        (4,4,4)
    ]
    execute(b4_data, 2)

    try :
        execute(b4_data, 4)
        print "Expected an exception"
    except :
        pass

    execute([(13,13,25), (13,1,1)], 5)

if __name__ == '__main__' :
    test()
