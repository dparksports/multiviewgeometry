# Build

## dev libraries
- Boost, Eigen, opencv 4.x

### Boost
```sh
cd boost_1_74_0/
./bootstrap.sh 
./b2
sudo ./b2 install
```  

### Eigen
```sh
cd eigen-3.3.7/
mkdir build && cd build;cmake ..
sudo make install
```    

### openCV
```sh
git clone git@github.com:opencv/opencv_contrib.git
git clone git@github.com:opencv/opencv.git
cd opencv-4.4.0/
mkdir build && cd build
cmake -DOPENCV_EXTRA_MODULES_PATH='~/Downloads/opencv_contrib-4.4.0/modules' ..
make
sudo make install
```    


```sh
sudo apt install build-essential cmake git pkg-config libgtk-3-dev \
    libavcodec-dev libavformat-dev libswscale-dev libv4l-dev \
    libxvidcore-dev libx264-dev libjpeg-dev libpng-dev libtiff-dev \
    gfortran openexr libatlas-base-dev python3-dev python3-numpy \
    libtbb2 libtbb-dev libdc1394-22-dev
```    
    
```sh
cmake -D CMAKE_BUILD_TYPE=RELEASE \
    -D CMAKE_INSTALL_PREFIX=/usr/local \
    -D INSTALL_C_EXAMPLES=ON \
    -D INSTALL_PYTHON_EXAMPLES=ON \
    -D OPENCV_GENERATE_PKGCONFIG=ON \
    -D OPENCV_EXTRA_MODULES_PATH=~/opencv_contrib/modules \
    -D BUILD_EXAMPLES=ON ..

export EIGEN3_INCLUDE_DIR=/usr/local/include/eigen3
export CMAKE_PREFIX_PATH=$CMAKE_PREFIX_PATH:/usr/local/share/eigen3/



```


