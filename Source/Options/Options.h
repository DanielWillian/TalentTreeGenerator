#pragma once

#include "ProgramOptions.h"
#include <vector>
#include <string>
#include <memory>

namespace Options
{
std::unique_ptr<ProgramOptions> parseArgs(const std::vector<std::string> args);
}

