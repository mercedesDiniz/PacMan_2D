# PacMan - 2D modeling project with OpenGL
 
## Goal:
1. Aprimorar a interface com o usuário e a modelagem / ambientação do [projeto Pacman](https://github.com/mercedesDiniz/Games.c/tree/main/PacMan).
2. Descreva e Implemente um ambiente em OPENGL através da modelagem geométrica (geometria e topologia) de objetos 2D cujo sofreram as transformações geométricas (translação, rotação e escala, etc).

## OpenGL
Open Graphics Library (OpenGL) é uma especificação de uma
Application Programming Interface (API) para a criação de
aplicações gráficas.
Foi introduzido em 1992 pela Silicon Graphics e atualmente é
mantida pelo Khronos Group.
### Documentation: 
- [Opengl.org](https://www.opengl.org/)
- [Curso  Computação Gráfica (2018) - USP](https://edisciplinas.usp.br/course/view.php?id=61213#section-5)
### Installation:
- Linux:
    1. Instale a OpenGL Utility Toolkit (GLUT):
    ~~~bash
     sudo apt-get install freeglut3-dev
    ~~~
    2. Instale o pacote Miscellaneous Mesa GL utilities 
    ~~~bash
    sudo apt-get install mesa-utils
    ~~~
    3. Instale as bibliotecas X11 miscellaneous utility library e X11 Input extension library 
    ~~~bash
    sudo apt-get install libxmu-dev libxi-dev
    ~~~
    4. Instale a biblioteca GLFW:
    ~~~bash
    sudo apt-get install libglfw3-dev
    ~~~
    5. Após completar as instalações, compile seu código com:
    ~~~bash
    g++ -o exemplo.out exemplo.cpp -lglfw -lglut -lGLU -lGL -lm
    ~~~
    6. Execute o programa
    ~~~bash
    ./exemplo.out
    ~~~

- Windows:
    1. Faça o download do [Visual studio](https://www.visualstudio.com/downloads/)  e instale-o em sua maquina com a opção Desktop development with C++:
    2. Acesse faça o [download](https://edisciplinas.usp.br/mod/resource/view.php?id=2300602) do zip dos arquivos necessários da OpenGL. Após a finalização do download, descompacte o arquivo e mova-o para um local de sua preferência.
    3. Abra o Visual Studio, crie um Empty Project do Visual C++ (Ctrl+Shift+N → Templates →
    Visual C++ → Empty Project) e atribua um nome ao projeto.
    4. Após a criação do projeto, acesse as propriedades deste projeto (Project → Properties). Mude a plataforma para win32.
    5. Adicione o diretório include do zip baixado do site da disciplina no Include Directories do Visual Studio. Para isso, vá até a opção VC++ Directories (Configuration Properties → VC++ Directories). Altere o item Include Directories e inclua o diretório include do zip.
    6. O próximo passo  ́e adicionar os arquivos das bibliotecas compiladas FreeGLUT e GLEW nas configurações do projeto. Para isso, ainda na janela de propriedades do projeto, vá até a opção Input (Configuration Properties → Linker →Input). Altere o item Additional Dependencies e inclua manualmente a localização dos arquivos .lib localizados na pasta lib do zip baixado.
    7. Acesse o diretório do seu projeto (Clique direito no Projeto → Open Folder in File Explorer) e copie para este mesmo diretório as duas dll (freeglut.dll e glew32.dll) contidas na pasta bin do zip baixado.
    8. Por fim, insira o arquivo exemplo.cpp, que está disponível no site da disciplina, no projeto (Shift+Alt+A → exemplo.cpp), compile o projeto (Ctrl+Shift+B) e execute o c ́odigo (F5).

## References:
- [Projeto Pacman](https://github.com/mercedesDiniz/Games.c/tree/main/PacMan)
- [Canal Programação Descomplicada - Pacman em linguagem C com OpenGL](https://www.youtube.com/watch?v=z7_dIC6ipZA&t=482s&ab_channel=Programa%C3%A7%C3%A3oDescomplicada)
- [Curso de Computação Gráfica da USP (2018)](https://edisciplinas.usp.br/course/view.php?id=61213#section-5)
