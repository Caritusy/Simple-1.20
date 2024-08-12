#include "ImportCommand.h"

ImportCommand::ImportCommand():IMCCommand("Import", "Import the file and work.","<path/[Delay/enabled/command]>"){
}

ImportCommand::~ImportCommand()
{
}
static std::ifstream file;

bool ImportCommand::execute(std::vector<std::string>* args)
{
    assertTrue(args->size() > 1);
	std::string directory = args->at(1);
    file.open(directory);
	if (!file.is_open()) {
		clientMessageF("%sCheck file existence or path format", RED);
		return false;
	}
	else {
		clientMessageF((const char*)u8"%s路径设置成功%s!", GREEN, directory);
        if (args->size() >= 2) {
            Import = args->at(2) == "true" ? true : "false" ? false : throw std::exception();

            command = args->at(2) == "command" ? true : false;

            delay = args->at(2) == "true" || "false" ? delay : assertFloat(args->at(2));
        }
		return true;
	}
    return false;
}

void ImportCommand::onTick(){
    if (delayTime.hasTimedElapsed(delay, true) && (Import||command)) {
        std::string line;
        if (std::getline(file, line)) {
            if (line.empty()) return;
            if (line[0] == '/'|| command) {
                commandrequest.command.setText(line);

                Game.getClientInstance()->loopbackPacketSender->sendToServer(&commandrequest);
            } else {
                Textpacket.messageType = 1;
                Textpacket.message.setText(line);
                Textpacket.sourceName.setText(Game.getLocalPlayer()->getNameTag()->getText());
                Game.getClientInstance()->loopbackPacketSender->sendToServer(&Textpacket);
            }
        }
        else {
            file.close();
            Game.getClientInstance()->getGuiData()->displayClientMessageF((const char*)u8"%s导入完成.", GREEN);
            Import = false;
            command = false;
        }
    }
}
