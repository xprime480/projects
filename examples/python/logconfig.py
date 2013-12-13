#!/usr/bin/env python3

import logging
import logging.config
import sys

class Example(object) :
    def __init__(self, base='test') :
        self.base = base

    def run(self) :
        self.config_log()
        self.emit_messages()

    def config_log(self) :
        config_file = '%s_log.conf' % self.base
        try :
            with open(config_file) as f :
                logging.config.fileConfig(f)
        except IOError as e :
            print (e, file=sys.stderr)

    def emit_messages(self) :
        logger = logging.getLogger(self.base)
        logger.debug('debug message')
        logger.info('info message')
        logger.warning('warning message')
        logger.error('error message')
        logger.critical('critical message')
        try :
            raise Exception('Oh no!!!!')
        except Exception as e :
            logger.exception(repr(e))
        logger.debug('All Done')


if __name__ == '__main__' :
    if sys.argv[1:] : 
        name = sys.argv[1]
    else :
        name = 'julius'
    eg = Example(name)
    eg.run()
