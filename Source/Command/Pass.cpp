#include "Pass.hpp"

Pass::Pass() {}
Pass::Pass(const Pass& rhs) {(void)rhs;}
Pass& Pass::operator=(const Pass& rhs) {(void)rhs;return *this;}
Pass::~Pass() {}

void Pass::execute(Resource& resource, Message message) {
	Client*	client = resource.findClient(message.getClientFd());

	if (message.getParam().size() < 2) {
		reply.errNeedMoreParams(client, "PASS");
		return ;
	} else if (client->getRegistered()) {

		reply.errAlreadyRegistered(client);
		return ;
	} else if (message.getParam()[1] != resource.getPassword()) {
		reply.errPasswdMisMatch(client);
		client->setPassed(false);
		return ;
	}
	client->setPassed(true);
}