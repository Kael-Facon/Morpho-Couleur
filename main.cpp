#include <iostream>
#include <filesystem>

#include "src/backend/shapes/shape.hh"
#include "src/backend/shapes/disk.hh"
#include "src/backend/shapes/diamond.hh"
#include "src/backend/shapes/square.hh"

int main(int argc, char* argv[])
{
    std::cout << "Hello World!" << std::endl;

    std::filesystem::path cwd = std::filesystem::current_path() / ".." / "morpho_couleur.tga";
    std::cout << cwd << std::endl;

    create_diamond(); create_disk(); create_square();
    std::cout << morpho_disk << '\n' << morpho_diamond << '\n';

    return 0;
}