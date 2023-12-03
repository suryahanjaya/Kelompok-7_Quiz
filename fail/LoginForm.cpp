//----------------------------------------------------------------------------------------------------

#include <fmx.h>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#pragma hdrstop

#include "LoginForm.h"
//----------------------------------------------------------------------------------------------------
#pragma package (smart_init)
#pragma resource "*.fmx"
TMyLoginForm *MyLoginForm;
//----------------------------------------------------------------------------------------------------
__fastcall TMyLoginFor::TMyLoginForm(TComponent* owner)
    : TForm(owner)
{
}
std::vector<std::string> parseCommaDelimitedString(std::string line) {
    std::vector<std::string> result;
    std::stringstream s_stream(line);

    while(s_stream.good()) {
        std::string substr;
        getline(s_stream,substr,',');
        result.push_back(substr);
    }
    return result;
}
const char* converToCharPtr(AnsiString ansiStr){
    return ansiStr.c_str();
}
//----------------------------------------------------------------------------------------------------
void__fastcall TMyLoginFor::loginButtonClick(TObject *sender)
{
    fstream myFile;
    myFile.open("registeredUsers.txt", ios::in);

    if(myFile.is_open()) {
        std::string line;

        while(getline(myFile,line)){
            std::vector<std::string> parsedLine= parseCommaDelimitedString(line);
            const char* username= parsedLine.at(2).c_str();

            // AnsiString editUsername=usernameEdit->Text;
            // const char* usernameString=editUsername.c_str();
            
            if (std::strcmp(username,converToCharPtr(usernameEdit->Text))==0){
                const char* password= parsedLine.at(3).c_str();

                // AnsiString editpassword=passwordEdit->Text;
                // const char* passwordString=editPassword.c_str();

                if(std:strcmp(password,converToCharPtr(passwordEdit))==0) 
                    messageLabel->Text="Success!";
                else
                    messageLabel->Text="Wrong password!";

            }
        }
    }
}
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
