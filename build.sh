
echo `sdl2-config --cflags --libs`
g++ -o programMovingTexture movingtexture/main.cpp `sdl2-config --cflags --libs`
