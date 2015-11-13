
import XmlProcedureReader
import ProcedureTransformer
import os.path
import glob
import re

class TransformationController(object) :
    def __init__(self, indir, outdir, tables) :
        self.indir = indir
        self.outdir = outdir
        self.processed = {}
        self.order = []
        self.tables_to_move = tables[:]
        self.locals = []
        self.local_text = ''

    def process(self, pattern) :
        for file in self.get_matching_files_in(pattern) :
            self.process_one(file)
        self.transform_locals()

    def export(self) :
        self.export_locals()
        for file in self.order :
            self.export_file(file)
                
    def make_master(self, dest) :
        with open(dest, "w") as f :
            f.write(self.local_text)
            f.write('\n\n')

            for file in self.order :
                pt = self.processed[file]
                f.write(pt.get_text())
                f.write(';\n\n')

    def get_state(self, pattern) :
        if self.processed.has_key(pattern) :
            return self.processed[pattern].get_state()
        return ProcedureTransformer.UNKNOWN

    def get_tables_to_move(self) :
        return self.tables_to_move

    def process_one(self, file) :
        base = self.extract_file_base(file)
        if self.processed.has_key(base) :
            return

        pt = ProcedureTransformer.ProcedureTransformer(self)
        text, local_text = self.get_procedure_contents(file)
        pt.process(text)
        if pt.get_state() == ProcedureTransformer.ProcedureTransformer.UNSAFE :
            self.order.append(base)
            self.locals.append(local_text)

        self.processed[base] = pt

    def get_matching_files_in(self, name) :
        wc = os.path.join(self.indir, '%s.procedure' % name)
        return glob.glob(wc)

    def extract_file_base(self, path) :
        h,t = os.path.split(path)
        b,x = os.path.splitext(t)
        return b

    def get_procedure_contents(self, f) :
        p = XmlProcedureReader.XmlProcedureReader()
        p.parse_file(f)

        h, d, l = p.results()
        return '%s%s' % (h,d), l

    def get_local_schema(self) :
        return 'davismic'

    def get_default_schema(self) :
        return 'SAPRMT'

    def get_client(self) :
        return '800'

    def transform_locals(self) :
        self.local_text = '\n'.join(self.locals)

        search_re = 'CREATE\s+TYPE\s+(\w+)'
        types = []
        for m in re.finditer(search_re, self.local_text) :
            t = m.group(1)
            if t not in types :
                types.append(t)

        local_schema = self.get_local_schema()
        for t in types :
            search_re = 'CREATE\s+TYPE\s+(\%s)' % t
            replace = 'DROP TYPE %s.\\1;\nCREATE TYPE %s.\\1' % (local_schema, local_schema)
            self.local_text = re.sub(search_re, replace, self.local_text)

    def export_locals(self) :
        out = os.path.join(self.outdir, 'locals.sql')
        with open(out, "w") as f :
            f.write(self.local_text)

    def export_file(self, file) :
        pt = self.processed[file]
        out = os.path.join(self.outdir, '%s.sql' % file)
        with open(out, "w") as f :
            f.write(pt.get_text())

