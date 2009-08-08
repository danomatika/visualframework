#ifndef APPLICATION_H
#define APPLICATION_H

#include "Common.h"

#include "Color.h"

class Application
{
    public:

        Application();

        virtual ~Application();

        virtual void setup() = 0;

        void mainLoop();

        virtual void update() = 0;

        virtual void draw() = 0;

        virtual void cleanup() = 0;

        // input events

        virtual void keyPressed(SDLKey key, SDLMod mod) {}

        virtual void keyReleased(SDLKey key, SDLMod mod) {}

        virtual void mousePressed(int button, int x, int y) {}

        virtual void mouseReleased(int button, int x, int y) {}

        virtual void mouseMotion(int x, int y, int xRel, int yRel) {}

        // utils

        //
        void setFrameRate(float frameRate);

        void setBackground(Color color) {_background = color;}

        void inline stop() {_bRun = false;};

    protected:

        bool _bRun;             /// is the main loop running?
        float _fFrameRate;      /// frame rate in FPS
        float _fFrameRateMs;    /// frame rate delay in ms
        Uint32 _ui32Ticks;      /// SDL ticks for frame rate timer
        Color _background;      /// back ground color

    private:

        void _events();

        void _draw();
};

#endif // APPLICATION_H
