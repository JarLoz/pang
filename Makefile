CC = g++

pang: Game.o pang.o MainMenu.o SplashScreen.o VisibleGameObject.o PlayerPaddle.o GameBall.o GameObjectManager.o ServiceLocator.o SFMLSoundProvider.o SoundFileCache.o
	$(CC) -o pang Game.o pang.o MainMenu.o SplashScreen.o VisibleGameObject.o PlayerPaddle.o GameBall.o GameObjectManager.o ServiceLocator.o SFMLSoundProvider.o SoundFileCache.o -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
	mv *.o src/

Game.o: src/Game.cpp
	$(CC) -c src/Game.cpp

pang.o: src/pang.cpp
	$(CC) -c src/pang.cpp

MainMenu.o: src/MainMenu.cpp
	$(CC) -c src/MainMenu.cpp

SplashScreen.o: src/SplashScreen.cpp
	$(CC) -c src/SplashScreen.cpp

VisibleGameObject.o: src/VisibleGameObject.cpp
	$(CC) -c src/VisibleGameObject.cpp

PlayerPaddle.o: src/PlayerPaddle.cpp
	$(CC) -c src/PlayerPaddle.cpp

GameBall.o: src/GameBall.cpp
	$(CC) -c src/GameBall.cpp

GameObjectManager.o: src/GameObjectManager.cpp
	$(CC) -c src/GameObjectManager.cpp

SFMLSoundProvider.o: src/SFMLSoundProvider.cpp
	$(CC) -c src/SFMLSoundProvider.cpp

ServiceLocator.o: src/ServiceLocator.cpp
	$(CC) -c src/ServiceLocator.cpp

SoundFileCache.o: src/SoundFileCache.cpp
	$(CC) -c src/SoundFileCache.cpp

clean:
	rm src/*.o && rm pang
