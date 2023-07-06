# SDL examples (Linux)

SDL2 simple examples.

## Setup SDL

Search for libraries
```
sudo apt search libsdl2*
```

Install libraries, example:
```
sudo apt install libsdl2-2.0-0
sudo apt install libsdl2-dev
```

It is also possible to build SDL from source. But there seems to be additional configuration to be done. When tested on Lubuntu, after successful compilation and lib installation there was a problem with a missing X11 driver. SDL could not see it.

## Build example file

```
./build.sh
```

