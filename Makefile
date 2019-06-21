CC = g++
CFLAGS = -lpcap
TARGET = arp_spoof

SOURCE_DIR = src
INCLUDE_DIR = include
BINARY_DIR = bin

OBJECTS = $(patsubst %.cpp, %.o, $(wildcard $(SOURCE_DIR)/*.cpp))
HEADERS = $(wildcard $(INCLUDE_DIR)/*.h)

$(TARGET): $(OBJECTS)
	@mkdir -p $(BINARY_DIR)
	@echo "[+] Make Binary File"
	$(CC) -g -o $(BINARY_DIR)/$@ $< $(CFLAGS)

%.o: %.cpp $(HEADERS)
	@echo "[+] Compile *.cpp File"
	$(CC) -g -c -o $@ $< -I$(INCLUDE_DIR)

clean:
	@rm -f $(SOURCE_DIR)/*.o
	@rm -f $(BINARY_DIR)/$(TARGET)
	@rmdir $(BINARY_DIR) 2>/dev/null
