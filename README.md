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

<h4>Módulo do kernel</h4>
<p>
  No Linux, um módulo do kernel é um pedaço de código que pode ser carregado e descarregado no kernel dinamicamente. Isso permite que funcionalidades sejam adicionadas ao kernel sem a necessidade de recompilar ou reiniciar o sistema.
</p>

<h4>Device numbers ou major e minor numbers</h4>
<p>
  No UNIX, existem dois principais tipos de números de dispositivos, sendo eles o “major number” e “minor number”. Estes números são basicamente identificadores, onde o “major number” identifica o tipo de dispositivo e, na maioria dos casos, o tipo de driver que vai lidar com o dispositivo, enquanto o “minor number” identifica o dispositivo, funcionando como um identificador único. Eles são usados para ajudar o kernel a direcionar operações de E/S para os drivers de dispositivos corretos. Esses números são parte integrante da maneira como o sistema lida com dispositivos de hardware.
</p>

<h4>Device files ou arquivos de dispositivos</h4>
<p>
Os arquivos de dispositivos são conhecidos como arquivos especiais. Eles representam a principal "ponte" de comunicação entre o driver de dispositivo e o espaço do usuário. Uma vez acessados através de funções de entrada e saída (como open, write, etc.), o sistema operacional gerencia a conexão com o hardware associado ao dispositivo.
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

<div id= "driver">

<h2>Desenvolvimento do módulo kernel</h2>

<p>
  O módulo desenvolvido no projeto visa comunicar-se com o processador gráfico presente na FPGA, de modo que realize as tarefas enviadas do espaço do usuário.
</p>
<h3>Funções</h3>

<p>A primeira etapa para desenvolver o módulo do kernel foi pesquisar e analisar qual seria sua estrutura básica. Após a pesquisa, descobriu-se que um módulo geralmente precisa apresentar funções básicas de entrada, que irão se comunicar com o arquivo responsável por estabelecer a comunicação entre o espaço do usuário e o hardware. Alguns desses métodos incluem: write, open, close, etc. Essas funções permitirão o envio de instruções para a GPU e vice-versa, por meio de mapeamento de memória, que será melhor detalhado posteriormente. Segue abaixo um resumo do papel de cada função do driver:
</p>

<h4>dev_open</h4>
<p>A função “dev_open” é chamada quando o dispositivo associado ao módulo é aberto. Esta função não realiza muitas operações, mas registra uma mensagem no log do kernel indicando que o dispositivo foi aberto com sucesso. Esta operação ajuda a monitorar e depurar o uso do dispositivo, confirmando que a abertura foi registrada pelo sistema.

<h4>dev_release</h4>
<p>A função “dev_release” é chamada quando o dispositivo é fechado. Semelhante à “dev_open”, esta função registra uma mensagem no log do kernel indicando que o dispositivo foi fechado com sucesso.
</p>

<h4>dev_read</h4>
<p>A função “dev_read” é responsável por ler dados do dispositivo e copiá-los para o espaço do usuário. Quando chamada, ela calcula quantos bytes ainda não foram lidos da mensagem armazenada em “mensagem_principal” e copia esses bytes para o buffer do usuário. Se a cópia for bem-sucedida, a função atualiza o offset para refletir a nova posição de leitura e retorna o número de bytes lidos. Se ocorrer um erro durante a cópia, a função retorna um código de erro.
</p>

<h4>dev_write</h4>
<p>A função “dev_write” é chamada quando dados são escritos no dispositivo a partir do espaço do usuário. Ela começa limpando o buffer “mensagem_principal” e então copia os dados do novo buffer para a mesma variável. Em seguida, a função separa dois inteiros da string recebida usando a função “separarInteiros” e envia esses inteiros via mapeamento de memória para os ponteiros que apontam para os endereços das FIFOS da GPU (“DATA_A_PTR” e “DATA_B_PTR”). Após isso, a função sinaliza o início da escrita, que ocorre de acordo com os valores dos registradores “START_PTR”, que funciona como uma espécie de clock, e “wrfull_ptr”, que guarda o status do estado da fila. Se a cópia dos dados do usuário falhar, a função retorna um código de erro.
</p>

<h4>separarInteiros</h4>
<p>A função separarInteiros é uma função auxiliar que processa uma string para extrair dois inteiros separados. Ela percorre a string caractere por caractere, acumulando o valor numérico até encontrar o delimitador 'd'. Após o delimitador, a função continua acumulando o segundo inteiro. Esses inteiros são então utilizados na formação das instruções para GPU.
</p>

<h4>ModuleInit e ModuleExit</h4>
<p>O módulo também precisa conter blocos de código que realizam operações quando o módulo é carregado e descarregado do sistema. No projeto, a função responsável pelo processo de inicialização do módulo é nomeada como “ModuleInit”. Ela é responsável por registrar o “major number” e “minor number” do módulo dinamicamente. Ao descarregar o módulo do sistema, a função “ModuleExit” é chamada, realizando o desregistro dos números de dispositivo associados ao módulo e, consequentemente, liberando os recursos que estavam sendo utilizados.</p>


<h3>Mapeamento de memória </h3>
<p>
  Para que fosse possível fazer com que o módulo de kernel desenvolvido fosse capaz de enviar instruções para GPU, foi preciso aplicar alguns conceitos de mapeamento de memória, que serão explicados ao decorrer desta seção.
</p>
<p>
  O processador ARM tem a possibilidade de se comunicar com a FPGA usando tanto a ponte HPS-to-FPGA quanto a ponte Lightweight HPS-to-FPGA. Essas pontes são designadas para áreas específicas na memória do HPS. Quando um componente na FPGA está conectado a uma dessas pontes, os registros que estão mapeados na memória ficam acessíveis para leitura e escrita pelo processador ARM, utilizando os endereços de memória correspondentes às pontes.
</p>

<p align="center">
  <img src = "https://github.com/Armaaaaaaaaaaaaaaaaaaaaaaaaaaando/Barramento/assets/129075181/18ed440c-d28f-4e95-9e0a-e028415bf867" width = "450px"/>
  <p align="center">
    <strong>Diagrama de blocos das pontes AXI no contexto da estrutura FPGA e da interconexão L3 com a HPS.</strong> 
  </p>
</p>

<p>
  A ponte utilizada para permitir que o módulo do kernel desenvolvido possa ter acesso aos componentes da GPU foi a Lightweight HPS-to-FPGA. Através da função "ioremap", que é uma função de mapeamento de memória disponível para o desenvolvimento de códigos para módulos do kernel, tornou-se possível acessar a posição de memória correspondente ao início do endereço de memória da ponte. Para isso, foi necessário inicialmente obter informações sobre o endereço base físico da ponte e o tamanho, em bytes, que abrange esse espaço. Toda a informação necessária foi encontrada no arquivo "address_map_arm.h", o qual fornecia os valores de "LW_BRIDGE_BASE" (endereço base físico) e "LW_BRIDGE_SPAN" (quantidade de espaço em bytes).
</p>

<p>
  No Linux, devido a questões de segurança, arquitetura ou gestão de recursos, não é possível ter acesso direto ao endereço físico de memória dos componentes mapeados nas regiões do espaço de memória do HPS. A função "ioremap", ao receber como parâmetro o endereço base físico e os bytes do endereço da ponte, retorna o endereço virtual, o qual pode ser manipulado para acessar a memória física correspondente, com a intermediação do sistema operacional e de alguns dispositivos de hardware que não veem ao caso.
</p>

<p>
  Após esse processo, para acessar os componentes da GPU, segue-se um procedimento não muito diferente do passo anterior: adiciona-se um offset ao endereço virtual, permitindo assim o acesso a cada componente. Os exemplos a seguir esclarecem melhor o mapeamento.
</p>

<h4>Alguns exemplos de endereços:</h4>

<p>LW_BRIDGE_BASE: 0xFF200000 (endereço físico base ponte)</p>
<p>LW_BRIDGE_SPAN: 0x100 (quantidade em bytes que abrange o endereço)</p>
<p>DATA_A: 0x80 (offset para a fila de instruções A)</p>
<p>DATA_B: 0x70 (offset para a fila de instruções B)</p>
<p>WRREG: 0xc0 (offset para o sinal de escrita na fila)</p>
<p>WRFULL: 0xb0 (offset para o sinal de verificação da fila)</p>

<h4>Exemplos de aplicações</h4>

```C
 LW_virtual = ioremap_nocache(LW_BRIDGE_BASE, LW_BRIDGE_SPAN); //mapeia e retorna o endereço virtual para LW_virtual
 DATA_A_PTR = (volatile int *)(LW_virtual + DATA_A); //soma o offset ao endereço virtual para ter acesso a posição de memória da fila de instrução A da GPU.

```
<h3>Arquivo de dispositivo</h3>
//explicar sobre a criação do arquivo especial

</div>

<div id = "biblioteca">
<h2>Desenvolvimento da biblioteca</h2>
<p>Desenvolvemos as instruções presentes na biblioteca com base em informações detalhadas obtidas na documentação do dispositivo. Ao verificarmos a documentação fornecida, pudemos entender os protocolos necessários para interagir com o dispositivo gráfico a partir das instruções.

No nosso processo de desenvolvimento da biblioteca, optamos por uma abordagem que inicialmente não utilizava parâmetros de arquivo em nossas funções. Isso se deve ao fato de termos implementado um mapeamento direto para o dispositivo de hardware. Essencialmente, isso significava que estávamos lidando diretamente com o dispositivo em si, sem a necessidade de especificar arquivos específicos em nossas chamadas de função. Após desenvolvermos e testarmos o mapeamento direto com sucesso, transferimos a responsabilidade de lidar com os arquivos para o driver do dispositivo.

Definimos as instruções principais para configuram os valores de "DATA_A_ptr" e "DATA_B_ptr"`, configurados como ponteiros para inteiros de 32 bits ("uint32_t*"), com base nos parâmetros das instruções. Os valores dessas variáveis são definidos de acordo com a necessidade da instrução a partir do que estava documentado no documento da GPU. A lógica utilizada buscou tratar o "DATA_A_ptr" e "DATA_B_ptr" como registradores de 32 bits. Como cada bit geralmente possui um significado específico, foi necessário colocá-los na posição correta. Para isso, utilizamos lógica de movimentação de deslocamento com o operador OR. Basicamente, deslocamos os valores para a esquerda e, em seguida, utilizamos a operação OR para combinar esses valores com os bits existentes no registrador.

Foi utilizado também funções de verificações de parâmetros para ajudar a prevenir erros decorrentes de valores fora dos limites esperados. Por exemplo, ao definir cores, coordenadas ou tamanhos, é crucial garantir que esses valores estejam dentro das especificações suportadas pela GPU, ou seja, evitando que essas entradas cheguem à GPU e causem problemas.

<h3>Funções</h3>

open_device(const char *device_path):

    Objetivo: Abrir o arquivo contido na /dev/.
    Funcionalidade: Tenta abrir o dispositivo especificado no modo de leitura e escrita. Retorna o descritor de arquivo (file descriptor) se bem-sucedido e -1 em caso de falha.

write_device(int fd, const char *data):

    Objetivo: Escreve os dados por abstração na /dev/.
    Funcionalidade: Tenta escrever os dados fornecidos no dispositivo associado ao descritor de arquivo fornecido. Retorna o número de bytes escritos se bem-sucedido e -1 em caso de falha.

read_device(int fd, char *buffer, size_t size):

    Objetivo: Ler do dispositivo.
    Funcionalidade: Tenta ler dados do dispositivo associado ao descritor de arquivo fornecido e os armazena no buffer fornecido. Retorna o número de bytes lidos se bem-sucedido e -1 em caso de falha.

close_device(int fd):

    Objetivo: Fechar o dispositivo.
    Funcionalidade: Tenta fechar o dispositivo associado ao descritor de arquivo fornecido.

verificar_cor(int vermelho, int verde, int azul):

    Objetivo: Verificar se os valores RGB estão dentro dos limites.
    Funcionalidade: Verifica se os valores de vermelho, verde e azul estão dentro do intervalo permitido (0 a 7).

verificar_cordenadas(int x, int y):

    Objetivo: Verificar se as coordenadas estão dentro dos limites da tela.
    Funcionalidade: Verifica se as coordenadas x e y estão dentro dos limites da tela (0 a 639 para x e 0 a 479 para y).

verificar_cordenadas_poligono(int x, int y):

    Objetivo: Verificar se as coordenadas estão dentro dos limites do polígono.
    Funcionalidade: Verifica se as coordenadas x e y estão dentro dos limites do polígono (0 a 511 para x e 0 a 479 para y).

verificar_tamanho(int tamanho):

    Objetivo: Verificar se o tamanho está dentro dos limites.
    Funcionalidade: Verifica se o tamanho fornecido está dentro do intervalo permitido (0 a 15).

verificar_sprite(int sprite):

    Objetivo: Verificar se o número do sprite está dentro dos limites.
    Funcionalidade: Verifica se o número do sprite fornecido está dentro do intervalo permitido (0 a 31).

verificar_registrador(int registrador):

    Objetivo: Verificar se o número do registrador está dentro dos limites.
    Funcionalidade: Verifica se o número do registrador fornecido está dentro do intervalo permitido (1 a 31).

verificar_bloco(int bloco):

    Objetivo: Verificar se o número do bloco está dentro dos limites.
    Funcionalidade: Verifica se o número do bloco fornecido está dentro do intervalo permitido (0 a 4799).

verificar_endereco(int endereco):

    Objetivo: Verificar se o endereço está dentro dos limites.
    Funcionalidade: Verifica se o endereço fornecido está dentro do intervalo permitido (0 a 12799).

editar_sprite(int fd, uint32_t DATA_A_ptr, uint32_t DATA_B_ptr, int endereco, int vermelho, int verde, int azul):

    Objetivo: Editar as propriedades de um sprite.
    Funcionalidade: Configura os valores de DATA_A e DATA_B para editar as propriedades do sprite com os valores fornecidos e escreve no dispositivo.

editar_bloco_background(int fd, uint32_t DATA_A_ptr, uint32_t DATA_B_ptr, int x, int y, int vermelho, int verde, int azul):

    Objetivo: Editar as propriedades de um bloco de fundo.
    Funcionalidade: Configura os valores de DATA_A e DATA_B para editar as propriedades do bloco de fundo com os valores fornecidos e escreve no dispositivo.

print_quadrado(int fd, uint32_t DATA_A_ptr, uint32_t DATA_B_ptr, int endereco, int x, int y, int tamanho, int vermelho, int verde, int azul):

    Objetivo: Desenhar um quadrado na tela.
    Funcionalidade: Configura os valores de DATA_A e DATA_B para desenhar um quadrado na tela com os valores fornecidos e escreve no dispositivo.

print_triangulo(int fd, uint32_t DATA_A_ptr, uint32_t DATA_B_ptr, int endereco, int x, int y, int tamanho, int vermelho, int verde, int azul):

    Objetivo: Desenhar um triângulo na tela.
    Funcionalidade: Configura os valores de DATA_A e DATA_B para desenhar um triângulo na tela com os valores fornecidos e escreve no dispositivo.

print_sprite(int fd, uint32_t DATA_A_ptr, uint32_t DATA_B_ptr, uint32_t ativar_sprite, int x, int y, int sprite, int registrador):

    Objetivo: Configurar e imprimir um sprite.
    Funcionalidade: Configura os valores de DATA_A e DATA_B para configurar e imprimir um sprite na tela com os valores fornecidos e escreve no dispositivo.

set_background(int fd, uint32_t DATA_A_ptr, uint32_t DATA_B_ptr, int vermelho, int verde, int azul):

    Objetivo: Definir a cor de fundo da tela.
    Funcionalidade: Configura os valores de DATA_A e DATA_B para definir a cor de fundo da tela com os valores fornecidos e escreve no dispositivo.

escrever_no_arquivo(int fd, uint32_t dataA, uint32_t dataB, char* informacao):

    Objetivo: Envia a string formatada contendo o data_A e data_B da função para o driver.
    Funcionalidade: Escreve a informação fornecida da instrução no arquivo associado ao descritor de arquivo fornecido.
</p>
</div>



<h2>Resultado e conclusão</h2>
<p>
  Após a conclusão de todos os processos de mapeamento de memória, criação do driver e desenvolvimento das funções da biblioteca, obtivemos o resultado esperado. Foi possível criar uma imagem por meio da alteração da cor de fundo, inserção de polígonos e sprites. Dessa forma, a imagem final resultou em uma paisagem de floresta, onde utilizamos a modificação dos blocos para simular a grama verde, polígonos para representar o sol, nuvens e árvores, e sprites para adornar o chão com flores e pedras. Além disso, a imagem incluiu uma nave espacial atirando em outra no céu, conforme ilustrado na Figura 6.
</p>

<p align="center">
  <img src = "https://github.com/Armaaaaaaaaaaaaaaaaaaaaaaaaaaando/Barramento/assets/111616936/5016e9fe-7bfc-4adc-ac72-d1fc1ec1b923" width = "450px"/>
  <p align="center">
    <strong>Figura 6.</strong> 
  </p>
</p>

<p>
  A conclusão deste projeto marca o fim de um trabalho detalhado e colaborativo, onde cada etapa foi realizada com dedicação. Enfrentamos desafios técnicos, mas superamos todos e atingimos nossos objetivos. Implementamos todas as funcionalidades planejadas, criando uma imagem detalhada com alteração da cor de fundo, inserção de polígonos e sprites.

O projeto atingiu suas metas e proporcionou aprendizados valiosos. O sucesso demonstra a importância do planejamento, comunicação e trabalho em equipe. Estamos orgulhosos do resultado final e agradecemos a todos pelo empenho. Este projeto servirá como um marco significativo em nossa trajetória, destacando nossa capacidade de inovar e entregar soluções de alta qualidade.
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





