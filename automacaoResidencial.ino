/* INSTITUTO FEDERAL DE MINAS GERAIS - CAMPUS BAMBUÍ

   TRABALHO DE CONCLUSÃO DE CURSO
   TEMA: AUTOMAÇÃO RESIDENCIAL DE BAIXO CUSTO UTILIZANDO ESP32

   ALUNO: EDUARDO AUGUSTO
   Código do Dia 11-01-2019
*/

#include <WiFiClientSecure.h> //Importação da Biblioteca Wifi com HTTPS

const char* nome_rede     = "NomeWifi";     // Nome da rede wifi existente
const char* senha = "SenhaWifi";       // Senha da rede wifi existente
const char*  servidor = "www.domoticaesp32.space"; //Url do Site que irá acessar

// Certificado de Autenticidade do Site
const char* certificadoSSL = \
      "-----BEGIN CERTIFICATE-----\n" \
      "MIIEkjCCA3qgAwIBAgIQCgFBQgAAAVOFc2oLheynCDANBgkqhkiG9w0BAQsFADA/\n" \
      "MSQwIgYDVQQKExtEaWdpdGFsIFNpZ25hdHVyZSBUcnVzdCBDby4xFzAVBgNVBAMT\n" \
      "DkRTVCBSb290IENBIFgzMB4XDTE2MDMxNzE2NDA0NloXDTIxMDMxNzE2NDA0Nlow\n" \
      "SjELMAkGA1UEBhMCVVMxFjAUBgNVBAoTDUxldCdzIEVuY3J5cHQxIzAhBgNVBAMT\n" \
      "GkxldCdzIEVuY3J5cHQgQXV0aG9yaXR5IFgzMIIBIjANBgkqhkiG9w0BAQEFAAOC\n" \
      "AQ8AMIIBCgKCAQEAnNMM8FrlLke3cl03g7NoYzDq1zUmGSXhvb418XCSL7e4S0EF\n" \
      "q6meNQhY7LEqxGiHC6PjdeTm86dicbp5gWAf15Gan/PQeGdxyGkOlZHP/uaZ6WA8\n" \
      "SMx+yk13EiSdRxta67nsHjcAHJyse6cF6s5K671B5TaYucv9bTyWaN8jKkKQDIZ0\n" \
      "Z8h/pZq4UmEUEz9l6YKHy9v6Dlb2honzhT+Xhq+w3Brvaw2VFn3EK6BlspkENnWA\n" \
      "a6xK8xuQSXgvopZPKiAlKQTGdMDQMc2PMTiVFrqoM7hD8bEfwzB/onkxEz0tNvjj\n" \
      "/PIzark5McWvxI0NHWQWM6r6hCm21AvA2H3DkwIDAQABo4IBfTCCAXkwEgYDVR0T\n" \
      "AQH/BAgwBgEB/wIBADAOBgNVHQ8BAf8EBAMCAYYwfwYIKwYBBQUHAQEEczBxMDIG\n" \
      "CCsGAQUFBzABhiZodHRwOi8vaXNyZy50cnVzdGlkLm9jc3AuaWRlbnRydXN0LmNv\n" \
      "bTA7BggrBgEFBQcwAoYvaHR0cDovL2FwcHMuaWRlbnRydXN0LmNvbS9yb290cy9k\n" \
      "c3Ryb290Y2F4My5wN2MwHwYDVR0jBBgwFoAUxKexpHsscfrb4UuQdf/EFWCFiRAw\n" \
      "VAYDVR0gBE0wSzAIBgZngQwBAgEwPwYLKwYBBAGC3xMBAQEwMDAuBggrBgEFBQcC\n" \
      "ARYiaHR0cDovL2Nwcy5yb290LXgxLmxldHNlbmNyeXB0Lm9yZzA8BgNVHR8ENTAz\n" \
      "MDGgL6AthitodHRwOi8vY3JsLmlkZW50cnVzdC5jb20vRFNUUk9PVENBWDNDUkwu\n" \
      "Y3JsMB0GA1UdDgQWBBSoSmpjBH3duubRObemRWXv86jsoTANBgkqhkiG9w0BAQsF\n" \
      "AAOCAQEA3TPXEfNjWDjdGBX7CVW+dla5cEilaUcne8IkCJLxWh9KEik3JHRRHGJo\n" \
      "uM2VcGfl96S8TihRzZvoroed6ti6WqEBmtzw3Wodatg+VyOeph4EYpr/1wXKtx8/\n" \
      "wApIvJSwtmVi4MFU5aMqrSDE6ea73Mj2tcMyo5jMd6jmeWUHK8so/joWUoHOUgwu\n" \
      "X4Po1QYz+3dszkDqMp4fklxBwXRsW10KXzPMTZ+sOPAveyxindmjkW8lGy+QsRlG\n" \
      "PfZ+G6Z6h7mjem0Y+iWlkYcV4PIWL1iwBi8saCbGS5jN2p8M+X+Q7UNKEkROb3N6\n" \
      "KOqkqm57TH2H3eDJAkSnh6/DNFu0Qg==\n" \
      "-----END CERTIFICATE-----\n";

WiFiClientSecure client; //Cria um cliente para a conexão

//Cria as variáveis para receber os valores dos sensores
int valor1 = -1;
int valor2 = -1;
int valor3 = -1;

//Cria variáveis para utilizar rele
String estados_rele;
int Reles[10] = {23, 22, 21, 19, 18, 5, 17, 16, 4, 2};
int i;

void setup() {
  Serial.begin(115200); //Inicializa a porta serial com frequencia de 115200Mhz
  delay(100);

  for (i = 0; i < 10; i++)pinMode(Reles[i], OUTPUT);//Define reles como porta de saída
  WiFi.begin(nome_rede, senha); //Inicia conexao Wifi com nome e senha informados
  
  //Aguarda até 1 segundo para a rede conectar
  while (WiFi.status() != WL_CONNECTED)delay(1000);

  //Informa por serial qual rede conectou - Utilizado para verificar apenas
  Serial.print("Conectado com "); Serial.println(nome_rede);
  
  client.setCACert(certificadoSSL); //Define que o client Wifi irá utilizar o SSL
}

void loop() {
  valor1 = 66;
  valor2 = 40;
  valor3 = 24;
  
  //Monta String para enviar dados dos sensores por uri
  String valores_sensores = "/RecebeSensores.php?&valor1=";
  valores_sensores += valor1;
  valores_sensores += "&valor2=";
  valores_sensores += valor2;
  valores_sensores += "&valor3=";
  valores_sensores += valor3;

  Serial.println("\nAcessando o servidor");
  //Verifica se o servidor foi conectada através da porta 443
  if (!client.connect(servidor, 443)) Serial.println("Conexão falhou");
  else {
    Serial.println("Conectou");

    //Realiza uma requisição para atualizar no servidor os valores dos sensores
    client.println(String("GET ") + valores_sensores + " HTTP/1.1\r\n" + "Host: " 
                          + servidor + "\r\n" + "Connection: close\r\n\r\n");

    /*Verifica se em 5 segundos obteve a resposta da requisição
      Caso não tenha a resposta, finaliza a conexão do client e 
      reinicie a função loop */
    unsigned long timeout = millis();
    while (client.available() == 0) {
      if (millis() - timeout > 5000) {
        Serial.println("Não respondeu a tempo"); client.stop(); return;
      }
    }

    /*Lê o retorno do servidor, que informará se as informações dos sensores
      foram salvas*/
    int i = 0;
    while (client.available()) {
      String line = client.readStringUntil('\n');
      if (i == 10)Serial.print(line); i++;
    }
    client.stop(); //Finaliza a conexão do cliente
  }

  Serial.println("\nAcessando o servidor");
  //Verifica se o servidor foi conectada através da porta 443
  if (!client.connect(servidor, 443)) Serial.println("Conexão falhou");
  else {
    Serial.println("Conectou");
    //Realiza uma requisição para buscar no servidor os estados do rele
    client.println(String("GET ") + "/EstadosRele.php" + " HTTP/1.1\r\n" + "Host: "
                          + servidor + "\r\n" + "Connection: close\r\n\r\n");

    /*Verifica se em 5 segundos obteve a resposta da requisição
      Caso não tenha a resposta, finaliza a conexão do client e 
      reinicie a função loop */
    unsigned long timeout = millis();
    while (client.available() == 0) {
      if (millis() - timeout > 5000) {
        Serial.println("Não respondeu a tempo"); client.stop(); return;
      }
    }

    /*Lê o retorno do servidor, que informará os estados dos reles*/
    int i = 0;
    estados_rele = ""; //Zera a string de reles lidos
    while (client.available()) {
      String line = client.readStringUntil('\n');
      if (i == 10) {Serial.print(line);estados_rele = line;}
      i++;
    }
    client.stop(); //Finaliza a conexão do cliente
  }

  /*Caso a variavel não esteja vazia, os reles ligam e desligam 
    o correspondente de acordo com a string recebido pelo servidor
  */
  //if(estados_rele != ""){
    digitalWrite(Reles[0], (estados_rele.substring(0, 1).toInt()));
    digitalWrite(Reles[1], (estados_rele.substring(1, 2).toInt()));
    digitalWrite(Reles[2], (estados_rele.substring(2, 3).toInt()));
    digitalWrite(Reles[3], (estados_rele.substring(3, 4).toInt()));
    digitalWrite(Reles[4], (estados_rele.substring(4, 5).toInt()));
    digitalWrite(Reles[5], (estados_rele.substring(5, 6).toInt()));
  //}
  
  Serial.println();
  delay(2000); //Aguarda 2 segundos até o próximo acesso ao servidor
}
