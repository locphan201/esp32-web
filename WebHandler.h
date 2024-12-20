#ifndef WEB_HANDLER_H
#define WEB_HANDLER_H

#include <WebServer.h>

// Expose the server object so it can be used in main.cpp if needed
extern WebServer server;

void initWebServer();
void handleCommand();

#endif
