#include "Client.hpp"

Client::Client() {};
Client::Client(const Client& rhs) {(void)rhs;}
Client& Client::operator=(const Client& rhs) {(void)rhs; return *this;}

Client::Client(int client_fd): _client_fd(client_fd), _info_cnt(0), _registered(false), _infocomplete(false), _passwdclear(false) {}

Client::~Client() {}

void Client::addReadbuf(std::string str) {_readbuf += str;}

std::string& Client::getReadbuf() const {return _readbuf;}

bool&	Client::getInfocomplete() {return _infocomplete;}

bool&	Client::getPasswdclear() {return _passwdclear;}

bool&	Client::getRegistered() {return _registered;}
