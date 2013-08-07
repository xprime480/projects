
import rangetools
import itertools


ofmt = '%b %d %Y'

def test1() :
    itxt = '19600117'

    d = rangetools.make_date(itxt)
    o = d.strftime(ofmt)

    print (o)

def test2(a, b, c=1) :
    dr = rangetools.DateRange(a, b, c).make_gen()
    for d in dr() :
        print (d)

def test3() :

    names = []
    seqs  = []

    names.append('date_key')
    dr = rangetools.DateRange('20010101', '20010201', 7, '%Y%m%d')
    seqs.append([x.strftime(dr.fmt) for x in dr.make_gen()()])

    names.append('product_key')
    seqs.append(range(1,4))

    for qx in [dict(zip(names, x)) for x in itertools.product(*seqs)] :
        print (qx)

def div() :
    print ('========================')

if __name__ == '__main__' :
    test1()
    div()

    test2('20130101', '20130105')
    div()

    test2('20130101', '20130205', 7)
    div()
    try :
        test2('20130101', '20130205', -1)
    except Exception as e:
        print (str(e))
    div()


    test3()
    div()
