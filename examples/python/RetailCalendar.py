#!/usr/bin/env python3

"""
Convert from regular calendar dates to NRF calendar.

The calendar has an exact number of 7-day weeks.  Usually there
are 52 weeks in a year, but in some years the leftover days from
previous years force a 53-week year.

see also: http://www.nrf.com/modules.php?name=pages&sp_id=391
"""

import datetime

def retail_weekday(date) :
    """Convert a date to a weekday.

    DATE is a python datetime object.
    
    1 => Sunday, 2 => Monday, ... 7 => Saturday
    """
    #
    # add 1 to convert from 0-based to 1-based indexing
    # add 1 to convert from Monday-start to Sunday-start
    #
    wd = date.weekday() + 2             
    if wd > 7 :
        wd -= 7
    return wd

def get_wednesday_delta(date) :
    """Return number of days to the closest Wednesday.

    DATE is a python datetime object.
    
    0 == given day is Wednesday.  Thurs - Saturday return negative
    numbers.
    
    """
    return 4 - retail_weekday(date)

def start_retail_year(date) :
    """Return the date that is the start of the retail year for a date.

    DATE is a python datetime object.

    The algorithm starts the year on the first Wednesday in February
    prior to or on the input date.
    
    """
    wednesday_delta = get_wednesday_delta(date)
    wednesday = date + datetime.timedelta(wednesday_delta)

    r_year = wednesday.year
    if wednesday.month == 1 :
        r_year = r_year - 1

    start = datetime.date(r_year, 2, 1)
    oneday = datetime.timedelta(days=1)
    while retail_weekday(start) != 4 :
        start = start + oneday

    return start
    
def to_retail(date) :
    """Converts a date into a (year, season, month, week, day) tuple.

    DATE is a python datetime object.

    Year   is the retail year, not the calendar year of the input.
    Season is 1 for the first 26 weeks of the year, 2 for the rest.
    Month  is the retail month based on the 4-5-4 calendar definition.
           February is month 1.  The first month of a quarter is 
           always 4 weeks, the second 5 weeks, the third 4 weeks.  The
           exception is that the last month of a 53-week year has 5
           weeks.
    Week   is the week number based on 7-day weeks from the year start.
           It ranges from 1 to 53.
    Day    is the day number based on the retail_weekday function.

    BUG:   Some dates may not conform to the algorithm in that they 
           return the wrong week number.  Compare dates around 
           2001-02-06.
    """

    r_year = 0
    r_season = 0
    r_month = 0
    r_week = 0
    r_day = retail_weekday(date)

    anchor = start_retail_year(date)
    delta = date - anchor

    r_year = anchor.year
    
    r_week = 1 + int(delta.days / 7)
    if r_day < 4 :
        r_week = r_week + 1
    
    r_season = 1
    if r_week > 26 :
        r_season = 2
        
    r_month = 1
    t_week = r_week
    while t_week > 13 :
        r_month = r_month + 3
        t_week = t_week - 13
    if t_week > 9 :
        r_month = r_month + 2
    elif t_week > 4 :
        r_month = r_month + 1

    if r_month == 13 :
        r_month = 12
        
    return (r_year, r_season, r_month, r_week, r_day)

def process(start, end) :
    """Print SQL to UPDATE the mst_time table for a range of dates.

    START is the first date processed.
    END   is the last date processed.

    Dates are python datetime objects.

    """

    oneday = datetime.timedelta(days=1)
    end = end + oneday

    key = 1
    
    while start < end :
        (year, season, month, week, day) = to_retail(start)
        print ('UPDATE mst_time SET retail_year = %d, retail_week_of_year = %d, retail_month_num = %d, retail_season_of_year = %d WHERE time_key = %d' % (year, week, month, season, key))
        ##print (start, key, year, season, month, week, day)
        start = start + oneday
        key = key + 1

def to_date(str) :
    """Convert a string into a python datetime object.

    STR is in the format 'YYYY-MM-DD'.
    """

    year, month, date = map(int, str.split('-'))
    return datetime.date(year, month, date)

def main() :
    """Convert two command line parameters to dates and run process.
    """

    import sys

    args = sys.argv[1:]
    if len(args) < 2 :
        print ('Two dates are required')
        return

    start = to_date(args[0])
    end   = to_date(args[1])
    process(start, end)


if __name__ == '__main__' :
    main()

