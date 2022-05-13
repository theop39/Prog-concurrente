#include "ClientConnecte.hpp"
#include "Serveur.hpp"

ClientConnecte::ClientConnecte(unsigned long numero_client_, Serveur& serveur_) :
  numero_client(numero_client_),
  serveur(serveur_),
  sock(serveur_.service_es)
{ }
