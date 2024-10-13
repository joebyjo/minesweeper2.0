
# output file name
TARGET = game

# source files
SOURCES = main.cpp Game.cpp Cell.cpp CellMatrix.cpp Empty.cpp Mine.cpp Number.cpp Powerup.cpp

# user data file
USERDATA_FILE = game_highscores.csv

UNAME_S := $(shell uname -s)

# OS specific config
ifeq ($(UNAME_S), Darwin)  # mac
    SFML_LIBS = -L/opt/homebrew/lib -I/opt/homebrew/include -lsfml-graphics -lsfml-window -lsfml-system
else ifeq ($(UNAME_S), Linux)  # linux
    SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system
endif


# build executable and run exectuable
$(TARGET): $(SOURCES) $(USERDATA_FILE)
	g++ -std=c++11 $(SOURCES) $(SFML_LIBS) -o $(TARGET).out
	./$(TARGET).out 

# create CSV if not exist
$(USERDATA_FILE):
	@if [ ! -f $(USERDATA_FILE) ]; then \
	    touch $(USERDATA_FILE); \
	    echo "player,score,time,difficulty" > $(USERDATA_FILE); \
	    echo "Created $(USERDATA_FILE) with headers."; \
	else \
	    echo "$(USERDATA_FILE) already exists."; \
	fi

# clean workspace
clean:
	rm -f *.out *.o $(USERDATA_FILE)
