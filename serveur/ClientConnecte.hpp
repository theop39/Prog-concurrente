#ifndef CLIENT_CONNECTE_HPP_
#define CLIENT_CONNECTE_HPP_

#include <boost/asio.hpp>

class Serveur;

class ClientConnecte
{
public :
  ClientConnecte(unsigned long numero_client_, Serveur& serveur_);

private :
  unsigned long numero_client;
  Serveur& serveur;

  boost::asio::ip::tcp::socket sock; // attribut non copiable !
  friend class Serveur;
  friend class ThreadClient;
};

#endif // CLIENT_CONNECTE_HPP_
