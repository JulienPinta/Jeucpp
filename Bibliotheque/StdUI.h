#include "Console.h"
#include "NetworkLogic.h"
#include "monMain.h"


class StdUI : public NetworkLogicListener
{
public:
	StdUI(void);
	void main(void);
	void main_loop(void);
private:
	virtual void stateUpdate(State newState) {}
	void usage(void);
	static NetworkLogic& getNetworkLogic(void);

	bool mExit;
};