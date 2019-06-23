CPP = g++
CFLAGS = -lpcap
TARGET = arp_spoof

SRC_DIR = src
INCLUDE_DIR = include
BINARY_DIR = bin

OBJECTS = $(patsubst %.cpp, %.o, $(wildcard $(SRC_DIR)/*.cpp))
HEADERS = $(wildcard $(INCLUDE_DIR)/*.h)

$(TARGET): $(OBJECTS)
	@echo "[+] Make Binary File"
	@mkdir -p $(BINARY_DIR)
	$(CPP) -g -o $(BINARY_DIR)/$@ $< $(CFLAGS)

%.o: %.cpp $(HEADERS)
	@echo "[+] Compile *.cpp File"
	$(CPP) -g -c -o $@ $< -I$(INCLUDE_DIR)

clean:
	@rm -f $(SOURCE_DIR)/*.o
	@rm -f $(BINARY_DIR)/$(TARGET)
	@rmdir $(BINARY_DIR) 2>/dev/null
