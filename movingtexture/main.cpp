
// Example file: moving texture
// Operation info: move a square tex with WASD keys
// SDL2 components: hardware renderer, keyboard input

#include <iostream>
#include <SDL2/SDL.h>

// gfx constants
constexpr int screenWidth = 640;  // px
constexpr int screenHeight = 480; // px
constexpr int squareTexSize = 64; // px
const char *textureFile = "assets/tex.bmp";

// auxiliary type declarations
using SdlWindowPtr = SDL_Window*;
using SdlSurfacePtr = SDL_Surface*;
using SdlRendererPtr = SDL_Renderer*;

// custom SDL initialization - create window and renderer
bool initSdl(SdlWindowPtr& window, SdlSurfacePtr& screenSurface, SdlRendererPtr& renderer);

// function for loading a texture from img file
SDL_Texture* loadSdlTexture(const char* filename, SDL_Renderer* renderer);

// processing input
void processSdlInputEvents(bool *quit, bool *moveDown, bool *moveUp, bool *moveLeft, bool *moveRight);

int main(int argc, char *argv[])
{
     // SDL structure pointers (all null for start)

     // window in which we display
     SDL_Window* window = nullptr;

     // surface on the screen
     SDL_Surface* screenSurface = nullptr;

     // renderer (can be software or hardware renderer)
     SDL_Renderer* renderer = nullptr;

     // texture to be drawn on the screen
     SDL_Texture* texture = nullptr;

     // initialize SDL
     if (!initSdl(window, screenSurface, renderer))
     {
          std::cout << "Could not initialize SDL!\n";
          return -1;
     }

     // set background fill color to white RGBA (255,255,255,255)
     SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);

     // load texture
     texture = loadSdlTexture(textureFile, renderer);
     if (!texture)
     {
          std::cout << "Failed to load texture!";
          return -1;
     }

     // object position on the screen
     int xPos = 100;
     int yPos = 100;

     bool quit = false;

     // program main loop
     while (quit == false)
     {
          bool isMoveUpPressed = false;
          bool isMoveDownPressed = false;
          bool isMoveLeftPressed = false;
          bool isMoveRightPressed = false;

          // handle event queue
          processSdlInputEvents(&quit, &isMoveDownPressed, &isMoveUpPressed,
                                &isMoveLeftPressed, &isMoveRightPressed);

          // perform action based on output - move the object
          if (isMoveUpPressed)
               yPos -= 5;
          if (isMoveDownPressed)
               yPos += 5;
          if (isMoveLeftPressed)
               xPos -= 5;
          if (isMoveRightPressed)
               xPos += 5;

          // rectangle in which a texture will be put into
          SDL_Rect r{xPos, yPos, squareTexSize, squareTexSize};

          // clear screen
          SDL_RenderClear(renderer);

          // copy to the screen
          SDL_RenderCopy(renderer, texture, nullptr, &r);
          SDL_RenderPresent(renderer);

          // wait some milliseconds
          SDL_Delay(50);
     }

     // cleanup
     SDL_DestroyTexture(texture);
     SDL_DestroyWindow(window);
     SDL_Quit();
}

// here we pass pointer-type object by reference
// because we want to modify the pointer itself - change its address inside the function
bool initSdl(SdlWindowPtr& window, SdlSurfacePtr& screenSurface, SdlRendererPtr& renderer)
{
     // initialize video driver
     if (SDL_Init(SDL_INIT_VIDEO) < 0)
     {
          std::cout << "Error while initializing SDL: " << SDL_GetError() << "\n";
          return false;
     }

     // create a window with title
     window = SDL_CreateWindow(
         "Test SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
         screenWidth, screenHeight, SDL_WINDOW_SHOWN);

     if (window == nullptr)
     {
          std::cout << "Error while creating a window!\n";
          return false;
     }

     // create renderer for rendering textures, we use hardware renderer - ACCELERATED
     renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
     if (renderer == nullptr)
     {
          std::cout << "Error while creating renderer!\n";
          return false;
     }
     screenSurface = SDL_GetWindowSurface(window);
     return true;
}

SDL_Texture* loadSdlTexture(const char* filename, SDL_Renderer* renderer)
{
     // temporary surface needed to create a texture
     // load
     SDL_Surface* tmpSurface = SDL_LoadBMP(filename);
     if (tmpSurface == nullptr)
     {
          std::cout << "could not load image file\n";
          return nullptr;
     }

     SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
     if (texture == nullptr)
     {
          std::cout << "could not create a texture\n";
          return nullptr;
     }

     SDL_FreeSurface(tmpSurface);

     return texture;
}

void processSdlInputEvents(bool* quit, bool* moveDown, bool* moveUp, bool* moveLeft, bool* moveRight)
{
     SDL_Event e;

     // while event queue is not empty...
     while (SDL_PollEvent(&e))
     {
          // check event type
          // quit event
          if (e.type == SDL_QUIT)
          {
               *quit = true;
          }
          // check keyboard
          else if (e.type == SDL_KEYDOWN)
          {
               switch (e.key.keysym.sym)
               {
               case SDLK_w:
                    *moveUp = true;
                    break;
               case SDLK_a:
                    *moveLeft = true;
                    break;
               case SDLK_s:
                    *moveDown = true;
                    break;
               case SDLK_d:
                    *moveRight = true;
                    break;
               }
          }
     }
}