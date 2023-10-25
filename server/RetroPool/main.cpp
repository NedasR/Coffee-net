#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include <SFML/Network.hpp>
#include "Server.hpp"
#include "NetworkIDHandler.hpp"

int main()
{
    sf::IpAddress serverIP = "192.168.1.153";

    unsigned short serverPort; serverPort = 60000;

    std::cout << serverPort << std::endl;

    NetworkManager networkManager;

    Server server(serverIP, serverPort);

    server.ServerInit();

    server.ServerLoop();

    return 0;
}