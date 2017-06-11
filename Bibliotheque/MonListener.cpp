#include "MonListener.h"



MonListener::MonListener()
{
}

void MonListener::connectReturn(int, const ExitGames::Common::JString &, const ExitGames::Common::JString &) {
	cout << "test connectReturn1" << endl;
}


void MonListener::debugReturn(int debugLevel, const Common::JString &string) {
	cout << "test debugreturn" << endl;
}

void MonListener::connectReturn(int errorCode, const Common::JString &errorString) {
	cout << "connectReturn2" << endl;
}
void 	MonListener::connectionErrorReturn(int errorCode) {
	cout << "connectionErrorReturn" << endl;
}
void 	MonListener::clientErrorReturn(int errorCode) {
	cout << "test ClienErrorReturn" << endl;
}
void 	MonListener::warningReturn(int warningCode)
{
	cout << "WarningReturn" << endl;
}
void 	MonListener::serverErrorReturn(int errorCode) {
	cout << "serverErrorReturn" << endl;
}
void 	MonListener::joinRoomEventAction(int playerNr, const Common::JVector< int > &playernrs, const Player &player) {
	cout << "JoinRoomEventAction" << endl;
}
void 	MonListener::leaveRoomEventAction(int playerNr, bool isInactive) {
	cout << "LeaveRoomEventAction" << endl;
}
void 	MonListener::customEventAction(int playerNr, nByte eventCode, const Common::Object &eventContent) {
	cout << "customEventAction" << endl;
}
void 	MonListener::disconnectReturn(void) {
	cout << "disconnectReturn" << endl;
}
void 	MonListener::createRoomReturn(int localPlayerNr, const Common::Hashtable &roomProperties, const Common::Hashtable &playerProperties, int errorCode, const Common::JString &errorString) {
	cout << "createRoomReturn" << endl;
}
void 	MonListener::joinOrCreateRoomReturn(int localPlayerNr, const Common::Hashtable &roomProperties, const Common::Hashtable &playerProperties, int errorCode, const Common::JString &errorString) {
	cout << "joinOrCreateRoomReturn" << endl;
}
void 	MonListener::joinRoomReturn(int localPlayerNr, const Common::Hashtable &roomProperties, const Common::Hashtable &playerProperties, int errorCode, const Common::JString &errorString) {
	cout << "JoinRoomReturn" << endl;
}
void 	MonListener::joinRandomRoomReturn(int localPlayerNr, const Common::Hashtable &roomProperties, const Common::Hashtable &playerProperties, int errorCode, const Common::JString &errorString) {
	cout << "joinRandomRoomReturn" << endl;
}
void 	MonListener::leaveRoomReturn(int errorCode, const Common::JString &errorString) {
	cout << "leaveRoomReturn" << endl;
}
void 	MonListener::joinLobbyReturn(void) {
	cout << "joinLobbyReturn" << endl;
}
void 	MonListener::leaveLobbyReturn(void) {
	cout << "LeaveLobbyReturn" << endl;
}
void 	MonListener::onFindFriendsResponse(void) {
	cout << "onFindFriendsResponse" << endl;
}
void 	MonListener::onLobbyStatsResponse(const Common::JVector< LobbyStatsResponse > &) {
	cout << "onLobbyStatsResponse" << endl;
}
void 	MonListener::webRpcReturn(int, const Common::JString &, const Common::JString &, int, const Common::Dictionary< Common::Object, Common::Object > &) {
	cout << "webRpcReturn" << endl;
}
void 	MonListener::onRoomListUpdate(void) {
	cout << "onRoomListUpdate" << endl;
}
void 	MonListener::onRoomPropertiesChange(const Common::Hashtable &) {
	cout << "onRoomPorpertiesChange" << endl;
}
void 	MonListener::onPlayerPropertiesChange(int, const Common::Hashtable &) {
	cout << "onPlayerPropertieschange" << endl;
}
void 	MonListener::onAppStatsUpdate(void) {
	cout << "onAppStatsUpdate" << endl;
}
void 	MonListener::onLobbyStatsUpdate(const Common::JVector< LobbyStatsResponse > &) {
	cout << "onLobbyStatsUpdate" << endl;
}
void 	MonListener::onCacheSliceChanged(int) {
	cout << "onCacheSlideChanged" << endl;
}
void 	MonListener::onCustomAuthenticationIntermediateStep(const Common::Dictionary< Common::JString, Common::Object > &) {
	cout << "onCustomeAuthenticationIntermediateStep" << endl;
}
void 	MonListener::onAvailableRegions(const Common::JVector< Common::JString > &, const Common::JVector< Common::JString > &) {
	cout << "onAvailableRegions" << endl;
}
void 	MonListener::onSecretReceival(const Common::JString &) {
	cout << "onSecretReceival" << endl;
}


MonListener::~MonListener()
{
}
