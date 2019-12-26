# RTv1
Simple raytracing project written in C.
It uses SDL2 library and accelerated on GPU via OpenCL.


### Build (Mac OS):
```
./compile.sh
```

### Build (Linux):

**You must have SDL2 and OpenCL installed.**
Ubuntu based distributions:
```
sudo apt install libsdl2-2.0-0
sudo apt install libsdl2-dev
```
Than you need to install OpenCL and it's headers. This can be tricky and vary between platforms.
You can use clinfo to verify installation of OpenCL:
```
sudo apt install clinfo
clinfo
```
And, finally
```
./compile.sh
```

### Run:
```
./RTv1 scenes/*.rtv1
```

### Examples:

**scene1.rtv1**
![Image alt](https://github.com/rearming/RTv1/raw/master/screenshots/scene1.png)
**temple.rtv1**
![Image alt](https://github.com/rearming/RTv1/raw/master/screenshots/temple.png)

### Feel free to modify scenes, according to this format:
```
sphere
{ center(0, -1, 3) radius(1) color(0xFF0000) specular(500) }

cylinder
{ pos(0, 0, 0) rotation(45, 0, 0) radius(1) length(10) color(0x7830E0) specular(200) }

plane
{ pos(0, -4, 0) normal(0, 1, 0) color(0xFFFFFF) specular(200) }

cone
{ pos(10, 0, 10} rotation(90, 0, 0) angle(10) length(10) color(0xFF00FF) specular(200) }

light
{ type(point) intensity(0.8) pos(6, -2, 1) dir() }

camera
{ pos(15, 0, 25) rotation(9, -150, 0) }
```
### Hope you enjoy!
