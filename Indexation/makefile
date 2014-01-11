All: Indexation Compare

Indexation: indexation.o wavFile.o wavData.o wavHeader.o histogramSound.o utility.o openPicture.o picture.o matrix.o histogram.o quantification.o histogramText.o parser.o descriptor.o
	gcc -o Indexation indexation.o wavFile.o wavData.o wavHeader.o histogramSound.o utility.o openPicture.o picture.o matrix.o histogram.o quantification.o histogramText.o parser.o descriptor.o -lm

Compare: utility.o compare.o histogramText.o
	gcc -o Compare utility.o compare.o histogramText.o

# Compare

compare.o: Sources/compare.c
	gcc -c Sources/compare.c

# Indexation

indexation.o: Sources/indexation.c
	gcc -c Sources/indexation.c

# Audio

wavHeader.o: Sources/Sound/wavHeader.c Sources/Sound/wavHeader.h
	gcc -c Sources/Sound/wavHeader.c

wavData.o: Sources/Sound/wavData.c Sources/Sound/wavData.h
	gcc -c Sources/Sound/wavData.c

wavFile.o: Sources/Sound/wavFile.c Sources/Sound/wavFile.h
	gcc -c Sources/Sound/wavFile.c
	
histogramSound.o: Sources/Sound/histogramSound.c Sources/Sound/histogramSound.h
	gcc -c Sources/Sound/histogramSound.c

# Picture

openPicture.o: Sources/Picture/openPicture.c Sources/Picture/openPicture.h
	gcc -c Sources/Picture/openPicture.c

picture.o: Sources/Picture/picture.c Sources/Picture/picture.h Sources/Picture/matrix.h
	gcc -c Sources/Picture/picture.c

matrix.o: Sources/Picture/matrix.c Sources/Picture/matrix.h Sources/Picture/picture.h
	gcc -c Sources/Picture/matrix.c

histogram.o: Sources/Picture/histogram.c Sources/Picture/histogram.h Sources/Picture/matrix.h
	gcc -c Sources/Picture/histogram.c

quantification.o: Sources/Picture/quantification.c Sources/Picture/quantification.h
	gcc -c Sources/Picture/quantification.c

# Texte

histogramText.o: Sources/Text/histogramText.c Sources/Text/histogramText.h
	gcc -c Sources/Text/histogramText.c

parser.o: Sources/Text/parser.c Sources/Text/parser.h
	gcc -c Sources/Text/parser.c

descriptor.o: Sources/Text/descriptor.c Sources/Text/descriptor.h
	gcc -c Sources/Text/descriptor.c

# Utility
	
utility.o: Sources/Utility/utility.c Sources/Sound/Utility/utility.h
	gcc -c Sources/Utility/utility.c

# Clean

clear: 
	rm *.o