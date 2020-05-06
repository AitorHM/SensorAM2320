#######################################################################
# 							Makefile
#######################################################################

#DESTDIR=./home/pi/Documents/dse/p1/c    				
#PREFIX=/local  				

#STATIC=libstatic.a 		 		
#DYNAMIC=libdynamic.so 			
DEBUG	= -O2       			

CC	= gcc  					
INCLUDE	= -I/usr/local/include		
CFLAGS	= $(DEBUG) -Wall $(INCLUDE) -Winline -pipe
#-Wall: warning all
LDFLAGS	= -L/usr/local//lib

#LIBS = -lpthread

SRC	=	AM2320.c

###############################################################################
OBJ	=	$(SRC:.c=.o)
BINS	=	$(SRC:.c=)

AM2320:	AM2320.o
	@echo [link]
	@$(CC) -o $@ AM2320.o $(LDFLAGS)
#$(LIBS)
#.c.o:
%.o: %.c
	@echo [Compile] $<
	@$(CC) -c $(CFLAGS) $< -o $@

.PHONEY:	clean
clean:
	rm -f $(OBJ) $(BINS) *~ core tags *.bak

#.PHONEY:	tags

#tags:	$(SRC)
	#@echo [ctags]
	#@ctags $(SRC)

#.PHONEY:	depend
#depend:
#	makedepend -Y $(SRC) 
