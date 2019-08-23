# Coltec QUIZ 2016

Um pequeno código usado no quiz da calourada do Coltec em 2016 e 2017.

Para compilá-lo basta instalar a biblioteca SDL: 
```
sudo apt install libsdl2-dev
```
E rodar o gcc:
```
g++ quiz.cpp -lSDL2 -o quiz
```

O código `arduino.ino` vai no arduino. Os pinos 2, 3, 4, 5, 6 e 7, correspondem às turmas 101, 102, 103, 104, 105 e 106 respectivamente.
O arduino mandará uma letra de "a" a "f" dependendo de qual turma apertar ou soltar o botão, sendo minúscula para apertar e maiúscula para soltar.

No programa as teclas usadas são:
* Q - quit
* F - fullscreen
* T - testscreen
* N - nextscreen

O endereço serial padrão do programa é `/dev/ttyACM1`, se não tiver nada conectado a isso o programa não abre. É possível alterar esse endereço na função main do `quiz.cpp`.

O código está uma bagunça, ele foi feito em cima da hora.