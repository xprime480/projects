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

        logging.getLogger('main').warn('Failed to configure logging; using default.')

        formatter = logging.Formatter('%(asctime)s: %(levelname)s: %(message)s')

        handler = logging.FileHandler('%s.log' % self.name )
        handler.setLevel(logging.INFO)
        handler.setFormatter(formatter)

        fatalformatter = logging.Formatter('%(levelname)s: %(message)s')

        fatalhandler = logging.StreamHandler()
        fatalhandler.setLevel(logging.WARNING)
        fatalhandler.setFormatter(fatalformatter)

        logger = logging.getLogger('main')
        logger.addHandler(handler)
        logger.addHandler(fatalhandler)

        
    ################################################################
    #
    def __setup_log(self, config_file) :
        try : 
            logging.config.fileConfig(config_file)
            return True
        except Exception as e :
            pass
            #print ('Logging configuration error:', e, file=sys.stderr)

        return False

    ################################################################
    #
    def run(self) :
        """Should do something useful."""

        logger = logging.getLogger('main')
        logger.debug('This is a test')
        logger.fatal('To be or not to be')

################################################################
#
if __name__ == '__main__' :
    app = ApplicationBase('test')
    app.run()

