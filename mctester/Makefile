

CC = g++
LD = g++

CFLAGS = -c -Wall -fno-elide-constructors
LFLAGS = -Wall -lSDL -lSDL_ttf -lSDL_mixer -lSDL_image


# Put any user application resources here. (ie images, sounds, etc.)
RESOURCES := images

PROG = app

OBJS = main.o doodleparts.o

default: gui_files setup program
	@echo "Done!"
	@echo $(PROG)

gui_files:
	@echo "Making GUI files."
	cd gui;	make

setup: setup_resources 
	

setup_resources: 
	@echo "\nCopying Resource files."
	mkdir -p Resources
	cp -R gui/GUIImages Resources
	cp -R gui/GUIFonts Resources
ifneq ($(RESOURCES),)
	cp -R $(RESOURCES) Resources
endif


# Separate this out into another make to get the updated .o files.
program: 
	@echo "\nBuilding Project."
	@make linking;

# Separate this out into another make to get the updated .o files.
linking:  $(wildcard gui/*.o) $(OBJS)
	@echo "\nLinking!"
	$(LD) $(wildcard gui/*.o) $(OBJS) $(LFLAGS) -o $(PROG)

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

doodleparts.o: doodleparts.cpp
	$(CC) $(CFLAGS) doodleparts.cpp


clean:
	rm -f *.o
	rm -f gui/*.o
clean_full:
	rm -f *.o $(PROG)
	rm -f gui/*.o
	rm -rf Resources



