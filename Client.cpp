#include "Client.hpp"

Client::Client() {};
Client::Client(const Client& rhs) {(void)rhs;}
Client& Client::operator=(const Client& rhs) {(void)rhs; return *this;}

Client::Client(int client_fd): _client_fd(client_fd) {}

Client::~Client() {}

void Client::setReadbuf(std::string str) {_readbuf += str;}

std::string& Client::getReadbuf() const {return _readbuf;}