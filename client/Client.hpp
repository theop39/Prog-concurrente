#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <boost/asio.hpp>
#include <string>

const std::string prompt="Client> ";

class Client
{
public :
  Client(std::string nom, unsigned short n_port);
  [[noreturn]] void dialogue_avec_serveur(void);

private :
  boost::asio::io_service service_es;
  boost::asio::ip::tcp::socket sock;
};

#endif // CLIENT_HPP_
