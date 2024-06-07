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

<h4>Monitores</h4>
<p>
Dois monitores foram utilizados para os testes e desenvolvimento: um monitor do tipo "Cathode Ray Tube" (CRT) e outro do tipo "Liquid Crystal Display" (LCD). Ambos apresentam conexão VGA e foram conectados, de acordo com a disponibilidade do equipamento no laboratório, ao kit de desenvolvimento DE1-SoC para verificar se a interação do hardware com o driver desenvolvido estaria ocorrendo de maneira satisfatória.
</p>

<p align="center">
  <img src = "https://github.com/Armaaaaaaaaaaaaaaaaaaaaaaaaaaando/Barramento/assets/129075181/a93c589a-7af7-450c-bebc-3afdfcb17657" width = "450px"/>
  <p align="center">
    <strong>Monitor CRT Dell</strong> 
  </p>
</p>

<p align="center">
  <img src = "https://github.com/Armaaaaaaaaaaaaaaaaaaaaaaaaaaando/Barramento/assets/129075181/53bacef8-4206-4f67-9757-bb5f96c66239" width = "450px"/>
  <p align="center">
    <strong>Monitor LCD Philips</strong> 
  </p>
</p>

<h4>Vscode</h4>
<p>
  O Visual Studio Code é um editor de código-fonte desenvolvido pela Microsoft para Windows, Linux e macOS. Foi utilizado no projeto como ambiente de desenvolvimento para codificar o driver e biblioteca.
</p>

<h4>Compilador</h4>
<p>
O Compilador GNU, também conhecido como GCC, é uma ferramenta de código aberto desenvolvida pelo Projeto GNU. Ele suporta várias linguagens de programação e é altamente portátil, funcionando em uma ampla variedade de sistemas operacionais. O GCC oferece opções avançadas de otimização e é amplamente utilizado tanto no desenvolvimento de software de código aberto quanto comercial. Sua capacidade de gerar código otimizado para diferentes arquiteturas o torna uma escolha popular entre os desenvolvedores. 
</p>

<h2>Arquitetura do kit de desenvolvimento DE1-SoC</h2>
<p>
Na presente seção serão apresentados os periféricos utilizados no kit de desenvolvimento para a realização do projeto, com o objetivo de compreensão da arquitetura geral utilizada e sua importância em cada etapa.
</p>


</div>


<h4>Historia da GPU </h4>

<p>
  A GPU (Unidade de Processamento Gráfico) começou a existir no final das décadas de 1970 e início das décadas de 1980, quando os primeiros computadores pessoais começaram a ser produzidos. Naquela época, os gráficos eram processados principalmente pela CPU (Unidade de Processamento Central), o que tornou muito difícil gerar imagens em tempo real e jogos.

No entanto, com o surgimento de jogos de computador e aplicações gráficas mais complexas, tornou-se evidente que o processamento gráfico requer hardware dedicado. A consequência disso foi a criação dos primeiros chips gráficos especializados, que posteriormente evoluíram para o que hoje chamamos de GPU.

A série de chips gráficos da IBM, lançada em 1987, foi uma das primeiras GPUs notáveis. Em 1991, o S3 Graphics lançou uma das primeiras placas gráficas aceleradoras 2D. Mas a introdução da 3dfx Voodoo em 1996 realmente revolucionou o mercado de placas de vídeo, oferecendo aos jogadores de PC gráficos 3D acelerados por hardware.

No período subsequente, empresas como NVIDIA e ATI – que posteriormente foi adquirida pela AMD – entraram no mercado com suas próprias soluções de GPU, lutando para fornecer o melhor desempenho e qualidade gráfica possível. 


</p>
</div>


<h4>GPU </h4>
<p>
 As GPUs são componentes essenciais em computadores, encarregadas do processamento de imagens. Com hardware especializado, elas lidam tanto com imagens 2D quanto 3D, realizando operações como cálculo de geometria, mapeamento de texturas e transformação de pixels.

No contexto dos jogos e aplicativos, as imagens 3D são geradas através de gráficos vetoriais. A GPU utiliza coordenadas (vértices) para formar polígonos que compõem a cena, aplicando texturas, iluminação e outros detalhes.

Após calcular a cena no espaço virtual, a GPU realiza a rasterização, convertendo-a em dados de pixels. Essas informações são então enviadas aos monitores, exibindo a imagem final. Esse ciclo se repete várias vezes por segundo, permitindo uma visualização fluida e dinâmica.


</p>
</div>

<h4>Barrramento </h4>
<p>
 Um barramento, em termos simplificados, é um canal de comunicação que facilita a interação entre o hardware e o software de um sistema computacional. No âmbito deste projeto, o objetivo central é estabelecer um barramento com a finalidade de viabilizar a comunicação entre uma biblioteca em modo de usuário e um driver no modo de kernel. Nesse contexto, a compreensão do conceito de barramento se revelou crucial para o desenvolvimento efetivo deste projeto.

</p>
</div>






<h2>Referências</h2>

KERNIGHAN, Brian; RITCHIE, Dennis. The C programming language. 2nd ed. Prentice Hall, 1983.
https://www.meupositivo.com.br/doseujeito/tecnologia/o-que-e-placa-de-video-gpu/ (tem que formatar)




