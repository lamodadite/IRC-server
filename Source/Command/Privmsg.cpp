#include "Privmsg.hpp"

Privmsg::Privmsg() { }
Privmsg::Privmsg(const Privmsg& rhs) { }
Privmsg& Privmsg::operator=(const Privmsg& rhs) { }
Privmsg::~Privmsg() { }

void	Privmsg::splitByComma(std::vector<std::string>& target, std::string param) {
	std::string	tmp;
	int					index;

	while ((index = param.find(',')) != std::string::npos) {
		tmp = param.substr(0, index);
		target.push_back(tmp);
		param.erase(0, index + 2);
	}
	if (param.size()) target.push_back(param);
}

void	Privmsg::execute(Resource& resource, Message message) {
	if (message.getParam().size() < 4) {
		//ERR_NEEDMOREPARAMS
		return;
	}
	std::vector<std::string> target;
	splitByComma(target, message.getParam()[1]);
	for (size_t i = 0; i < target.size(); i++) {
		
	}
}