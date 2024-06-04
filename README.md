# Trabajo Práctico Final - Integración de Módulo Encriptador AES-128

<p align="center">
  <img src="img/system-bd.png " />
</p>

* **Autor:** Ing. Leandro Soria
* **Asignatura:** Microarquitecturas y Softcores.
* **Plataforma:** `Arty Z7-20`

## Objetivos
* Empaquetar el módulo encriptador desarrollado en la asignatura Circuitos Lógicos Programables ([link del repositorio](https://github.com/lmsoria/cese-clp-workspace/tree/master/tp-final)) dentro de un IP Core compatible con el bus AXI4.
* Realizar un *test bench* que permita simular el comportamiento de los mismos utilizando ModelSim.
* Integrar el IP Core (PL) con el procesador Zynq-7000 (PS) embebido en el SoC.
* Sintetizar la implementación realizada para la plataforma `Arty Z7-20` usando Vivado.
* Desarrollar una aplicación en C que interactúe con la PL.
* Desarrollar una aplicación en Python para interactuar con el dispositivo desde la PC.

## Estructura del Repositorio
* `aes-ip`: Archivos necesarios para describir el IP Core (solo se dejaron los más importantes, como [`aes_128_encoder_v1_0_S_AXI.vhd`](https://github.com/lmsoria/cese-mys-tp-final/blob/master/aes-ip/ip_repo/aes_128_encoder_1.0/hdl/aes_128_encoder_v1_0_S_AXI.vhd) y [`aes_128_encoder_v1_0.vhd`](https://github.com/lmsoria/cese-mys-tp-final/blob/master/aes-ip/ip_repo/aes_128_encoder_1.0/hdl/aes_128_encoder_v1_0.vhd)).
* `app`: Código fuente de la aplicación que corre en el PS.
* `img`: Imágenes usadas en este archivo README.
* `rtl`: Componentes del encriptador AES-128 (PL) desarrollados en CLP (sólo parte encriptadora, no desenctiptadora).
* `scripts`: Scripts de Python para testear la interacción con la placa.
* `sim`: Archivos de simulación (no agregados, debería crearse un proyecto de ModelSim en este directorio).
* `tb`: Test benches para probar los componentes desarrollados.
* `synth`: Archivos de síntesis (no agregados, debería crearse un proyecto de Vivado en este directorio).

## Notas del autor
* Al core del proyecto desarrollado en CLP (`aes_encoder_logic.vhd`) se le adicionó un wrapper que sincroniza la lógica combinacional con el clock y reset del bus AXI. Este archivo es `aes_encoder.vhd` y es el componente que se expondrá a la hora de hacer el IP core.
* Esta vez la interacción con el usuario se realizará a través de los dos periféricos UART (UART0 y UART1) provistos por el PS. UART0 (interfaceado por el puerto USB de la placa) será el shell de interacción con el usuario, y UART1 enviará la data encriptada.

## Corriendo el proyecto
1. Conectar los pines Vcc/RX/Gnd de un adaptador Serie/USB al conector JA (RX debe ir al pin 2)
2. Conectar la placa, y programar el bitstream generado en la FPGA
3. Conectar una aplicación de terminal al puerto COM de la FPGA (este será UART0), usando 115200 bauds, 8N1
4. Correr la aplicación en el PS. Deberá empezar a verse la aplicación corriendo en la terminal.
5. Correr el script de python, y especificar el puerto COM del conversor Serie/USB.
<p align="center">
  <img src="img/demo.png " />
</p>


## Links de Referencia
* [AES Step by Step - CrypTool.org ](https://www.cryptool.org/en/cto/aes-step-by-step)
* [Arty Z7-20 Resource Center](https://digilent.com/reference/programmable-logic/arty-z7/start?redirect=1)
* [digilent-xdc: XDC Files](https://github.com/Digilent/digilent-xdc/)