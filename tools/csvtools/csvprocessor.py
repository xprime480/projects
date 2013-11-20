#!/usr/bin/python3

import csvfileio

#
# Framework for processing CSV files

class CsvProcessor(object) :
    def __init__(self) :
        self.current_input  = None
        self.current_output = None

    def read(self, *files) :
        self.start_read()
        for f in files :
            self.current_input = f
            with csvfileio.CsvFileIo(f, False) as rdr :
                if not self.pre_row_processing(rdr.fieldnames) :
                    continue
                for row in rdr :
                    self.process_row(row)
                self.post_row_processing()
            self.current_input = None
        self.finish_read()

    def write(self, *files) :
        headers = self.start_write()
        for f in files :
            self.current_output = f
            with csvfileio.CsvFileIo(f, True, headers) as rtr :
                rtr.writeheader()
                for row in self.get_next_output_row() :
                    rtr.write_row(row)
            self.current_output = None
        self.finish_write()


    def start_read(self) :
        pass

    def pre_row_processing(self, rdr) :
        return True

    def process_row(self, row) :
        return True

    def post_row_processing(self) :
        pass

    def finish_read(self) :
        pass

    def start_write(self) :
        return None

    def get_next_output_row(self) :
        pass

    def finish_write(self) :
        pass

