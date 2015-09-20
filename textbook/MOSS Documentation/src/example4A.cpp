#include <iostream>
#include <vector>

using namespace std;


class Users
{
	private:
		string password;
		string username;

	public:
		vector<Users> registered_users;

		Users(){}
		Users(string user1, string pw)
		:username(user1), password(pw)
		{}

		
		void register_activity()
		{
			string new_username, new_password;
			cout << "Please enter in your new username: ";
			cin >> new_username;
			cout << endl;
			cout << "Please enter in your new password: ";
			cin >> new_password;
			Users information(new_username, new_password);
			registered_users.push_back(information);
			int vect_size = registered_users.size();
			cout << "New Users credentials, Username: " 
			<< registered_users.at(vect_size - 1).username << endl << "Password: " 
			<< registered_users.at(vect_size - 1).password << endl;
		}	

		void loop_string()
		{
			for(int x = 0; x < username.size(); x++)
			{
				if(username.at(x) == a + x)
				{
					cout << "this works right now" << endl;
				}
				else
				{
					cout << "not working at alll" << endl;
				}
			}
		}
};

int main()
{
	string possible_answer = "yes";
	registrant new_object_user;
	string response;
	cout << "new users only, are you one of them?";
	cin >> response;
	if(response == possible_answer)
	{
		new_object_user.create_user();
	}
	else
	{
		new_object_user.logins();
	}

}