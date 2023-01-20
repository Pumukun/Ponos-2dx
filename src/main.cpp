#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Utils.hpp"

using namespace std;

int main(int argc, char* args[]) {

	// Инициализация библиотеки SDL и проверка все ли норм
	if (SDL_Init(SDL_INIT_VIDEO) > 0) 
		cout << "SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << endl;
	if (!IMG_Init(IMG_INIT_PNG))
		cout << "IMG_INIT HAS FAILED. ERROR: " << SDL_GetError() << endl;

	// Инициализация окна
	int windowWidth = 1920;
	int windowHeight = 1080;

	RenderWindow window("Cocos-2dx)))", windowWidth, windowHeight);

	// Загрузка текстур
	SDL_Texture* playerTexture = window.loadTexture("res/gfx/Smilik.png");

	Entity Player({512, 512}, playerTexture, 512, 512);


	bool gameRunning = true;
	SDL_Event event;

	const float timeStep = 0.01f;
	float accumulator = 0.0f; // Обновления экрана, каждый раз когда заполнится аккумулятор
	float currentTime = utils::hireTimeInSeconds();

	// main game loop
	while (gameRunning) {
		int startTicks = SDL_GetTicks();

		float newTime = utils::hireTimeInSeconds();
		float frameTime = newTime - currentTime;

		currentTime = newTime;
		accumulator += frameTime;

		while (accumulator >= timeStep) {
			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT)
					gameRunning = false;

			accumulator -= timeStep;
		}

		// Texture display
		window.clear();

		// тут рендер обьектов
		window.render(Player);

		window.display();

		int frameTicks = SDL_GetTicks() - startTicks;

		if (frameTicks < 1000 / window.getRefreshRate())
			SDL_Delay(1000 / window.getRefreshRate() - frameTicks);
		}
	}

	window.cleanUp();
	SDL_Quit();

	return 0;
}
