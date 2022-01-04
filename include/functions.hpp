// Copyright 2021 by SovesT

#ifndef INCLUDE_FUNCTIONS_HPP_
#define INCLUDE_FUNCTIONS_HPP_
#include <unistd.h>

#include <boost/log/core.hpp>
#include <boost/log/exceptions.hpp>
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
#include "picosha2.h"

namespace bl = boost::log;
using nlohmann::json;
using std::string;
using std::vector;
using std::thread;
using std::mutex;

void print(const std::string&, int, time_t);
void init();
void calc(time_t);

#endif  // INCLUDE_FUNCTIONS_HPP_
