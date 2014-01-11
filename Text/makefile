tst-text: main.o histogramText.o parser.o descriptor.o utility.o
	gcc -o tst-text main.o histogramText.o parser.o descriptor.o utility.o
	rm *.o

histogramText.o: Sources/histogramText.c Sources/histogramText.h
	gcc -c Sources/histogramText.c

parser.o: Sources/parser.c Sources/parser.h
	gcc -c Sources/parser.c

descriptor.o: Sources/descriptor.c Sources/descriptor.h
	gcc -c Sources/descriptor.c

main.o: Sources/main.c
	gcc -c Sources/main.c

utility.o: Sources/Utility/utility.c
	gcc -c Sources/Utility/utility.c

clean:
	rm *.o	
