clean:
	rm -f table
table: table.c
	gcc -Wall -Werror -fsanitize=address -o table table.c
