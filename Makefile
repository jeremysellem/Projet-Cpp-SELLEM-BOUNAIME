
all: install
	./MainPricer

install:
	g++ MainPricer.cpp -o MainPricer -std=c++17