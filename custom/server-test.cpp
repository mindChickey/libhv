
#include <ifaddrs.h>
#include <string>
#include <sys/types.h>
#include <stdio.h>

#include "hv/hlog.h"
#include "hv/HttpServer.h"

using namespace hv;

char startTime[1024];

int index1(HttpRequest *req, HttpResponse *res) {
  puts("index");
  res->String("Hello, World!");
  return 200;
}


void printServerUrls(bool external, int port) {
  char ip[INET_ADDRSTRLEN];
  struct ifaddrs *ifaddr, *ifa;
  printf("\nServer is running on:\n");
  if(!external){
    printf("  http://127.0.0.1:%d\n", port);
  } else if (getifaddrs(&ifaddr) != -1) {
    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
      if (ifa->ifa_addr && ifa->ifa_addr->sa_family == AF_INET) {
        struct sockaddr_in *addr = (struct sockaddr_in *)ifa->ifa_addr;
        inet_ntop(AF_INET, &addr->sin_addr, ip, INET_ADDRSTRLEN);
        printf("  http://%s:%d\n", ip, port);
      }
    }
    freeifaddrs(ifaddr);
  }
}

void server(int port){
  hlog_disable();
  HttpService router;
  router.GET("/", index1);

  router.AllowCORS();

  HttpServer server(&router);
  server.setPort(port);

  printServerUrls(true, port);
  fflush(stdout);
  server.run();
}

int getPort(int argc, char** argv){
  if(argc == 1){
    return 8892;
  } else {
    return atoi(argv[1]);
  }
}

extern "C" void init_libhv();

__attribute__((constructor(300)))
void init(int argc, char **argv, char** envp){
  init_libhv();
  int port = getPort(argc, argv);
  server(port);
}

int main(int argc, char** argv){
  return 0;
}

/*
clang++ -fuse-ld=/usr/local/bin/ld.lld server-test.cpp -o server-test -L /usr/local/lib ./libhv.bc -pthread -lmbedtls -lmbedcrypto -lmbedx509

*/
