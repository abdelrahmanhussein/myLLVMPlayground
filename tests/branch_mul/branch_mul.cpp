#include <iostream>

int main(int argc, char **argv)
{
    int x = std::stoi(argv[1]);
    int y = 0;
    if (x == 10)
    {
        y = x * 2;
    }
    else if (x == 20)
    {
        y = 0xbeef;
    }
    std::cout << "y = " << std::hex << y << std::endl;
    return 0;
}