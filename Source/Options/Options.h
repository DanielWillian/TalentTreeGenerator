#pragma once

#include "ProgramOptions.h"
#include <vector>
#include <string>
#include <memory>

namespace Options
{
std::unique_ptr<ProgramOptions> parseArgs(std::vector<std::string> args);
}

