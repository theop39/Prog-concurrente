#include <iostream>
#include <mutex>
#include <sys/syscall.h>

#include "ThreadClient.hpp"
#include "Serveur.hpp"
#include "EnvoiReception.hpp"

using namespace std;

ThreadClient::ThreadClient(ClientConnecte& client_, unsigned long numero_client_) :
  client(client_),
  serveur(client_.serveur),
  numero_client(numero_client_)
{ }

void ThreadClient::dialogue_avec_client(void)
{
  serveur.mut.lock();
  cout<<"Démarrage d'un thread de TID "<<syscall(SYS_gettid)<<" pour le client n°"<<numero_client<<endl;
  serveur.mut.unlock();

  try
  {
    while(true)
    {


       string chaine_recue = EnvoiReception::recevoir_chaine(client.sock);

       serveur.mut.lock();
	     cout<<"Client "<<numero_client<<" : "<<client.sock.remote_endpoint()<<" Chaîne reçue : "<<chaine_recue<<endl;
       serveur.mut.unlock();
       serveur.envoyer_message_vers_tous_clients(numero_client,chaine_recue);

    }
  }
  catch(exception& e)
  {
    //retirer client
    serveur.mutex_clients.lock();
    serveur.clients.erase(numero_client);
    serveur.mutex_clients.unlock();

    serveur.mut.lock();
    cerr<<"Exception dans un thread: "<<e.what()<<endl;
    serveur.mut.unlock();
  }


    serveur.mut.lock();

    cout<<"Client déconnecté : "<<client.sock.remote_endpoint()<<endl;
    cout<<"Suppression du client "<<numero_client<<endl;

    serveur.mut.unlock();

  // TODO: à compléter: enlever le client de la map, en exclusion mutuelle
  serveur.envoyer_message_vers_tous_clients(0,"Déconnexion du client n°"+to_string(numero_client)); // 0 = n° spécial représentant le serveur

    serveur.mut.lock();

    cout<<"Nombre de clients restants : "<<serveur.nb_clients()<<endl;
    cout<<"Fin du thread de TID "<<syscall(SYS_gettid)<<" associé au client n°"<<numero_client<<endl;

    serveur.mut.unlock();
}

void ThreadClient::operator()(void)
{
  dialogue_avec_client();
}
