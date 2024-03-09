#include "Command.hpp"

Command::Command() {}
Command::Command(const Command& rhs) {(void)rhs;}
Command& Command::operator=(const Command& rhs) {(void)rhs; return *this;}
Command::~Command() {}
