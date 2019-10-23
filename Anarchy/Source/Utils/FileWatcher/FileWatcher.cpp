#include "FileWatcher.h"
#include <cassert>

namespace anarchy::utils
{
    size_t FileWatcher::AddFileForWatch(std::string filePath)
    {
        assert(std::filesystem::exists(filePath));
        
        auto lastModifiedTime = std::filesystem::last_write_time(filePath);
        
        m_filePathsToWatch.emplace_back(filePath);
        m_watchFilesLastWriteTime.emplace_back(lastModifiedTime);
        
        return (m_filePathsToWatch.size() - 1); // Return the index of the element added
    }

    bool FileWatcher::IsFileModified(size_t fileIndex)
    {
        assert(fileIndex < m_filePathsToWatch.size());

        auto time = std::filesystem::last_write_time(m_filePathsToWatch[fileIndex]);
        
        if (time > m_watchFilesLastWriteTime[fileIndex])
        {
            m_watchFilesLastWriteTime[fileIndex] = time;
            return true;
        }
        
        return false;
    }
}