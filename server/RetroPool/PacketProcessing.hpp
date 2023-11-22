#pragma once

#include <SFML/Network.hpp>
#include <chrono>

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
};

enum class ObjectTypeIDs : sf::Uint8
{
	None = 0,
	Character = 1,
};

class PacketProcessing
{
	private:

	public:

	static std::chrono::milliseconds serverTimeStamp;

	static void ProcessPacket(sf::Packet packet);

};