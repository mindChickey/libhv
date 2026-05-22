
#include "hv/HttpClient.h"
#include "hv/hlog.h"
#include <hv/httpdef.h>

using namespace hv;

extern "C" void init_libhv();

void send(){
  hlog_disable();
  HttpResponse res;
  HttpRequest req;
  req.method = HTTP_GET;
  req.url = "http://127.0.0.1:8892";
  int ret = http_client_send(&req, &res);

  if (ret != 0) {
    printf("error %s\n", res.body.c_str());
  } else {
    printf("succ %s\n", res.body.c_str());
  }
}

__attribute__((constructor(300)))
void init(int argc, char **argv, char** envp){
  init_libhv();
  send();
}

int main(int argc, char* argv[]) {
  return 0;
}

/*
clang++ -fuse-ld=/usr/local/bin/ld.lld client-test.cpp -o client-test -L /usr/local/lib ./libhv.bc -pthread -lmbedtls -lmbedcrypto -lmbedx509

*/