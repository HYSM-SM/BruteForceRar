#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void deleteFileExtension(string* File)
{
    File->erase(File->size() - 4, File->size()); //delete .rar
}

string getScript(string nameRar,string nameFolder)
{
   return  "setlocal EnableDelayedExpansion\n"
           "for /f \"usebackq tokens=*\" %%a in (\"rockyou.txt\") Do (\n"
           "start /wait winRar -inul -ibck x -p%%a " + nameRar + " " + nameFolder + " -y\n"
           "if !errorlevel! equ 0 (\n"
           "cls\n"
           "echo password: %%a > ./" + nameFolder + "/" + nameFolder + "Password.txt\n"
           "echo password: %%a\n"
           "pause\n"
           "exit)\n"
           ")\n"
           "cls\n"
           "echo SORRY PASSWORD NOT FOUND\n"
           "pause\n"
           "exit";
}

void createFileScript(string script,string nameBat)
{
    ofstream Filescript(nameBat);
    Filescript << script;
    Filescript.close();
}

void startBrutForce(string nameFolder,string nameBat)
{
    system(("mkdir " + nameFolder).c_str());
    system(("start " + nameBat).c_str());
}

int main()
{
    string nameRar;
    cout << "Enter name rar file(example:work.rar)\n>";
    cin >> nameRar;
    string nameFolder = nameRar;
    deleteFileExtension(&nameFolder);

    string script = getScript(nameRar,nameFolder);
    string nameBat = nameFolder + ".bat";
    createFileScript(script,nameBat);

    startBrutForce(nameFolder, nameBat);
}