#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <random>

/**
 * @brief Class representing a web request.
 */
class Request {
public:
    std::string ip_in;    ///< Source IP address
    std::string ip_out;   ///< Destination IP address
    int process_time;     ///< Time required to process the request
    char job_type;        ///< Job type ('P' for processing, 'S' for streaming)

    /**
     * @brief Construct a new Request with random IP addresses, job type, and processing time.
     */
    Request();

    /**
     * @brief Generates a random IP address.
     * 
     * @return std::string A randomly generated IP address.
     */
    std::string generateRandomIP();
};

#endif
