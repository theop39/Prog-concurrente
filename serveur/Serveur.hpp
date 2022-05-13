#ifndef SERVEUR_HPP_
#define SERVEUR_HPP_

#include <mutex>
#include <map>
#include <boost/asio.hpp>

#include "ThreadClient.hpp"
#include "ClientConnecte.hpp"

class Serveur
{
public :
  Serveur(unsigned short n_port);

  [[noreturn]] void attend_clients(void);
  unsigned long nb_clients(void);
  void envoyer_message_vers_tous_clients(unsigned long numero_client, const std::string& chaine_recue);

private :
  boost::asio::io_service service_es;
  boost::asio::ip::tcp::acceptor socket_ecoute;
  unsigned long numero_nouveau_client;
  std::mutex mut;
  std::map<unsigned long, ClientConnecte> clients;
  std::mutex mutex_clients;
  friend class ThreadClient;
  friend class ClientConnecte;
};

#endif // SERVEUR_HPP_
