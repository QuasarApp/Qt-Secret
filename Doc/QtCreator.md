
# incude Qt-Secret in qtCreator 
* Open QtCreator
* Create a new subdirs project (file >> create a new project of file >> other projects >> subdirs project) and call it 'Master'
* Copy **your project folder** into **the Master project folder** or if you use git then add your project like submodule of a master project. Use the command: "git submodules add **URL**"
* Open Master.pro and add your project like subproject

``` qmake
TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS += \
           youProjectFolder

youProjectFolder.file = path/to/yuorProject.pro
```
 * Open the Master project folder in git console. If git is not installed then install it [this](https://git-scm.com/download/win)
 * run: git submodule add https://github.com/QuasarApp/Qt-Secret.git 
 * run: git submodule update --init --recursive
 * Open Master.pro
 * Add Qt-Secret library like subproject of Master
``` qmake
TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS += \
           Qt-Secret \
           youProjectFolder \

youProjectFolder.file = path/to/yuorProject.pro
``` 
 * Open YouProject.pro
 * Include in your MyProject.pro file the pri file of Qt-Secret library (insert it to end of the file next line :)
``` qmake
 include($$PWD/../Qt-Secret/src/Qt-Secret.pri)

```
 * Rebuild Master project
 * All done!. Now you need to build only a master project, because it will build both your project and the project Qt-Secret. QT-Secret will already be included in your project and you will be able to use it in your code. 


For Example, you can see my [master](https://github.com/QuasarApp/Qt-Secret/blob/master/Qt-Secret.pro) project and include library [lines](https://github.com/QuasarApp/Qt-Secret/blob/a6828ea53d8b6a5f60def149fee2792ae6d7d774/Qt-Secret-GUI/Qt-Secret-GUI.pro#L22). 
