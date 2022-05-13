#include <iostream>
#include <string>

#include "Serveur.hpp"

using namespace std;

int main(int argc, char* argv[])
{
  if (argc-1 != 1)
  {
    cerr << "Usage : " << argv[0] << " N°PORT" << endl;
    exit(0);
  }
  unsigned short n_port = static_cast<unsigned short>(stoul(argv[1]));

  Serveur serveur(n_port);
  serveur.attend_clients();
}
