#ifndef THREAD_RECEPTION_HPP_
#define THREAD_RECEPTION_HPP_

#include <boost/asio.hpp>

class ThreadReception
{
public :
  ThreadReception(boost::asio::ip::tcp::socket& sock_);
  [[noreturn]] void recevoir_et_afficher_messages(void);
  [[noreturn]] void operator()(void);

private :
  boost::asio::ip::tcp::socket& sock;
};

#endif // THREAD_RECEPTION_HPP_
