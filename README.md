# ChessNet
Attempt at networking in C++ with a classic chess game. (No GUI)  
Tested with gcc(9.3.0) on linux and MacOS Big sur.  

# Thanks and Inspirations
Huge thanks to OneLoneCoder ([JavidX9](https://github.com/OneLoneCoder)) and his [video series](https://youtu.be/2hNdkYInj4g) on Networking in C++ using ASIO.  
The Networking module of this project has been inspired from his [olcPixelGameEngine](https://github.com/OneLoneCoder/olcPixelGameEngine).

## How to build
Download and Install ASIO from [here](https://think-async.com/Asio/)  or from Boost C++ library.  
or check your package manager for easier setup.

~~`cmake file to be added soon.`~~  
CMAKE added. 

##### To Build
Clone the repository.  
Navigate to repo directory.  
Type the following commands in terminal :

```
mkdir Build && cd Build  
cmake ..  
cmake --build .  
```

## Run 
Once you've built the executables, you're ready to start playing!  
The `ChessNet-server` is the host side of the game.  Use it to host the game and wait for a client to connect.  
The `ChessNet-client` is the client side of the game.  Use it to connect to a game and start playing.  


## ~~How to contribute~~

# Disclaimer
> - Game never ends
> - I killed the king
> - Game logic is not perfect 
> - ~~Multiple clients on same machine will conflict. Need to find a way to check foreground terminal window.~~
