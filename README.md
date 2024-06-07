<h1>
  <p align="center">Barramento</p>
</h1>

<h2>
  <p align="center">Desenvolvimento de módulos do kernel em C para processador gráfico, utilizando o kit de desenvolvimento DE1-SoC.</p>
</h2>

<h2>Sobre o projeto</h2>
<p>
  O estudante Gabriel Sá Barreto Alves, durante suas atividades de iniciação científica e no desenvolvimento de seu trabalho de conclusão de curso, projetou e implementou um processador gráfico. Este processador possibilita mover e controlar elementos em um monitor VGA com resolução de 640×480 pixels, permitindo desenhar dois tipos de polígonos convexos (quadrados e triângulos) e uma quantidade específica de sprites. Durante o desenvolvimento, Gabriel utilizou como unidade de processamento principal o NIOS II. Ele foi embarcado na mesma FPGA que o Processador Gráfico. 
</p>
<p>
A plataforma DE1-SoC possui um processador ARM (HPS), eliminando a necessidade do NIOS II. No entanto, isso gera um problema: como o HPS se comunicará com o processador gráfico? Para resolver essa questão, foi solicitado aos alunos da disciplina TEC499 MI - Sistemas Digitais, do curso de Engenharia de Computação da Universidade Estadual de Feira de Santana (UEFS), que desenvolvessem módulos de kernel no HPS para o processador gráfico.
</p>
<p>
Este projeto tem como objetivo desenvolver módulos do kernel para estabelecer a comunicação entre o HPS e o processador gráfico, além de criar uma biblioteca em C para facilitar o trabalho do programador ao realizar tarefas com o auxílio da GPU disponibilizada na plataforma DE1-SoC.
</p>

<h2>
  Requisitos do projeto
</h2>
<p>
• O código deve ser escrito na linguagem C;
</p>
<p>
• A biblioteca deve conter no mínimo uma função para cada Instrução do Processador Gráfico;
</p>
<p>
• A biblioteca deve seguir as recomendações descritas em: https://github.com/MaJerle/c-code-style.
</p>

<h2>Equipe</h2>
<uL>
  <li><a href="https://github.com/Armaaaaaaaaaaaaaaaaaaaaaaaaaaando">Armando de Lima Almeida</a></li>
  <li><a href="https://github.com/DiogoDSJ">Diogo dos Santos de Jesus</a></li>
  <li><a href="https://github.com/eugabrielbr">Gabriel Silva dos Santos</a></li>
</ul>

<h2>Sumário</h2>

<div id = "componentes">
<h2>Componentes, ferramentas e softwares utilizados</h2>

<h4>Placa de Desenvolvimento DE1-SoC</h4>

<p>
A DE1-SoC é uma plataforma de desenvolvimento integrando um processador dual-core ARM Cortex-A9 com um FPGA Cyclone V da Intel. Com uma variedade de periféricos como display de 7 segmentos, porta Ethernet, USB, porta de áudio, entre outros, é ideal para projetos que demandam integração entre software e hardware.
</p>
<p align="center">
  <img src = "https://github.com/Armaaaaaaaaaaaaaaaaaaaaaaaaaaando/Barramento/assets/129075181/fab1cc1e-9c36-48e1-81e5-ae7fd73da53e" width = "450px"/>
  <p align="center">
    <strong>Kit de desenvolvimento DE1-SoC</strong> 
  </p>
</p>

<h4>Linguagem de programação C</h4>

<p>
C é uma linguagem de programação de uso geral conhecida por sua concisão, controle de fluxo moderno, estruturas de dados eficientes e ampla gama de operadores. Embora não seja uma linguagem de "altíssimo nível" nem "extensa", e não seja especializada em nenhuma área específica, sua flexibilidade e generalidade a tornam mais prática e eficaz para diversas tarefas em comparação com linguagens consideradas mais avançadas (KERNIGHAN & RITCHIE, 1983, pag. 8).
</p>

<h4>Monitor CRT</h4>

<p>
  ...
</p>
</div>






<h2>Referências</h2>

KERNIGHAN, Brian; RITCHIE, Dennis. The C programming language. 2nd ed. Prentice Hall, 1983.




