# NodeMCU4Leds

## Versión 1.1.0.0

## Node MCU Web Server 4 Leds Control.

### Novedades versión 1.1.0.0:

> Configuración de cuatro Leds cableados en nueva disposición GPIOs D1, D2, D3, D4.

> Actualizado código HTML mostrado en cliente.

> En desarrollo conexión a sensor DHT11.

### Implementaciones.

> Aaptación con Arduino IDE.

> Servicio Web integrado en el dispositivo desarrollada en HTML5.

> Diseño propio del autor.

> Lib ``esp8266.com`` para soporte del ESP8266 en Arduino IDE.

### Descripción.

Programación Dispositivo Node MCU 1.0 (ESP-12E).

El presente código configura el dispositivo Node MCU en una red local mediante el
módulo de acceso WiFi incorporado, asignandole una IP de forma automática.

Mediante el acceso por HTTP, queremos controlar cuatro GPIO, los cuales tienen
conectados cuatro diodos led, GPIOs D1, D2, D3, D4.

Accediendo con un navegador web al dispositivo Node MCU con la IP asignada de
forma automática, el dispositivo nos muestra una pagina web en HTML con una
serie de elementos para poder interaccionar con el dispositivo.

Finalmente comentar que aunque el proyecto es muy simple y accesible, tiene
un gran potencial, debido a la simple programación necesaria y al bajo
coste del dispositivo.

La aplicación Android se ha desarrollado con la ayuda del IDE **Arduino IDE**, y
con las librerias del proyecto **Arduino core for ESP8266 WiFi chip**:

> Stable version: 

> Boards manager link: http://arduino.esp8266.com/stable/package_esp8266com_index.json

> Documentation: http://esp8266.github.io/Arduino/versions/2.3.0/

### Dependencias.

Diseño de la aplicación:

> [DevAge] (http://www.antoniohorrillo.com)

Arduino core for ESP8266 WiFi chip:

> [esp8266.com] (https://github.com/esp8266/Arduino.git)

### Capturas.

Portada Gestión de Leds:

![Portada Gestión de Leds](https://dl.dropboxusercontent.com/u/3193442/Proyectos/nodemcu4leds.png)

### Licencia.

**GNU GENERAL PUBLIC LICENSE** Version 3, 29 June 2007. Ver el archivo LICENSE.

NodeMCU4Leds.
![Antonio Horrillo.](http://blog.antoniohorrillo.com)
