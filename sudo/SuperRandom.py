#!/usr/bin/python

import Board
import random

def main(order) :
    size = order * order
    board = Board.Board(order)

    stop_after_n_failures = 50
    failures = 0
    successes = 0
    clues = []

    while not board.is_done() and failures < stop_after_n_failures :
        r,c = random.randint(1,size),random.randint(1,size)
        vs = board.get_cell(r,c)
        if len(vs) > 1 :
            ix = random.randrange(1,len(vs))
            try :
                clue = (r,c,list(vs)[ix])
                board.set_cell(*clue)
                failures = 0
                successes = successes + 1
                clues.append(clue)
            except Exception as e:
                failures = failures + 1
                print e
        else : 
            failures = failures + 1

    board.show()
    
    print
    print "solved with %d clues" % successes
    print

    board_with_clues_only = Board.Board(order)
    for c in clues :
        board_with_clues_only.set_cell_without_update(*c)
    board_with_clues_only.show()
    

if __name__ == '__main__' :
    import sys
    order = 5
    try :
        order = int(sys.argv[1])
    except :
        pass
    main(order)
