#include <iostream>
#include <string>

#include "Client.hpp"

using namespace std;

int main(int argc, char* argv[])
{
  if (argc-1 != 2)
  {
    cerr << "Usage : " << argv[0] << " NOM_SERVEUR N°PORT" << endl;
    exit(0);
  }
  string nom(argv[1]);
  unsigned short n_port = static_cast<unsigned short>(stoul(argv[2]));

  Client client(nom, n_port);
  client.dialogue_avec_serveur();
}
