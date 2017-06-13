#include "Console.h"
#include "NetworkLogic.h"


class StdUI : public NetworkLogicListener
{
public:
	StdUI(void);
	void main(void);
	void main_loop();
private:
	virtual void stateUpdate(State newState) {}
	void usage(void);
	static NetworkLogic& getNetworkLogic(void);

	bool mExit;
};