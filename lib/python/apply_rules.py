#!/usr/bin/env python3

def apply_rules(initial, *rules) :
    """Take an initial object; apply rules in order; return results."""

    obj = initial
    for rule in rules :
        obj = rule(obj)

    return obj

def find_a_matching_rule(data, *rules) :
    """Pass DATA to each of RULES until one returns a True value."""

    for rule in rules :
        if rule(data) :
            return rule

    return None


def main() :
    """Test by generating some random numbers."""

    import random

    def rule1(x) :
        random.shuffle(x)
        return x

    def rule2(x) :
        y = len(x)
        return x[:(y//2)]

    def rule3(x) :
        x.sort(reverse=True)
        return x


    o1 = list(range(20))
    print (o1)
    
    o2 = apply_rules(o1, rule1, rule2, rule3)
    print (o2)
    
if __name__ == '__main__' :
    main()
