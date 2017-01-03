This file defines a pair of functions that are inverses.  The first
is a mapping f : N -> N x N, the second is g : N x N -> N.  Here an
element of N x N is represented by a tuple (a,b).

The exact form of the functions derives from a proof that N ~ N x N.
Draw a grid of elements of N x N:

(0,0) (1,0) (2,0) ...

(0,1) (1,1) (2,1) ...

(0,2) (1,2) (2,2) ...

.
.
.

Order the pairs as such:  (0,0), (0,1), (1,0), ...
where the continuation is from lower left to upper right along
successive diagonals.  It is clear that with this ordering, each
pair corresponds to an element of N.

It would be nice to have a data type that actually implements the
naturals, however we will ignore this detail for now.  In the
remainder of this code we will use Ints and assume values >= 0.

Let us define this successor function.

> pair_succ :: (Int, Int) -> (Int, Int)
> pair_succ (a,b)
>    | b == 0    = (0, a+1)
>    | otherwise = (a+1, b-1)

Using this function, we can easily define a sequence of pairs.

> pairs :: [(Int, Int)]
> pairs = (0,0) : (map pair_succ pairs)

Also of use is the sequence of natural numbers

> nats :: [Int]
> nats = 0 : (map (1 +) nats)

The function from NxN -> N is fairly straightforward -- it has a closed
form solution:

> g :: (Int, Int) -> Int
> g (a,b) = t + a
>    where n = a + b
>          t = n * (n + 1) `div` 2

From the diagram above, it should be easy to see the derivation of
the formula for g.  t tells us how many integers are consumed by 
completed diagonals.  It is in the known form of the equation for 
triangular numbers, which the upper left corner is, of course.  The 
remaining addition of a tells us how far up the incomplete diagonal
we are.  Adding these gives the value in N to which (a,b) maps.

Perhaps this knowledge will be useful to construct the inverse function
f : N -> N x N.

First, let us find a simple solution that works.  Sinxe NxN is 
isomorphic to N, we could just count from the beginning.  That is
what the pairs function above does, so we just have to skip to 
the correct value.

> f0 :: Int -> (Int, Int)
> f0 n = head (drop n pairs)

The trouble is, this gets pretty slow as n gets large and we 
have to realize n values that get thrown away.

