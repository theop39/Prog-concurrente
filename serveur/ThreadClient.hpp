#ifndef THREAD_CLIENT_HPP_
#define THREAD_CLIENT_HPP_

#include "ClientConnecte.hpp"

class Serveur; // déclaration "forward" pour couper le cycle de dépendances entre classes

class ThreadClient
{
public :
  ThreadClient(ClientConnecte& client_, unsigned long numero_client_);
  void dialogue_avec_client(void);
  void operator()(void);

private :
  ClientConnecte& client;
  Serveur& serveur;
  unsigned long numero_client;
};

#endif // THREAD_CLIENT_HPP_
