#include "acpch.h"

#include "CommandLineManager.h"

#include <boost/algorithm/string.hpp> // for split
#include <Framework/AppContext.h>
#include <Utils/CommandLineOptions/CommandLineOptions.h>

#define OPTION_CALLBACK(x) std::bind(&x, this, std::placeholders::_1)

namespace anarchy
{
    void CommandLineManager::RegisterAllOptions()
    {
        RegisterCommandLineOption(string("-gendata"), OPTION_CALLBACK(CommandLineManager::GenDataCallback));
    }
    
    void CommandLineManager::ParseAndApplyOptions(string commandLine)
    {
        std::vector<string> splitUpOptionString = {};
        boost::split(splitUpOptionString, commandLine, [](char ch) { return ch == '-'; });

        for (auto& optionString : splitUpOptionString)
        {
            if(optionString.length() == 0) // for the first one being  ""
                continue;

            std::vector<string> optionArguments = {};
            boost::split(optionArguments, commandLine, [](char ch) { return std::isspace(ch); });
            string option = optionArguments[0];
            optionArguments.erase(optionArguments.begin()); // remove the option
            m_callbackMap[option](optionArguments);
        }
    }

    void CommandLineManager::RegisterCommandLineOption(string optionString, OPTION_CALLBACK_FUNCTOR functor)
    {
        m_callbackMap[optionString] = functor;
    }
    
    //--------------------------------------------CALLBACKS---------------------------------------------------

    void CommandLineManager::GenDataCallback(OPTION_CALLBACK_FUCTOR_ARG arg)
    {
        Assert(arg.size() == 1, "More than 1 data file provided"); // only 1 acentity file allowed right now

        if (arg.size() > 0)
        {
            CommandLineOptions::shouldGenerateData = true;
            CommandLineOptions::dataFile = arg[0];
        }
    }
}
