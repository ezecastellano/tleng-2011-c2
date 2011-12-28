#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "automata.hpp"
#include "graph.hpp"
#include "debugging.hpp"

using namespace std;

string basedir("graph/dots/");
string suffix_dot(".dot");
char file_id = 'a';

string next_file(const string & name) {
    string res = basedir + name + "-" + file_id + suffix_dot;
    file_id++;
    return res;
}

string next_file() {
    return next_file("");
}

void guardar(Automata a) {
    string name("Auto");
    guardar(a, name);
}

void guardar(Automata a, const string & name) {
    ofstream f(next_file(name));
    a.mostrar(f);
    f.close();
}

void guardar(LDGraph a) {
    ofstream f(next_file());
    a.mostrar(f);
    f.close();
}
