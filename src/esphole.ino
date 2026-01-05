#include <WiFi.h>
#include <WebServer.h>
#include <LittleFS.h>

#include "DNSServer.h"

#define wifi_ssid "****"
#define wifi_password "****"

const byte DNS_PORT = 53;
DNSServer dnsServer;
WebServer webServer(80);
File f;

int find_text(String needle, String haystack) {
  int foundpos = -1;
  for (int i = 0; i <= haystack.length() - needle.length(); i++) {
    if (haystack.substring(i,needle.length()+i) == needle) {
      foundpos = i;
    }
  }
  return foundpos;
}

bool filter(String domain) {
  Serial.println ();
  Serial.print ("Domain: ");
  Serial.print (domain);
    
  char str[12];
  sprintf(str, "/hosts_%d", domain.length());

  f = LittleFS.open(str, "r");
  if (!f) {
      Serial.printf("\nError: file open failed\n");
  }
  f.seek(0, SeekSet);
  
  char dom_str[domain.length()+2];
  sprintf(dom_str, ",%s,", domain.c_str());
  bool found = f.findUntil(dom_str,"@@@");

  return found;
}

void setup_wifi() {
  delay(10);

  Serial.println();
  Serial.print("Connecting to: ");
  Serial.println(wifi_ssid);

  WiFi.begin(wifi_ssid, wifi_password);
  

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("WiFi connected | IP address: ");
  Serial.println(WiFi.localIP());

  webServer.begin();
  Serial.println("HTTP server started");
}

void setup() {
  Serial.begin(9600);
 
  WiFi.mode(WIFI_AP_STA);

  setup_wifi();
 
  LittleFS.begin();

  dnsServer.setErrorReplyCode(DNSReplyCode::ServerFailure);
  
  bool dns_running = dnsServer.start(DNS_PORT, "*", WiFi.localIP(), filter);
  if (dns_running) {
    Serial.println("DNS Server ready"); 
  }
  else{
    Serial.println("Error: DNS Server not running");     
  }
}

void loop() {
  delay(10);
}
