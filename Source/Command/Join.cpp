#include "Join.hpp"

Join::Join() { }
Join::Join(const Join& rhs) { }
Join& Join::operator=(const Join& rhs) { }
Join::~Join() { }

void Join::execute(Resource& resource, Message message) {
	if (message.getParam().size() < 2) {
		//ERR_NEEDMOREPARAMS
	}
	std::vector<std::string>	channels;
	std::vector<std::string>	keys;

	splitByComma(channels, message.getParam()[1]);
	if (message.getParam().size() >= 3)
		splitByComma(keys, message.getParam()[2]);
}

void	Join::splitByComma(std::vector<std::string>& target, std::string param) {
	std::string	tmp;
	int					index;

	while ((index = param.find(',')) != std::string::npos) {
		tmp = param.substr(0, index);
		target.push_back(tmp);
		param.erase(0, index + 2);
	}
	if (param.size()) target.push_back(param);
}