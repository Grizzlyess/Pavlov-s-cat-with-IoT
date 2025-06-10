# Projeto Gato de Pavlov 🐈‍⬛⚡

**Um alimentador IoT inteligente para animais de estimação, construído com ESP32 e controlado inteiramente via Telegram.**

Este projeto combina os princípios do condicionamento clássico com tecnologia IoT para criar um treinador de Pets. 
Através de músicas, o sistema ensina o pet a associar uma melodia específica à hora da refeição, e consequentemente ao prêmio.
Será tocada 2 melodias, o objetivo é que o pet venha ao alimentador após a música certa, o sensor ultrassônico monitora sua presença e libera a comida.

---

## ✨ Conceito Central

O objetivo é resolver dois problemas comuns: a ansiedade dos animais que não têm horários fixos para comer e a necessidade dos donos de automatizar essa tarefa.

A lógica é simples e eficaz:
1.  **Melodia de Recompensa:** Uma melodia específica (`melody1`) é tocada pelo buzzer, e logo em seguida a comida é liberada pelo servo motor.
2.  **Melodia Neutra:** Uma melodia diferente (`melody2`) é tocada em outros momentos, sem liberar comida.
3.  **Monitoramento:** Um sensor ultrassônico detecta se o gato se aproxima da tigela após o estímulo.
