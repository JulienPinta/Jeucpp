#include "NetworkLogic.h"
#include<string.h>
#include <SFML/Graphics.hpp>





static const ExitGames::Common::JString appId = L"26067891-e671-49e0-9644-556529bedbac"; // set your app id here
static const ExitGames::Common::JString appVersion = L"1.0";

static const bool autoLobbyStats = true;
#if defined EG_PLATFORM_SUPPORTS_CPP11 && defined EG_PLATFORM_SUPPORTS_MULTITHREADING
// pinging takes a moment, so for a real game it makes sense to retrive the best region with getRegionWithBestPing(), store it in a file, use RegionSelectionMode::SELECT and pass that region to selectRegion() and to only use RegionSelectionMode::BEST, if no best region has been determined yet or if the player explicitly requests to repeat pinging
static const nByte regionSelectionMode = ExitGames::LoadBalancing::RegionSelectionMode::BEST;

#endif

static const ExitGames::Common::JString PLAYER_NAME = L"Windows";


ExitGames::Common::JString& NetworkLogicListener::toString(ExitGames::Common::JString& retStr, bool /*withTypes*/) const
{
	return retStr;
}

State StateAccessor::getState(void) const
{
	return mState;
}

void StateAccessor::setState(State newState)
{
	mState = newState;
	for (unsigned int i = 0; i<mStateUpdateListeners.getSize(); i++)
		mStateUpdateListeners[i]->stateUpdate(newState);
}

void StateAccessor::registerForStateUpdates(NetworkLogicListener* listener)
{
	mStateUpdateListeners.addElement(listener);
}

Input NetworkLogic::getLastInput(void) const
{
	return mLastInput;
}

void NetworkLogic::setLastInput(Input newInput)
{
	mLastInput = newInput;
}

State NetworkLogic::getState(void) const
{
	return mStateAccessor.getState();
}

// functions
NetworkLogic::NetworkLogic(OutputListener* listener)
#ifdef _EG_MS_COMPILER
#	pragma warning(push)
#	pragma warning(disable:4355)
#endif
	: mLoadBalancingClient(*this, appId, appVersion, ExitGames::Photon::ConnectionProtocol::DEFAULT, autoLobbyStats, regionSelectionMode)
	, mLastPlayerNr(0)
	, mLastInput(INPUT_NON)
	, mpOutputListener(listener)
	, mAutoJoinRoom(false)
	, fond(RectangleShape(Vector2f(1920, 1080)))
	, window(sf::VideoMode(1920, 1080), "SFML works!")

#ifdef _EG_MS_COMPILER
#	pragma warning(pop)
#endif
{
	mStateAccessor.setState(STATE_INITIALIZED);
	mLoadBalancingClient.setDebugOutputLevel(DEBUG_RELEASE(ExitGames::Common::DebugLevel::INFO, ExitGames::Common::DebugLevel::WARNINGS)); // that instance of LoadBalancingClient and its implementation details
	mLogger.setListener(*this);
	mLogger.setDebugOutputLevel(DEBUG_RELEASE(ExitGames::Common::DebugLevel::INFO, ExitGames::Common::DebugLevel::WARNINGS)); // this class
	ExitGames::Common::Base::setListener(this);
	ExitGames::Common::Base::setDebugOutputLevel(DEBUG_RELEASE(ExitGames::Common::DebugLevel::INFO, ExitGames::Common::DebugLevel::WARNINGS)); // all classes that inherit from Base
	fond.setFillColor(Color(119, 181, 254));
	window.draw(fond);
	window.display();
}

void NetworkLogic::registerForStateUpdates(NetworkLogicListener* listener)
{
	mStateAccessor.registerForStateUpdates(listener);
}

void NetworkLogic::connect(void)
{
	mpOutputListener->writeLine(ExitGames::Common::JString(L"connecting to Photon"));
	mLoadBalancingClient.connect(ExitGames::LoadBalancing::AuthenticationValues().setUserID(ExitGames::Common::JString() + GETTIMEMS()), PLAYER_NAME);
	mStateAccessor.setState(STATE_CONNECTING);
}

void NetworkLogic::disconnect(void)
{
	mLoadBalancingClient.disconnect();
}

void NetworkLogic::opCreateRoom(void)
{
	ExitGames::Common::JString name;
	name += GETTIMEMS();
	mLoadBalancingClient.opCreateRoom(name, ExitGames::LoadBalancing::RoomOptions().setMaxPlayers(4).setPlayerTtl(INT_MAX / 2).setEmptyRoomTtl(10000));
	mStateAccessor.setState(STATE_JOINING);
	mpOutputListener->writeLine(ExitGames::Common::JString(L"creating room ") + name + L"...");
}

void NetworkLogic::opJoinRandomRoom(void)
{
	mLoadBalancingClient.opJoinRandomRoom();
}

void NetworkLogic::opJoinOrCreateRoom(void)
{
	ExitGames::Common::JString name(L"DemoLoadBalancing");
	mLoadBalancingClient.opJoinOrCreateRoom(name);
	mStateAccessor.setState(STATE_JOINING);
	mpOutputListener->writeLine(ExitGames::Common::JString(L"joining or creating room ") + name + L"...");
}

void NetworkLogic::run(void)
{
	State state = mStateAccessor.getState();
	if (mLastInput == INPUT_EXIT && state != STATE_DISCONNECTING && state != STATE_DISCONNECTED)
	{
		disconnect();
		mStateAccessor.setState(STATE_DISCONNECTING);
		mpOutputListener->writeLine(L"terminating application");
	}
	else
	{
		switch (state)
		{

		case PLAYING:
			
			window.clear();
			window.draw(fond);
			plat.draw(window);
			sf::Event event;
			window.pollEvent(event);
			gestionClavier();
			ajouterElement();
			plat.tourne();

			window.display();

			switch (mLastInput)
			{
			case INPUT_1: // leave Game
				window.clear();
				window.draw(fond);
				window.display();
				mLoadBalancingClient.opLeaveRoom();
				mpOutputListener->writeLine(L"");
				mpOutputListener->writeLine(L"leaving room");
				mStateAccessor.setState(STATE_LEAVING);
				break;
			case INPUT_2: // leave Game
				window.clear();
				window.draw(fond);
				window.display();
				mLoadBalancingClient.opLeaveRoom(true);
				mpOutputListener->writeLine(L"");
				mpOutputListener->writeLine(L"leaving room (will come back)");
				mStateAccessor.setState(STATE_LEAVING);
				break;
			}
			break;


		case STATE_INITIALIZED:
			//mpOutputListener->writeLine(L"INITIALIZED");
			connect();
			break;
		case STATE_CONNECTING:
			//mpOutputListener->writeLine(L"CONNECTING");
			break; // wait for callback
		case STATE_CONNECTED:
			//mpOutputListener->writeLine(L"CONNECTED");
			switch (mLastInput)
			{
			case INPUT_1: // create Game
				mpOutputListener->writeLine(L"\n=========================");
				opCreateRoom();


				break;
			case INPUT_2: // join Game
				mpOutputListener->writeLine(L"\n=========================");
				// remove false to enable rejoin
				if (mLastJoinedRoom.length())
				{
					mpOutputListener->writeLine(ExitGames::Common::JString(L"rejoining ") + mLastJoinedRoom + " with actorNr = " + mLastPlayerNr + "...");
					mLoadBalancingClient.opJoinRoom(mLastJoinedRoom, mLastPlayerNr);
				}
				else
				{
					mpOutputListener->writeLine(ExitGames::Common::JString(L"joining random room..."));
					opJoinRandomRoom();
				}
				mStateAccessor.setState(STATE_JOINING);
				// il faut recevoir le plateau de la room et le passer en argument
				sendEventString(ExitGames::Common::JString(L"Bonjour"));
				//mStateAccessor.setState(PLAYING);
				break;
			default: // no or illegal input -> stay waiting for legal input
				break;
			}
			break;
		case STATE_CREATED:
			switch (mLastInput) {
			case INPUT_3:
				mStateAccessor.setState(PLAYING);
				break;
			}
			//mpOutputListener->writeLine(L"Waiting for another player");
			break;
		case STATE_JOINING:
			//mpOutputListener->writeLine(L"JOINING");
			break; // wait for callback
		case STATE_JOINED:
			sendEventJoin();
			mStateAccessor.setState(PLAYING);
			mpOutputListener->writeLine(L"JOINED");
			//sendEvent();
			switch (mLastInput)
			{
			case INPUT_1: // leave Game
				mLoadBalancingClient.opLeaveRoom();
				mpOutputListener->writeLine(L"");
				mpOutputListener->writeLine(L"leaving room");
				mStateAccessor.setState(STATE_LEAVING);
				break;
			case INPUT_2: // leave Game
				mLoadBalancingClient.opLeaveRoom(true);
				mpOutputListener->writeLine(L"");
				mpOutputListener->writeLine(L"leaving room (will come back)");
				mStateAccessor.setState(STATE_LEAVING);
				break;
			case INPUT_3: //play
				mStateAccessor.setState(PLAYING);
				break;
			default: // no or illegal input -> stay waiting for legal input
				break;
			}
			break;
		case STATE_LEAVING:
			//mpOutputListener->writeLine(L"LEAVING");
			break; // wait for callback
		case STATE_LEFT:
			//mpOutputListener->writeLine(L"LEFT");
			mStateAccessor.setState(STATE_CONNECTED);
			break;
		case STATE_DISCONNECTING:
			//mpOutputListener->writeLine(L"DISCONNECTING");
			break; // wait for callback
		default:
			break;
		}
	}
	mLastInput = INPUT_NON;
	mLoadBalancingClient.service();
}


void NetworkLogic::gestionClavier(void) {

	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		plat.moveJoueur1(0,-1);
		sendEventMovey(-1);
	}
	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		plat.moveJoueur1(0, 1);
		sendEventMovey(1);
	}
	
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		plat.moveJoueur1(1,0);
		sendEventMovex(1);
	}
	
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		plat.moveJoueur1(-1,0);
		sendEventMovex(-1);
	}
}

// random entre 0 et7 
int NetworkLogic::d7()
{
	static std::random_device rd;
	static std::default_random_engine engine(rd());
	static std::uniform_int_distribution<> distribution(0, 7);
	return distribution(engine);
}

// random entre 0 et 1000

int NetworkLogic::d1000()
{
	static std::random_device rd;
	static std::default_random_engine engine(rd());
	static std::uniform_int_distribution<> distribution(0, 1000);
	return distribution(engine);
}

void NetworkLogic::ajouterElement() {
	int y = 120 * d7();

	bool libre = plat.disponible(y);

	if (libre && d1000() < 5) {
		ajouterNoisette(y);
		sendEventNoisette(y);
	}
	// 10 chances sur 190 de faire apparaitre un nuage;
	if (libre && d1000() > 985) {
		ajouterNuage(y);
		sendEventNuage(y);
	}
}

void NetworkLogic::ajouterNoisette(int y) {
	auto nois = make_unique<noisette>(1920, y);
	plat.add(nois->copy());
}

void NetworkLogic::ajouterNuage(int y) {
	auto nuag = make_unique<nuage>(1920, y);
	plat.add(nuag->copy());
}

void NetworkLogic::sendEvent(void)
{
	static int64 count = 0;
	mLoadBalancingClient.opRaiseEvent(false, ++count, 0);
	mpOutputListener->write(ExitGames::Common::JString(L"s") + count + L" ");
}

void NetworkLogic::sendEventMovex(int x)
{
	
	mLoadBalancingClient.opRaiseEvent(false, x, 3);
}

void NetworkLogic::sendEventMovey( int y)
{
	
	mLoadBalancingClient.opRaiseEvent(false, y, 4);
}

void NetworkLogic::sendEventString(ExitGames::Common::JString myString)
{
	mLoadBalancingClient.opRaiseEvent(false, myString, 1);
	//mpOutputListener->write(ExitGames::Common::JString(L"Bonjour envoy�"));
}

void NetworkLogic::sendEventJoin(void)
{
	mLoadBalancingClient.opRaiseEvent(false, 0, 2);
	
}


void NetworkLogic::sendEventNoisette(int y)
{
	mLoadBalancingClient.opRaiseEvent(false, y, 5);

}

void NetworkLogic::sendEventNuage(int y)
{
	mLoadBalancingClient.opRaiseEvent(false, y, 6);

}



// protocol implementations

void NetworkLogic::debugReturn(int debugLevel, const ExitGames::Common::JString& string)
{
	mpOutputListener->debugReturn(debugLevel, string);
}

void NetworkLogic::connectionErrorReturn(int errorCode)
{
	EGLOG(ExitGames::Common::DebugLevel::ERRORS, L"code: %d", errorCode);
	mpOutputListener->writeLine(ExitGames::Common::JString(L"received connection error ") + errorCode);
	mStateAccessor.setState(STATE_DISCONNECTED);
}

void NetworkLogic::clientErrorReturn(int errorCode)
{
	EGLOG(ExitGames::Common::DebugLevel::ERRORS, L"code: %d", errorCode);
	mpOutputListener->writeLine(ExitGames::Common::JString(L"received error ") + errorCode + L" from client");
}

void NetworkLogic::warningReturn(int warningCode)
{
	EGLOG(ExitGames::Common::DebugLevel::WARNINGS, L"code: %d", warningCode);
	mpOutputListener->writeLine(ExitGames::Common::JString(L"received warning ") + warningCode + L" from client");
}

void NetworkLogic::serverErrorReturn(int errorCode)
{
	EGLOG(ExitGames::Common::DebugLevel::ERRORS, L"code: %d", errorCode);
	mpOutputListener->writeLine(ExitGames::Common::JString(L"received error ") + errorCode + " from server");
}

void NetworkLogic::joinRoomEventAction(int playerNr, const ExitGames::Common::JVector<int>& /*playernrs*/, const ExitGames::LoadBalancing::Player& player)
{
	EGLOG(ExitGames::Common::DebugLevel::INFO, L"%ls joined the game", player.getName().cstr());
	mpOutputListener->writeLine(L"");
	mpOutputListener->writeLine(ExitGames::Common::JString(L"player ") + playerNr + L" " + player.getName() + L" has joined the game");
	ExitGames::Common::JString myString (L"Je suis la !");
	sendEventString(myString);
}

void NetworkLogic::leaveRoomEventAction(int playerNr, bool isInactive)
{
	EGLOG(ExitGames::Common::DebugLevel::INFO, L"");
	mpOutputListener->writeLine(L"");
	mpOutputListener->writeLine(ExitGames::Common::JString(L"player ") + playerNr + L" has left the game");
}

void NetworkLogic::customEventAction(int /*playerNr*/, nByte eventCode, const ExitGames::Common::Object& eventContent)
{

	// you do not receive your own events, unless you specify yourself as one of the receivers explicitly, so you must start 2 clients, to receive the events, which you have sent, as sendEvent() uses the default receivers of opRaiseEvent() (all players in same room like the sender, except the sender itself)
	EGLOG(ExitGames::Common::DebugLevel::ALL, L"");

	switch (eventCode) {
	case 0:
		mpOutputListener->write(ExitGames::Common::JString(L"r") + ExitGames::Common::ValueObject<long long>(eventContent).getDataCopy() + L" ");
		mpOutputListener->writeLine(L"CAS0");
		break;
	case 1:
		mpOutputListener->write(ExitGames::Common::JString(L"RECU") + ExitGames::Common::ValueObject<ExitGames::Common::JString>(eventContent).getDataCopy() + L" ");
		mpOutputListener->writeLine(L"CAS1");
		break;
	case 2:
		if (mStateAccessor.getState() == STATE_CREATED)
			mStateAccessor.setState(PLAYING);
		mpOutputListener->writeLine(L"CAS2");
		break;
	case 3:
		mpOutputListener->writeLine(L"CAS3");

		plat.moveJoueur2(ExitGames::Common::ValueObject<int>(eventContent).getDataCopy(), 0);

		break;
	case 4:
		mpOutputListener->writeLine(L"CAS3");

		plat.moveJoueur2(0, ExitGames::Common::ValueObject<int>(eventContent).getDataCopy());

		break;

	case 5:
		ajouterNoisette(ExitGames::Common::ValueObject<int>(eventContent).getDataCopy());
		break;

	case 6:
		ajouterNuage(ExitGames::Common::ValueObject<int>(eventContent).getDataCopy());
		break;
	}
}

void NetworkLogic::connectReturn(int errorCode, const ExitGames::Common::JString& errorString, const ExitGames::Common::JString& cluster)
{
	EGLOG(ExitGames::Common::DebugLevel::INFO, L"connected to cluster " + cluster);
	if (errorCode)
	{
		EGLOG(ExitGames::Common::DebugLevel::ERRORS, L"%ls", errorString.cstr());
		mStateAccessor.setState(STATE_DISCONNECTING);
		return;
	}
	mpOutputListener->writeLine(L"connected to cluster " + cluster);
	mStateAccessor.setState(STATE_CONNECTED);
	if (mAutoJoinRoom)
		opJoinOrCreateRoom();
}

void NetworkLogic::disconnectReturn(void)
{
	EGLOG(ExitGames::Common::DebugLevel::INFO, L"");
	mpOutputListener->writeLine(L"disconnected");
	mStateAccessor.setState(STATE_DISCONNECTED);
}

void NetworkLogic::createRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& /*gameProperties*/, const ExitGames::Common::Hashtable& /*playerProperties*/, int errorCode, const ExitGames::Common::JString& errorString)
{
	EGLOG(ExitGames::Common::DebugLevel::INFO, L"");
	if (errorCode)
	{
		EGLOG(ExitGames::Common::DebugLevel::ERRORS, L"%ls", errorString.cstr());
		mpOutputListener->writeLine(L"opCreateRoom() failed: " + errorString);
		mStateAccessor.setState(STATE_CONNECTED);
		return;
	}
	mLastJoinedRoom = mLoadBalancingClient.getCurrentlyJoinedRoom().getName();
	mLastPlayerNr = localPlayerNr;

	EGLOG(ExitGames::Common::DebugLevel::INFO, L"localPlayerNr: %d", localPlayerNr);
	mpOutputListener->writeLine(L"... room " + mLoadBalancingClient.getCurrentlyJoinedRoom().getName() + " has been created");
	mpOutputListener->writeLine(L"regularly sending dummy events now");
	mStateAccessor.setState(STATE_CREATED);
}

void NetworkLogic::joinOrCreateRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& /*gameProperties*/, const ExitGames::Common::Hashtable& /*playerProperties*/, int errorCode, const ExitGames::Common::JString& errorString)
{
	EGLOG(ExitGames::Common::DebugLevel::INFO, L"");
	if (errorCode)
	{
		EGLOG(ExitGames::Common::DebugLevel::ERRORS, L"%ls", errorString.cstr());
		mpOutputListener->writeLine(L"opJoinOrCreateRoom() failed: " + errorString);
		mStateAccessor.setState(STATE_CONNECTED);
		return;
	}
	mLastJoinedRoom = mLoadBalancingClient.getCurrentlyJoinedRoom().getName();
	mLastPlayerNr = localPlayerNr;

	EGLOG(ExitGames::Common::DebugLevel::INFO, L"localPlayerNr: %d", localPlayerNr);
	mpOutputListener->writeLine(L"... room " + mLoadBalancingClient.getCurrentlyJoinedRoom().getName() + " has been entered");
	mpOutputListener->writeLine(L"regularly sending dummy events now");
	mStateAccessor.setState(STATE_JOINED);
}

void NetworkLogic::joinRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& /*gameProperties*/, const ExitGames::Common::Hashtable& /*playerProperties*/, int errorCode, const ExitGames::Common::JString& errorString)
{
	EGLOG(ExitGames::Common::DebugLevel::INFO, L"");
	if (errorCode)
	{
		mLastJoinedRoom = L"";
		mLastPlayerNr = 0;
		EGLOG(ExitGames::Common::DebugLevel::ERRORS, L"%ls", errorString.cstr());
		mpOutputListener->writeLine(L"opJoinRoom() failed: " + errorString);
		mStateAccessor.setState(STATE_CONNECTED);
		return;
	}
	EGLOG(ExitGames::Common::DebugLevel::INFO, L"localPlayerNr: %d", localPlayerNr);
	mpOutputListener->writeLine(L"... room " + mLoadBalancingClient.getCurrentlyJoinedRoom().getName() + " has been successfully joined");
	mpOutputListener->writeLine(L"regularly sending dummy events now");
	mStateAccessor.setState(STATE_JOINED);
}

void NetworkLogic::joinRandomRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& /*gameProperties*/, const ExitGames::Common::Hashtable& /*playerProperties*/, int errorCode, const ExitGames::Common::JString& errorString)
{
	EGLOG(ExitGames::Common::DebugLevel::INFO, L"");
	if (errorCode)
	{
		EGLOG(ExitGames::Common::DebugLevel::ERRORS, L"%ls", errorString.cstr());
		mpOutputListener->writeLine(L"opJoinRandomRoom() failed: " + errorString);
		mStateAccessor.setState(STATE_CONNECTED);
		return;
	}

	mLastJoinedRoom = mLoadBalancingClient.getCurrentlyJoinedRoom().getName();
	mLastPlayerNr = localPlayerNr;

	EGLOG(ExitGames::Common::DebugLevel::INFO, L"localPlayerNr: %d", localPlayerNr);
	mpOutputListener->writeLine(L"... room " + mLoadBalancingClient.getCurrentlyJoinedRoom().getName() + " has been successfully joined");
	mpOutputListener->writeLine(L"regularly sending dummy events now");
	mStateAccessor.setState(STATE_JOINED);
}

void NetworkLogic::leaveRoomReturn(int errorCode, const ExitGames::Common::JString& errorString)
{
	EGLOG(ExitGames::Common::DebugLevel::INFO, L"");
	if (errorCode)
	{
		EGLOG(ExitGames::Common::DebugLevel::ERRORS, L"%ls", errorString.cstr());
		mpOutputListener->writeLine(L"opLeaveRoom() failed: " + errorString);
		mStateAccessor.setState(STATE_DISCONNECTING);
		return;
	}
	mStateAccessor.setState(STATE_LEFT);
	mpOutputListener->writeLine(L"room has been successfully left");
}

void NetworkLogic::joinLobbyReturn(void)
{
	EGLOG(ExitGames::Common::DebugLevel::INFO, L"");
	mpOutputListener->writeLine(L"joined lobby");
}

void NetworkLogic::leaveLobbyReturn(void)
{
	EGLOG(ExitGames::Common::DebugLevel::INFO, L"");
	mpOutputListener->writeLine(L"left lobby");
}

void NetworkLogic::onLobbyStatsResponse(const ExitGames::Common::JVector<ExitGames::LoadBalancing::LobbyStatsResponse>& lobbyStats)
{
	EGLOG(ExitGames::Common::DebugLevel::INFO, L"%ls", lobbyStats.toString().cstr());
	mpOutputListener->writeLine(L"LobbyStats: " + lobbyStats.toString());
}

void NetworkLogic::onLobbyStatsUpdate(const ExitGames::Common::JVector<ExitGames::LoadBalancing::LobbyStatsResponse>& lobbyStats)
{
	EGLOG(ExitGames::Common::DebugLevel::INFO, L"%ls", lobbyStats.toString().cstr());
	mpOutputListener->writeLine(L"LobbyStats: " + lobbyStats.toString());
}

void NetworkLogic::onAvailableRegions(const ExitGames::Common::JVector<ExitGames::Common::JString>& availableRegions, const ExitGames::Common::JVector<ExitGames::Common::JString>& availableRegionServers)
{
	EGLOG(ExitGames::Common::DebugLevel::INFO, L"%ls / %ls", availableRegions.toString().cstr(), availableRegionServers.toString().cstr());
	mpOutputListener->writeLine(L"onAvailableRegions: " + availableRegions.toString() + L" / " + availableRegionServers.toString());
	// select first region from list
	mpOutputListener->writeLine(L"selecting region: " + availableRegions[0]);
	mLoadBalancingClient.selectRegion(availableRegions[0]);
}