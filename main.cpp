#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cstdlib>
#include "DBClasses_preprocessed.h"
#include "exceptions.h"

class main_session{
private:
	int permissions;
	std::string last_command;
	std::string username;
	std::string password;
	std::map<std::string, void*> funcmap;
public:
	void test(){
		std::string name;
		std::vector<std::string> chosen_test;
		std::cout << "Choose the name of test" << std::endl;
		std::vector<std::string> tests = get_test(username, password);
		for (std::vector<std::string>::iterator it=tests.begin(); it != tests.end(); ++it) {
			std::cout << *it << std::endl;
		}
		std::cin >> name;
		chosen_test = get_certain_test(username, password, name);
		std::cout << chosen_test[0] << " " << chosen_test[1] << " " << "questions." << std::endl;
		int result = 0;
		int max = std::atoi(chosen_test[1]);
		std::string num;
		std::vector<std::string> answers;
		for (int i=0; i<max; i++){
			for (int j=0; j<5; j++){
				std::cout << chosen_test[2 + j + 5*i] << std::endl;
			}
			std::cin >> num;
			answers.push_back(num);
			if (std::atoi(num) == 1){
				result += 1;
			}
		}
		set_result("13.11.2001", username, password, name, result, answers);
	}
	void grades(){
		std::vector<std::vector<std::string>> marks = get_grades(username, password);
		for (std::vector<std::vector<std::string>>::iterator it=marks.begin(); it!=marks.end(); ++it){
			for (std::vector<std::string>::iterator ij=it.begin(); ij != it.end(); ++ij){
				std::cout << **ij << " ";
			}
			std::cout << std::endl;
		}
	}
	void quit(){
		throw "QUIT";
	}
	main_session(){
		std::cout << "Enter \"quit\" to end session. Enter \*sign_in\" to authorize" << std::endl;
		bool start_program = 0;
		funcmap["test"] = (void*)&test;
		funcmap["grades"] = (void*)&grades;
		funcmap["quit"] = (void*)&grades;
		std::cin >> last_command;
		if (last_command == "quit"){
			return;
		}else if(command == "sign_in"){
			std::cin >> username >> password;
			try{
				permissions = get_log(username.c_str(), password.c_str());
				bool start_program=1;
			}
			catch(const custom_exceptions exception){
				std::cout << exception.message << std::endl;
				return;
			}
		}else{
			std::cout << "Unknown command" << std::endl;
		}
		if start_program{
			main_body();
		}
	}
	void main_body(){
		while true{
			std::cout << "Enter command" << std::endl;
			std::cin >> last_command;
			try{
				if (funcmap.find(last_command) == funcmap.end()){
					std::cout << "Unknown command" <<std::endl;
				}else{
					&funcmap[last_command];
				}
			}catch(const custom_exceptions exception){
				std::cout << exception.message << std::endl;
			}catch(const std::string quit_message){
				return;
			}
		}
	}
}


int main(){
	main_session session = main_session();
	return 0;
}
