class TestClass:
    def __init__(self, name, ID):
        self.name = name
        self.ID = ID
    def ShowInfo(self):
        print('name:', name, ',ID:', ID)
    def ChangeName(self, newName):
        self.name = newName

#test
