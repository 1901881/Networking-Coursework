#include <iostream>

using namespace std;

int main()
{
	//Creates class objects necessary for run


	//Asks for whether the user wants to run the client or the server protocol
	char connectionType;
	std::cout << "(s) for rer, (c) for client: ";
	std::cin >> connectionType;

	if (connectionType == 's')
	{
		//serverObj.initialiseServer();
	}
	else
	{
		//clientObj.initialiseClient();
	}
}