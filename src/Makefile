Makefile: 
 
CC = g++  

INC_PATH = C:/Users/Amelia/Desktop/Capstone/Daisy/DaisyExamples-master/MyProjects/Daisy-MultiFx-new/src
 
#INCLUDES = -I /src -I $(HOME)/src -I $(INC_PATH) 
INCLUDE = $(INC_PATH)

LIBDAISY_DIR = C:\Users\Amelia\Desktop\Capstone\Daisy\DaisyExamples-master\libDaisy
DAISYSP_DIR = C:\Users\Amelia\Desktop\Capstone\Daisy\DaisyExamples-master\DaisySP
 
LIBINCLUDES = -I $(LIBDAISY_DIR)/core -I $(LIBDAISY_DIR)/core  -I $(HOME)/$(LIBDAISY_DIR)/core 
 
INC = $(INCLUDES) $(LIBINCLUDES)  
CFLAGS= -O2 -fPIC  
 
OBJS =  a.o
 
LIBS = #-lm -lthread -lgtk2

all_tests:
	$(CC) -o all_test test.cpp $(INC) $(LIBS)

# # a build command to build myprogram executable from myprogram.o and mylib.lib
# all:myprogram.o mylib.o
#         gcc –o myprogram myprogram.o mylib.o
# clean:
#         $(RM) myprogram
 
# prog:	prog main.o 
# 	$(CC) $(CFLAGS) $(INC) main.o $(OBJS) $(LIBS) 
 
# main.o:	main.c $(OBJS) 
# 	$(CC) $(CFLAGS) $(INC) -c main.c  
 
# a.o:	a/a.c 
# 	cd a 
# 	$(CC) $(CFLAGS) $(INC) -c a.c  
 
# b.o:	b/b.c 
# 	cd b 
# 	$(CC) $(CFLAGS) $(INC) -c b.c  
 
# c.o:	c/c.c 
#      cd c 
# 	$(CC) $(CFLAGS) $(INC) -c c.c 
 
# clean: 
# 	rm -f *.o *~ prog 
#     cd a 
#     rm -f *.o *~ 
#     cd b 
#     rm -f *.o *~ 
#     cd c 
#     rm -f *.o *~ 