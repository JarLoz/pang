CC = g++

pang: Game.o pang.o MainMenu.o SplashScreen.o
	$(CC) -o pang Game.o pang.o MainMenu.o SplashScreen.o -lsfml-graphics -lsfml-window -lsfml-system
	mv *.o src/

Game.o: src/Game.cpp
	$(CC) -c src/Game.cpp

pang.o: src/pang.cpp
	$(CC) -c src/pang.cpp

MainMenu.o: src/MainMenu.cpp
	$(CC) -c src/MainMenu.cpp

SplashScreen.o: src/SplashScreen.cpp
	$(CC) -c src/SplashScreen.cpp

clean:
	rm src/*.o && rm pang
