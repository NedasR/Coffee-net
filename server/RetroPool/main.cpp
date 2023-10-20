#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include <SFML/Network.hpp>


int main()
{
    sf::RenderWindow window(sf::VideoMode(400, 400), "Coffee's Server");

    unsigned int serverPort;

    sf::IpAddress serverIP = "192.168.1.153";

    unsigned short clinetPort;
    std::string clinetIP;

    sf::IpAddress rec = "192.168.1.153";

    sf::UdpSocket socket;
    serverPort = 60000;

    sf::TcpListener listner;
    listner.setBlocking(false);

    socket.setBlocking(false);
    if (socket.bind(serverPort, serverIP) != sf::Socket::Done)
    {
        std::cout << "nope";
    };

    std::cout << serverPort << std::endl;

    char data[100];

    std::size_t received;

    std::size_t size = 100;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        if (socket.receive(data, size, received, rec, clinetPort) == sf::Socket::Done)
        {
            std::cout << std::string(data,received) << std::endl;
        }

        if (listner.listen(60000, serverIP) != sf::Socket::Done)
        {
            //std::cout << "this got pinged";
        }

        window.clear();
        //window.draw();
        window.display();
    }
    return 0;
}