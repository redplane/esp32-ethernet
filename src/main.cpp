
#include <SPI.h>
#include <Ethernet2.h>

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
char server[] = "www.google.com";    // name address for Google (using DNS)

// Initialize the Ethernet client library
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

void setup() {
    // Open serial communications and wait for port to open:
    Serial.begin(115200);
    while (!Serial) { ;
    }

    Ethernet.init(2);
    Ethernet.begin(mac);
    // start the Ethernet connection:
    if (Ethernet.begin(mac) == 0) {
        Serial.println("Failed to configure Ethernet using DHCP");
        Ethernet.begin(mac, Ethernet.localIP());
    }
    // give the Ethernet shield a second to initialize:
    delay(1000);
    Serial.println("connecting...");
    Serial.println(Ethernet.localIP());
    delay(1000);

    // if you get a connection, report back via serial:
    if (client.connect(server, 80)) {
        Serial.println("connected");
        // Make a HTTP request:
        client.println("GET /search?q=arduino HTTP/1.1");
        client.println("Host: www.google.com");
        client.println("Connection: close");
        client.println();
    } else {
        // kf you didn't get a connection to the server:
        Serial.println("connection failed");
    }
}

void loop() {
    // if there are incoming bytes available
    // from the server, read them and print them:
    if (client.available()) {
        char c = client.read();
        Serial.print(c);
    }

    // if the server's disconnected, stop the client:
    if (!client.connected()) {
        Serial.println();
        Serial.println("disconnecting.");
        client.stop();

        // do nothing forevermore:
        while (true);
    }
}
