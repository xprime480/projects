#!/usr/bin/env python3

import logging

def setup_log(base) :
    formatter = logging.Formatter('%(asctime)s: %(levelname)s: %(message)s')

    handler = logging.FileHandler('%s.log' % base )
    handler.setLevel(logging.INFO)
    handler.setFormatter(formatter)

    fatalformatter = logging.Formatter('%(levelname)s: %(message)s')

    fatalhandler = logging.StreamHandler()
    fatalhandler.setLevel(logging.WARNING)
    fatalhandler.setFormatter(fatalformatter)

    logger = logging.getLogger('main')
    logger.addHandler(handler)
    logger.addHandler(fatalhandler)

    return logger

def setup_alt(base) :
    handler = logging.FileHandler('%s_bad.log' % base)

    logger = logging.getLogger('detail')
    logger.addHandler(handler)

    logger.warning('Tell me a secret.')

def test(base) :

    logger = logging.getLogger('main')
    logger.debug('This is a test')
    logger.fatal('To be or not to be')

    tracer = logging.getLogger('detail')
    tracer.warning('Tell me a secret.')

if __name__ == '__main__' :
    base = 'loggingexample'

    setup_log(base)
    setup_alt(base)
    test(base)
