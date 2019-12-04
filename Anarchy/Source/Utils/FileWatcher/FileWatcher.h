#pragma once

#include <filesystem>
#include <string>
#include <vector>

#include "../../Framework/Includes/FrameworkAliases.h"

namespace anarchy::utils
{
    class FileWatcher
    {
    public:
        FileWatcher() = default;
        ~FileWatcher() = default;

        [[nodiscard]]size_t AddFileForWatch(framework::AC_String filePath);
        bool IsFileModified(size_t fileIndex);

    private:
		std::vector<framework::AC_String> m_filePathsToWatch = {};
		std::vector<std::filesystem::file_time_type> m_watchFilesLastWriteTime = {};
    };
}