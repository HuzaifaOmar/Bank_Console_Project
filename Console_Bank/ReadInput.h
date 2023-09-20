	#pragma once

	#include <iostream>;
	#include <string>;
	using namespace std;

	namespace ReadInput
	{
		int ReadInt(string Message)
		{
			int Num;
			cout << Message;
			cin >> Num;

			//validate input is a number
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				cout << "Please enter a number!" << endl;
				cout << Message;
				cin >> Num;
			}

			return Num;
		}
		int ReadInt(string Message, int From, int To, string ErrorMessage = "Invalid Input")
		{
			int Num;
			cout << Message;
			cin >> Num;

			//validate input is a number
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				cout << "Please enter a number!" << endl;
				cout << Message;
				cin >> Num;
			}
			//validate condition
			while (Num < From || Num > To)
			{
				cout << ErrorMessage << endl;
				cout << Message;
				cin >> Num;
			}

			return Num;
		}

		int ReadPositiveInt(string Message)
		{
			int Num;
			cout << Message;
			cin >> Num;

			//validate input is a number
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				cout << "Please enter a number!" << endl;
				cout << Message;
				cin >> Num;
			}
			while (Num < 0)
			{
				cout << "Please enter a positive number" << endl;
				cout << Message; 
				cin >> Num;
			}
	
			return Num;
		}
		int ReadPositiveInt(string Message, int From, int To, string ErrorMessage = "Invalid Input")
		{
			int Num;
			cout << Message;
			cin >> Num;
			
			//validate input is a number
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				cout << "Please enter a number!" << endl;
				cout << Message;
				cin >> Num;
			}
			while (Num < 0)
			{
				cout << "Please enter a positive number" << endl;
				cout << Message;
				cin >> Num;
			}
			//validate condition
			while (Num < From || Num > To)
			{
				cout << ErrorMessage << endl;
				cout << Message;
				cin >> Num;
			}


			return Num;
		}

		short ReadShort(string Message)
		{
			short Num;
			cout << Message;
 			cin >> Num;

			//validate input is a number
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				cout << "Please enter a number!: ";
				cin >> Num;
			}
			return Num;
		}
		short ReadShort(string Message, int From, int To, string ErrorMessage = "Invalid Input")
		{
			short Num;
			cout << Message;
			cin >> Num;

			//validate input is a number
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				cout << "Please enter a number!" << endl;
				cout << Message;
				cin >> Num;
			}
			//validate condition
			while (Num < From || Num > To)
			{
				cout << ErrorMessage << endl;
				cout << Message;
				cin >> Num;
			}

			return Num;
		}

		short ReadPositiveShort(string Message)
		{
			short Num;
			cout << Message;
			cin >> Num;

			//validate input is a number
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				cout << "Please enter a number!" << endl;
				cout << Message;
				cin >> Num;
			}
			while (Num < 0)
			{
				cout << "Please enter a positive number" << endl;
				cout << Message;
				cin >> Num;
			}

			return Num;
		}
		short ReadPositiveShort(string Message, int From, int To, string ErrorMessage = "Invalid Input")
		{
			short Num;
			cout << Message;
			cin >> Num;

			//validate input is a number
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				cout << "Please enter a number!" << endl;
				cout << Message;
				cin >> Num;
			}
			while (Num < 0)
			{
				cout << "Please enter a positive number" << endl;
				cout << Message;
				cin >> Num;
			}
			//validate condition
			while (Num < From || Num > To)
			{
				cout << ErrorMessage << endl;
				cout << Message;
				cin >> Num;
			}


			return Num;
		}

		float ReadFLoat(string Message)
		{
			float flt;
			cout << Message;
			cin >> flt;

			while (cin.fail())
			{
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				cout << "Please enter a number!: ";
				cin >> flt;
			}

			return flt;
		}
		float ReadFLoat(string Message, int From, int To, string ErrorMessage = "Invalid Input")
		{
			float flt;
			cout << Message;
			cin >> flt;

			//validate input is a number
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				cout << "Please enter a number!" << endl;
				cout << Message;
				cin >> flt;
			}
			//validate condition
			while (flt < From || flt > To)
			{
				cout << ErrorMessage << endl;
				cout << Message;
				cin >> flt;
			}

			return flt;
		}
	
		float ReadPositiveFloat(string Message)
		{
			float flt;
			cout << Message;
			cin >> flt;

			while (cin.fail())
			{
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				cout << "Please enter a number!: ";
				cin >> flt;
			}

			while (flt < 0)
			{
				cout << "Please enter a positive number: ";
			}

			return flt;
		}
		float ReadPositiveFloat(string Message, int From, int To, string ErrorMessage = "Invalid Input")
		{
			float flt;
			cout << Message;
			cin >> flt;

			//validate input is a number
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				cout << "Please enter a number!" << endl;
				cout << Message;
				cin >> flt;
			}
			while (flt < 0)
			{
				cout << "Please enter a positive number" << endl;
				cout << Message;
				cin >> flt;
			}
			//validate condition
			while (flt < From || flt > To)
			{
				cout << ErrorMessage << endl;
				cout << Message;
				cin >> flt;
			}


			return flt;
		}

		char ReadChar(string Message)
		{
			char ch;
			cout << Message;
			cin >> ch;

			return ch;
		}

		string ReadString(string Message)
		{
			string st;
			cout << Message;
			getline(cin, st);

			return st;
		}

		bool YesOrNo(string Message)
		{
			char C;

			cout << Message;
			cin >> C;

			while ((tolower(C) != 'y') && (tolower(C) != 'n'))
			{
				cout << "Please enter a valid input" << endl;
				cout << Message;
				cin >> C;
			}
			if (tolower(C) == 'y')
			{
				return 1;
			}
			return 0;
		}

	}

