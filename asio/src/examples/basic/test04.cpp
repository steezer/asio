#include <iostream>
#include <asio.hpp>

using namespace std::placeholders;

void print(const asio::error_code& /*e*/,
    asio::steady_timer* t, int* count, int tid)
{
  if (*count < 5)
  {
    std::cout << "TID: "<< tid << " - "<< *count << std::endl;
    ++(*count);

    t->expires_at(t->expiry() + asio::chrono::seconds(1));
    t->async_wait(std::bind(print,_1, t, count, tid));
  }
}

int main()
{
  asio::thread_pool pool(4);
  int maxThreads=10;

  while(maxThreads--){
      asio::post(pool,
        [maxThreads]()
        {
          asio::io_context io;
          int count = 0;
          asio::steady_timer t(io, asio::chrono::seconds(1));
          t.async_wait(std::bind(print, _1, &t, &count, maxThreads));
          io.run();
          std::cout << "Final count is " << count << std::endl;
        }
      );
  }
  
  pool.join();
  return 0;
}