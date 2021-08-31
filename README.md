# ChessNet
Attempt at networking in C++ with a classic chess game. (No GUI)  
Tested with gcc(9.3.0) on linux and MacOS.  

## Thanks and Inspirations
Huge thanks to OneLoneCoder ([JavidX9](https://github.com/OneLoneCoder)) and his [video series](https://youtu.be/2hNdkYInj4g) on Networking in C++ using ASIO.  
The Networking module of this project has been inspired from his [olcPixelGameEngine](https://github.com/OneLoneCoder/olcPixelGameEngine).

## How to build
Download and Install ASIO from [here](https://think-async.com/Asio/)  or from Boost C++ library.  
or check your package manager for easier setup.

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
The `ChessNet-server` is the host side of the game.  Use it to host the game.  
The Server-side application sets up the game and waits for the opponent to connect.  

The `ChessNet-client` is the client side of the game.  Use it to connect to a game and start playing.  
The Client-side asks for the IP address, connects and starts the game if IP is valid and is accepting connections.  

> **Note :** Only IPv6 is supported right now. I had some DNS issues with IPv4.   
> It's tedious and annoying so I'll probably add a better alternative sometime later.  
> Probably..


## Some Issues
> - IPv6 only for now. DNS issues with IPv4. Will sort that out.
> - Game never ends 
> - I killed the king
> - Game logic is not perfect 
> - Need a parity check to ensure valid game states between the two players.
> - Gotta make Spectator mode, and something to automate connections? 
> - ~~Multiple clients on same machine will conflict. Need to find a way to check foreground terminal window.~~
