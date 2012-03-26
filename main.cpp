/*
Compile with (includes debugging information):
	Linux:
	g++ main.cpp -o ags_linux -lSDLmain -lSDL -lGLU -lGL -Wall -ggdb
	Windows:
	g++ main.cpp -o ags_win -lmingw32 -lSDLmain -lSDL -lopengl32 -lglu32 -lwinmm -mwindows -Wall -ggdb
*/

#include "base_classes/ags_instance.h"
#include "utility/input_handler.h"

bool running = true;
ags_instance test;
input_handler userInput;

void exit_callback_function() {
	running = false;
}

void input_callback_function(int button, int callbackType) {
	switch (callbackType) {
		case MOUSE_DOWN:
			//call the game's mouse down function
			test.MouseDown(button);
			break;
		case MOUSE_UP:
			//call the game's mouse up function
			break;
		case BUTTON_DOWN:
			//call the game's button down function
			//test.regen();
			test.ButtonDown(button);
			break;
		case BUTTON_UP:
			//call the game's button up function
			break;
	}
}
Uint64 currentTime;
Uint64 frames = 0;
Uint64 dt = 0;

void ChangeTitle() {
	frames++;
	currentTime = SDL_GetTicks();
	float averageFps = 1000 * frames / currentTime;
	std::stringstream cap;
	cap << "Total frames" << frames << " total millis " << currentTime << " FPS:" << averageFps << " DT:" << dt << " AV DT:" << 1000 / averageFps<<" agents:"<<test.agents.size();
	if (frames % 100 == 0) {
		SDL_WM_SetCaption(cap.str().c_str(), NULL);
		if (frames % 1000 == 0) {
			//test.regen();
		}
	}
}

void render_loop() {
	while (running) {
		ChangeTitle();
		SDL_Event ev;
		userInput.PassEvent(ev);
		test.simulate(dt, userInput);
		dt = SDL_GetTicks() - currentTime;
		while(dt<8)
		{
			dt = SDL_GetTicks() - currentTime;
		}
	}
}

int main(int argc, char** argv) {
	test.start(800, 600, false, "hi there");
	userInput.RegisterExitCallback(exit_callback_function);
	userInput.RegisterCallback(input_callback_function);
	render_loop();
	return 0;
}
