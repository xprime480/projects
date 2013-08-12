#!/usr/bin/env python3

class TestNewStyle(object) :

    allowable_attrs = ['catfish', 'banana', 'spam']

    def __getattr__(self, attr) :
        attr = attr.lower()
        if attr in self.allowable_attrs :
            if 'spam' == attr :
                return 'Yum'
            return attr
        return None

    def __setattr__(self, attr, value) :
        pass

    def __delattr__(self, attr) :
        pass


Q = TestNewStyle()
print(Q.catfish)
print(Q.hotdog)
print(Q.spam)
print(Q.Spam)
TestNewStyle.allowable_attrs.append('hotdog')
print(Q.HotDog)

