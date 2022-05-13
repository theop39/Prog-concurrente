#include <iostream>
#include <string>

#include "ThreadReception.hpp"
#include "EnvoiReception.hpp"
#include "Client.hpp"

using namespace std;

ThreadReception::ThreadReception(boost::asio::ip::tcp::socket& sock_) :
  sock(sock_)
{ }

[[noreturn]] void ThreadReception::recevoir_et_afficher_messages(void)
{
  try
  {
    while(true)
    {
      (void)sock;
      unsigned long numero=0;
      string chaine_recue="";

      cout<<endl;
      if(numero==0)
	cout<<"Le serveur dit : "<<chaine_recue<<endl;
      else
	cout<<"Le client n°"+to_string(numero)+" dit : "+chaine_recue<<endl;
      cout<<prompt<<flush; // on ré-affiche le "prompt"
    }
  }
  catch(exception& e)
  {
    cerr<<"Exception dans le thread de réception : "<<e.what()<<endl;
  }
  cout<<"Connexion au serveur perdue.  Fin du programme."<<endl;
  exit(0); 
}

[[noreturn]] void ThreadReception::operator()(void)
{
  recevoir_et_afficher_messages();
}
