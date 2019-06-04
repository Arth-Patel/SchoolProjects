client : libnetfiles.c libnetfiles.h netfileserver.c
	gcc libnetfiles.c libnetfiles.h -o client
server : libnetfiles.h netfileserver.c
	gcc netfileserver.c libnetfiles.h -pthread -o server
