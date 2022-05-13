#ifndef ENVOI_RECEPTION_HPP_
#define ENVOI_RECEPTION_HPP_

#include <string>
#include <boost/asio.hpp>

class EnvoiReception
{
public:
  static void envoyer_entier(boost::asio::ip::tcp::socket& sock, unsigned long entier);
  static void envoyer_chaine(boost::asio::ip::tcp::socket& sock, const std::string& chaine);
  static unsigned long recevoir_entier(boost::asio::ip::tcp::socket& sock);
  static std::string recevoir_chaine(boost::asio::ip::tcp::socket& sock);
};

#endif // ENVOI_RECEPTION_HPP_
