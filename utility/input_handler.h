#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

enum
{
    MOUSE_DOWN,
    MOUSE_UP,
    BUTTON_DOWN,
    BUTTON_UP
};
class input_handler
{
public:
    input_handler() {}
    virtual ~input_handler() {}
    void PassEvent(SDL_Event ev)
    {
        SDL_GetMouseState(&x,&y);
        while (SDL_PollEvent(&ev))
        {
            switch (ev.type)
            {
            case SDL_QUIT:
				if(eFunc != NULL)
				{
					eFunc();
				}
                break;
            case SDL_KEYDOWN:
                if (ev.key.keysym.sym == SDLK_ESCAPE)
                {
                    eFunc();
                }
                else
                {
                    Keys[ev.key.keysym.sym] = true;
                    if(ev.key.keysym.sym == SDLK_q)
                    {
                        ssFunc();
                    }
                    cbFunc(ev.key.keysym.sym,BUTTON_DOWN);
                }
                break;
            case SDL_KEYUP:
                Keys[ev.key.keysym.sym] = false;
                cbFunc(ev.key.keysym.sym,BUTTON_UP);
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (ev.button.button == SDL_BUTTON_LEFT)
                {
                    cbFunc(1,MOUSE_DOWN);
                }
                if (ev.button.button == SDL_BUTTON_RIGHT)
                {
                    cbFunc(2,MOUSE_DOWN);
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if (ev.button.button == SDL_BUTTON_LEFT)
                {
                    cbFunc(1,MOUSE_UP);
                }
                if (ev.button.button == SDL_BUTTON_RIGHT)
                {
                    cbFunc(2,MOUSE_UP);
                }
                break;
            case SDL_MOUSEMOTION:
                x = ev.button.x;
                y = ev.button.y;
                break;
            }
        }
    }
    int GetWinMousePosX()
    {
        return x;
    }
    int GetWinMousePosY()
    {
        return y;
    }
    float GetSDLMousePosX()
    {
        int viewport[4];
        double modelview[16], projection[16];

        glGetIntegerv(GL_VIEWPORT, viewport);
        glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
        glGetDoublev(GL_PROJECTION_MATRIX, projection);

        int mx = x;
        int my = viewport[3]-0;

        GLdouble WinX,WinY,WinZ;
        gluProject(0,0,0,modelview, projection, viewport, &WinX,&WinY,&WinZ);

        GLdouble X,Y,Z;
        gluUnProject((double)mx, (double)my,WinZ, modelview, projection, viewport, &X, &Y, &Z);

        float Xf;
        Xf = (float)X;
//        std::cout<<"x: "<<X<<" y: "<<Y<<"\n";
//        std::cout<<"iX: "<<x<<" iY "<<y<<"\n";
        return Xf;
    }
    float GetSDLMousePosY()
    {
        int viewport[4];
        double modelview[16], projection[16];

        glGetIntegerv(GL_VIEWPORT, viewport);
        glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
        glGetDoublev(GL_PROJECTION_MATRIX, projection);

        int mx = 0;
        int my = viewport[3]-y;

        GLdouble WinX,WinY,WinZ;
        gluProject(0,0,0,modelview, projection, viewport, &WinX,&WinY,&WinZ);

        GLdouble X,Y,Z;
        gluUnProject((double)mx, (double)my,WinZ, modelview, projection, viewport, &X, &Y, &Z);

        float Yf;
        Yf = (float)Y;

//        std::cout<<"x: "<<X<<" y: "<<Y<<"\n";

        return Yf;
    }
    bool ButtonDown(int Button)
    {
        return Keys[Button];
    }
    int RegisterExitCallback(void (*pt2Func)(void))
    {
        if (pt2Func == NULL)
        {
            return 1;
        }
        eFunc = pt2Func;
        return 0;
    }
    int RegisterSSCallback(void (*pt2Func)(void))
    {
        if(pt2Func == NULL)
        {
            return 1;
        }
        ssFunc = pt2Func;
        return 0;
    }
    int RegisterCallback(void (*pt2Func)(int,int))
    {
        if (pt2Func != NULL)
        {
            cbFunc = pt2Func;
        }
        else
        {
            return 1;
        }
        return 0;
    }
protected:
private:
    bool Keys[322];
    bool left, right;
    int x,y;
    void (*cbFunc)(int,int);
    void (*eFunc)(void);
    void (*ssFunc)(void);
};

#endif // INPUT_HANDLER_H
