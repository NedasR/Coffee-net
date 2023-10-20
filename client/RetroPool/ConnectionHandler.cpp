#include "ConnectionHandler.hpp"
#include "ProcessPacket.hpp"
void ConnectionHandler::PingListener()
{
	if (m_tcpSocket.receive(packet) == sf::Socket::Done)
	{
		//ProcessPacket::UnPackPacket(packet);
	}

}
