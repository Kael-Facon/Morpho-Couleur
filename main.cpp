#include <iostream>
#include <filesystem>

int main(int argc, char* argv[])
{
    std::cout << "Hello World!" << std::endl;

    std::filesystem::path cwd = std::filesystem::current_path() / ".." / "image_test.png";
    std::cout << cwd;

    return 0;
}