object= start.o main.o DataTable.o ./Index/BPlusTreeIndex.o\
	./DataSource/FileDS.o ./DataSource/TerminalDS.o  ./BPlusTree/BTree.o

start:$(object)
	g++ $(object) -o start -lpthread

start.o: start.cpp
	g++  -c -g start.cpp 

main.o:main.cpp main.h
	g++  -c -g main.cpp

DataTable.o:DataTable.cpp DataTable.h
	g++ -c -g DataTable.cpp -lpthread

./DataSource/FileDS.o:./DataSource/FileDS.cpp ./DataSource/FileDS.h ./DataSource/DataSource.h
	g++ -c -g ./DataSource/FileDS.cpp -o ./DataSource/FileDS.o

./DataSource/TerminalDS.o:./DataSource/TerminalDS.cpp ./DataSource/TerminalDS.h ./DataSource/DataSource.h
	g++ -c -g ./DataSource/TerminalDS.cpp -o ./DataSource/TerminalDS.o

./BPlusTree/BTree.o:./BPlusTree/BTree.cpp ./BPlusTree/BTree.h ./BPlusTree/struct.h
	g++ -c -g ./BPlusTree/BTree.cpp -o ./BPlusTree/BTree.o

./Index/BPlusTreeIndex.o:./Index/BPlusTreeIndex.cpp ./Index/BPlusTreeIndex.h ./Index/index.h
	g++ -c -g ./Index/BPlusTreeIndex.cpp -o ./Index/BPlusTreeIndex.o
clean:
	rm -rf start $(object)
