class BST:
    def __init__(self, num):
        self.data = num
        self.left = None
        self.right = None
        self.parent = None

    def getData(self):
        return self.data

    def setLeft(self, num):
        if self.left == None:
            self.left = BST(num)
            self.left.parent = self
        else:
            self.left.insert(num)

    def setRight(self, num):
        if self.right == None:
            self.right = BST(num)
            self.right.parent = self
        else:
            self.right.insert(num)
   
    def getLeft(self):
        return self.left

    def getRight(self):
        return self.right

    def insert(self, num):
        if num <= self.getData():
            self.setLeft(num)
        else:
            self.setRight(num)

    def printTree(self):
        if self.getLeft() != None:
            self.left.printTree()

        print(self.getData())

        if self.getRight() != None:
            self.right.printTree()

    def printLeft(self):
        if self.left == None:
            print('L')
        else:
            print(self.left.getData())

    def printRight(self):
        if self.right == None:
            print('R')
        else:
            print(self.right.getData())

    def printChildren(self):
        self.printLeft()
        self.printRight()

    def printNodes(self):
        node = self
        while node != None:
        if self.parent == None:
            print(self.getData())
            self.printChildren()
            if self.left != None:
                self.left.printNodes()
            if self.right != None:
                self.right.printNodes()

        elif self != None:
            self.printChildren()
            if self.left != None:
                self.left.printChildren()
            if self.right != None:
                self.right.printChildren()


    def numNodes(self):
        if self == None:
            return 0
        else:
            return 1 + numNodes(self.getLeft()) + numNodes(self.getRight())

    #def createArray(self):
    #    if self == None:
    #        return []
    #    else:

    #    arr = []
    #    arr.append(self.getData())
    #    arr.ex
        



if __name__ == "__main__":
    n = int(input('Enter number off BSTs: '))
    trees = []
    for i in range(0, n):
        inp = input().split()
        inp = list(map(int, inp)) # turn list of numbers into ints
        print(inp)

        trees.append(BST(inp[1]))  # create root node of BST (inp[0] is the number
                                # of items in the BST

        for x in range(2, len(inp)):
            trees[i].insert(inp[x])

    for tree in trees:
        tree.printNodes()
        print('-----------------------')
    
