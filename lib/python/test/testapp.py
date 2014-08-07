#!/usr/bin/env python3

import logging
import unittest

import applicationbase

class TestApp(applicationbase.ApplicationBase) :
    def __init__(self, name='tests') :
        super().__init__(name)

    def run(self) :
        logging.getLogger('main').info('Starting tests...')
        unittest.main()

