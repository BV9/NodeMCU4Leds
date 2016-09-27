/**
   Programación Dispositivo Node MCU 1.0 (ESP-12E).

   El presente código configura el dispositivo Node MCU en una red local mediante el
   módulo de acceso WiFi incorporado, asignandole una IP de forma automática.

   Mediante el acceso por HTTP, queremos controlar cuatro GPIO, los cuales tienen
   conectados cuatro diodos led.

   Accediendo con un navegador web al dispositivo Node MCU con la IP asignada de
   forma automática, el dispositivo nos muestra una pagina web en HTML con una
   serie de elementos para poder interaccionar con el dispositivo.

   Finalmente comentar que aunque el proyecto es muy simple y accesible, tiene
   un gran potencial, debido a la simple programación necesaria y al bajo
   coste del dispositivo.

   Antonio Horrillo.
   http://www.antoniohorrillo.com

*/

// Incluimos la libreria del módulo ESP8266 incluido en la Node MCU.
#include <ESP8266WiFi.h>

// Definimos las variables de conexión a la red local por WiFi.
// Introducir un ssid y un password válido de la red WiFi.
const char* ssid = "";
const char* password = "";

// Definimos los puertos GPIO. Figuran todos, aunque solo vamos a conectar cuatro de ellos.
// No es necesario definirlos todos.
#define D0 16
#define D1 5 // I2C Bus SCL (clock)
#define D2 4 // I2C Bus SDA (data)
#define D3 0
#define D4 2 // LED_BUILTIN, led interno azul con lógica invertida.
#define D5 14 // SPI Bus SCK (clock)
#define D6 12 // SPI Bus MISO
#define D7 13 // SPI Bus MOSI
#define D8 15 // SPI Bus SS (CS)
#define D9 3 // RX0 (Serial console)
#define D10 1 // TX0 (Serial console)

// Instanciamos 'server(80)' como objeto de la clase WiFiServer escuchando peticiones por el puerto 80.
WiFiServer server(80);

// Método setup().
void setup() {

  // Conexión serie a 115200. No existe problema por conectar a esta velocidad.
  Serial.begin(115200);
  delay(10);

  // Inicializamos los GPIO D1, D2, D3, D4 como 'output' y estado 'low'.
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);

  // Conectando a la red WiFi con el ssid y contraseña indicados en las variables.
  // Mostramos la IP que tiene asignada el dispositivo Node MCU.
  Serial.print("\n\nEnlazando a la red WiFi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(">");
  }
  Serial.println("\nEnlace a la Red WiFi realizado correctamente.");
  Serial.print("IP Asignada al Dispositivo: ");
  Serial.print(WiFi.localIP());

  // Iniciamos el Servidor Web.
  server.begin();
  Serial.println("\nServidor Web Iniciado.\n");
}

// Método loop().
void loop() {

  // Comprobamos si existe conexión con un cliente. Si no tenemos conexión retornamos.
  WiFiClient cliente = server.available();
  if (!cliente) {
    return;
  }

  // En el caso de tener conexión con un cliente, mostramos mensaje y mientras esté disponible
  // mantenemos abierta la conexión.
  Serial.println("Cliente Conectado: ");
  while (!cliente.available()) {
    delay(1);
  }

  // Realizamos la lectura de la petición, la imprimimos y limpiamos el cliente.
  String peticion = cliente.readStringUntil('\r');
  Serial.println(peticion);
  cliente.flush();

  // Variables de estado de los Leds.
  int ledazul = LOW;
  int ledverde = LOW;
  int ledrojo = LOW;
  int ledamarillo = LOW;

  // Gestionamos las peticiones para encender o apagar los leds.
  if (peticion.indexOf("azulon") != -1)  {
    digitalWrite(D1, HIGH);
    ledazul = HIGH;
  }
  if (peticion.indexOf("azuloff") != -1)  {
    digitalWrite(D1, LOW);
    ledazul = LOW;
  }
  if (peticion.indexOf("verdeon") != -1)  {
    digitalWrite(D2, HIGH);
    ledverde = HIGH;
  }
  if (peticion.indexOf("verdeoff") != -1)  {
    digitalWrite(D2, LOW);
    ledverde = LOW;
  }
  if (peticion.indexOf("rojoon") != -1)  {
    digitalWrite(D3, HIGH);
    ledrojo = HIGH;
  }
  if (peticion.indexOf("rojooff") != -1)  {
    digitalWrite(D3, LOW);
    ledrojo = LOW;
  }
  if (peticion.indexOf("amarilloon") != -1)  {
    digitalWrite(D4, HIGH);
    ledamarillo = HIGH;
  }
  if (peticion.indexOf("amarillooff") != -1)  {
    digitalWrite(D4, LOW);
    ledamarillo = LOW;
  }

  // Imprimimos la respuesta en el navegador web del cliente.
  cliente.println("HTTP/1.1 200 OK");
  cliente.println("Content-Type: text/html");
  cliente.println(""); //  Separación
  cliente.println("<!DOCTYPE html>");
  cliente.println("<html>");
  cliente.println("    <head>");
  cliente.println("        <title>Node MCU</title>");
  cliente.println("        <meta charset='UTF-8'>");
  cliente.println("        <meta name='viewport' content='width=device-width,initial-scale=1.0'>");
  cliente.println("    </head>");
  cliente.println("    <body>");
  cliente.println("        <div style='width:70%; margin-left:auto; margin-right:auto; background-color:#E43F3F; color:#CCCCCC;'>");
  cliente.println("            <div>");
  cliente.println("                <h1 style='text-align:center; margin-left:auto; margin-right:auto;'>Node MCU Web Server</h1>");
  cliente.println("                <p style='text-align:center; margin-left:auto; margin-right:auto;'>Programación Dispositivo Node MCU 1.0 (ESP-12E).</p>");
  cliente.println("            </div>");
  cliente.println("            <hr />");
  cliente.println("            <div>");
  cliente.println("                <p style='text-align:justify; padding:10px;'>El presente código configura el dispositivo");
  cliente.println("                    Node MCU en una red local mediante el módulo de acceso WiFi incorporado,");
  cliente.println("                    asignandole una IP de forma automática. Mediante el acceso por HTTP, queremos");
  cliente.println("                    controlar cuatro GPIO, los cuales tienen conectados cuatro diodos led.</p>");
  cliente.println("                <p style='text-align:justify; padding:10px;'>Accediendo con un navegador web al dispositivo");
  cliente.println("                    Node MCU con la IP asignada de forma automática, el dispositivo nos muestra");
  cliente.println("                    una pagina web en HTML con una serie de elementos para poder interaccionar con");
  cliente.println("                    el dispositivo y los cuatro leds que tiene conectados.</p>");
  cliente.println("            </div>");
  cliente.println("            <hr />");
  cliente.println("            <div>");
  cliente.println("                <h2 style='text-align:center; margin-left:auto; margin-right:auto;'>Control de 4 Leds conectados a los puertos GPIO D1, D2, D3, D4</h2>");
  cliente.println("            </div>");
  cliente.println("            <div>");
  cliente.println("                <p style='text-align:center; padding:1px;'>GPIO D1 Led Azul: <span style='color:#FFD700;'>");

  if (ledazul == HIGH) {
    cliente.print("Encendido.");
  } else {
    cliente.print("Apagado");
  }
  cliente.print("                  </span></p>");

  cliente.println("                <p style='text-align:center; padding:1px;'>GPIO D1 Led Verde: <span style='color:#FFD700;'>");

  if (ledverde == HIGH) {
    cliente.print("Encendido.");
  } else {
    cliente.print("Apagado");
  }
  cliente.print("                  </span></p>");

  cliente.println("                <p style='text-align:center; padding:1px;'>GPIO D1 Led Rojo: <span style='color:#FFD700;'>");

  if (ledrojo == HIGH) {
    cliente.print("Encendido.");
  } else {
    cliente.print("Apagado");
  }
  cliente.print("                  </span></p>");

  cliente.println("                <p style='text-align:center; padding:1px;'>GPIO D1 Led Amarillo: <span style='color:#FFD700;'>");

  if (ledamarillo == HIGH) {
    cliente.print("Encendido.");
  } else {
    cliente.print("Apagado");
  }
  cliente.print("                  </span></p>");

  cliente.println("            </div>");
  cliente.println("            <div style='text-align:justify; padding:10px;'>");
  cliente.println("                <form action='?' method='get' id='formled'>");
  cliente.println("                    <fieldset>");
  cliente.println("                        <legend>Control de Leds</legend>");
  cliente.println("                        GPIO D1 Led Azul <br />");
  cliente.println("                        <input type='radio' name='ledazul' value='azuloff' checked='checked'/> Apagar Led Azul");
  cliente.println("                        <input type='radio' name='ledazul' value='azulon'/> Encender Led Azul");
  cliente.println("                        <br /><br />");
  cliente.println("                        GPIO D1 Led Verde <br />");
  cliente.println("                        <input type='radio' name='ledverde' value='verdeoff' checked='checked'/> Apagar Led Verde");
  cliente.println("                        <input type='radio' name='ledverde' value='verdeon'/> Encender Led Verde");
  cliente.println("                        <br /><br />");
  cliente.println("                        GPIO D1 Led Rojo <br />");
  cliente.println("                        <input type='radio' name='ledrojo' value='rojooff' checked='checked'/> Apagar Led Rojo");
  cliente.println("                        <input type='radio' name='ledrojo' value='rojoon'/> Encender Led Rojo");
  cliente.println("                        <br /><br />");
  cliente.println("                        GPIO D1 Led Amarillo <br />");
  cliente.println("                        <input type='radio' name='ledamarillo' value='amarillooff' checked='checked'/> Apagar Led Amarillo");
  cliente.println("                        <input type='radio' name='ledamarillo' value='amarilloon'/> Encender Led Amarillo");
  cliente.println("                        <br /><br />");
  cliente.println("                        <input type='submit' value='Enviar Estado de los Leds' name='enviar' />");
  cliente.println("                        <input type='reset' value='Borrar Estado de los Leds' name='limpiar' />");
  cliente.println("                    </fieldset>");
  cliente.println("                </form>");
  cliente.println("            </div>");
  cliente.println("            <div>");
  cliente.println("                <p style='text-align:right; margin-left:auto; margin-right:0; padding:10px;'>Node MCU 1.0 (ESP-12E). <a href='http://www.antoniohorrillo.com' target='_blank'>Antonio Horrillo Horrillo</a></p>");
  cliente.println("            </div>");
  cliente.println("        </div>");
  cliente.println("    </body>");
  cliente.println("</html>");

  // Esperamos y mostramos la desconexión del cliente.
  delay(1);
  Serial.println("Cliente Desconectado.\n");
}
