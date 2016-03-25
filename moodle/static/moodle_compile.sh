# Bash script to compile the application

# compile:
g++ *.cpp -o app.o `pkg-config gtkmm-3.0 --cflags --libs` -std=c++11

# run app if compilation was successful and parameter `run` was passed:
[ ! $? -ne 0 ] && [ "$1" == "run" ] && ./app.o
