#include "simple_file_watcher.h"
#include <iostream>

int main()
{

    Simple_file_watcher watcher;
    watcher.setTimeout(std::chrono::duration<int,std::milli> (2 * 1000))
           .addFileToWatch("/home/user/test.txt")
           .addFolderToWatch("/home/user/test_folder")
           .addFileAction([] (std::string file, File_status status) -> void {
                switch(status) {
                    case File_status::created:
                        std::cout << "File created: " << file << '\n';
                        break;
                    case File_status::modified:
                        std::cout << "File modified: " << file << '\n';
                        break;
                    case File_status::erased:
                        std::cout << "File erased: " << file << '\n';
                        break;
                }
            })
            .addFolderAction([] (std::string folder, Folder_status status) -> void {
                switch(status) {
                    case Folder_status::created:
                        std::cout << "Folder created: " << folder << '\n';
                        break;
                    case Folder_status::modified:
                        std::cout << "Folder modified: " << folder << '\n';
                        break;
                    case Folder_status::erased:
                        std::cout << "Folder erased: " << folder << '\n';
                        break;
                }
            })
            .startWatching();

    std::this_thread::sleep_for(std::chrono::seconds(600));
    watcher.stopWatching();
    return 0;
}