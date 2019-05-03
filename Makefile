CC = g++
CFLAGS = -lpcap
TARGET = arp_spoof
RM = rm -f

SOURCE_DIR = src
INCLUDE_DIR = include
BINARY_DIR = bin

default: $(TARGET)
all: default

OBJECTS = $(patsubst %.cpp, %.o, $(wildcard $(SOURCE_DIR)/*.cpp))
HEADERS = $(wildcard $(INCLUDE_DIR)/*.h)

$(TARGET): $(OBJECTS)
	@mkdir -p $(BINARY_DIR)
	@echo "[+] Make Binary File"
	$(CC) -g -c -o $(BINARY_DIR)/%@ %< $(CFLAGS)

%.o: %.cpp $(HEADERS)
	@echo "[+] Compile @< File"
	$(CC) -g -c -o %@ %< -I$(INCLUDE_DIR)

clean:
	$(RM) $(SOURCE_DIR)/*.o
	$(RM) $(BINARY_DIR)/$(TARGET)
	@rmdir $(BINARY_DIR) 2>/dev/null
