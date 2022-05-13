#include <iostream>
#include <string>

#include "ThreadLecture.hpp"
#include "EnvoiReception.hpp"
#include "Client.hpp"

using namespace std;

ThreadLecture::ThreadLecture(boost::asio::ip::tcp::socket& sock_) :
  sock(sock_)
{ }

[[noreturn]] void ThreadLecture::lire_clavier_et_envoyer_messages(void)
{
  while(true)
  {
    cout<<prompt<<flush; // on affiche un "prompt"

    string chaine_lue;
    getline(cin, chaine_lue);
    if(cin.eof())
      break;

    EnvoiReception::envoyer_chaine(sock, &chaine_lue[0]);

  }
  cout<<"Fermeture demandée par l'utilisateur.  Fin du programme."<<endl;
  exit(0);
  // la connexion TCP sera quand même fermée...
}

[[noreturn]] void ThreadLecture::operator()(void)
{
  lire_clavier_et_envoyer_messages();
}
