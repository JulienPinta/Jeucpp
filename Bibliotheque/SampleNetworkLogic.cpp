#include "SampleNetworkLogic.h"


SampleNetworkLogic::SampleNetworkLogic(const ExitGames::Common::JString& appID, const ExitGames::Common::JString& appVersion)
	: mLoadBalancingClient(mListener, appID, appVersion)
{
}

void SampleNetworkLogic::connect(void)
{
	// connect() is asynchronous - the actual result arrives in the Listener::connectReturn() or the Listener::connectionErrorReturn() callback
	if (!mLoadBalancingClient.connect())
		EGLOG(ExitGames::Common::DebugLevel::ERRORS, L"Could not connect.");
}

void SampleNetworkLogic::run(void)
{
	mLoadBalancingClient.service(); // needs to be called regularly!
}

void SampleNetworkLogic::disconnect(void)
{
	mLoadBalancingClient.disconnect(); // disconnect() is asynchronous - the actual result arrives in the Listener::disconnectReturn() callback
}

void SampleNetworkLogic::createRoom(const ExitGames::Common::JString& roomName, nByte maxPlayers)
{
	mLoadBalancingClient.opCreateRoom(roomName, ExitGames::LoadBalancing::RoomOptions().setMaxPlayers(maxPlayers));
}


/*SampleNetworkLogic::~SampleNetworkLogic()
{
}*/
