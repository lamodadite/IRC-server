#include "Pass.hpp"

Pass::Pass() {}
Pass::Pass(const Pass& rhs) {}
Pass& Pass::operator=(const Pass& rhs) {}
Pass::~Pass() {}

void Pass::execute(Resource& resource, Message message) {
	Client*	client = resource.findClient(message.getClientFd());

	if (message.getParam().size() < 2) {
		// ERR_NEEDMOREPARAMS();
		return ;
	} else if (client->getRegistered()) {
		//ERR_ALREADYREGISTERED.(client);
		return ;
	} else if (message.getParam()[1] != resource.getPassword()) {
		//ERR_PASSWDMISMATCH;
		client->setPassed(false);
		return ;
	}
	client->setPassed(true);
}