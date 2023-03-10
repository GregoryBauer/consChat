#include "chat.h"
#include <limits>

Chat::Chat(std::string n) : _name(n) {}

void Chat::working()
{
    int choice;
    bool b{true};
    while(b) {
        std::cout << "\n********* START CHAT **********" << endl;
        std::cout << "0 - Exit " << endl;
        std::cout << "1 - Create new User " << endl;
        std::cout << "2 - Enter the chat as a user " << endl;
        std::cin >> choice;
        switch (choice) {
        case 0:
            b = false;
            break;
        case 1:
            createUser();
            break;
        case 2:
            chatEntry();
            break;
        default:
            std::cout << "Retry please... " << endl;
            break;
        }
    }
}

void Chat::createUser()
{
    std::cout << "Creating a new user" << endl;
    std::cout << "Enter user login:" << endl;
    std::string login;
    std::cin >> login;
    std::cout << "Enter user password:" << endl;
    std::string password;
    std::cin >> password;
    std::cout << "Enter user name:" << endl;
    std::string name;
    std::cin >> name;
    /*if(login.length()!=0 && password.length()!=0 && name.length()!=0) {
        User* newUser = new User(login, password, name);
        addUser(newUser);
    }*/
    if (login == "all" || getHavingLogin(login))
    {
        std::cout << "Error. This login already exists." << std::endl;
    }
    else if (name == "all" || getHavingName(name))
    {
        std::cout << "Error. This name already exists." << std::endl;
    }
    else
    {
        User user = User(login, password, name);
        _users.push_back(user);
        //_curentUserName = std::make_shared<User>(user);
    }
}

//void Chat::addUser(User* newUser)
//{
//    users[numberOfUsers] = newUser;
//    numberOfUsers++;
//}

std::shared_ptr<User> Chat::getCurentUserName() const
{
    return _curentUserName;
}

void Chat::chatEntry()
{
    /*bool b{true};
    while(b) {
        std::cout << "Chat entry" << endl;
        std::cout << "User choice:" << endl;
        for(int i=0; i<numberOfUsers; i++) {
            std::cout << i+1 << " - " << users[i]->getUserLogin() << endl;
        }
        int choice;
        std::cin >> choice;
        std::cout << "Enter password for " << users[choice-1]->getUserLogin() << endl;
        std::string password;
        std::cin >> password;
        if(password == users[choice-1]->getUserPassword()) {
            setCurrentUser(users[choice-1]);
            std::cout << "Current user is " << currentUser()->getUserLogin() << endl;
            workingUser();
            b = false;
        }
        else {
            std::cout << "Incorrect password" << endl;
        }
    } */
    std::cout << "Enter login: ";
    std::string login;
    std::cin >> login;
    std::cout << "Enter password: ";
    std::string password;
    std::cin >> password;
    _curentUserName = getHavingLogin(login);
    if (_curentUserName == nullptr || (password != _curentUserName->getUserPassword()))
    {
        _curentUserName = nullptr;
        std::cout << "Error." << std::endl;
    }
    else
    {
        workingUser();
    }
}

void Chat::workingUser()
{
    bool b{true};

    while(b) {
        std::cout << "\n********** " << "User " << _curentUserName->getUserName() << " **********" << endl;
        std::cout << "0 - back" << endl;
        std::cout << "1 - read messages" << endl;
        std::cout << "2 - to write a message" << endl;
        //std::cout << "3 - Show outgoing" << endl;
        //std::cout << "4 - Message in general chat" << endl;
        //std::cout << "5 - Private message" << endl;
        int choice;
        std::cin >> choice;
        switch (choice) {
        case 0:
            b = false;
            break;
        case 1:
            readMessages();
            break;
        case 2:
            writeMessage();
            break;
        /*case 3:
            showOutgoing();
            break;
        case 4:
            messageInGeneralChat();
            break;
        case 5:
            privateMessage();
            break;*/
        default:
            std::cout << "Retry please... " << endl;
            break;
        }
    }
}

std::shared_ptr<User> Chat::getHavingLogin(const std::string& login) const
{
    for (auto& user : _users)
    {
        if (login == user.getUserLogin())
            return std::make_shared<User>(user);
    }
    return nullptr;
}

std::shared_ptr<User> Chat::getHavingName(const std::string& name) const
{
    for (auto& user : _users)
    {
        if (name == user.getUserName())
            return std::make_shared<User>(user);
    }
    return nullptr;
}

void Chat::readMessages()
{

}

void Chat::writeMessage()
{
    std::string to;
    std::cout << "To whom: ";
    std::cin >> to;
    std::string text;
    std::cout << "Message text: ";
    std::cin.ignore();
    getline(std::cin, text);

    if (to == "all")
    {
        _messages.push_back(Message(_curentUserName->getUserName(), "all", text));
    }
    else if (getHavingName(to))
    {
        _messages.push_back(Message(_curentUserName->getUserName(), getHavingName(to)->getUserName(), text));
    }
    else
    {
        std::cout << "Error. No username." << std::endl;
    }   

    /*std::cout << "Inbox messages:" << endl;
    for (unsigned int i=0; i<messages.size(); i++) {
        if(messages.at(i)->getTo() == currentUser()->getUserLogin()) {
            std::cout << "From " << messages.at(i)->getFrom() << ":       " << messages.at(i)->getMessage() << endl;
        }
    }*/
}
//void Chat::showOutgoing()
//{
//    std::cout << "Outgoing messages:" << endl;
//    for (unsigned int i=0; i<messages.size(); i++) {
//        if(messages.at(i)->getFrom() == currentUser()->getUserLogin()) {
//            std::cout << "To " << messages.at(i)->getTo() << ":       " << messages.at(i)->getMessage() << endl;
//        }
//    }
//}
//void Chat::messageInGeneralChat()
//{
//
//}
//void Chat::privateMessage()
//{
//    std::cout << "To whom: " << endl;
//    std::vector<User*> addressees;
//    for(int i=0; i<numberOfUsers; i++) {
//        if(users[i]->getUserLogin() != currentUser()->getUserLogin())
//            addressees.push_back(users[i]);
//    }
//    for(unsigned int i=1; i<=addressees.size(); i++) {
//        std::cout << i << " - " << addressees[i-1]->getUserLogin() << endl;
//    }
//    unsigned int choice;
//    std::cin >> choice;
//    std::cout << "Enter your message to " << addressees[choice-1]->getUserLogin() << ":" << endl;
//    std::string mes;
//    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//    std::getline(std::cin, mes);
//    Message *message = new Message(currentUser()->getUserLogin(),
//                                   addressees[choice-1]->getUserLogin(),
//                                    mes);
//    messages.push_back(message);
//    std::cout << "Message sent" << endl;
//}
