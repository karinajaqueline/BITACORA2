
#include <WiFi.h>
#include "time.h"

const char* ssid     = "Axel’s iPhone";
const char* password = "PapuAxel";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = -18000; 
const int   daylightOffset_sec = 0; 

void setup(){
  Serial.begin(115200);

  Serial.print("Conectando a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado.");
  
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();

  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}

void loop(){
  delay(1000);
  printLocalTime();
}

void printLocalTime(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Error al obtener la hora");
    return;
  }
  Serial.println(&timeinfo, "%A, %d de %B de %Y %H:%M:%S");
  Serial.print("Día de la semana: ");
  Serial.println(translateWeekDay(&timeinfo));
  Serial.print("Mes: ");
  Serial.println(translateMonth(&timeinfo));
  Serial.print("Día del mes: ");
  Serial.println(&timeinfo, "%d");
  Serial.print("Año: ");
  Serial.println(&timeinfo, "%Y");
  Serial.print("Hora: ");
  Serial.println(&timeinfo, "%H");
  Serial.print("Hora (formato de 12 horas): ");
  Serial.println(&timeinfo, "%I");
  Serial.print("Minuto: ");
  Serial.println(&timeinfo, "%M");
  Serial.print("Segundo: ");
  Serial.println(&timeinfo, "%S");

  Serial.println("Variables de tiempo");
  char timeHour[3];
  strftime(timeHour, 3, "%H", &timeinfo);
  Serial.println(timeHour);
  char timeWeekDay[10];
  strftime(timeWeekDay, 10, "%A", &timeinfo);
  Serial.println(timeWeekDay);
  Serial.println();
}

String translateWeekDay(struct tm *timeinfo) {
  switch (timeinfo->tm_wday) {
    case 0:
      return "Domingo";
    case 1:
      return "Lunes";
    case 2:
      return "Martes";
    case 3:
      return "Miércoles";
    case 4:
      return "Jueves";
    case 5:
      return "Viernes";
    case 6:
      return "Sábado";
    default:
      return "";
  }
}

String translateMonth(struct tm *timeinfo) {
  switch (timeinfo->tm_mon) {
    case 0:
      return "Enero";
    case 1:
      return "Febrero";
    case 2:
      return "Marzo";
    case 3:
      return "Abril";
    case 4:
      return "Mayo";
    case 5:
      return "Junio";
    case 6:
      return "Julio";
    case 7:
      return "Agosto";
    case 8:
      return "Septiembre";
    case 9:
      return "Octubre";
    case 10:
      return "Noviembre";
    case 11:
      return "Diciembre";
    default:
      return "";
  }
}
