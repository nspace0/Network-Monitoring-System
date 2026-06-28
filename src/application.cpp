#include "../include/application.hpp"

#include <chrono>
#include <iostream>

#include "../include/config.hpp"
#include "../include/console_report.hpp"
#include "../include/json_parser.hpp"
#include "../include/report_generator.hpp"
#include "../include/scanner.hpp"
#include "../include/statistics.hpp"

int Application::Run()
{
    auto start = std::chrono::steady_clock::now();

    try
    {
        // Загружаем настройки из общего JSON
        Config config = Config::Load("../config/devices.json");

        JsonParser parser;

        auto devices = parser.ParseDevices();
        auto ports = parser.ParsePorts();

        Scanner scanner(config);

        auto results = scanner.Scan(devices, ports);

        for (const auto& result : results)
        {
            PrintResult(result);
        }

        ReportGenerator report;

        if (config.generate_txt)
            report.SaveTxt(results);

        if (config.generate_csv)
            report.SaveCsv(results);

        if (config.generate_html)
            report.SaveHtml(results);

        Statistics::Print(results);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }

    auto end = std::chrono::steady_clock::now();

    auto seconds =
        std::chrono::duration_cast<std::chrono::seconds>(end - start);

    std::cout << "\n====================================\n";
    std::cout << "Время выполнения: " << seconds.count() << " сек\n";
    std::cout << "====================================\n";

    return EXIT_SUCCESS;
}