#include <Common-cpp\inc\Common.h>
#include <LoadBalancing-cpp\inc\Client.h>
#include <LoadBalancing-cpp\inc\Listener.h>
#include <iostream>
#pragma once
using namespace ExitGames;
using namespace LoadBalancing;
using namespace std;
class MonListener : public Listener
{
public:
	MonListener();
	void debugReturn(int debugLevel, const Common::JString &string);
	void ExitGames::LoadBalancing::Listener::connectReturn(int, const ExitGames::Common::JString &, const ExitGames::Common::JString &);
	void 	connectionErrorReturn(int errorCode);
	void 	clientErrorReturn(int errorCode);
	void 	warningReturn(int warningCode);
	void 	serverErrorReturn(int errorCode);
	void 	joinRoomEventAction(int playerNr, const Common::JVector< int > &playernrs, const Player &player);
	void 	leaveRoomEventAction(int playerNr, bool isInactive);
	void 	customEventAction(int playerNr, nByte eventCode, const Common::Object &eventContent);
	void 	connectReturn(int errorCode, const Common::JString &errorString);
	void 	disconnectReturn(void);
	void 	createRoomReturn(int localPlayerNr, const Common::Hashtable &roomProperties, const Common::Hashtable &playerProperties, int errorCode, const Common::JString &errorString);
	void 	joinOrCreateRoomReturn(int localPlayerNr, const Common::Hashtable &roomProperties, const Common::Hashtable &playerProperties, int errorCode, const Common::JString &errorString);
	void 	joinRoomReturn(int localPlayerNr, const Common::Hashtable &roomProperties, const Common::Hashtable &playerProperties, int errorCode, const Common::JString &errorString);
	void 	joinRandomRoomReturn(int localPlayerNr, const Common::Hashtable &roomProperties, const Common::Hashtable &playerProperties, int errorCode, const Common::JString &errorString);
	void 	leaveRoomReturn(int errorCode, const Common::JString &errorString);
	void 	joinLobbyReturn(void);
	void 	leaveLobbyReturn(void);
	void 	onFindFriendsResponse(void);
	void 	onLobbyStatsResponse(const Common::JVector< LobbyStatsResponse > &);
	void 	webRpcReturn(int, const Common::JString &, const Common::JString &, int, const Common::Dictionary< Common::Object, Common::Object > &);
	void 	onRoomListUpdate(void);
	void 	onRoomPropertiesChange(const Common::Hashtable &);
	void 	onPlayerPropertiesChange(int, const Common::Hashtable &);
	void 	onAppStatsUpdate(void);
	void 	onLobbyStatsUpdate(const Common::JVector< LobbyStatsResponse > &);
	void 	onCacheSliceChanged(int);
	void 	onCustomAuthenticationIntermediateStep(const Common::Dictionary< Common::JString, Common::Object > &);
	void 	onAvailableRegions(const Common::JVector< Common::JString > &, const Common::JVector< Common::JString > &);
	void 	onSecretReceival(const Common::JString &);
	~MonListener();
private:

};

