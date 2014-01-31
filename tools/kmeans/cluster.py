

class Cluster(object) :
    def __init__(self, centroid) :
        self.centroid = centroid
        self.items    = []

    def add_item(self, item) :
        self.items.append(item)

    def get_items(self) :
        return self.items[:]

    def get_centroid(self) :
        return self.centroid

    def __repr__(self) :
        return '%s with centroid %s' % (str(self.items), str(self.centroid))


