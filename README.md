# API-ESP8266

## Sumário
___
* [Sobre](#Sobre)
* [Componentes](#Componentes)
* [Esquemático](#Esquemático)
* [Softwares](#Softwares)
* [Como utilizar](#Como-utilizar)
    * [Barra de ferramentas PlatformIO](#Barra-de-ferramentas-PlatformIO)
* [Postman](#Postman)
___
# Sobre
<p> API para ESP8266, com objetivo de realizar o monitoramento de temperatura e umidade utilizando o sensor DHT11.</p>

# Componentes
+ ESP8266;
+ DHT11;
+ Jumpers;

# Esquemático
<img src="./img/esquematico.PNG">

# Softwares
+ Visual Studio Code;
+ PlatformIO;

# Como utilizar

+ Realize o clone do projeto em sua máquina;
+ Abra o projeto com o vscode utilizando a extensão PlatformIO;
+ Abra a pasta src, nessa pasta terá três arquivos, abra o arquivo Config.h;
+ Coloque o ssid e a senha da sua rede Wi-Fi, e em seguida preencha as configurações de rede para que o ESP possua um endereço estático;
+ Em seguida iremos utilizar a barra de ferramentas do PlatformIO para enviar o código para a placa;
+ Após o envio ser finalizado, abra o Serial monitor e verá se o ESP conectou com sucesso na rede;

## Barra-de-ferramentas-PlatformIO

<img src="./img/platformio-toolbar.png" >

1-Home

2-Compilar

3-Upload

4-Clean

5-Serial monitor

6-PlatformIO Core (CLI)

7-Alterar o projeto
___

# Postman

<p>Após realizar os passos anteriores, iremos realizar um teste em nossa API, para verificar se o mesmo esta funcionando, abra o seu Postman e realize um teste, coloque o seguite endereço: ip/sensor

OBS: Mesmo endereço configurado no codigo

</p>

<img src="./img/postman.png" >

<footer align="center">


<p>Estou disposto para qualquer duvida do projeto</p>

<a href="https://www.linkedin.com/in/vinicios-moraes-anhas-199478160/" target="_blank"><img src="https://img.shields.io/badge/-LinkedIn-%230077B5?style=for-the-badge&logo=linkedin&logoColor=white" target="_blank"></a> 


</footer>