
ar x ../build/lib/libhv_static.a

llvm-link -o libhv0.bc  \
  AsyncHttpClient.cpp.o \
  HttpClient.cpp.o \
  hstring.cpp.o \
  httpdef.c.o \
  HttpServer.cpp.o \
  hsocket.c.o \
  hlog.c.o \
  mbedtls.c.o \
  hssl.c.o \
  hmain.c.o \
  hbase.c.o \
  FileCache.cpp.o \
  htime.c.o \
  hloop.c.o \
  hevent.c.o \
  nio.c.o \
  unpack.c.o \
  epoll.c.o \
  HttpHandler.cpp.o \
  HttpParser.cpp.o \
  Http1Parser.cpp.o \
  http_parser.c.o \
  HttpMessage.cpp.o \
  http_content.cpp.o \
  hurl.cpp.o \
  multipart_parser.c.o \
  base64.c.o \
  HttpResponseWriter.cpp.o \
  WebSocketParser.cpp.o \
  websocket_parser.c.o \
  wsdef.c.o \
  sha1.c.o \
  ThreadLocalStorage.cpp.o \
  WebSocketChannel.cpp.o \
  hasync.cpp.o \
  HttpService.cpp.o \
  HttpMiddleware.cpp.o \
  http_page.cpp.o \
  hdir.cpp.o


opt --load-pass-plugin=/home/wang/cmusee-dev/cmuseeTools/build/ElimCtor/libElimCtorPass.so  -O0 ./libhv0.bc -o ./libhv.bc --funcname=init_libhv

rm *.o libhv0.bc

clang++ -fuse-ld=/usr/local/bin/ld.lld server-test.cpp -o server-test -L /usr/local/lib ./libhv.bc -pthread -lmbedtls -lmbedcrypto -lmbedx509
clang++ -fuse-ld=/usr/local/bin/ld.lld client-test.cpp -o client-test -L /usr/local/lib ./libhv.bc -pthread -lmbedtls -lmbedcrypto -lmbedx509