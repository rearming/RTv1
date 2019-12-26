if [[ ! -f "libft/Makefile" ]]; then
  git submodule init
  git submodule update --merge --remote
fi
cd libft || echo "can't find libft directory!"
make
cd ..
mkdir build
cd build || echo "can't make build directory!"
cmake -DCMAKE_BUILD_TYPE=Release ..
make RTv1 -j 4
mv RTv1 ..
