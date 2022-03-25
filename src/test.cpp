#include <iostream>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

int main(){
    fs::path pathToShow("D:\\Identitas");
    cout << "exists() = " << fs::exists(pathToShow) << "\n"
        << "root_name() = " << pathToShow.root_name() << "\n"
        << "root_path() = " << pathToShow.root_path() << "\n"
        << "relative_path() = " << pathToShow.relative_path() << "\n"
        << "parent_path() = " << pathToShow.parent_path() << "\n"
        << "filename() = " << pathToShow.filename() << "\n"
        << "stem() = " << pathToShow.stem() << "\n"
        << "extension() = " << pathToShow.extension() << "\n";
}