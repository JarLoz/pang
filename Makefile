CC = g++

pang: Game.o pang.o
	$(CC) -o pang Game.o pang.o -lsfml-graphics -lsfml-window -lsfml-system
	mv *.o src/

Game.o: src/Game.cpp
	$(CC) -c src/Game.cpp

pang.o: src/pang.cpp
	$(CC) -c src/pang.cpp

clean:
	rm src/*.o && rm pang
