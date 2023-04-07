all: linkedList.o sortedArray.o data.o dict2.o dict1.o dict1 dict2

dict1.o: dict1.c data.h linkedList.h

dict2.o: dict2.c data.h sortedArray.h

data.o: data.c data.h

sortedArray.o: sortedArray.c sortedArray.h data.h

linkedList.o: linkedList.c linkedList.h data.h

dict1:
	gcc -Wall -g -o dict1 dict1.o data.o linkedList.o

dict2:
	gcc -Wall -g -o dict2 dict2.o data.o sortedArray.o