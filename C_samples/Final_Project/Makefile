paint.out: main.o board.o command.o inputvalidation.o help.o resize.o save.o load.o write.o
	gcc -g -Wall -Werror -o paint.out main.o board.o command.o inputvalidation.o help.o resize.o save.o load.o write.o

main.o: main.c board.h command.h help.h write.h resize.h save.h load.h
	gcc -g -Wall -Werror -c main.c

board.o: board.c board.h
	gcc -g -Wall -Werror -c board.c

command.o: command.c command.h inputvalidation.h board.h
	gcc -g -Wall -Werror -c command.c

inputvalidation.o: inputvalidation.c inputvalidation.h command.h
	gcc -g -Wall -Werror -c inputvalidation.c

help.o: help.c help.h command.h board.h
	gcc -g -Wall -Werror -c help.c

resize.o: resize.c resize.h command.h board.h
	gcc -g -Wall -Werror -c resize.c

save.o: save.c save.h command.h board.h
	gcc -g -Wall -Werror -c save.c

load.o: load.c load.h board.h resize.h command.h
	gcc -g -Wall -Werror -c load.c

write.o: write.c write.h command.h board.h
	gcc -g -Wall -Werror -c write.c

clean:
	rm -f *.o *.out