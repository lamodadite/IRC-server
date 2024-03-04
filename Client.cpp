#include "Client.hpp"

Client::Client() {};
Client::Client(const Client& rhs): _client_fd(rhs._client_fd), _info_cnt(rhs._info_cnt), _registered(rhs._registered), _infocomplete(rhs._registered), _passwdclear(rhs._passwdclear), _nickname_on(rhs._nickname_on), _username_on(rhs._username_on) {}
Client& Client::operator=(const Client& rhs) {(void)rhs; return *this;}

Client::Client(int client_fd): _client_fd(client_fd), _info_cnt(0), _registered(false), _infocomplete(false), _passwdclear(false), _nickname_on(false), _username_on(false) {}

Client::~Client() {}

void Client::addReadbuf(std::string str) {_readbuf += str;}

std::string& Client::getReadbuf() {return _readbuf;}

bool&	Client::getInfocomplete() {return _infocomplete;}

bool&	Client::getPasswdclear() {return _passwdclear;}

bool&	Client::getRegistered() {return _registered;}

void	Client::setNickname(std::string msg) {_nickname = msg; _nickname_on = true;}

void	Client::setUsername(std::string msg) {_username = msg; _username_on = true;}

void	Client::checkRegistered() {
	if (_nickname_on && _username_on && _passwdclear)
		_infocomplete = true;
}

std::string	Client::getWriteBuf() {return _sendbuf;}

void	Client::addWriteBuf(std::string rhs) {
	_sendbuf += rhs + ' ';
	_sendbuf += _nickname + ' ';
	_sendbuf += _username + '\n';
}