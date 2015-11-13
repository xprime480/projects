
import xml.parsers.expat

class XmlProcedureReader(object) :
    def __init__(self) :
        self.head_data = []
        self.defn_data = []
        self.locl_data = []
        self.in_head = False
        self.in_defn = False
        self.in_locl = False

        self.parser = xml.parsers.expat.ParserCreate()
        self.parser.StartElementHandler  = self.start_element
        self.parser.EndElementHandler    = self.end_element
        self.parser.CharacterDataHandler = self.char_data

    # 3 handler functions

    def start_element(self, name, attrs):
        if name == 'header' :
            self.in_head = True
        elif name == 'definition' :
            self.in_defn = True
        elif name == 'localTableType' :
            self.in_locl = True

    def end_element(self, name):
        if name == 'header' :
            self.in_head = False
        elif name == 'definition' :
            self.in_defn = False
        elif name == 'localTableType' :
            self.in_locl = False

    def char_data(self, data):
        if self.in_head :
            self.head_data.append(data)
        elif self.in_defn :
            self.defn_data.append(data)
        elif self.in_locl :
            self.locl_data.append(data)

    def parse_file(self, name) :
        f = open(name)
        self.parser.ParseFile(f)

    def results(self) :
        return ''.join(self.head_data), ''.join(self.defn_data), ''.join(self.locl_data)

    def write(self, name) :
        with open(name, "w") as f : 
            h, d, l = self.results()
            f.write(h)
            f.write(d)
            f.write(l)

if __name__ == '__main__' :
    p = XmlProcedureReader()
    p.parse_file('/home/i809989/tmp/test.xml')
    p.write('/home/i809989/tmp/test.sql')

