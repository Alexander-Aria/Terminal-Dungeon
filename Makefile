all: 
	g++ src/main.cpp src/battle.cpp src/inventory.cpp src/player.cpp src/stages.cpp src/shop.cpp -o build/app

clean: 
	rm build/app

run:
	./build/app