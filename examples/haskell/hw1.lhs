This file implements the solutions to Homework 1 from 
http://www.cis.upenn.edu/~cis194/spring13/lectures.html

Exercise 1 is to define the functions 

    toDigits
and
    toDigitsRev

which will expand a strictly positive integer into a list of digits 
while returning an empty list for non-positive integers.  

The "natural" implementation expands from the beginning so define it
first:

> toDigitsRev :: Integer -> [Integer]
> toDigitsRev n
>    | n <= 0    = []
>    | otherwise = mod n 10 : (toDigitsRev (div n 10))

With toDigitsRev defined, toDigits is trivial.

> toDigits :: Integer -> [Integer]
> toDigits = reverse . toDigitsRev

Exercise 2 is to define the function
   
    doubleEveryOther

which doubles every other element of a list of integers, starting
from the right.

For example, 

    doubleEveryOther [1 2 3] -> [1 4 3]

First we define a function to double every other digit starting
from the left.  An empty or singleton list is returned unchanged.

> doubleEveryOtherL :: [Integer] -> [Integer]
> doubleEveryOtherL []         = []
> doubleEveryOtherL (x:[])     = x : []
> doubleEveryOtherL (x:y:rest) = x:(2*y):(doubleEveryOtherL rest)

Using this definition it is easy to implement doubleEveryOther

> doubleEveryOther :: [Integer] -> [Integer]
> doubleEveryOther = reverse . doubleEveryOtherL . reverse

Exercise 3 is to define the function

    sumDigits

which takes a list of integers and computes the sum of the digits of 
all of the values.

This is fairly straightforward if we take care with the case where
an entry has multiple digits, as we must recursively sum its digits.

> sumDigits :: [Integer] -> Integer
> sumDigits [] = 0
> sumDigits (x:xs) 
>     | x >= 10   = sumDigits (toDigits x) + (sumDigits xs)
>     | otherwise = x + (sumDigits xs)

Exercise 4 is to define the function 

    validate,

which validates a putative credit card number using the following
algorithm:
     1. Double each digit from the right
     2. Sum the results
     3. Take the remainder mod 10
     4. Number is valid if result is 0

First define a helper function to handle steps 1 and 2.

> validateHelper :: Integer -> Integer
> validateHelper = sumDigits . doubleEveryOther . toDigits

Now apply the modulus and test the result.

> validate :: Integer -> Bool
> validate n = 0 == (validateHelper n) `mod` 10

-----------------------------------------------------------------------------


