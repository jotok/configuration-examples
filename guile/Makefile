P = get_params_scm
OBJECTS = 
CFLAGS = -g -Wall -pthread
LDLIBS = -lguile -Wl,-O1,--sort-common,--as-needed,-z,relro,--hash-style=gnu \
		 -lgmp -lcrypt -lm -lltdl
LDFLAGS = 
CC = c99

$(P) : $(OBJECTS)

clean:
	rm -f $(OBJECTS) $(P)
