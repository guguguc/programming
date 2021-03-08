#include <boost/asio.hpp>
#include <iostream>
#include <string>

using boost::asio::ip::tcp;

const char *end = "www.greyhex.cn";

int main()
{
    boost::asio::io_context io_context;

    // resolve host
    tcp::resolver resolver(io_context);
    auto endpoints = resolver.resolve(end, "http");

    // bind socket
    tcp::socket socket(io_context);
    boost::asio::connect(socket, endpoints);

    boost::asio::streambuf request;
    std::ostream request_stream(&request);
    request_stream << "GET "
                   << "/"
                   << " HTTP/1.1\r\n";
    request_stream << "Host: " << end << "\r\n";
    request_stream << "Accept: */*\r\n";
    request_stream << "Connection: close\r\n\r\n";

    // send the request
    boost::asio::write(socket, request);

    // read response
    boost::asio::streambuf response;
    boost::asio::read_until(socket, response, "\r\n");
    std::cout << "size " << response.size() << "\n";
    std::cout << &response << "\n";
    getchar();

    // check response
    std::istream response_stream(&response);
    std::string http_version, msg;
    unsigned int status_code;
    response_stream >> http_version;
    response_stream >> status_code;
    std::getline(response_stream, msg);

    // error handle
    if (!response_stream) {
        std::cout << "Invalid response\n";
        std::cout << http_version << " " << status_code << " " << msg << "\n";
        return 1;
    }
    if (status_code != 200) {
        std::cout << "Error status_code " << status_code << "\n";
        return 1;
    }

    // read response header, which are terminateb by a blank line
    boost::asio::read_until(socket, response, "\r\n");
    std::string header;
    while (std::getline(response_stream, header) && header != "\r")
        std::cout << header << "\n";
    std::cout << "\n";
    std::cout << "others\n";

    // pause for print header
    getchar();

    // read until EOF
    std::string line, html;
    while (getline(response_stream >> std::ws, line))
        html += line + "\n";
    boost::system::error_code error;
    while (boost::asio::read(socket, response,
                             boost::asio::transfer_at_least(4096), error)) {
        std::cout << response.capacity() << "\n";
        response_stream.clear();
        while (getline(response_stream >> std::ws, line))
            html += line + "\n";
    }

    if (error != boost::asio::error::eof)
        throw boost::system::system_error(error);

    getchar();
    std::cout << html;

    return 0;
}
