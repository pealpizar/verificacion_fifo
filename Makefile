include Makefile.config

OBJ_NAME = run

INCDIR =    -I.

            
SRCDIR          = .
SRCCOMMONDIR    = .
CPPFILES        = $(wildcard $(SRCDIR)/*.cpp)
 
CFLAGS = $(FLAGS) $(INCDIR)
OBJS=$(CPPFILES:.cpp=.o)

.PHONY: clean all check

all: announce $(OBJ_NAME).exe

announce:
	@if  ( test ! -d $(FLAG_BATCH) ); \
	 	then echo; echo "$(OBJ_NAME):"; echo; \
	 fi
	
check: announce $(OBJ_NAME).exe
	@$(VALGRIND) ./$(OBJ_NAME).exe > run.log
	@diff run.log ../results/expected.log > diff.log 2>&1;\
	if [ -s diff.log ]; then echo "***ERROR:"; cat diff.log; else echo "OK"; fi

run: announce $(OBJ_NAME).exe
	@./$(OBJ_NAME).exe

$(OBJ_NAME).exe: $(OBJS)
	$(LD) -o $@ $(OBJS) $(LDFLAGS)


.cpp.o: 
	$(GXX) $(CFLAGS) -c $< -o $@

#lib.o: verif_elements.cpp 
#	$(GXX) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o *.log $(OBJ_NAME).exe

# DO NOT DELETE

