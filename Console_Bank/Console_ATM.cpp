#include <iostream>
#include <vector>
#include <fstream>
#include "ReadInput.h"

using namespace std;
using namespace ReadInput;

static string ClientsDataFileName = "ClientsData.txt";


struct stClientData
{
	string AccountNumber, PinCode, ClientName, PhoneNumber;
	float AccountBalance;
	bool MarkToDelete = false;
};


//stClientData <> RecordLine
vector<string> SplitString(string str, string delimiter = " /_\\ ")
{
	vector<string> vStrings;
	short pos = 0;
	string word = "";

	while ((pos = str.find(delimiter)) != string::npos)
	{
		word = str.substr(0, pos);
		if (word != "")
		{
			vStrings.push_back(word);
		}
		str.erase(0, pos + delimiter.length());
	}
	if (str != "")
	{
		vStrings.push_back(str);
	}

	return vStrings;
}
stClientData RecordLineTo_stClientData(string Record, string delimiter = " /_\\ ")
{
	vector<string> vClient = SplitString(Record);
	stClientData Client;

	Client.AccountNumber = vClient[0];
	Client.PinCode = vClient[1];
	Client.ClientName = vClient[2];
	Client.PhoneNumber = vClient[3];
	Client.AccountBalance = stof(vClient[4]);

	return Client;
}


//File <> Vector_stClient
vector<stClientData> LoadFileToVector_stClientData(string FileName)
{
	vector<stClientData> vClients;

	string Line = "";

	fstream File;
	File.open(FileName, ios::in);

	while (getline(File, Line))
	{
		vClients.push_back(RecordLineTo_stClientData(Line));
	}
	File.close();

	return vClients;
}


/*FindClient() returns the Line index and print client's info
if the client is not found it returns (-1)*/
short FindClient(string AccountNumber)
{
	vector<stClientData> vClients = LoadFileToVector_stClientData(ClientsDataFileName);
	short ClientPosition = 0;
	for (stClientData Client : vClients)
	{
		if (Client.AccountNumber == AccountNumber)
		{
			return ClientPosition;
		}
		ClientPosition++;
	}
	return -1;
}


void Login()
{
	cout << "-------------------------------------------------" << endl;
	cout << "\t\t Login Screen" << endl;
	cout << "-------------------------------------------------" << endl;

	string UserName = "", PinCode = "";
	bool WrongAnswer = 1;
	do
	{
		cout << "Enter username: ";
		getline(cin >> ws, UserName);
		short UserPosition = FindClient(UserName);
		if (UserPosition == -1)
		{
			cout << "\nWrong Username!\n";
			WrongAnswer = YesOrNo("Try Again? [Y/N]  ");
		}
		else
		{
			PinCode = ReadPositiveShort("Enter Pin Code: ");
			vector<stClientData> vClients = LoadFileToVector_stClientData(ClientsDataFileName);

			if (vClients[UserPosition].PinCode == PinCode)
			{
				WrongAnswer = false;
			}
			else
			{
				cout << "\nWrong Pin Code!\n";
				WrongAnswer = YesOrNo("Try Again? [Y/N]  ");
			}
		}

	} while (WrongAnswer);

}

int main()
{
	Login();
}