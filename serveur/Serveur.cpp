#include <iostream>
#include <utility> // pour std::move()
#include <thread>

#include "Serveur.hpp"
#include "EnvoiReception.hpp"

using namespace std;
using boost::asio::ip::tcp;


Serveur::Serveur(unsigned short n_port) :
  socket_ecoute(service_es,
		tcp::endpoint(tcp::v4(), n_port))
{
  numero_nouveau_client=1; // le n° 0 est réservé pour le serveur
}


[[noreturn]] void Serveur::attend_clients(void)
{
  cout<<"Adresse IP et n° de port côté serveur : "<<socket_ecoute.local_endpoint()<<endl;
  cout<<"En attente d'un client..."<<endl;

  // boucle infinie pour attendre les nouveaux clients
  while(true) {

    // DONE 2021: créer un objet ClientConnecte
    ClientConnecte client(numero_nouveau_client,*this);

    // DONE 2021: attendre une connexion TCP
    socket_ecoute.accept(client.sock);

    unique_lock<mutex> verrou_clients(mutex_clients); // début section critique
    clients.emplace(numero_nouveau_client, move(client));
    ClientConnecte& client_ref=clients.at(numero_nouveau_client); // référence de l'objet déplacé qu'on aura le droit d'utiliser en dehors de cette section critique
    verrou_clients.unlock();                          // fin section critique


      cout<<"Connexion d'un client : "<<client_ref.sock.remote_endpoint()<<endl;

    // DONE 2021: envoyer au client son numéro
     EnvoiReception::envoyer_entier(client_ref.sock, numero_nouveau_client);


     thread tClient(ThreadClient(client_ref, numero_nouveau_client));

     tClient.detach();

      cout<<"Nombre de clients : "<<nb_clients()<<endl;

    // DONE 2021: incrementer le nouveau numero du client
    numero_nouveau_client++;
  }
}

// pas const car on modifie un mutex
unsigned long Serveur::nb_clients(void)
{

  mutex_clients.lock();
  unsigned long taille = clients.size();
  mutex_clients.unlock();

  return taille;
}

void Serveur::envoyer_message_vers_tous_clients(unsigned long numero_client, const std::string& chaine)
{

   lock_guard<mutex> verrou(mutex_clients);


   for( auto it = clients.begin(); it != clients.end(); ++it) {
     if (numero_client != it->first) { //la map contient les socket => 1 socket/client
       //envoyer_chaine(it second, chaine);
     }
   }

  (void)numero_client; (void)chaine;
}
