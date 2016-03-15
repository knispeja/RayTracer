# make settings
NEWLINE=1 #newline after each object
ifdef NEWLINE
	NEWLINE = @echo ""
endif

# compile settings
CXX?=gcc
LINK=gcc
PROGRAM=a.out
DEL=rm -rf
#LIBS=-lm
DBG=-g
WARN=-w
OP=-O0
#FLAGS= $(WARN) $(OP)
FLAGS= $(WARN) $(DBG)

# setup object list
LOCAL_C_OBJECTS= $(patsubst %.c, %.o, $(wildcard ./*.c))
OBJECTS=$(LOCAL_C_OBJECTS)

# make targets
makeall:
	make $(PROGRAM)
	$(NEWLINE)

$(PROGRAM): $(OBJECTS) 
	@echo "--$(PROGRAM)--"
	$(LINK) $(FLAGS) $(OBJECTS) -o $(PROGRAM)

%.o: %.c
	@echo "--$@--"
	$(CXX) -c $(FLAGS) $< $(LIBS) -o $@
	$(NEWLINE)

# clean
.PHONEY: clean
clean:
	$(DEL) $(OBJECTS)

.PHONEY: cleanall
cleanall:
	$(DEL) $(OBJECTS)
	$(DEL) $(PROGRAM)
