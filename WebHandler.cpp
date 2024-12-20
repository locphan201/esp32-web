#include "WebHandler.h"
#include "MotorControl.h"
#include "HTMLPage.h"
#include <WiFi.h>

// Create a global WebServer instance
WebServer server(80);

void handleCommand() {
    // Check if "action" parameter is present
    if (!server.hasArg("action")) {
        server.send(400, "text/plain", "No action provided");
        return;
    }

    String action = server.arg("action");

    if (action == "stop") {
        stopAllMotors();
        server.send(200, "text/plain", "Stopped");
    } else if (action == "forward") {
        moveForward();
        server.send(200, "text/plain", "Forward");
    } else if (action == "backward") {
        moveBackward();
        server.send(200, "text/plain", "Backward");
    } else if (action == "left") {
        moveLeft();
        server.send(200, "text/plain", "Left");
    } else if (action == "right") {
        moveRight();
        server.send(200, "text/plain", "Right");
    } else if (action == "rotate_left") {
        rotateLeft();
        server.send(200, "text/plain", "Rotate Left");
    } else if (action == "rotate_right") {
        rotateRight();
        server.send(200, "text/plain", "Rotate Right");
    } else {
        server.send(400, "text/plain", "Unknown action");
    }
}

void initWebServer() {
    // Serve the main page at "/"
    server.on("/", HTTP_GET, []() {
        server.send_P(200, "text/html", MAIN_page);
    });

    // Serve the command handler at "/cmd"
    server.on("/cmd", HTTP_GET, handleCommand);

    // Start the server
    server.begin();
}
