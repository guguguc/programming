#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <fmt/color.h>
#include <fmt/core.h>
#include <fstream>
#include <iostream>
#include <istream>
#include <ostream>
#include <string>

namespace asio = boost::asio;
using asio::ip::tcp;
using namespace std;

class Client {
  using error_type          = boost::system::error_code;
  using resolve_result_type = tcp::resolver::results_type;

public:
  Client(asio::io_context &ctx, const string &server, const string &path)
      :_resolver(ctx), _socket(ctx)
  {
      ostream requst_stream(&_request);
      string request_content = "GET {} HTTP/1.1\r\nHost: {}\r\nAccept: */*\r\nConnection: close\r\n\r\n";
      request_content = fmt::format(request_content, path, server);
      fmt::print("request header:\n{}", request_content);
      requst_stream << request_content;
      auto handler = boost::bind(&Client::handle_resovle, this,
              asio::placeholders::error, asio::placeholders::results);
      _resolver.async_resolve(server, "http", handler);
  }

private:
  void handle_resovle(const error_type &err, const resolve_result_type &endpoint);
  void handle_connect(const error_type &err);
  void handle_write_request(const error_type &err);
  void handle_read_header(const error_type &err, size_t transfer_size);
  void handle_read_content_segment(const error_type &err);
  void handle_read_content_all(const error_type &err);

private:
  tcp::resolver _resolver;
  tcp::socket _socket;
  boost::asio::streambuf _request;
  boost::asio::streambuf _response;
};

void Client::handle_resovle(const error_type &err,
                            const resolve_result_type &endpoint)
{
    if (!err) {
        for (auto &p : endpoint)
          fmt::print("ip {}\n", p.endpoint().address().to_string());
        asio::async_connect(_socket, endpoint,
                boost::bind(&Client::handle_connect,
                this, asio::placeholders::error));
    } else {
        fmt::print("resovle {}", err.message());
    }
}

void Client::handle_connect(const error_type &err)
{
    if (!err) {
        asio::async_write(_socket, _request,
                boost::bind(&Client::handle_write_request,
                this, asio::placeholders::error));
    } else {
        fmt::print(err.message());
    }
}

void Client::handle_write_request(const error_type &err)
{
    if (!err) {
      asio::async_read_until(_socket, _response, "\r\n\r\n",
                             boost::bind(&Client::handle_read_header, this,
                                         asio::placeholders::error,
                                         asio::placeholders::results));
    }
    else {
        fmt::print(err.message());
    }
}

void Client::handle_read_header(const error_type &err, size_t transfer_size)
{
  if (!err) {
    // debug
    // fmt::print("size: {}, transfer size {}", _response.size(), transfer_size);
    // getchar();
    string http_version, msg, header, line;
    unsigned int ret_code;
    istream response_stream(&_response);
    // read retcode and http version
    response_stream >> http_version >> ret_code;
    getline(response_stream >> std::ws, msg);
    if (ret_code != 200) {
      fmt::print("error retcode {}\n", ret_code);
      return;
    }
    // read header
    while (getline(response_stream, line) && line != "\r")
      header += line + "\n";
    fmt::print(fg(fmt::color::red), "http version: {}\nstatus code: {}\n",
               http_version, ret_code, msg);
    fmt::print(fg(fmt::color::light_green), "header:\n{}", header);
    getchar();
    // read untill end of html
    asio::async_read(_socket, _response, asio::transfer_all(),
                     boost::bind(&Client::handle_read_content_all,
                                 this, asio::placeholders::error));
  }
  else {
    fmt::print(err.message());
  }
}

void Client::handle_read_content_segment(const error_type &err)
{
  if (!err) {
    const char *data = asio::buffer_cast<const char*>(_response.data());
    fmt::print("{}", data);
    asio::async_read(_socket, _response, asio::transfer_at_least(1),
                     boost::bind(&Client::handle_read_content_segment,
                                 this, asio::placeholders::error));
  }
  else if (err != asio::error::eof) {
    fmt::print(err.message());
  }
}

void Client::handle_read_content_all(const error_type &err)
{
  if (err != asio::error::eof) {
    fmt::print(err.message());
    return;
  }
  // read html to string
  const string filename("test.html");
  istream response_stream(&_response);
  fstream file(filename, file.in | file.out | file.trunc);
  string content, line;
  while (getline(response_stream >> std::ws, line)) {
    content += (line + "\n");
  }
  fmt::print("{}", content.size());
  // write to file
  if (!file.is_open()) {
    fmt::print("fail to open {}", filename);
  }
  else {
    file << content;
  }
}

int main()
{
  const string server = "raw.githubusercontent.com";
  const string path = "/greyhexy/cs231n-assignment/master/scratch/fire_function.py";
  try {
  asio::io_context ctx;
  Client client(ctx, server, path);
  ctx.run();
  }
  catch (exception &e) {
    fmt::print("exception: {}", e.what());
  }

  return 0;
}
