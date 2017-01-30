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

		void while_loop_string()
		{
			int x = name.size();
			while(x != 0)
			{
				if(name.at(x) == pass.size())
				{
					cout << "new pass does not work" << endl;
				}
				else
				{
					cout << "this is working after all" << endl;
				}
				x--;
			}
		}

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
};

int main()
{
	Users new_object_user;
	string answer;
	cout << "Are you a new User? Type in yes or no" << endl;
	cin >> answer;
	if(answer == "yes")
	{
		new_object_user.register_activity();
	}
	else
	{
		new_object_user.login_system();
	}

}	


	
