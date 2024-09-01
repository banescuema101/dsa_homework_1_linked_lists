build:
	gcc -g -o tema1 tema1.c operatii.c operatii.h
run:
	./tema1
clean:
	rm tema1
valgrind:
	valgrind --leak-check=yes --track-origins=yes -s ./tema1