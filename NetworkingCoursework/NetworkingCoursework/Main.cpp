#include "Server.h"
#include "Client.h"
#include "Game.h"

int main()
{
	Game gameObj;
	Server serverObj;
	Client clientObj;
	

	char connectionType;
	std::cout << "(s) for server, (c) for client: ";
	std::cin >> connectionType;

	if (connectionType == 's')
	{
		serverObj.runTcpServer();
	}
	else
	{
		clientObj.runTcpClient();
	}


	//gameObj.setupTCPServer(); 
	//gameObj.setupTCPClient();


	//gameObj.runGame();

	//game is server window open?
}