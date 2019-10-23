#pragma once

#include <filesystem>
#include <string>
#include <vector>

namespace anarchy::utils
{
    class FileWatcher
    {
    public:
        FileWatcher() = default;
        ~FileWatcher() = default;

        [[nodiscard]]size_t AddFileForWatch(std::string filePath);
        bool IsFileModified(size_t fileIndex);

    private:
		std::vector<std::string> m_filePathsToWatch = {};
		std::vector<std::filesystem::file_time_type> m_watchFilesLastWriteTime = {};
    };
}