#pragma once

#include <atomic>
#include <chrono>
#include <optional>
#include <filesystem>
#include <list>
#include <thread>
#include <mutex>
#include <map>
#include <set>
#include <functional>

enum class File_status {created, modified, erased};
enum class Folder_status {created, modified, erased};

class Simple_file_watcher
{
    private:
        std::atomic<bool> watching_;
        std::chrono::duration<int,std::milli> timeout;
        std::mutex paths_mutex_;
        std::mutex file_actions_mutex_;
        std::mutex folder_actions_mutex_;
        std::map<std::filesystem::path, std::optional<std::filesystem::file_time_type>> paths_;
        std::list<std::function<void (std::string, File_status)>> file_actions_;
        std::list<std::function<void (std::string, Folder_status)>> folder_actions_;
        std::set<std::filesystem::path> folders_;
        std::map<std::filesystem::path, File_status> file_changes_;
        std::map<std::filesystem::path, Folder_status> folder_changes_;
        std::thread watcher_;
        void watcherFunction();
        void fireFileActions();
        void fireFolderActions();

    public:
        Simple_file_watcher();
        ~Simple_file_watcher();
        Simple_file_watcher& startWatching();
        Simple_file_watcher& stopWatching();
        Simple_file_watcher& setTimeout(std::chrono::duration<int,std::milli>);
        Simple_file_watcher& addFileToWatch(const std::string);
        Simple_file_watcher& addFolderToWatch(const std::string);
        Simple_file_watcher& addFileAction(const std::function<void (std::string, File_status)> &);
        Simple_file_watcher& addFolderAction(const std::function<void (std::string, Folder_status)> &);
};