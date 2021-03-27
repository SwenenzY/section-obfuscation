#include <iostream>
#include <filesystem>


int main(int argc,char* argv[])
{
    // have args
    if (argv[1]) {
        // file exits
        if (std::filesystem::exists(argv[1])) {
            std::cout << "[!] Working file : " << argv[1] << std::endl; // print

        }
    }
    else {
        std::cout << "[-] File is not specified, please use this project.exe any.exe/.dll" << std::endl;
    }

    system("pause");
}