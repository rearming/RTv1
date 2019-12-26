mkdir build
cd build || echo "can't make build directory!"
cmake -DCMAKE_BUILD_TYPE=Release ..
make RTv1 -j 4
mv RTv1 ..