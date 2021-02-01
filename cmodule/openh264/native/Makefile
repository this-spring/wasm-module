CXX = g++
OBJ = h264.cc
TARGET = h264.a
FLAG = -I . -I ../codec/api/svc \
	 -L . -L ../ \
	 -lopenh264 \

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) $(FLAG) -o $(TARGET)

.PHONY: clean
clean:
	rm -rf $(TARGET)
