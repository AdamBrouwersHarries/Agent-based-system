#ifndef AGS_INSTANCE_H
#define AGS_INSTANCE_H
#include "../utility/general_includes.h"
#include "../utility/ogl_includes.h"
#include "../utility/input_handler.h"
#include "../graph/graph.h"
class ags_instance {
public:
		int w_width, w_height;
		int restriction;

		graph g;

		ags_instance() {

		}

		virtual ~ags_instance() {
		}

		void start(int window_width, int window_height, bool fullscreen, const char* title) {
				restriction = 200;
				w_width = window_width;
				w_height = window_height;
				open_window(window_width, window_height, 32, fullscreen, title, true);
				regen();
				std::cout<<"finished intialising instance\n";
		}

		void regen() {
			g.initialise(w_width, w_height);
			g.connect();
		}

		void simulate(float dt, input_handler ih) {
				glClearColor(0.0, 0.0, 0.0, 1.0);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				glColor4f(1.0, 1.0, 1.0, 1.0);
				glLoadIdentity();
				//RENDER
				for(int i = 0;i<g.vertex_count;i++)
				{
					vertex* v = &(g.verticies[i]);
					draw_square(v->location.x, v->location.y, 10);
					glBegin(GL_LINES);
					for(llnode<vertex*>* iter=v->adjacent.dummy_start.next_ptr;iter!=&(v->adjacent.dummy_end);iter = iter->next_ptr)
					{
						glVertex2f(v->location.x, v->location.y);
						glVertex2d(iter->payload->location.x, iter->payload->location.y);
					}
					glEnd();
				}
				//ENDRENDER
				SDL_GL_SwapBuffers();
		}
private:

		int open_window(int width, int height, int bpp, bool fullscreen, const char* title, bool two_d) {

				putenv((char*) "SDL_VIDEO_CENTERED=true");
				SDL_SetVideoMode(width, height, bpp, SDL_OPENGL | (fullscreen * SDL_FULLSCREEN));
				SDL_WM_SetCaption(title, NULL);

				//set the location of the opengl viewport?
				glViewport(0, 0, width, height);
				//if we're not using a 2d rendering area...
				if (!two_d) {
						double fov = 1000.0, znear = 1.0, zfar = 50000.0;
						glMatrixMode(GL_PROJECTION);
						glLoadIdentity();

						double fw, fh;

						//TEMPORARY
						double pi = 3.141;
						//TEMPORARY

						fw = tan((fov / 360.0) * pi) * znear;
						fh = (float(height) / float(width)) * fw;

						glFrustum(-fw, fw, -fh, fh, znear, zfar);

						glMatrixMode(GL_MODELVIEW);
						glLoadIdentity();

						glEnable(GL_DEPTH_TEST);
						glDepthFunc(GL_LEQUAL);
				} else {
						glMatrixMode(GL_PROJECTION);
						glLoadIdentity();
						glOrtho(0, width, height, 0, 0, 1);
						glMatrixMode(GL_MODELVIEW);
						glDisable(GL_DEPTH_TEST);
				}

				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				atexit(SDL_Quit);
				return 1;
		}

		void ButtonDown(int button) {
				//std::cout<<"Button "<<button<<" down\n";
		}

		void ButtonUp(int button) {
				//std::cout<<"Button "<<button<<" up\n\n";
		}

		void MouseDown(int button) {
				//std::cout<<"Mouse "<<button<<" down\n";
		}

		void MouseUp(int button) {
				//std::cout<<"Mouse "<<button<<" up\n\n";
		}
};
#endif //AGS_INSTANCE_H
