all: 
	g++ src/main.cpp src/battle.cpp src/player.cpp src/stages.cpp -o build/app

clean: 
	rm build/app

run:
	./build/app