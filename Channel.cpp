#include "Channel.hpp"

Channel::Channel() {};
Channel::Channel(const Channel& rhs) {(void)rhs;}
Channel& Channel::operator=(const Channel& rhs) {(void)rhs; return *this;}

Channel::Channel(std::string channel_name): _name(channel_name) {}

Channel::~Channel() {}