#include "Request.h"

Request::Request() {
    ip_in = generateRandomIP();
    ip_out = generateRandomIP();
    process_time = rand() % 100 + 1;  // Random time between 1 and 100
    job_type = rand() % 2 == 0 ? 'P' : 'S';  // Randomly assign job type
}
std::string Request::generateRandomIP() {
    return "192.168." + std::to_string(rand() % 256) + "." + std::to_string(rand() % 256);
}
