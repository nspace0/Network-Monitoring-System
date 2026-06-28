#include "../include/json_parser.hpp"
#include "../include/scanner.hpp"

#include <chrono>
#include <iostream>

int main()
{
    auto start = std::chrono::steady_clock::now();

    try
    {
        JsonParser parser;

        auto devices = parser.Parse();

        Scanner scanner;

        scanner.Scan(devices);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }

    auto end = std::chrono::steady_clock::now();

    auto sec =
        std::chrono::duration_cast<std::chrono::seconds>(end - start);

    std::cout
        << "\nFinished in "
        << sec.count()
        << " sec\n";
}