OUT := sequence
OBJS := main.o

CXX := g++
CXXFLAGS := -std=c++17

TMP := .$(OUT)

$(OUT): $(OBJS)
	touch $(TMP).cc
	make $(TMP)
	mv $(TMP) $@
	rm -f $(TMP)*

$(TMP): $(TMP).cc $(OBJS)

.PHONY: clean
clean:
	rm -rf *.o
	rm -rf $(OUT)
	rm -rf $(TMP)*
