class Person:
    def __init__(self, name):
        self._name = name
        self._mother = None
        self._children = []
    def __repr__(self):
        return self.__class__.__name__+"('"+self._name+"')"

    @property
    def name(self):
        return self._name

    @property
    def children(self):
        return self._children
    
    def add_children(self,*children):
        for _name in children:
            self._children.append(Person(_name))
            self._children[-1]._mother = self

    @property
    def mother(self):
        return self._mother

    @property
    def sisters(self):
        return [c for c in self._mother.children if c != self]

    @property
    def aunts(self):
        return self._mother.sisters

    @property
    def grandmother(self):
        return self._mother.mother

    @property
    def grandchildren(self):
        _ls = []
        for c in self._children:
            _ls += c.children
        return _ls

    @property
    def family_tree(self):
        def sub_tree(p):
            if not p.children:
                return {}
            else:
                return {c.name : sub_tree(c) for c in p.children}
        return { self.name : sub_tree(self) }
