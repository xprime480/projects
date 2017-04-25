In this file we solve the Tower of Hanoi problem for n disks and 3 pegs, 
then generalize for m pegs.

Exercise 5 is the original Tower of Hanoi with 3 pegs.

The first task is to define data types:

> type Peg = String
> type Move = (Peg,Peg)

The algorithm to move a stack of N disks from src to dst using hlp is
quite straightforward:
    1. Move the substack of N-1 disks from src to hlp using dst
    2. Move the single disk N from src to dst
    3. Move the substack of N-1 dists from hlp to dst using src

The recursion stops when moving a stack of 1 disk:  just move src to
dst.

With that in mind, we define the moveSingle function to handle case 2.
It does not matter what disk is on top, the move is the same.  The 
function returns a list of the single move.

> moveSingle :: Peg -> Peg -> [Move]
> moveSingle src dst = [(src,dst)]

Now define the function to move a stack, using the algorithm above.
The function returns a combined list of moves from all the steps.

> moveStack :: Integer -> Peg -> Peg -> Peg -> [Move]
> moveStack 1 src _ dst   = moveSingle src dst
> moveStack n src hlp dst = moveStack (n-1) src dst hlp ++ (moveSingle src dst) ++ (moveStack (n-1) hlp src dst)

Define the main function.

> hanoi :: Integer -> Peg -> Peg -> Peg -> [Move]
> hanoi n src hlp dst = moveStack n src hlp dst

Exercise 6 is the problem with 4 pegs.

The definition of moveSingle stays the same.  We will generalize the 
defintion of moveStack to take a list of helper pegs. We observe that
the smallest disks move the most often.  If we can reduce the number of
moves of the smaller disks, the process will complete proportionally
faster.  The strategy is as follows:
    1. If we have n disks and 1 helper, the algorithm is the previously
       solved problem
    2. If we have n disks and k helpers, n > k, we execute the following
       steps
         a. recursively move disks 1..(n-k) from src to h_1 with helpers
            [h_2, h_3, ... , dst]
         b. flip the stack at src onto dst via [h_2, h_3, ..., h_k]
         c. recursively move disks 1..(n-k) from h_1 to dst with helpers
            [h_2, h_3, ..., src]

Flipping the stack involves moving the smallest disk from the source to
the first helper, flipping the remainder of the stack from src onto dst
using the remaining helpers, and finally moving the smallest disk from the
first helper to the destination.  For flexibility, we assume the last
helper is the destination so we can specialize for one disk to be flipped
without regard to how many helpers are available.

> flipStack :: Integer -> Integer -> Peg -> [Peg] -> [Move]
> flipStack first last src []
>    | first > last  = []
>    | otherwise     = [("Error", "no helper pegs")]
> flipStack first last src (h:[])
>    | first > last  = []
>    | first == last = moveSingle src h
>    | otherwise     = [("Error", "no helper pegs")]
> flipStack first last src (h:hs)
>    | first > last  = []
>    | first == last = moveSingle src (head (reverse hs))
>    | otherwise     = moveSingle src h ++ (flipStack (first+1) last src hs) ++ (moveSingle h (head (reverse hs)))

> moveStack' :: Integer -> Peg -> Peg -> [Peg] -> [Move]
> moveStack' 0 _ _ _            = []
> moveStack' 1 src dst _        = moveSingle src dst
> moveStack' n src dst []       = [("error", "no helper pegs")]
> moveStack' n src dst (hlp:[]) = moveStack n src hlp dst
> moveStack' n src dst (h:hs)   = moveStack' (n-(toInteger (length hs))-1) src h (hs ++ [dst]) ++ (flipStack (n-(toInteger (length hs))) n src (hs++[dst])) ++ (moveStack' (n-(toInteger (length hs))-1) h dst (hs ++ [src]))

The final function has the same general form as the hanoi function.
 
> hanoi' :: Integer -> Peg -> Peg -> [Peg] -> [Move]
> hanoi' n src dst hlp = moveStack' n src dst hlp


hanoi' 4 _1 _4 [_2 _3]
moveStack' 4 _1 _4 [_2 _3]
moveStack' 2 _1 _2 [_3, _4] ++ (flipStack 3 4 _1 [_3, _4]) ++ (moveStack' 2 _2 _4 [_3, _1])
(flipStack 1 2 _1 [_4, _2]) ++ (flipStack 3 4 _1 [_3, _4]) ++ (moveStack' 2 _2 _4 [_3, _1])
[(_1, _4)] ++ (flipStack 2 2 _1 [_2]) ++ [(_4, _2)] ++ (flipStack 3 4 _1 [_3, _4]) ++ (moveStack' 2 _2 _4 [_3, _1])
[(_1, _4), (_1, _2), (_4, _2)] ++ (flipStack 3 4 _1 [_3, _4]) ++ (moveStack' 2 _2 _4 [_3, _1])
[(_1, _4), (_1, _2), (_4, _2), (_1, _3), (_1, _4), (_3, _4)] ++ (moveStack' 2 _2 _4 [_3, _1])
[(_1, _4), (_1, _2), (_4, _2), (_1, _3), (_1, _4), (_3, _4)] ++ (flipStack 1 2 _2 ([_1, _4]))
[(_1, _4), (_1, _2), (_4, _2), (_1, _3), (_1, _4), (_3, _4)] ++ ([(_2, _1)] ++ (flipStack 2 2 _2 [_4]) ++ [(_1, _4)])
[(_1, _4), (_1, _2), (_4, _2), (_1, _3), (_1, _4), (_3, _4), (_2, _1), (_2, _4), (_1, _4)]

