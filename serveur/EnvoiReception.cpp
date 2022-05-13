#include "EnvoiReception.hpp"

void EnvoiReception::envoyer_entier(boost::asio::ip::tcp::socket& sock, unsigned long entier)
{
  boost::asio::write(sock, boost::asio::buffer(&entier, sizeof(entier)));
}

void EnvoiReception::envoyer_chaine(boost::asio::ip::tcp::socket& sock, const std::string& chaine)
{
  unsigned long taille=chaine.size(); // nombre d'octets et pas de caractères
  envoyer_entier(sock, taille);
  boost::asio::write(sock, boost::asio::buffer(&chaine.front(), chaine.size()));
}

unsigned long EnvoiReception::recevoir_entier(boost::asio::ip::tcp::socket& sock)
{
  unsigned long entier;
  boost::asio::read(sock, boost::asio::buffer(&entier, sizeof(entier)));
  return entier;
}

std::string EnvoiReception::recevoir_chaine(boost::asio::ip::tcp::socket& sock)
{
  unsigned long taille=recevoir_entier(sock);
  std::string chaine(taille,' '); // chaîne avec la bonne taille remplie d'espaces
  boost::asio::read(sock, boost::asio::buffer(&chaine.front(), taille));
  return chaine;
}
