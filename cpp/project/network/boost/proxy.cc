#include <boost/asio.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/asio/write.hpp>
#include <streambuf>
#include <string>
#include <iostream>
#include <ostream>
#include <fmt/core.h>

namespace asio = boost::asio;
using asio::ip::tcp;

bool veriyfy_cert(bool preverified, asio::ssl::verify_context &ctx)
{
    char subject_name[256];
    X509 *cert = X509_STORE_CTX_get_current_cert(ctx.native_handle());
    X509_NAME_oneline(X509_get_subject_name(cert), subject_name, 256);
    std::cout << "Verifying " << subject_name << "\n";
    return preverified;
}

int main()
{
    const std::string endpoint("www.pornhub.com");
    const std::string path("/");

    boost::system::error_code ec;
    asio::io_context context;
    asio::ssl::context ctx(asio::ssl::context::method::sslv23);
    asio::ssl::stream<tcp::socket> ssock(context, ctx);
    ctx.set_default_verify_paths();
    ssock.set_verify_mode(asio::ssl::verify_peer);
    ssock.set_verify_callback(veriyfy_cert);

    // connect to proxy
    asio::ip::tcp::resolver resolve(context);
    auto it = resolve.resolve({"www.pornhub.com", "https"});
    auto s = it->endpoint().address().to_string();
    asio::connect(ssock.lowest_layer(), it);
    ssock.handshake(asio::ssl::stream_base::handshake_type::client);

    // ready to write
    asio::streambuf request, response;
    std::ostream request_stream(&request);
    std::istream response_stream(&response);
    auto content =  "GET {} HTTP/1.1\r\nHost: {}\r\nAccept: */*\r\nConnection: close\r\n\r\n";
    fmt::format(content, path, endpoint);
    request_stream << content;
    asio::write(ssock, request);
    asio::read_until(ssock, response, "\r\n");
    std::cout << &response << "\n";
    return 0;
}
