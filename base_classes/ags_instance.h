#ifndef AGS_INSTANCE_H
#define AGS_INSTANCE_H
#include "../utility/general_includes.h"
#include "../utility/ogl_includes.h"
#include "../utility/input_handler.h"
#include "../graph/graph.h"
#include "../agent/agent.h"
class ags_instance {
public:
		int w_width, w_height;
		int restriction;

		graph g;
		vertex* highlighted;
		vertex *connect_a, *connect_b;
		agent agent_a;
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
			g.initialise(w_width, w_height,10);
			g.connect();
			agent_a.current_node = &(g.verticies[0]);
		}

		void simulate(float dt, input_handler ih) {
				glClearColor(0.0, 0.0, 0.0, 1.0);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				glColor4f(1.0, 1.0, 1.0, 1.0);
				glLoadIdentity();
				float mx = ih.GetSDLMousePosX();
				float my = ih.GetSDLMousePosY();
				for(int i = 0;i<g.vertex_count;i++)
				{
					vertex* cv = &(g.verticies[i]);
					double dx = abs(cv->location.x-mx);
					double dy = abs(cv->location.y-my);
					if(dx<5 && dy <5)
					{
						highlighted = cv;
					}
				}
				//RENDER
				for(int i = 0;i<g.vertex_count;i++)
				{
					vertex* v = &(g.verticies[i]);
					if(v == highlighted)
					{
						double dx = abs(highlighted->location.x-mx);
						double dy = abs(highlighted->location.y-my);
						if(!(dx<10 && dy <10))
						{
							highlighted = NULL;
						}
						draw_square(v->location.x, v->location.y, 20);
					}else if(v == connect_a || v == connect_b)
					{
						draw_square(v->location.x, v->location.y, 5);
					}else{
						draw_square(v->location.x, v->location.y, 10);
					}
					
					glColor4f(1.0,1.0,1.0,0.1);
					glBegin(GL_LINES);
					for(llnode<vertex*>* iter=v->adjacent.dummy_start.next_ptr;iter!=&(v->adjacent.dummy_end);iter = iter->next_ptr)
					{
						glVertex2f(v->location.x, v->location.y);
						glVertex2d(iter->payload->location.x, iter->payload->location.y);
					}
					glEnd();
					glColor4f(1.0, 1.0, 1.0, 1.0);
				}
				draw_square(agent_a.current_location.x, agent_a.current_location.y, 4);
				agent_a.simulate();
				//ENDRENDER
				SDL_GL_SwapBuffers();
		}

		void MouseDown(int button) {
				//std::cout<<"Mouse "<<button<<" down\n";
			if(connect_a != NULL && connect_b != NULL)
			{
				//both assigned, so connect them
				if(connect_a != connect_b)
				{
					if(connect_a->adjacent.find_node(connect_b) == NULL)
					{
						connect_a->adjacent.add_node(connect_b);
					}
					if(connect_b->adjacent.find_node(connect_a) == NULL)
					{
						connect_b->adjacent.add_node(connect_a);
					}
					agent_a.current_node = connect_b;
				}
				connect_a = NULL;
				connect_b = NULL;
				highlighted = NULL;
			}else{
				if(connect_a == NULL)
				{
					connect_a = highlighted;
				}else{
					connect_b = highlighted;
				}
			}
		}
		void ButtonDown(int button) {
				//std::cout<<"Button "<<button<<" down\n";
				agent_a.running = true;
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

		

		void ButtonUp(int button) {
				//std::cout<<"Button "<<button<<" up\n\n";
		}

		

		void MouseUp(int button) {
				//std::cout<<"Mouse "<<button<<" up\n\n";
		}
};
#endif //AGS_INSTANCE_H
