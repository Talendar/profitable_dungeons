# Profitable Dungeons

<i>Profitable Dungeons</i> is a free-to-play open-source game developed as part of the final project of the course <a href="https://uspdigital.usp.br/jupiterweb/obterDisciplina?sgldis=SSC0140&codcur=55041&codhab=0">"SSC0140 - Operating Systems I"</a>. Our goal for implementing the game was to practise <i>multi-threading</i>. More information can be found in <a href="https://www.youtube.com/watch?v=1CQ72u19udw&t=3s">this</a> video (in Portuguese). In order to play, you can either download the latest release of the game (Windows only) or compile the game from the source code (instructions bellow).


# Instructions for compiling

In order to compile the game from source, you must have <a href="https://www.qt.io/download-qt-installer">Qt5</a> installed on your machine. If you're a Linux user, the easiest way to install it is through a package manager. Check <a href="https://wiki.qt.io/Main">Qt wiki</a> for more information on how to install it.

Using <i>apt-get</i> (debian-based distros):

```sudo apt-get install qt5-default```

Once you've Qt installed, simply open the game's project ("src" folder) with QtCreator, build the project and run the game executable inside the folder with the binaries.
