#include <Common-cpp\inc\Common.h>
#include <LoadBalancing-cpp\inc\Client.h>
#include <LoadBalancing-cpp\inc\Listener.h>
#include "MonListener.h"
#pragma once
using namespace ExitGames;
using namespace LoadBalancing;

class SampleNetworkLogic
{
public:
	SampleNetworkLogic(const ExitGames::Common::JString& appID, const ExitGames::Common::JString& appVersion);
	void connect(void);
	void disconnect(void);
	void run(void);
	void createRoom(const ExitGames::Common::JString& roomName, nByte maxPlayers);
private:
	RoomOptions roomOptions;
	ExitGames::LoadBalancing::Client mLoadBalancingClient;
	MonListener mListener; // your implementation of the ExitGames::LoadBalancing::Listener interface
	ExitGames::Common::Logger mLogger; // accessed by EGLOG()
};

//EXEMPLE
/*
int main(void)
{
	static const ExitGames::Common::JString appID = L"2a1a1b5b-7a32-4a96-8f2b-2a5b6454062c"; // set your app id here
	static const ExitGames::Common::JString appVersion = L"1.0";

	SampleNetworkLogic networkLogic(appID, appVersion);
	

	networkLogic.connect();
}*/
	