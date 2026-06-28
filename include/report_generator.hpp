#pragma once

#include <vector>

#include "scanner.hpp"

class ReportGenerator {
   public:
    void SaveTxt(const std::vector<ScanResult>& results);

    void SaveCsv(const std::vector<ScanResult>& results);

    void SaveHtml(const std::vector<ScanResult>& results);

   private:
    std::string GetTimeStamp();
};