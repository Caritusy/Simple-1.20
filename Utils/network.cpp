//#pragma comment(lib, "Crypt32.lib")
#pragma comment(lib, "libcrypto_static.lib")
//#pragma comment(lib, "libcrypto_static.lib")
//#pragma comment(lib, "libssl_static.lib")
#include <boost/asio.hpp>
//#include <boost/asio/ssl.hpp>
#include "network.h"

#include <openssl/md5.h>
#include "../Memory/GameData.h"
#include <filesystem>

using boost::asio::ip::tcp;

std::string Network::Request(const std::string& api, const std::string& additionalParams){
    //std::string protocol, host, path;
    //std::size_t protocol_pos = api.find("://");
    //if (protocol_pos != std::string::npos) {
    //    protocol = api.substr(0, protocol_pos);
    //    std::size_t host_pos = api.find('/', protocol_pos + 3);
    //    if (host_pos != std::string::npos) {
    //        host = api.substr(protocol_pos + 3, host_pos - protocol_pos - 3);
    //        path = api.substr(host_pos);
    //    }
    //    else {
    //        host = api.substr(protocol_pos + 3);
    //        path = "/";
    //    }
    //}
    //else {
    //    throw std::invalid_argument("Invalid API URL");
    //}

    //boost::asio::io_service io_service;
    //tcp::resolver resolver(io_service);
    //tcp::resolver::query query(host, protocol == "https" ? "443" : "80");
    //tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
    //tcp::socket socket(io_service);
    //boost::asio::connect(socket, endpoint_iterator);

    //std::string request;
    //if (!additionalParams.empty()) {
    //    request = "POST " + path + " HTTP/1.1\r\n"
    //        "Host: " + host + "\r\n"
    //        "Content-Type: application/json\r\n"
    //        "Content-Length: " + std::to_string(additionalParams.length()) + "\r\n"
    //        "Connection: close\r\n\r\n" + additionalParams;
    //}
    //else {
    //    request = "GET " + path + " HTTP/1.1\r\n"
    //        "Host: " + host + "\r\n"
    //        "Connection: close\r\n\r\n";
    //}
    //boost::asio::write(socket, boost::asio::buffer(request));

    //boost::asio::streambuf response;
    //boost::system::error_code error;
    //boost::asio::read(socket, response, boost::asio::transfer_all(), error);

    //std::istream response_stream(&response);
    //std::string response_data((std::istreambuf_iterator<char>(response_stream)), std::istreambuf_iterator<char>());

    //socket.shutdown(tcp::socket::shutdown_both, error);
    //socket.close();

    //// Find the end of the headers
    //std::size_t header_end = response_data.find("\r\n\r\n");
    //if (header_end != std::string::npos) {
    //    response_data = response_data.substr(header_end + 4);
    //}

    //// Remove chunked transfer encoding
    //std::stringstream body;
    //std::string::size_type pos = 0;
    //while (true) {
    //    std::size_t chunk_size_end = response_data.find("\r\n", pos);
    //    if (chunk_size_end == std::string::npos) {
    //        std::cerr << "Error: Chunk size delimiter not found" << std::endl;
    //        break;
    //    }
    //    std::string chunk_size_str = response_data.substr(pos, chunk_size_end - pos);
    //    std::size_t chunk_size;
    //    try {
    //        chunk_size = std::stoul(chunk_size_str, nullptr, 16);
    //    }
    //    catch (const std::invalid_argument& e) {
    //        std::cerr << "Invalid chunk size: " << chunk_size_str << std::endl;
    //        break;
    //    }
    //    if (chunk_size == 0) {
    //        break;
    //    }
    //    pos = chunk_size_end + 2;
    //    if (pos + chunk_size > response_data.size()) {
    //        std::cerr << "Error: Chunk size exceeds remaining data size" << std::endl;
    //        break;
    //    }
    //    body.write(response_data.data() + pos, chunk_size);
    //    pos += chunk_size + 2; // Skip the chunk data and the trailing \r\n
    //}

    //return body.str();
    return "";
}
