#!/usr/bin/python3

def likely_flag(v) :
    """Check that the current value is likely a flag."""

    t = str(v).lower()
    return t == '0' or t == '1'

def all_flags(vs) :
    """Check that all inputs are likely flags."""
    for v in vs :
        if not likely_flag(v) :
            return False
    return True

def all_floats(vs) :
    """Check that all inputs are convertible to float."""

    for v in vs :
        try :
            float(v)
        except ValueError :
            return False
    return True

def all_strings(vs) :
    """Check that all inputs are type string."""

    for v in vs :
        if type(v) != type('') :
            return False

    return True

