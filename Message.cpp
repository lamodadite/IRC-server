#include "Message.hpp"

Message::Message() {}
Message::Message(const Message& rhs) {}
Message& Message::operator=(const Message& rhs) {}
Message::~Message() {}

const std::string& Message::getFirstParam() {return firstParam;}