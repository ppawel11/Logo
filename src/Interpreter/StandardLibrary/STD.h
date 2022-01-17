#ifndef TKOM_STD_H
#define TKOM_STD_H

#include "Backward.h"
#include "Forward.h"
#include "Circle.h"
#include "Clear.h"
#include "Turn.h"
#include "Switch.h"
#include "Write.h"
#include "Read.h"
#include "Reset.h"
#include "../../Program/LanguageElements/FunctionDefinition.h"

#include <memory>

namespace tkom::std_lib {
    static std::vector<std::string> function_names = { "backward","circle","clear","forward","read","reset","switch","turn","write"};

    static std::map<std::string, std::unique_ptr<FunctionDefinition>> init_functions(){
        std::map<std::string, std::unique_ptr<FunctionDefinition>> mp;

        mp["backward"] = std::make_unique<FunctionDefinition>("backward", std::vector<std::string>{"length"}, std::make_unique<Backward>());
        mp["circle"] = std::make_unique<FunctionDefinition>("circle", std::vector<std::string>{"radius"}, std::make_unique<Circle>());
        mp["clear"] = std::make_unique<FunctionDefinition>("clear", std::vector<std::string>{ }, std::make_unique<Clear>());
        mp["forward"] = std::make_unique<FunctionDefinition>("forward", std::vector<std::string>{"length"}, std::make_unique<Forward>());
        mp["read"] = std::make_unique<FunctionDefinition>("read", std::vector<std::string>{ }, std::make_unique<Read>());
        mp["reset"] = std::make_unique<FunctionDefinition>("reset", std::vector<std::string>{ }, std::make_unique<Reset>());
        mp["switch"] = std::make_unique<FunctionDefinition>("switch", std::vector<std::string>{ }, std::make_unique<Switch>());
        mp["turn"] = std::make_unique<FunctionDefinition>("turn", std::vector<std::string>{"angle"}, std::make_unique<Turn>());
        mp["write"] = std::make_unique<FunctionDefinition>("write", std::vector<std::string>{"message"}, std::make_unique<Write>());

        return mp;
    }
}

#endif //TKOM_STD_H
