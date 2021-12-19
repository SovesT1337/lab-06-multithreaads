// Copyright 2021 by SovesT

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <unistd.h>

#include <boost/log/core.hpp>
#include <boost/log/exceptions.hpp>

//#include <boost/log/utility/setup.hpp>
//#include <boost/log/utility/setup/file.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/thread.hpp>
#include <chrono>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <numeric>
#include <random>
#include <string>
#include <thread>
#include <vector>

#include "nlohmann/json.hpp"
namespace bl = boost::log;
using json = nlohmann::json;
#endif  // INCLUDE_HEADER_HPP_