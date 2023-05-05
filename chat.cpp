#include "chat.h"

#define PASSLENGTH 16			                           // Длина пароля

void setColor(int text, int bg) {                          //установка цвета текста консоли
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
}

Chat::Chat(std::string n) : _name(n) {}

void Chat::working() 
{
    char choice;
    bool b{ true };
    while (b) {
        setColor(11, 0);
        std::cout << "\n********* START CHAT **********" << std::endl;
        std::cout << "0 - Exit " << std::endl;
        std::cout << "1 - Create new User " << std::endl;
        std::cout << "2 - Enter the chat as a user " << std::endl;
        std::cout << "3 - Show info about users" << std::endl;
        std::cin >> choice;
        switch (choice) {
        case '0':
            b = false;
            break;
        case '1':
            createUser();
            break;
        case '2':
            chatEntry();
            break;
        case '3':
            showUsersInfo();
            break;
        default:
            setColor(4, 0);
            std::cout << "Retry please..." << std::endl;
            break;
        }
    }
}

void Chat::createUser()
{
    setColor(7, 0);
    std::cout << "Creating a new user" << std::endl;
    std::cout << "Enter user login:" << std::endl;
    std::string login;
    std::cin >> login;
    std::cout << "Enter user password:" << std::endl;
    char password[PASSLENGTH];
    std::cin >> password;
           
    if (login == "all" || _users.find(login) != _users.end())
    {
        setColor(4, 0);
        std::cout << "Error. This login already exists." << std::endl;
    }
    else
    {
        uint* hashPass = sha1(password, PASSLENGTH);
        std::cout << *hashPass << std::endl;
        _users.emplace(login, hashPass);
    }
}

void Chat::chatEntry()
{
    setColor(7, 0);
    std::cout << "Enter login: ";
    std::string login;
    std::cin >> login;
    std::cout << "Enter password: ";
    char password[PASSLENGTH];
    std::cin >> password;
    uint* hashPass = sha1(password, PASSLENGTH);
    std::cout << *hashPass << std::endl;
    std::map <std::string, uint* >::iterator it = _users.find(login);
    
    if (it == _users.end())     
    {
        _curentUserName.clear();
        setColor(4, 0);
        std::cout << "Login error. " << std::endl;
    }
    else if (it != _users.end() && (memcmp(hashPass, it->second, SHA1HASHLENGTHBYTES) != 0)) {
        _curentUserName.clear();
        setColor(4, 0);
        std::cout << "Password error." << std::endl;
    }
    else
    {
        _curentUserName = it->first;
        workingUser();
    }
}

void Chat::workingUser()
{
    bool b{ true };

    while (b) {
        setColor(9, 0);
        std::cout << "\n********** " << "User " << _curentUserName << " **********" << std::endl;
        std::cout << "0 - back" << std::endl;
        std::cout << "1 - read messages" << std::endl;
        std::cout << "2 - to write a message" << std::endl;
        std::cout << "3 - change password" << std::endl;

        char choice;
        std::cin >> choice;
        switch (choice) {
        case '0':
            b = false;
            break;
        case '1':
            readMessages();
            break;
        case '2':
            writeMessage();
            break;
        case '3':
            changePassword();
            break;
        default:
            setColor(4, 0);
            std::cout << "Retry please..." << std::endl;
            break;
        }
    }
}

void Chat::readMessages() const
{
    setColor(10, 0);    //общие
    std::cout << "\n********** Messages to all **********" << std::endl;
    for (const auto& message : _messages)
    {
        if (message->getTo() == "all")
        {
            std::cout << "\nFrom " << message->getFrom() << " : " << message->getMessage() << std::endl;
        }
    }

    setColor(14, 0);    //личные входящие
    std::cout << "\n********** Messages to " << _curentUserName << " **********" << std::endl;
    for (const auto& message : _messages)
    {
        if (_curentUserName == message->getTo())
        {
            std::cout << "\nFrom " << message->getFrom() << " : " << message->getMessage() << std::endl;
        }
    }
    std::cout << "----------------end------------------" << std::endl;
}

void Chat::writeMessage()
{
    setColor(7, 0);
    std::string to;
    std::cout << "To (all or user name): ";
    std::cin >> to;
    std::string text;
    std::cout << "Message text: ";
    std::cin.ignore();
    getline(std::cin, text);

    if (to == "all")
    {
        const auto message = std::make_shared<Message>(Message(_curentUserName, "all", text));
        _messages.push_back(message);
    }
    else if (_users.find(to) != _users.end())
    {
        const auto message = std::make_shared<Message>(Message(_curentUserName, _users.find(to)->first, text));
        _messages.push_back(message);
    }
    else
    {
        setColor(4, 0);
        std::cout << "Error. No username." << std::endl;
    }
}
void Chat::changePassword() {
    std::map <std::string, uint* >::iterator it = _users.find(_curentUserName);
    std::cout << "Enter new password: ";
    char password[PASSLENGTH];
    std::cin >> password;
    uint* hashPass = sha1(password, PASSLENGTH);
    _users[_curentUserName] = hashPass;
}

void Chat::showUsersInfo()
{
    setColor(7, 0);
    for (auto user : _users) {
        std::cout << "\n****** Info about user " << user.first << " ******" << std::endl;
        std::cout << "Login: " << user.first << std::endl;
        std::cout << "Hash password: " << *user.second << std::endl;
        int a{ 0 }, b{ 0 };
        for (auto mes : _messages) {
            if (mes->getFrom() == user.first) a++;
            if (mes->getTo() == user.first) b++;
        }
        std::cout << "Number of outgoing messages: " << a << std::endl;
        std::cout << "Number of incoming messages: " << b << std::endl;
    } 
}