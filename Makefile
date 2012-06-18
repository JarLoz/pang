CC = g++
OBJECTS = Game.o pang.o MainMenu.o SplashScreen.o VisibleGameObject.o PlayerPaddle.o GameBall.o GameTile.o GameObjectManager.o ServiceLocator.o SFMLSoundProvider.o SoundFileCache.o
SOURCES = src/Game.cpp src/pang.cpp src/MainMenu.cpp src/SplashScreen.cpp src/VisibleGameObject.cpp src/PlayerPaddle.cpp src/GameBall.cpp src/GameTile.cpp src/GameObjectManager.cpp src/ServiceLocator.cpp src/SFMLSoundProvider.cpp src/SoundFileCache.cpp

pang: $(OBJECTS)
	$(CC) -o pang $(OBJECTS) -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
	mv *.o src/


$(OBJECTS): $(SOURCES)
	$(CC) -c $(SOURCES)

clean:
	rm src/*.o && rm pang
