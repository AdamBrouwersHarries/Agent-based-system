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
		std::vector<vertex*> selected_verticies;
		std::vector<agent> agents;
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
			for(int i = 0;i<g.vertex_count;i++)
			{
				agent new_agent;
				new_agent.current_node = &(g.verticies[i]);
				agents.push_back(new_agent);
			}
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
				for(unsigned int i = 0;i<selected_verticies.size();i++)
				{
					vertex* iv = selected_verticies[i];
					draw_square(iv->location.x, iv->location.y, 5);
				}
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
				for(unsigned int i = 0;i<agents.size();i++)
				{
					agents[i].simulate();
					agents[i].draw();
				}
				//ENDRENDER
				SDL_GL_SwapBuffers();
				if(ih.ButtonDown(SDLK_k))
				{
					agent new_agent;
					new_agent.current_node = &(g.verticies[rand()%g.vertex_count]);
					new_agent.running = agents[0].running;
					agents.push_back(new_agent);
				}
		}

		void MouseDown(int button) {
			//std::cout<<"Mouse "<<button<<" down\n";
			if(highlighted!=NULL)
			{
				selected_verticies.push_back(highlighted);
			}
		}
		void ButtonDown(int button) {
				//std::cout<<"Button "<<button<<" down\n";
				switch(button)
				{
					case SDLK_c:
					for(unsigned int i = 0;i<selected_verticies.size();i++)
					{
						vertex* ivertex = selected_verticies[i];
						for(unsigned int j = i;j<selected_verticies.size();j++)
						{
							if(i!=j)
							{
								vertex* jvertex = selected_verticies[j];
								if(ivertex->adjacent.find_node(jvertex) == NULL)
								{
									ivertex->adjacent.add_node(jvertex);
								}
								if(jvertex->adjacent.find_node(ivertex) == NULL)
								{
									jvertex->adjacent.add_node(ivertex);
								}
							}
						}
					}
					selected_verticies.clear();
					break;
					case SDLK_x:
					for(unsigned int i = 0;i<selected_verticies.size()-1;i++)
					{
						vertex* ivertex = selected_verticies[i];
						vertex* jvertex = selected_verticies[i+1];
						if(ivertex->adjacent.find_node(jvertex) == NULL)
						{
							ivertex->adjacent.add_node(jvertex);
						}
						if(jvertex->adjacent.find_node(ivertex) == NULL)
						{
							jvertex->adjacent.add_node(ivertex);
						}
					}
					selected_verticies.clear();
					break;
					case SDLK_s:
					for(unsigned int i = 0;i<agents.size();i++)
					{
						agents[i].running = !agents[i].running;
					}
					break;
					case SDLK_d:
					for(unsigned int i = 0;i<agents.size();i++)
					{
						agents[i].current_node = &(g.verticies[rand()%g.vertex_count]);
						agents[i].find_new_target();
					}
					break;
					case SDLK_e:
					{
						agent new_agent;
						new_agent.current_node = &(g.verticies[rand()%g.vertex_count]);
						new_agent.running = agents[0].running;
						agents.push_back(new_agent);
					}
					break;
					case SDLK_w:
					if(agents.size()>0)
					{
						agents.pop_back();
					}
					break;
				}
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

