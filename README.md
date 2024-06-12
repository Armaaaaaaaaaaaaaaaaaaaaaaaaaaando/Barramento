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

<div id= "fundamentacao">
<h2>Fundamentação teórica</h2>
<p>
  Nesta seção será apresentado alguns conceitos teóricos básicos para compreensão do projeto.
</p>

<h4>Espaço do usuário ou "userspace"</h4>
<p>
O userspace, ou espaço do usuário, refere-se à parte do sistema operacional onde os aplicativos e processos de usuário são executados. É uma área separada do kernel do sistema operacional, que gerencia recursos de hardware e fornece serviços fundamentais para os aplicativos. No userspace, os programas têm acesso limitado aos recursos do sistema e são executados em um ambiente mais controlado, o que ajuda a garantir a estabilidade e segurança do sistema como um todo. O userspace é onde a maioria das interações diretas dos usuários com o sistema ocorre, através de aplicativos de software, enquanto o kernel cuida das operações mais fundamentais e de baixo nível do sistema.
</p>

<h4>Kernel</h4>
<p>
  O kernel é o núcleo do sistema operacional, responsável por gerenciar recursos de hardware e fornecer serviços essenciais para os aplicativos. Ele atua como intermediário entre o hardware e o software, controlando acesso à memória, processadores, dispositivos e sistemas de arquivos. Existem diferentes tipos de kernels, incluindo monolítico, microkernel e híbrido, cada um com abordagens distintas de design. O kernel é crucial para a estabilidade, segurança e desempenho do sistema operacional. Sua operação eficiente é essencial para garantir o funcionamento adequado do sistema como um todo.
</p>

<h4>Processador gráfico ou GPU</h4>
<p>Um processador gráfico, ou GPU (Graphics Processing Unit), é um componente especializado projetado para lidar com tarefas gráficas intensivas em computadores e dispositivos eletrônicos. Ele executa operações como renderização de imagens 2D e 3D, processamento de vídeo e cálculos matriciais com eficiência. As GPUs são compostas por vários núcleos de processamento paralelo, o que permite uma execução rápida de operações gráficas complexas. Elas desempenham um papel crucial em jogos, design gráfico, computação científica e outras áreas que requerem processamento gráfico avançado. Sua arquitetura altamente paralela as torna ideais para lidar com grandes volumes de dados de forma eficiente.</p>

<h4>Processador de propósito geral</h4>
<p>Um processador de propósito geral, conhecido como CPU, é um componente vital em computadores e dispositivos eletrônicos, responsável por executar uma ampla gama de tarefas de propósito geral. Desde o processamento de texto até a execução de aplicativos complexos, a CPU lida com instruções de software, executa cálculos matemáticos e controla o fluxo de dados. Diferentemente de uma GPU, otimizada para operações gráficas, a CPU é projetada para lidar com diversas atividades, garantindo a versatilidade e flexibilidade do dispositivo. Sua arquitetura inclui unidades de processamento, cache de memória e controladores de barramento, desempenhando um papel crucial no funcionamento de computadores modernos.</p>

</div>
<div id = "componentes">
<h2>Componentes, ferramentas e softwares utilizados</h2>

<h4>Placa de Desenvolvimento DE1-SoC</h4>

<p>
A DE1-SoC da Altera integra um sistema de processador rígido (HPS) baseado em ARM, composto pelo processador Dual-core ARM Cortex-A9, periféricos e interfaces de memória interligados perfeitamente com a estrutura FPGA através de uma espinha dorsal de interconexão de alta largura de banda. A placa de desenvolvimento DE1-SoC vem com memória DDR3 de alta velocidade, recursos de vídeo e áudio, conectividade Ethernet e muito mais, oferecendo inúmeras aplicações.
</p>
<p align="center">
  <img src = "https://github.com/Armaaaaaaaaaaaaaaaaaaaaaaaaaaando/Barramento/assets/129075181/a012967b-6624-4b1f-a59d-741b56e773cd" width = "450px"/>
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

<h4>Processador gráfico</h4>
<p>O Processador Gráfico, desenvolvido pelo estudante Gabriel Sá Barreto Alves, é responsável por gerenciar o processo de renderização da imagem e executar um conjunto de instruções que permitem inicialmente inserir sprites, além de modificar o layout do background da tela e renderizar polígonos do tipo quadrado e triângulo. A GPU atua em conjunto com um processador de propósito geral, que para este projeto é o Dual-core ARM Cortex-A9 presente no kit, duas FIFOs (First In, First Out) e uma PLL (Phase Locked Loop), em resumo.</p>

<p align="center">
  <img src = "https://github.com/Armaaaaaaaaaaaaaaaaaaaaaaaaaaando/Barramento/assets/129075181/591de9f8-4a37-4d81-8051-57e107099bac" width = "450px"/>
  <p align="center">
    <strong>Diagrama da estrutura interna do processador gráfico</strong> 
  </p>
</p>

</div>

<div id= "driver">

<h2>Desenvolvimento do módulo do kernel</h2>

<p>
  O módulo desenvolvido no projeto visa comunicar-se com o processador gráfico presente na FPGA, de modo que realize as tarefas enviadas do espaço do usuário.
</p>
<h4>Desenvolvimento</h4>
<p>
  A primeira etapa para desenvolver o módulo,  foi pesquisar e analisar qual seria sua estrutura básica
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

<h2>Instruções da GPU</h2>
Com o entendimento teorico da GPU, é necessario agora entender como funciona as instruções da mesma e como foram implementadas

<p>
  Para efetuar a modificação da cor de fundo, é necessário realizar alterações em duas FIFOS, denominadas data A e data B.

O data A é composto por 32 bits, onde as informações cruciais são o registrador, com um tamanho de 5 bits, e o opcode, com um tamanho de 4 bits. Os bits restantes, até completar 32 bits, são preenchidos com zeros à esquerda. O registrador indica onde as alterações estão armazenadas, variando de acordo com a finalidade, como por exemplo, um registrador de sprite. O opcode representa o código de operação da instrução correspondente.

Por outro lado, o conteúdo do data B pode variar conforme o objetivo específico. No caso da modificação da cor de fundo, são necessárias informações mais simplificadas, que serão detalhadas posteriormente. Esta estrutura difere consideravelmente da definição de um polígono, que requer coordenadas, cores, entre outros dados.

Além das informações contidas em data A e data B, há duas variáveis adicionais: uma variável de ativação denominada "start", utilizada para atualizar as informações enviadas ao VGA; e outra variável indicadora chamada "wrfull", que sinaliza quando as FIFOS estão cheias. Neste caso, o valor 1 indica que a FIFO está cheia, enquanto o valor 0 indica que está vazia.
</p>
<h4>Instrução de cor de fundo </h4>
<p>
  Para efetuar a modificação da tela de fundo do VGA, é necessário enviar instruções tanto para o dataA quanto para o dataB, além de ajustar o parâmetro "start" para desencadear a atualização no VGA.

No contexto do dataA, não é necessário realizar nenhuma alteração, permanecendo a modificação exclusivamente no dataB. Portanto, enviamos um valor de 0 para o dataA.

No que diz respeito ao dataB, a modificação concentra-se na alteração das cores. Como dispomos de apenas 6 bits para representar as cores (2 bits para cada cor: azul, vermelho e verde), devemos manipular e combinar esses bits para obter novas cores. Assim, a instrução a ser enviada possui 6 bits destinados às cores desejadas, complementados com zeros à esquerda para preencher os 32 bits do registro.
  
</p>

<h4>Instrução de sprite </h4>
<p>
  Para sprite é necessario modificar um pouco a estrutura das instruções dataA e dataB
</p>





<h2>Referências</h2>

<p>
  KERNIGHAN, Brian; RITCHIE, Dennis. The C programming language. 2nd ed. Prentice Hall, 1983.
</p>
<p>
  https://www.meupositivo.com.br/doseujeito/tecnologia/o-que-e-placa-de-video-gpu/ (tem que formatar)
</p>
<p>
  ALVES, Gabriel Sá B.; DIAS, Anfranserai M.; SARINHO, Victor T.. Development of a Sprite-Based Architecture for Creating 2D Games in Reconfigurable Environments Using FPGA Devices. In: TRILHA DE COMPUTAÇÃO – ARTIGOS CURTOS - SIMPÓSIO BRASILEIRO DE JOGOS E ENTRETENIMENTO DIGITAL (SBGAMES), 21. , 2022, Natal/RN. Anais [...]. Porto Alegre: Sociedade Brasileira de Computação, 2022 . p. 283-288.
</p>





