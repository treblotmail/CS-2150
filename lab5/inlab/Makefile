# Liam Tolbert, lct4am, 10/5/2021

CXX=clang++ $(CXXFLAGS)
CXXFLAGS=-Wall
DEBUG=-g

binary: BinaryNode.o BinarySearchTree.o BSTPathTest.o
	$(CXX) $(DEBUG) BinaryNode.o BinarySearchTree.o BSTPathTest.o

BinaryNode.o: BinaryNode.cpp BinaryNode.h

BinarySearchTree.o: BinarySearchTree.cpp BinaryNode.h BinarySearchTree.h

BSTPathTest.o: BSTPathTest.cpp BinarySearchTree.h BinaryNode.h

.PHONY: clean
clean:
	-rm -f *.o *~a.out
