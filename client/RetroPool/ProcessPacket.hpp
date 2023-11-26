#pragma once
#include <SFML/Network/Packet.hpp>

enum class PacketIDs : sf::Uint8
{	
	Ping = 1,
	RequastNetworkID = 2,
	ReceiveNetworkID = 3,
	ConnectToServer = 4,
	FailedToConnect = 5,
	PostionUpdate = 6,
	SyncObject = 7,
	LateJoinerSync = 8,
	SendCurrentTick = 9,
	SyncClientTick = 10,
	ClientSyncCallback = 11,
};

enum class ObjectTypeIDs : sf::Uint8
{
	None = 0,
	Character = 1,
};


class ProcessPacket
{
	public:

	static void ReceiveUdpPackets(sf::Packet& packet);

};