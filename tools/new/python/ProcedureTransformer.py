
import re

class ProcedureTransformer(object) :
    UNKNOWN = -1
    IN_PROCESS = 1
    SAFE = 2
    UNSAFE = 3

    def __init__(self, tc) :
        self.state = ProcedureTransformer.IN_PROCESS
        self.tc = tc
        self.local_schema = self.tc.get_local_schema()

        self.subs = []
        self.text = ''

    def process(self, text) :
        self.text = text
        self.change_creation_schema()
        self.change_default_schema()
        self.change_mandt()
        self.change_calls()
        self.change_table_schema()

        if self.state == ProcedureTransformer.IN_PROCESS :
            self.state = ProcedureTransformer.SAFE

    def get_state(self) :
        return self.state

    def get_text(self) :
        return self.text

    def change_creation_schema(self) :
        search_re = 'CREATE\s+PROCEDURE\s+_SYS_BIC\.(\w+)'
        replace = 'DROP PROCEDURE %s.\\1;\nCREATE PROCEDURE %s.\\1' % (self.local_schema, self.local_schema)
        self.text = re.sub(search_re, replace, self.text)

    def change_default_schema(self) :
        search_re = 'DEFAULT\s+SCHEMA\s+SAP_DDF'
        replace = 'DEFAULT SCHEMA %s' % self.tc.get_default_schema()
        self.text = re.sub(search_re, replace, self.text)

    def change_mandt(self) :
        search_re = 'SESSION_CONTEXT\w*\(\w*\'CLIENT\'\w*\)'
        if re.search(search_re, self.text) :
            self.state = ProcedureTransformer.UNSAFE
        replace = "'%s'" % self.tc.get_client()
        self.text = re.sub(search_re, replace, self.text)

    def change_calls(self) :
        call_list = self.scan_calls()
        if call_list :
            self.modify_calls(call_list)
            self.state = ProcedureTransformer.UNSAFE

    def scan_calls(self) :
        search_re = 'CALL\s+"_SYS_BIC"\."sap\.is\.ddf\.udf/(\w+)"'
        call_list = []
        for m in re.finditer(search_re, self.text) :
            callee = m.group(1)
            self.tc.process(callee)
            if self.tc.get_state(callee) == ProcedureTransformer.UNSAFE :
                call_list.append(callee)

        return call_list

    def modify_calls(self, call_list) :
        for callee in call_list :
            search_re = 'CALL\s+"_SYS_BIC"\."sap\.is\.ddf\.udf/(%s)"' % callee
            replace = 'CALL %s.%s' % (self.local_schema, callee)
            self.text = re.sub(search_re, replace, self.text)

    def change_table_schema(self) :
        for table in self.tc.get_tables_to_move() :
            search_re = '"%s"' % table
            if re.search(search_re, self.text) :
                self.state = ProcedureTransformer.UNSAFE
                replace = '%s."%s"' % (self.local_schema, table)
                self.text = re.sub(search_re, replace, self.text)

