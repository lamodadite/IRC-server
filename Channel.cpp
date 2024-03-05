#include "Channel.hpp"

Channel::Channel() {};
Channel::Channel(const Channel& rhs) {(void)rhs;}
Channel& Channel::operator=(const Channel& rhs) {(void)rhs; return *this;}

Channel::Channel(const std::string& name): name(name) {}

Channel::~Channel() {}