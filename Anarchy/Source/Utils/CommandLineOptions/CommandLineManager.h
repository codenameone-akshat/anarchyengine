#ifndef _COMMAND_LINE_MANAGER_H_
#define _COMMAND_LINE_MANAGER_H_

#include <functional>
#include <map>

#define OPTION_CALLBACK_FUCTOR_ARG std::vector<string>
#define OPTION_CALLBACK_FUNCTOR std::function<void(OPTION_CALLBACK_FUCTOR_ARG)>

namespace anarchy
{
    class CommandLineManager
    {
    public:
        CommandLineManager() = default;
        ~CommandLineManager() = default;
    
        void RegisterAllOptions();
        void ParseAndApplyOptions(string commandLine);

        void RegisterCommandLineOption(string optionString, OPTION_CALLBACK_FUNCTOR functor);
    
    private:
        void GenDataCallback(OPTION_CALLBACK_FUCTOR_ARG arg);

        std::map<string, OPTION_CALLBACK_FUNCTOR> m_callbackMap;
    };
}

#endif // _COMMAND_LINE_MANAGER_H_
