
# output file name
TARGET = game

# source files
SOURCES = Game.cpp Cell.cpp CellMatrix.cpp Empty.cpp Mine.cpp Number.cpp Powerup.cpp
TEST_SOURCES = testing/unit_test.cpp testing/Cell_tests.h testing/CellMatrix_tests.h testing/Game_tests.h

# user data file
USERDATA_FILE = game_stats.csv

UNAME_S := $(shell uname -s)

# OS specific config
ifeq ($(UNAME_S), Darwin)  # mac
    SFML_LIBS = -L/opt/homebrew/lib -I/opt/homebrew/include -lsfml-graphics -lsfml-window -lsfml-system
else ifeq ($(UNAME_S), Linux)  # linux
    SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system
endif


# build executable and run exectuable
$(TARGET): main.cpp $(SOURCES) $(USERDATA_FILE)
	g++ -std=c++11 main.cpp $(SOURCES) $(SFML_LIBS) -o $(TARGET).out
	./$(TARGET).out 

test: $(TEST_SOURCES) $(SOURCES)
	g++ -std=c++11 $(TEST_SOURCES) $(SOURCES) $(SFML_LIBS) -o test.out
	./test.out

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