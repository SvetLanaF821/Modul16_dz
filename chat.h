#pragma once

#include "Message.h"
#include "sha1.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <windows.h>

class Chat
{
private:

    std::string _name;                                      //имя чата
    std::map<std::string, uint*> _users;                    //пользователи чата
    std::vector<std::shared_ptr<Message>> _messages;        //все сообщения
    std::string _curentUserName = "";                       //текущий пользователь

public:
    Chat(std::string n);
    ~Chat();

    void working();                                         //работа чата
    void createUser();                                      //создать юзера
    void chatEntry();                                       //вход в чат
    void workingUser();                                     //работа чата от юзера
    void readMessages() const;                              //чтение сообщений
    void writeMessage();                                    //написать сообщение
    void changePassword();                                  //изменить пароль
    void showUsersInfo();                                   //показать информацию о пользователях
};