CC = gcc

C_FLAGS = -g3 -Wall

C_FILES = gw.c main.c \

O_FILES := $(patsubst %.c, %.o, $(C_FILES) )

H_FILES = $(wildcard *.h)

all:
	$(MAKE) -s gworld

gworld: $(O_FILES)
	rm -f gworld
	$(CC) -o gworld $(O_FILES)
	@echo "Source Compilation Complete.";
	chmod g+w gworld
	chmod a+x gworld
	chmod g+w $(O_FILES)

clean:
	rm -f *.o gworld *~

format:
	indent -ts4 -ut -bap -bli0 -di1 -l120 -nlp -i4 -nbc -cli4 -sc -cdb -c1 -cd1 -nbfda -npcs -bad -hnl -nce -npsl -bl -prs $(C_FILES)
	indent -ts4 -ut -bap -bli0 -di1 -l120 -nlp -i4 -nbc -cli4 -sc -cdb -c1 -cd1 -nbfda -npcs -bad -hnl -nce -npsl -bl -prs $(H_FILES)

%.o: %.c
	echo "  Compiling $@...";
	$(CC) -c $(C_FLAGS) $< -o $@
