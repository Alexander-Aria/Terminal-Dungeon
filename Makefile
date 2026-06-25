all: 
	g++ src/main.cpp src/gamestate.cpp src/battle.cpp src/inventory.cpp src/entity.cpp src/player.cpp src/enemy.cpp src/stages.cpp src/shop.cpp -o build/app

clean: 
	rm build/app

run:
	./build/app