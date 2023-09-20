#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>
#include "ReadInput.h"

using namespace std;
using namespace ReadInput;

static string ClientsDataFileName = "ClientsData.txt";
static string UsersDataFileName = "Users.txt";

//this enum has "op" prefix
enum enMainOptions
{
	opShowClientList = 1,
	opAddNewClient = 2,
	opDeleteClient = 3,
	opUpdateClientInfo = 4,
	opFindClient = 5,
	opTransaction = 6,
	opManageUsers = 7,
	opExit = 8
};
//this enum has "trans" prefix
enum enTransactionOptions
{
	transDeposit = 1,
	transWithdraw = 2,
	transTotalBalances = 3,
	transMainMenu = 4
};
//this enum has "user" prefix
enum enUserOptions
{
	userListUsers = 1,
	userAddNewUser = 2,
	userDeleteUser = 3,
	userUpdateUser = 4,
	userFindUser = 5,
	userMainMenu = 6,
};


struct stClientData
{
	string AccountNumber, PinCode, ClientName, PhoneNumber;
	float AccountBalance;
	bool MarkToDelete = false;
};
struct stUser
{
	string UserName;
	short Password, Permissions = 0;
	bool MarkToDelete = false;
};


//function declarations
enMainOptions MainMenu();
void TransactionMenu();


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
string stClientDataTo_RecordLine(stClientData Client, string delimiter = " /_\\ ")
{
	string str = "";
	str += Client.AccountNumber + delimiter;
	str += Client.PinCode + delimiter;
	str += Client.ClientName + delimiter;
	str += Client.PhoneNumber + delimiter;
	str += to_string(Client.AccountBalance);

	return str;
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
void LoadVectorToFile(string FileName, vector<stClientData> vClients)
{
	string Record = "";
	fstream File;
	File.open(ClientsDataFileName, ios::out);//overwrite mode

	for (stClientData& Client : vClients)
	{
		if (Client.MarkToDelete == false)
		{
			Record = stClientDataTo_RecordLine(Client);
			File << Record << endl;
		}
	}
	//Refreshing the vector with the new file data
	vClients = LoadFileToVector_stClientData(FileName);
}

//Client Operations
void PrintClientData(stClientData Client)
{
	cout << "\n\t\t Client Info" << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "Account Number : " << Client.AccountNumber << endl;
	cout << "Pin Code       : " << Client.PinCode << endl;
	cout << "Name           : " << Client.ClientName << endl;
	cout << "Phone Number   : " << Client.PhoneNumber << endl;
	cout << "Account Balance: " << Client.AccountBalance << endl;
	cout << "-------------------------------------------------" << endl;
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
			PrintClientData(Client);
			return ClientPosition;
		}
		ClientPosition++;
	}
	return -1;
}
stClientData UpdateClientInfo(string AccountNumber)
{
	stClientData Client;
	Client.AccountNumber = AccountNumber;

	// Usage of std::ws will extract all the whitespace character   
	cout << "Enter Name: ";
	getline(cin >> ws, Client.ClientName);

	Client.PhoneNumber = ReadString("Enter Phone Number: ");
	Client.PinCode = ReadString("Enter Pin Code: ");
	Client.AccountBalance = ReadFLoat("Enter Account Balance: ");

	return Client;
}


//Transaction Operations
void DepositScreen()
{
	cout << "-------------------------------------------------" << endl;
	cout << "\t\t Deposit Screen" << endl;
	cout << "-------------------------------------------------" << endl;

	string AccountNumber;
	//to avoid whitespaces
	cout << "Enter Account Number: ";
	getline(cin >> ws, AccountNumber);

	short ClientPosition = FindClient(AccountNumber);
	if (ClientPosition == -1)
	{
		cout << "Client With Account Number [" << AccountNumber << "] Not Found!";
	}
	else
	{
		int DepositAmount = ReadPositiveInt("Please enter deposit amount: ");

		if (YesOrNo("Are you sure you want to perform this transaction ? [Y / N]  "))
		{
			vector<stClientData> vClients = LoadFileToVector_stClientData(ClientsDataFileName);
			vClients[ClientPosition].AccountBalance += DepositAmount;
			LoadVectorToFile(ClientsDataFileName, vClients);
			cout << "Transaction Successful!" << endl;
		}
	}
}
void WithDrawScreen()
{
	cout << "-------------------------------------------------" << endl;
	cout << "\t\t Withdraw Screen" << endl;
	cout << "-------------------------------------------------" << endl;

	string AccountNumber;
	//to avoid whitespaces
	cout << "Enter Account Number: ";
	getline(cin >> ws, AccountNumber);

	short ClientPosition = FindClient(AccountNumber);
	if (ClientPosition == -1)
	{
		cout << "Client With Account Number [" << AccountNumber << "] Not Found!";
	}
	else
	{
		vector<stClientData> vClients = LoadFileToVector_stClientData(ClientsDataFileName);
		int WithdarawalAmount = ReadPositiveInt("Please enter withdrawal amount: ");

		while (WithdarawalAmount > vClients[ClientPosition].AccountBalance)
		{
			cout << "Withdrawal Exceeds Account Balance, You can withdraw up to: " << vClients[ClientPosition].AccountBalance << endl;
			WithdarawalAmount = ReadPositiveInt("Please enter valid withdrawal amount: ");
		}

		if (YesOrNo("Are you sure you want to perform this transaction ? [Y / N]  "))
		{

			vClients[ClientPosition].AccountBalance -= WithdarawalAmount;
			LoadVectorToFile(ClientsDataFileName, vClients);
			cout << "Transaction Successful!" << endl;
		}
	}

}
void BalancesListScreen()
{
	vector<stClientData> vClients = LoadFileToVector_stClientData(ClientsDataFileName);
	int TotalBalances = 0;
	cout << "\t\t\t\tClient List (" << vClients.size() << ") Client(s)" << endl;
	cout << "_______________________________________________________________" << endl << endl;
	cout << "| Account Number | Client Name                    | Balance  " << endl;
	cout << "_______________________________________________________________" << endl;
	for (stClientData Client : vClients)
	{
		TotalBalances += Client.AccountBalance;
		cout << "| " << setw(15) << left << Client.AccountNumber;
		cout << "| " << setw(31) << left << Client.ClientName;
		cout << "| " << setw(9) << left << Client.AccountBalance;

		cout << endl;
	}
	cout << "_______________________________________________________________" << endl;
	cout << "\t\tTotal Balances = " << TotalBalances;
}
void PerformTransactionOption(enTransactionOptions option)
{
	switch (option)
	{
	case transDeposit:
		DepositScreen();
		break;
	case transWithdraw:
		WithDrawScreen();
		break;
	case transTotalBalances:
		BalancesListScreen();
		break;
	default:
		break;
	}
}


//stUser <> RecordLine
stUser RecordLineTo_stUser(string Record, string delimiter = " /_\\ ")
{
	vector<string> vUsers = SplitString(Record);
	stUser User;

	User.UserName = vUsers[0];
	User.Password = (short)stoi(vUsers[1]);
	User.Permissions = (short)stoi(vUsers[2]);

	return User;
}
string stUserTo_RecordLine(stUser User, string delimiter = " /_\\ ")
{
	string str = "";
	str += User.UserName + delimiter;
	str += to_string(User.Password) + delimiter;
	str += to_string(User.Permissions);

	return str;
}

//File <> Vector_stUser
vector<stUser> LoadFileToVector_stUser(string FileName)
{
	vector<stUser> vUsers;

	string Line = "";

	fstream File;
	File.open(FileName, ios::in);

	while (getline(File, Line))
	{
		vUsers.push_back(RecordLineTo_stUser(Line));
	}
	File.close();

	return vUsers;
}
void LoadVectorToFile(string FileName, vector<stUser> vUsers)
{
	string Record = "";
	fstream File;
	File.open(FileName, ios::out);//overwrite mode

	for (stUser& User : vUsers)
	{
		if (User.MarkToDelete == false)
		{
			Record = stUserTo_RecordLine(User);
			File << Record << endl;
		}
	}
	//Refreshing the vector with the new file data
	vUsers = LoadFileToVector_stUser(FileName);
}

//User Operations
int ReadUserPermissions(stUser& user)
{

	if (YesOrNo("Do you want to give user full access? [Y/N]  "))
	{
		user.Permissions = -1;
		return 0;
	}
	YesOrNo("\nAccess to show client list: [Y/N]  ") ? (user.Permissions += 64) : 0;
	YesOrNo("\nAccess to add new client: [Y/N]  ") ? (user.Permissions += 32) : 0;
	YesOrNo("\nAccess to delete client: [Y/N]  ") ? (user.Permissions += 16) : 0;
	YesOrNo("\nAccess to update client: [Y/N]  ") ? (user.Permissions += 8) : 0;
	YesOrNo("\nAccess to find client: [Y/N]  ") ? (user.Permissions += 4) : 0;
	YesOrNo("\nAccess to perform transactions: [Y/N]  ") ? (user.Permissions += 2) : 0;
	YesOrNo("\nAccess to manage users: [Y/N]  ") ? (user.Permissions += 1) : 0;

	(user.Permissions == 127) ? user.Permissions = -1 : 0;

}
bool GiveUserPermission(stUser user, enMainOptions option)
{
	if (user.Permissions == -1)
		return 1;

	switch (option)
	{
	case opShowClientList:
		if ((user.Permissions & 1) == 1)
			return 1;
		else
			return 0;
		break;
	case opAddNewClient:
		if ((user.Permissions & 2) == 2)
			return 1;
		else
			return 0;
		break;
	case opDeleteClient:
		if ((user.Permissions & 4) == 4)
			return 1;
		else
			return 0;
		break;
	case opUpdateClientInfo:
		if ((user.Permissions & 8) == 8)
			return 1;
		else
			return 0;
		break;
	case opFindClient:
		if ((user.Permissions & 16) == 16)
			return 1;
		else
			return 0;
		break;
	case opTransaction:
		if ((user.Permissions & 32) == 32)
			return 1;
		else
			return 0;
		break;
	case opManageUsers:
		if ((user.Permissions & 64) == 64)
			return 1;
		else
			return 0;
		break;
	case opExit:
		return 1;
		break;
	default:
		break;
	}
	
}
void PrintUser (stUser User)
{
	cout << "\n\t\t User Info" << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "User Name : " << User.UserName << endl;
	cout << "Password  : " << User.Password << endl;
	cout << "Permission: " << User.Permissions << endl;
	cout << "-------------------------------------------------" << endl;
}
short FindUser(string UserName)
{
	vector<stUser> vUsers = LoadFileToVector_stUser(UsersDataFileName);
	short UserPosition = 0;
	for (stUser User: vUsers)
	{
		if (User.UserName == UserName)
		{
			return UserPosition;
		}
		UserPosition++;
	}
	return -1;
}
stUser UpdateUserInfo(string UserName)
{
	stUser User;
	User.UserName = UserName;
	
	User.Password  = ReadPositiveShort("Enter User Password: ");
	ReadUserPermissions(User);

	return User;
}

//Manage Users Options
void ListUsersScreen()
{
	vector<stUser> vUsers = LoadFileToVector_stUser(UsersDataFileName);
	cout << "\t\t\t\tUsers List (" << vUsers.size() << ") User(s)" << endl;
	cout << "______________________________________________" << endl << endl;
	cout << "| User Name           | Password | Permissions  " << endl;
	cout << "______________________________________________" << endl;
	for (stUser User : vUsers)
	{
		cout << "| " << setw(20) << left << User.UserName;
		cout << "| " << setw(9) << left << User.Password;
		cout << "| " << setw(11) << left << User.Permissions;

		cout << endl;
	}
	cout << "_______________________________________________" << endl;

}
void AddNewUserScreen()
{
	cout << "-------------------------------------------------" << endl;
	cout << "\t\t Add User Screen" << endl;
	cout << "-------------------------------------------------" << endl;

	vector<stUser> vUsers = LoadFileToVector_stUser(UsersDataFileName);

	//ws to avoid whitespaces
	string UserName;
	cout << "Enter Username: ";
	getline(cin >> ws, UserName);

	bool AddNewUser = 1;

	do
	{
		//if the account number matches with an existing account
		while ((FindUser(UserName) != -1) && AddNewUser)
		{
			cout << "User [" << UserName << "] already exists, ";
			AddNewUser = YesOrNo("Do you want to try again? [Y/N]  ");
			UserName = ReadString(", Enter Account Number: ");
		}

		if (AddNewUser)
		{
			vUsers.push_back(UpdateUserInfo(UserName));
			cout << "New User Added Successfully, ";
			AddNewUser = YesOrNo("Do you want to add more users? [Y/N] ");
		}

		if (AddNewUser)
		{
			cout << "Enter Username: ";
			getline(cin >> ws, UserName);
		}
	} while (AddNewUser);

	LoadVectorToFile(UsersDataFileName, vUsers);
}
void DeleteUserScreen()
{
	cout << "-------------------------------------------------" << endl;
	cout << "\t\t Delete User Screen" << endl;
	cout << "-------------------------------------------------" << endl;

	string UserName;
	//to avoid whitespaces
	cout << "Enter Username: ";
	getline(cin >> ws, UserName);

	short UserPosition = FindUser(UserName);

	if (UserPosition == -1)
	{
		cout << "User With Username [" << UserName << "] Not Found!";
	}
	else 
	{
		vector<stUser> vUsers = LoadFileToVector_stUser(UsersDataFileName);
		PrintUser(vUsers[UserPosition]);

		if (YesOrNo("Are you sure you want to delete this Account ? [Y / N]  "))
		{
			vUsers[UserPosition].MarkToDelete = 1;
			LoadVectorToFile(UsersDataFileName, vUsers);
		}
	}
}
void UpdateUserScreen()
{
	cout << "-------------------------------------------------" << endl;
	cout << "\t    Update User Screen" << endl;
	cout << "-------------------------------------------------" << endl;

	string UserName;
	//to avoid whitespaces
	cout << "Enter Username: ";
	getline(cin >> ws, UserName);

	short UserPosition = FindUser(UserName);

	if (UserPosition == -1)
	{
		cout << "User With Username [" << UserName << "] Not Found!";
	}
	else 
	{
		vector<stUser> vUsers = LoadFileToVector_stUser(UsersDataFileName);
		PrintUser(vUsers[UserPosition]);

		if (YesOrNo("Are you sure you want to update this user? [Y / N]  "))
		{
			vUsers[UserPosition] = UpdateUserInfo(UserName);
			LoadVectorToFile(UsersDataFileName, vUsers);
		}
	}
}
void FindUserScreen()
{
	cout << "-------------------------------------------------" << endl;
	cout << "\t\t Find User Screen" << endl;
	cout << "-------------------------------------------------" << endl;

	string UserName;
	//to avoid whitespaces
	cout << "Enter Username: ";
	getline(cin >> ws, UserName);

	short UserPosition = FindUser(UserName);

	if (UserPosition == -1)
		cout << "User With Username [" << UserName << "] Not Found!" << endl;
	else
	{
		vector<stUser> vUsers = LoadFileToVector_stUser(UsersDataFileName);
		PrintUser(vUsers[UserPosition]);
	}
}
void PerformUserOption(enUserOptions option)
{
	switch (option)
	{
	case userListUsers:
		ListUsersScreen();
		break;
	case userAddNewUser:
		AddNewUserScreen();
		break;
	case userDeleteUser:
		DeleteUserScreen();
		break;
	case userUpdateUser:
		UpdateUserScreen();
		break;
	case userFindUser:
		FindUserScreen();
		break;
	default:
		break;
	}
}



//Bank Operations
void ShowClientListScreen()
{
	vector<stClientData> vClients = LoadFileToVector_stClientData(ClientsDataFileName);
	cout << "\t\t\t\tClient List (" << vClients.size() << ") Client(s)" << endl;
	cout << "_________________________________________________________________________________________" << endl << endl;
	cout << "| Account Number | Pin Code  | Client Name                    | Phone Number  | Balance  " << endl;
	cout << "_________________________________________________________________________________________" << endl;
	
	//Printing each client
	for (stClientData Client : vClients)
	{
		cout << "| " << setw(15) << left << Client.AccountNumber;
		cout << "| " << setw(10) << left << Client.PinCode;
		cout << "| " << setw(31) << left << Client.ClientName;
		cout << "| " << setw(14) << left << Client.PhoneNumber;
		cout << "| " << setw(9) << left << Client.AccountBalance;

		cout << endl;
	}

	cout << "_________________________________________________________________________________________" << endl;
}
void AddNewClientScreen()
{
	cout << "-------------------------------------------------" << endl;
	cout << "\t\t Add Client Screen" << endl;
	cout << "-------------------------------------------------" << endl;

	vector<stClientData> vClients = LoadFileToVector_stClientData(ClientsDataFileName);

	//ws to avoid whitespaces
	string AccountNumber;
	cout << "Enter Account Number: ";
	getline(cin >> ws, AccountNumber);

	bool AddNewClient = 1;

	do
	{
		//if the account number matches with an existing account
		while ((FindClient(AccountNumber) != -1) && AddNewClient)
		{
			cout << "Account [" << AccountNumber << "] already exists, ";
			AddNewClient = YesOrNo("Do you want to try again? [Y/N]  ");

			cout << "Enter Account Number: ";
			getline(cin >> ws, AccountNumber);
		}

		if (AddNewClient)
		{
			vClients.push_back(UpdateClientInfo(AccountNumber));
			cout << "New Client Added Successfully, ";
			AddNewClient = YesOrNo("Do you want to add more clients? [Y/N] ");
		}

		if (AddNewClient)
		{
			cout << "Enter Account Number: ";
			getline(cin >> ws, AccountNumber);
		}
	} while (AddNewClient);

	LoadVectorToFile(ClientsDataFileName, vClients);
}
void DeleteClientScreen()
{
	cout << "-------------------------------------------------" << endl;
	cout << "\t\t Delete Client Screen" << endl;
	cout << "-------------------------------------------------" << endl;

	string AccountNumber;
	//to avoid whitespaces
	cout << "Enter Account Number: ";
	getline(cin >> ws, AccountNumber);

	short ClientPosition = FindClient(AccountNumber);

	if (ClientPosition == -1)
	{
		cout << "Client With Account Number [" << AccountNumber << "] Not Found!";
	}
	else if (YesOrNo("Are you sure you want to delete this Account ? [Y / N]  "))
	{
		vector<stClientData> vClients = LoadFileToVector_stClientData(ClientsDataFileName);
		vClients[ClientPosition].MarkToDelete = 1;
		LoadVectorToFile(ClientsDataFileName, vClients);
	}
}
void UpdateClientInfoScreen()
{
	cout << "-------------------------------------------------" << endl;
	cout << "\t    Update Client Info Screen" << endl;
	cout << "-------------------------------------------------" << endl;

	string AccountNumber;
	//to avoid whitespaces
	cout << "Enter Account Number: ";
	getline(cin >> ws, AccountNumber);

	short ClientPosition = FindClient(AccountNumber);

	if (ClientPosition == -1)
	{
		cout << "Client With Account Number [" << AccountNumber << "] Not Found!";
	}
	else if (YesOrNo("Are you sure you want to update this Account ? [Y / N]  "))
	{
		vector<stClientData> vClients = LoadFileToVector_stClientData(ClientsDataFileName);
		vClients[ClientPosition] = UpdateClientInfo(AccountNumber);
		LoadVectorToFile(ClientsDataFileName, vClients);
	}
}
void FindClientScreen()
{
	cout << "-------------------------------------------------" << endl;
	cout << "\t\t Find Client Screen" << endl;
	cout << "-------------------------------------------------" << endl;

	string AccountNumber;
	//to avoid whitespaces
	cout << "Enter Account Number: ";
	getline(cin >> ws, AccountNumber);

	if (FindClient(AccountNumber) == -1)
	{
		cout << "Client With Account Number [" << AccountNumber << "] Not Found!" << endl;
	}
}
enTransactionOptions TransactionMenuScreen()
{
	cout << "-------------------------------------------------" << endl;
	cout << "\t\t Transactions Menu Screen" << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "\t[1] Deposit." << endl;
	cout << "\t[2] Withdraw." << endl;
	cout << "\t[3] Total Balances." << endl;
	cout << "\t[4] Main Menu." << endl;
	cout << "-------------------------------------------------" << endl;

	return (enTransactionOptions)ReadShort("Choose What to You want to do ? [1 to 4]  ", 1 , 4);
}
void TransactionMenu()
{
	enTransactionOptions UserOption;
	do
	{
		system("cls");
		UserOption = TransactionMenuScreen();

		if (UserOption != enTransactionOptions::transMainMenu)
		{
			system("cls");
			PerformTransactionOption(UserOption);
			cout << "\n\nPress any key to go back to transaction menu...";
			system("pause > 0");
		}

	} while (UserOption != enTransactionOptions::transMainMenu);

}
enUserOptions ManageUsersMenuScreen()
{
	cout << "-------------------------------------------------" << endl;
	cout << "\t\t Manage Users Menu Screen" << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "\t[1] List Users." << endl;
	cout << "\t[2] Add New User." << endl;
	cout << "\t[3] Delete User." << endl;
	cout << "\t[4] Update User." << endl;
	cout << "\t[5] Find User." << endl;
	cout << "\t[6] Main Menu." << endl;
	cout << "------------------------------------------------" << endl;

	return (enUserOptions)ReadShort("Choose What to You want to do ? [1 to 6]  ", 1, 6);
}
void ManageUsersMenu()
{
	enUserOptions UserOption;
	do
	{
		system("cls");
		UserOption = ManageUsersMenuScreen();

		if (UserOption != enUserOptions::userMainMenu)
		{
			system("cls");
			PerformUserOption(UserOption);
			cout << "\n\nPress any key to go back to manage users menu...";
			system("pause > 0");
		}

	} while (UserOption != enUserOptions::userMainMenu);
}


//Home Page 
enMainOptions MainMenu()
{
	cout << "-------------------------------------------------" << endl;
	cout << "\t\t Main Menu Screen" << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "\t[1] Show Client List." << endl;
	cout << "\t[2] Add New Client." << endl;
	cout << "\t[3] Delete Client." << endl;
	cout << "\t[4] Update Client Info." << endl;
	cout << "\t[5] Find Client." << endl;
	cout << "\t[6] Transactions." << endl;
	cout << "\t[7] Manage Users." << endl;
	cout << "\t[8] Exit." << endl;
	cout << "-------------------------------------------------" << endl;

	return (enMainOptions)ReadShort("Choose What to You want to do? [1 to 8]  ", 1, 8);
}
void ExecuteOption(enMainOptions option)
{
	switch (option)
	{
	case opShowClientList:
		ShowClientListScreen();
		break;
	case opAddNewClient:
		AddNewClientScreen();
		break;
	case opDeleteClient:
		DeleteClientScreen();
		break;
	case opUpdateClientInfo:
		UpdateClientInfoScreen();
		break;
	case opFindClient:
		FindClientScreen();
		break;
	case opTransaction:
		TransactionMenu();
		break;
	case opManageUsers:
		ManageUsersMenu();
	default:
		break;
	}
}


void Bank(stUser User)
{
	enMainOptions UserOption;
	do
	{
		system("cls");
		UserOption = MainMenu();
		if (GiveUserPermission(User, UserOption))
		{
			system("cls");
			ExcuteOption(UserOption);
			if (UserOption != enMainOptions::opExit)
			{
				cout << "\n\nPress any key to go back to main menue...." << endl;
				system("pause > 0");
			}
			else
			{

				break;
			}
		}
		else
		{
			system("cls");
			cout << "-----------------------------------------------------------" << endl;
			cout << "Access Denied\n";
			cout << "You do not have permission to perform this option\n";
			cout << "If you think this is a mistake, please contact your admin\n";
			cout << "-----------------------------------------------------------" << endl;

			cout << "\n\nPress any key to go back to main menu...." << endl;
			system("pause > 0");
		}

	} while (UserOption != enMainOptions::opExit);

	cout << "-------------------------------------------------" << endl;
	cout << "\t     Terminating Program :-)" << endl;
	cout << "-------------------------------------------------" << endl;
}
void Login()
{
	cout << "-------------------------------------------------" << endl;
	cout << "\t\t Login Screen" << endl;
	cout << "-------------------------------------------------" << endl;

	string UserName = "";
	short Password = 0;
	bool WrongAnswer = 1;
	do
	{
		cout << "Enter username: ";
		getline(cin >> ws, UserName);
		short UserPosition = FindUser(UserName);
		if (UserPosition == -1)
		{
			cout << "\nWrong Username!\n";
			WrongAnswer = YesOrNo("Try Again? [Y/N]  ");
		}
		else
		{
			Password = ReadPositiveShort("Enter Password: ");
			vector<stUser> vUsers = LoadFileToVector_stUser(UsersDataFileName);

			if (vUsers[UserPosition].Password == Password)
			{
				WrongAnswer = false;
				Bank(vUsers[UserPosition]);
			}
			else
			{
				cout << "\nWrong Password!\n";
				WrongAnswer = YesOrNo("Try Again? [Y/N]  ");
			}
		}

	} while (WrongAnswer);

}


int main()
{
	Login();
}