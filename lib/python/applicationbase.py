#!/usr/bin/env python3

"""Module for wrapping the logging functionality."""

import logging
import logging.config
import sys

################################################################
#
class ApplicationBase(object) :

    ################################################################
    #
    def __init__(self, name) :
        self.name = name
        self.setup_log()

    ################################################################
    #
    def setup_log(self) :
        if self.__setup_log('%s_log.conf' % self.name) :
            return

        formatter = logging.Formatter('%(asctime)s: %(levelname)s: %(message)s')

        handler = logging.FileHandler('%s.log' % self.name )
        handler.setLevel(logging.DEBUG)
        handler.setFormatter(formatter)

        fatalformatter = logging.Formatter('%(levelname)s: %(message)s')

        fatalhandler = logging.StreamHandler()
        fatalhandler.setLevel(logging.WARNING)
        fatalhandler.setFormatter(fatalformatter)

        logger = logging.getLogger('root')
        logger.addHandler(handler)
        logger.addHandler(fatalhandler)
        logger.setLevel(logging.DEBUG)

        logger.warn('Failed to configure logging; using default.')
        
    ################################################################
    #
    def __setup_log(self, config_file) :
        try :
            with open(config_file) as f :
                logging.config.fileConfig(f)
                return True
        except IOError as e :
            print (e, file=sys.stderr)

        return False

    ################################################################
    #
    def run(self) :
        """Should do something useful."""

        logger = logging.getLogger('root')
        logger.debug('This is a test')
        logger.fatal('To be or not to be')

################################################################
#
if __name__ == '__main__' :
    app = ApplicationBase('test')
    app.run()

