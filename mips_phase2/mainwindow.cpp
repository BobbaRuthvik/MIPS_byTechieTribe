#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <string>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <utility>
#include <QMessageBox>
#include <QFileDialog>
#include <QMainWindow>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::edit(QString s) {
    ui->textBrowser->setPlainText(s);
}

void MainWindow::showMessage(QString s){
    QMessageBox::warning(this,"",s);
}

void MainWindow::showStalls_1(pair<vector<int>, pair<int, double>> p){
    string s = "WITH DATA FORWARDING\n\nStalls\t: ";
    s += to_string(p.second.first);
    s += "\n\nIPC\t: ";
    s += to_string(p.second.second);
    s += "\n\n---------------------------------------------------\n\nNumber of stalls for each instruction: \n\n";
    for(int i=0; i<p.first.size(); i++){
        s += to_string(i+1);
        s += "\t";
        s += to_string(p.first[i]);
        s += "\n";
    }
    ui->textEdit_3->setPlainText(QString::fromStdString(s));
}

void MainWindow::showStalls_2(pair<vector<int>, pair<int, double>> p){
    string s = "WITHOUT DATA FORWARDING\n\nStalls\t: ";
    s += to_string(p.second.first);
    s += "\n\nIPC\t: ";
    s += to_string(p.second.second);
    s += "\n\n---------------------------------------------------\n\nNumber of stalls for each instruction: \n\n";
    for(int i=0; i<p.first.size(); i++){
        s += to_string(i+1);
        s += "\t";
        s += to_string(p.first[i]);
        s += "\n";
    }
    ui->textEdit_3->setPlainText(QString::fromStdString(s));
}

class mipsSimulator {

    private:
    string registerNames[32] = {"zero", "at", "v0", "v1", "a0", "a1", "a2", "a3", "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7", "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7", "t8", "t9", "k0", "k1", "gp", "sp", "fp", "ra"};
        map<string, int> Register;
        vector<vector<string>> program; // entire program is stored line by line
            set<string> data_types = {".word", ".asciiz"};
            int programCounter;				// to store current line
            int PC = 0;
            int TotalLines;				// total no. of commands in program(basically no. of lines)
            map<string, vector<int>> map_word;
            string memory[1024][2];  // arr[I][0] = value arr[][1] = type
            int freeMemoryAvailable = 1024*4; // bytes
            map<string, int> labels; // for storing address associated with label
            int current_mem_address = 0;
            int instrStart = 0;
            int stalls = 0;
            vector<vector<int>> rememberStalls; // stalls, pc value
            vector<int> instructionStalls;
            int idealClockCycle = 4;
        string console = "Console :\n\n";
    public:
        mipsSimulator(vector<string> v, MainWindow* m) {            // constructor checks size
            TotalLines = 0;
            programCounter = 0;
            string lineInput;
            vector<int> temp;
            temp.push_back(0);
            temp.push_back(0);
            for(int i=0; i<v.size(); i++){
                TotalLines++;
                program.push_back(subVector(v[i],m));		// now entire program is stored line by line, no file business anymore
                rememberStalls.push_back(temp);
                instructionStalls.push_back(0);
            }
        }

        map<int, string> Memdisplay(){                      // dislays memory occupied
            map<int, string> mp;
            for(int i=0; i<current_mem_address; i++){
                mp[i*4] = memory[i][0];
            }
            return mp;
        }

        vector<string> subVector(string s, MainWindow* m){     // separates all neccesory keywords(essentials of instruction) by space
            vector<string> v;
            string temp = "";
            for(int i=0; i<s.size(); i++){
                if(s[i] == ',' || s[i] == '$' || s[i] == '(' || s[i] == ')'){     // (resolved) if someone writes add $s0 $s1 $s2 still it works...
                    temp+=' ';
                    temp+=s[i];
                    temp+=' ';
                }
                else{
                    temp += s[i];
                }
            }
            return getWords(temp, m);
        }


        vector<string> getWords(string temp, MainWindow* m){       // returns vector of keywords
            vector<string> v;
            string word = "";
            for (int i=0; i<temp.length(); i++)
            {
                if(temp[i] == '"'){
                    for (i=i+1;temp[i] != '"' && i<temp.length(); i++) {
                         word = word + temp[i];
                    }
                    if(++i != temp.length()){
                        cout << "error";
                        m->showMessage("Error");
                        exit(1);                 // assumption : only one string can be initialized and that too at only end
                    }
                }
                else if(temp[i] == ' ' || temp[i] == '\t')
                {
                    if(word!="")
                        v.push_back(word);
                    word = "";
                }
                else {
                    word = word + temp[i];
                }
            }
            if(word!="")
                v.push_back(word);
            return v;
        }

        pair<map<string, int>, map<int, string>> execute_2(MainWindow* m){                 // Executes program
            cout << "\nConsole : \n";

            find_data(m);
            int i;
            for(i=programCounter; i<program.size(); i++){
                if(program[i].size()!=0){
                    if(program[i][0] == ".text")
                        break;
                }
            }
            if(i==program.size()){
                cout << "Error please mention .text" << endl;
                m->showMessage("Error please mention .text");
                exit(1);
            }
            else
                programCounter = ++i;
            initialize();
            for(i=programCounter; i<program.size(); i++){
                if(program[i].size()!=0){
                    if(program[i][0] == "main:"){
                        break;
                    }
                }
            }
            if(i==program.size()){
                cout << "Error, please mention .main" << endl;
                m->showMessage("Error, please mention .main");
                exit(1);
            }
            programCounter = ++i;
            instrStart = i;
            PC = programCounter;
            for(i=programCounter; i<program.size(); i++){
                for(int j=0; j<rememberStalls.size(); j++){
                    if((PC - rememberStalls[j][1]) >= 2){               // rememberStalls[i][0] -> stalls, rememberStalls[i][1] -> i
                        rememberStalls[j][0] = 0;
                    }
                }
                if(program[i].size()!=0){
                    string instruction = program[i][0];
                    if(instruction == "add"){
                        add(program[i], i, m);
                        checkDependencyWithoutForwarding(i, program[i][2], PC);
                    }
                    else if(instruction == "addi"){
                        addi(program[i], i, m);
                        checkDependencyWithoutForwarding(i, program[i][2], PC);
                    }
                    else if(instruction == "sub"){
                        sub(program[i], i, m);
                        checkDependencyWithoutForwarding(i, program[i][2], PC);
                    }
                    else if(instruction == "j"){
                        i =  j(program[i], i, m);
                        programCounter = i;
                        checkDependencyWithoutForwarding(i, "null", PC);
                    }
                    else if(instruction == "bne"){
                        int tempi;
                        tempi = bne(program[i], i, m);
                        if(tempi==program.size()){
                            cout << "Label not found " << endl;
                            m->showMessage("Label not found...");
                            exit(1);
                        }
                        if(tempi != -1){
                            i = tempi;
                            programCounter = i;
                        }
                        checkDependencyWithoutForwarding(i, "null", PC);
                    }
                    else if(instruction == "beq"){
                        int tempi;
                        tempi = beq(program[i], i, m);
                        if(tempi==program.size()){
                            cout << "Label not found " << endl;
                            m->showMessage("Label not found...");
                            exit(1);
                        }
                        if(tempi != -1){
                            i = tempi;
                            programCounter = i;
                        }
                        checkDependencyWithoutForwarding(i, "null", PC);
                    }
                    else if(instruction == "lw"){
                        lw(program[i], i, m);
                        checkDependencyWithoutForwarding(i, program[i][2], PC);
                    }
                    else if(instruction == "sw"){
                        sw(program[i], i, m);
                    }
                    else if(instruction == "la"){
                        la(program[i], i, m);
                        checkDependencyWithoutForwarding(i, program[i][2], PC);
                    }
                    else if(instruction == "slt"){
                        slt(program[i], i, m);
                        checkDependencyWithoutForwarding(i, program[i][2], PC);
                    }
                    else if(instruction == "syscall"){
                        if(Register.find("v0") -> second == 10){
                            double ipc = (double) (idealClockCycle - 4.0)/ (stalls+idealClockCycle);
                            m->showStalls_2(make_pair(instructionStalls, make_pair(stalls, ipc)));
                            return make_pair(registerDisplay(), Memdisplay());
                        }
                        syscall(i,m);
                    }
                    else{
                        if(program[i].size() == 1 && instruction[instruction.length()-1] == ':') // since label name is single string and ending with ':'
                            continue;
                        else{
                            cout << "Error in line " << i+1 << "." << endl;
                            string temp = "Error in line "+to_string(i+1);
                            m->showMessage(QString::fromStdString(temp));
                            exit(1);
                        }
                    }
                    idealClockCycle++;
                    PC++;
                }
                programCounter++;
                if(i+1 == program.size()){ // assumption :  there must be a syscall for exit else there will be an error
                    cout << "\nERROR : No exit call" << endl;
                    m->showMessage(QString::fromStdString("\nERROR : No exit call"));
                    exit(1);
                }
            }
            registerDisplay();
            cout << "----------" << endl;
//            Memdisplay();
            cout << programCounter << endl;
        }

        pair<map<string, int>, map<int, string>> execute_1(MainWindow* m){                 // Executes program
            cout << "\nConsole : \n";

            find_data(m);
            int i;
            for(i=programCounter; i<program.size(); i++){
                if(program[i].size()!=0){
                    if(program[i][0] == ".text")
                        break;
                }
            }
            if(i==program.size()){
                cout << "Error please mention .text" << endl;
                m->showMessage("Error please mention .text");
                exit(1);
            }
            else
                programCounter = ++i;
            initialize();
            for(i=programCounter; i<program.size(); i++){
                if(program[i].size()!=0){
                    if(program[i][0] == "main:"){
                        break;
                    }
                }
            }
            if(i==program.size()){
                cout << "Error, please mention .main" << endl;
                m->showMessage("Error, please mention .main");
                exit(1);
            }
            programCounter = ++i;
            instrStart = i;
            PC = programCounter;
            for(i=programCounter; i<program.size(); i++){
                for(int j=0; j<rememberStalls.size(); j++){
                    if((PC - rememberStalls[j][1]) >= 2){               // rememberStalls[i][0] -> stalls, rememberStalls[i][1] -> i
                        rememberStalls[j][0] = 0;
                    }
                }
                if(program[i].size()!=0){
                    string instruction = program[i][0];
                    if(instruction == "add"){
                        add(program[i], i, m);
                        checkDependencyWithForwarding(i, program[i][2], program[i][0], PC);
                    }
                    else if(instruction == "addi"){
                        addi(program[i], i, m);
                        checkDependencyWithForwarding(i, program[i][2], program[i][0], PC);
                    }
                    else if(instruction == "sub"){
                        sub(program[i], i, m);
                        checkDependencyWithForwarding(i, program[i][2], program[i][0], PC);
                    }
                    else if(instruction == "j"){
                        i =  j(program[i], i, m);
                        programCounter = i;
                        checkDependencyWithForwarding(i, "null", program[i][0], PC);
                    }
                    else if(instruction == "bne"){
                        int tempi;
                        tempi = bne(program[i], i, m);
                        if(tempi==program.size()){
                            cout << "Label not found " << endl;
                            m->showMessage("Label not found...");
                            exit(1);
                        }
                        if(tempi != -1){
                            i = tempi;
                            programCounter = i;
                        }
                        checkDependencyWithForwarding(i, "null", program[i][0], PC);
                    }
                    else if(instruction == "beq"){
                        int tempi;
                        tempi = beq(program[i], i, m);
                        if(tempi==program.size()){
                            cout << "Label not found " << endl;
                            m->showMessage("Label not found...");
                            exit(1);
                        }
                        if(tempi != -1){
                            i = tempi;
                            programCounter = i;
                        }
                        checkDependencyWithForwarding(i, "null", program[i][0], PC);
                    }
                    else if(instruction == "lw"){
                        lw(program[i], i, m);
                        checkDependencyWithForwarding(i, program[i][2], program[i][0], PC);
                    }
                    else if(instruction == "sw"){
                        sw(program[i], i, m);
                    }
                    else if(instruction == "la"){
                        la(program[i], i, m);
                        checkDependencyWithForwarding(i, program[i][2], program[i][0], PC);
                    }
                    else if(instruction == "slt"){
                        slt(program[i], i, m);
                        checkDependencyWithForwarding(i, program[i][2], program[i][0], PC);
                    }
                    else if(instruction == "syscall"){
                        if(Register.find("v0") -> second == 10){
                            double ipc = (double) (idealClockCycle - 4.0)/ (stalls+idealClockCycle);
                            m->showStalls_1(make_pair(instructionStalls, make_pair(stalls, ipc)));
                            return make_pair(registerDisplay(), Memdisplay());
                        }
                        syscall(i,m);
                    }
                    else{
                        if(program[i].size() == 1 && instruction[instruction.length()-1] == ':') // since label name is single string and ending with ':'
                            continue;
                        else{
                            cout << "Error in line " << i+1 << "." << endl;
                            string temp = "Error in line "+to_string(i+1);
                            m->showMessage(QString::fromStdString(temp));
                            exit(1);
                        }
                    }
                    idealClockCycle++;
                    PC++;
                }
                programCounter++;
                if(i+1 == program.size()){ // assumption :  there must be a syscall for exit else there will be an error
                    cout << "\nERROR : No exit call" << endl;
                    m->showMessage(QString::fromStdString("\nERROR : No exit call"));
                    exit(1);
                }
            }
            registerDisplay();
            cout << "----------" << endl;
//            Memdisplay();
            cout << programCounter << endl;
        }

        map<string, int> registerDisplay(){
            return Register;
        }

        void initialize(){              // refreshes register values
            string temp = "";
            for(int i=0; i<32; i++){
                temp = registerNames[i];
                Register.insert(pair<string, int>(temp, 0));
            }
            // string registerNames[32] = {"zero", "at", "v0", "v1", "a0", "a1", "a2", "a3", "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7", "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7", "t8", "t9", "k0", "k1", "gp", "sp", "fp", "ra"};
        }

        void add(vector<string> v, int pc, MainWindow* m){
            if(v.size() == 9 && v[1] == "$" && v[4] == "$" && v[7] == "$" && v[3] == "," && v[6] == ","){
                int a = Register.find(v[5]) -> second;
                int b = Register.find(v[8]) -> second;
                int c = a + b;
                Register.find(v[2]) -> second = c;
            }
            else{
                cout << "Error in line " << pc+1 << "." << endl;
                string temp = "Error in line "+to_string(pc+1);
                m->showMessage(QString::fromStdString(temp));
                exit(1);
            }
        }

        // sub $ s0 , $ s2 , $ s3 // assumption : v[7] should be either '$' or an integer
        void sub(vector<string> v, int pc, MainWindow* m){
            if((v.size() == 9 || v.size() == 8) && v[1] == "$" && v[4] == "$"  && v[3] == "," && v[6] == ","){
                if(v.size() == 9 && v[7] == "$"){
                    int a = Register.find(v[5]) -> second;
                    int b = Register.find(v[8]) -> second;
                    int c = a - b;
                    Register.find(v[2]) -> second = c;
                }
                else{
                    int a = Register.find(v[5]) -> second;
                    int c = a - stoi(v[7]);
                    Register.find(v[2]) -> second = c;
                }
            }
            else{
                cout << "Error in line " << pc+1 << "." << endl;
                string temp = "Error in line "+to_string(pc+1);
                m->showMessage(QString::fromStdString(temp));
                exit(1);
            }
        }

        void addi(vector<string> v, int pc, MainWindow* m){
            if(v.size() == 8 && v[1] == "$" && v[4] == "$" && v[3] == "," && v[6] == ","){
                int a = Register.find(v[5]) -> second;
                int b = stoi(v[7]);
                int c = a + b;
                Register.find(v[2]) -> second = c;
            }
            else{
                cout << "Error in line " << pc+1 << "." << endl;
                string temp = "Error in line "+to_string(pc+1);
                m->showMessage(QString::fromStdString(temp));
                exit(1);
            }
        }

        int j(vector<string> v, int pc, MainWindow* m){
            if(v.size() == 2){
                string label = v[1] + ":" + "\0";
                int i;
                for(i=0; i<program.size(); i++){
                    if(program[i].size() != 0){
                        if(program[i][0] == label){
                            break;
                        }
                    }
                }
                return i;
            }
            else{
                cout << "Error in line " << pc+1 << "." << endl;
                string temp = "Error in line "+to_string(pc+1);
                m->showMessage(QString::fromStdString(temp));
                exit(1);
            }
        }

        // bne $ s0 , $ s8 , label
        int bne(vector<string> v, int pc, MainWindow* m){
            if(v.size() == 8 && v[1] == "$" && v[4] == "$" && v[3] == "," && v[6] == ","){
                string label = v[7] + ":";
                int a = Register.find(v[2]) -> second;
                int b = Register.find(v[5]) -> second;
                int i;
                if(a != b){
                    for(i=0; i<program.size(); i++){
                        if(program[i].size() != 0){
                            if(program[i][0] == label)
                                break;
                        }
                    }
                }
                else{
                    i = -1;
                }
                return i;
            }
            else{
                cout << "Error in line " << pc+1 << "." << endl;
                string temp = "Error in line "+to_string(pc+1);
                m->showMessage(QString::fromStdString(temp));
                exit(1);
            }
        }

        int beq(vector<string> v, int pc, MainWindow* m){
            if(v.size() == 8 && v[1] == "$" && v[4] == "$" && v[3] == "," && v[6] == ","){
                string label = v[7] + ":";
                int a = Register.find(v[2]) -> second;
                int b = Register.find(v[5]) -> second;
                int i;
                if(a == b){
                    for(i=0; i<program.size(); i++){
                        if(program[i].size() != 0){
                            if(program[i][0] == label)
                                break;
                        }
                    }
                }
                else{
                    i = -1;
                }
                return i;
            }
            else{
                cout << "Error in line " << pc+1 << "." << endl;
                string temp = "Error in line "+to_string(pc+1);
                m->showMessage(QString::fromStdString(temp));
                exit(1);
            }
        }

        void lw(vector<string> v, int pc, MainWindow* m){
            // lw $s0, 0($s2)
            if(v.size() == 9 && v[1] == "$" && v[3] == "," && v[5] == "(" && v[6] == "$" && v[8] == ")"){
                int b = stoi(v[4]);
                int c = Register.find(v[7]) -> second;
                if(b%4 != 0 && memory[(b + c)/4][1] != "word" && c%4 != 0){
                    cout << "Error in line " << pc+1 << "." << endl;
                    string temp = "Error in line "+to_string(pc+1);
                    m->showMessage(QString::fromStdString(temp));
                    exit(1);
                }
                Register[v[2]] = stoi(memory[(b + c)/4][0]);

            }
            else{
                cout << "Error in line " << pc+1 << "." << endl;
                string temp = "Error in line "+to_string(pc+1);
                m->showMessage(QString::fromStdString(temp));
                exit(1);
            }
        }

        void sw(vector<string> v, int pc, MainWindow* m){
            // sw $s0, 0($s2)
            if(v.size() == 9 && v[1] == "$" && v[3] == "," && v[5] == "(" && v[6] == "$" && v[8] == ")"){
                int a = Register.find(v[2]) -> second;
                int b = stoi(v[4]);
                int c = Register.find(v[7]) -> second;
                if(b%4 != 0 && memory[(b + c)/4][1] != "word" && c%4 != 0){
                    cout << "Error in line " << pc+1 << "." << endl;
                    string temp = "Error in line "+to_string(pc+1);
                    m->showMessage(QString::fromStdString(temp));
                    exit(1);
                }
                memory[(b + c)/4][0] = to_string(a);
            }
            else{
                cout << "Error in line " << pc+1 << "." << endl;
                string temp = "Error in line "+to_string(pc+1);
                m->showMessage(QString::fromStdString(temp));
                exit(1);
            }
        }

        void la(vector<string> v, int pc, MainWindow* m){
            // la $ s0 , label
            if(v.size() == 5 && v[1] == "$" && v[3] == ","){
                if(labels.find(v[4]) != labels.end()){
                    Register[v[2]] = labels.find(v[4]) -> second;
                }
                else{
                cout << "Error in line " << pc+1 << "." << endl;
                string temp = "Error in line "+to_string(pc+1);
                m->showMessage(QString::fromStdString(temp));
                exit(1);
                }
            }
            else{
                cout << "Error in line " << pc+1 << "." << endl;
                string temp = "Error in line "+to_string(pc+1);
                m->showMessage(QString::fromStdString(temp));
                exit(1);
            }
        }
        // li $ v0 , 10
        void li(vector<string> v, int pc, MainWindow* m){
            if(v.size() == 5 && v[1] == "$" && v[3] == ","){
                Register.find(v[2]) -> second = stoi(v[4]);
            }
            else{
                cout << "Error in line " << pc+1 << "." << endl;
                string temp = "Error in line "+to_string(pc+1);
                m->showMessage(QString::fromStdString(temp));
                exit(1);
            }
        }



        void slt(vector<string> v, int pc, MainWindow* m){
            // slt $ t2 , $ t0 , $ t1
            if(v.size() == 9 && v[1] == "$" && v[4] == "$" && v[7] == "$" && v[3] == "," && v[6] == ","){
                int b = Register.find(v[5]) -> second;
                int c = Register.find(v[8]) -> second;

                if(b<c)
                    Register[v[2]] = 1;
                else
                    Register[v[2]] = 0;
            }
            else{
                cout << "Error in line " << pc+1 << "." << endl;
                string temp = "Error in line "+to_string(pc+1);
                m->showMessage(QString::fromStdString(temp));
                exit(1);
            }
        }

        // assumption : syscall is used only for exit, printing integers or strings. therefore before calling syscall v0 should be 10 or 1 or 4 else syntax error
        void syscall(int pc, MainWindow* m){
            if(Register.find("v0") -> second == 1){
                cout << Register.find("a0")->second;
                console += to_string(Register.find("a0")->second);
                m->edit(QString::fromStdString(console));
            }
            else if(Register.find("v0") -> second == 4){
                int a = Register.find("a0") -> second;
                if(current_mem_address > a && memory[a][1] == "asciiz"){
                    cout << memory[a][0];
                    console += memory[a][0];
                    m->edit(QString::fromStdString(console));
                }
                else{
                    cout << "Error in line " << pc+1 << "." << endl;
                    string temp = "Error in line "+to_string(pc+1);
                    m->showMessage(QString::fromStdString(temp));
                    exit(1);
                }
            }
            else{
                cout << "Error in line " << pc+1 << "." << endl;
                string temp = "Error in line "+to_string(pc+1);
                m->showMessage(QString::fromStdString(temp));
                exit(1);
            }
        }

        void checkDependencyWithoutForwarding(int i, string reg1, int pc){    // polymorphism
                    //cout << "vachina" << endl;
                    int copy1 = i;
                    while(copy1+1 < program.size() && (program[copy1+1].size() == 0 || program[copy1+1].size() == 1) ){
                        copy1++;
                    }
                    int copy2 = copy1+1;            // check with spaces if this is correct
                    while(copy2+1 < program.size() && (program[copy2+1].size() == 0 || program[copy2+1].size() == 1)){
                        copy2++;
                    }

                    if(copy1+1 < program.size() && reg1 == "null"){         // if current line is bne, beq or j
                        rememberStalls[copy1+1][0] = 1;
                        rememberStalls[copy1+1][1] = pc;
                        instructionStalls[copy1+1]++;
                        stalls++;
                        return;
                    }
                    if(copy1+1 < program.size() && (program[copy1+1][0] == "add" || program[copy1+1][0] == "slt") && (program[copy1+1][5] == reg1 || program[copy1+1][8] == reg1)){
                        if(rememberStalls[copy1+1][0] < 2){
                            rememberStalls[copy1+1][0] == 0 ? stalls +=2: stalls++;
                            rememberStalls[copy1+1][0] == 0 ? instructionStalls[copy1+1] +=2 : instructionStalls[copy1+1]++;
                            rememberStalls[copy1+1][0] = 2;
                            rememberStalls[copy1+1][1] = pc;
                        }
                        return;
                    }
                    if(copy1+1 < program.size() && program[copy1+1][0] == "sub"){
                        if(program[copy1+1].size() == 9 && (program[copy1+1][5] == reg1 || program[copy1+1][8] == reg1)){
                            if(rememberStalls[copy1+1][0] < 2){
                                rememberStalls[copy1+1][0] == 0 ? stalls +=2 : stalls++;
                                rememberStalls[copy1+1][0] == 0 ? instructionStalls[copy1+1] +=2 : instructionStalls[copy1+1]++;
                                rememberStalls[copy1+1][0] = 2;
                                rememberStalls[copy1+1][1] = pc;
                            }
                        }
                        if(program[copy1+1].size() == 8 && program[copy1+1][5] == reg1){
                            if(rememberStalls[copy1+1][0] < 2){
                                rememberStalls[copy1+1][0] == 0 ? stalls +=2 : stalls++;
                                rememberStalls[copy1+1][0] == 0 ? instructionStalls[copy1+1] +=2 : instructionStalls[copy1+1]++;
                                rememberStalls[copy1+1][0] = 2;
                                rememberStalls[copy1+1][1] = pc;
                            }
                        }
                        return;
                    }
                    if(copy1+1 < program.size() && program[copy1+1][0] == "addi" && program[copy1+1][5] == reg1){
                        if(rememberStalls[copy1+1][0] < 2){
                            rememberStalls[copy1+1][0] == 0 ? stalls +=2 : stalls++;
                            rememberStalls[copy1+1][0] == 0 ? instructionStalls[copy1+1] +=2 : instructionStalls[copy1+1]++;
                            rememberStalls[copy1+1][0] = 2;
                            rememberStalls[copy1+1][1] = pc;
                        }
                        return;
                    }
                    if(copy1+1 < program.size() && (program[copy1+1][0] == "lw") && (program[copy1+1][7] == reg1)){
                        if(rememberStalls[copy1+1][0] < 2){
                            rememberStalls[copy1+1][0] == 0 ? stalls +=2 : stalls++;
                            rememberStalls[copy1+1][0] == 0 ? instructionStalls[copy1+1] +=2 : instructionStalls[copy1+1]++;
                            rememberStalls[copy1+1][0] = 2;
                            rememberStalls[copy1+1][1] = pc;
                        }
                        return;
                    }
                    if(copy1+1 < program.size() && (program[copy1+1][0] == "sw") && (program[copy1+1][2] == reg1 || program[copy1+1][7] == reg1)){
                        if(rememberStalls[copy1+1][0] < 2){
                            rememberStalls[copy1+1][0] == 0 ? stalls +=2 : stalls++;
                            rememberStalls[copy1+1][0] == 0 ? instructionStalls[copy1+1] +=2 : instructionStalls[copy1+1]++;
                            rememberStalls[copy1+1][0] = 2;
                            rememberStalls[copy1+1][1] = pc;
                        }
                        return;
                    }
                    if(copy1+1 < program.size() && (program[copy1+1][0] == "bne" || program[copy1+1][0] == "beq" || program[copy1+1][0] == "j")){
                        if(program[copy1+1][0] == "j"){
                            return;
                        }
                        if((program[copy1+1][2] == reg1 || program[copy1+1][5] == reg1)){
                            if(rememberStalls[copy1+1][0] < 2){
                                rememberStalls[copy1+1][0] == 0 ? stalls +=2 : stalls++;
                                rememberStalls[copy1+1][0] == 0 ? instructionStalls[copy1+1] +=2 : instructionStalls[copy1+1]++;
                                rememberStalls[copy1+1][0] = 2;
                                rememberStalls[copy1+1][1] = pc;
                            }
                        }
                        return;
                    }
                    // copy2 ......
                    if(copy2+1 < program.size() && (program[copy2+1][0] == "add" || program[copy2+1][0] == "slt") && (program[copy2+1][5] == reg1 || program[copy2+1][8] == reg1)){
                        stalls++;
                        instructionStalls[copy2+1]++;
                        rememberStalls[copy2+1][0] = 1;
                        rememberStalls[copy2+1][1] = pc;
                        return;
                    }
                    if(copy2+1 < program.size() && program[copy2+1][0] == "sub"){
                        if(program[copy2+1].size() == 9 && (program[copy2+1][5] == reg1 || program[copy2+1][8] == reg1)){
                            stalls++;
                            instructionStalls[copy2+1]++;
                            rememberStalls[copy2+1][0] = 1;
                            rememberStalls[copy2+1][1] = pc;
                        }
                        if(program[copy2+1].size() == 8 && program[copy2+1][5] == reg1){
                            stalls++;
                            instructionStalls[copy2+1]++;
                            rememberStalls[copy2+1][0] = 1;
                            rememberStalls[copy2+1][1] = pc;
                        }
                        return;
                    }
                    if(copy2+1 < program.size() && program[copy2+1][0] == "addi" && program[copy2+1][5] == reg1){
                        stalls++;
                        instructionStalls[copy2+1]++;
                        rememberStalls[copy2+1][0] = 1;
                        rememberStalls[copy2+1][1] = pc;
                        return;
                    }
                    if(copy2+1 < program.size() && (program[copy2+1][0] == "lw") && (program[copy2+1][7] == reg1)){
                        stalls++;
                        instructionStalls[copy2+1]++;
                        rememberStalls[copy2+1][0] = 1;
                        rememberStalls[copy2+1][1] = pc;
                        return;
                    }
                    if(copy2+1 < program.size() && (program[copy2+1][0] == "sw") && (program[copy2+1][2] == reg1 || program[copy2+1][7] == reg1)){
                        rememberStalls[copy2+1][0] = 1;
                        rememberStalls[copy2+1][1] = pc;
                        instructionStalls[copy2+1]++;
                        stalls++;
                        return;
                    }
                    if(copy2+1 < program.size() && (program[copy2+1][0] == "bne" || program[copy2+1][0] == "beq") && (program[copy2+1][2] == reg1 || program[copy2+1][5] == reg1)){
                        rememberStalls[copy2+1][0] = 1;
                        rememberStalls[copy2+1][1] = pc;
                        instructionStalls[copy2+1]++;
                        stalls++;
                        return;
                    }
                }

                void checkDependencyWithForwarding(int i, string reg1, string operation, int PC){
                    // cout << "vachina" << endl;
                    int copy1 = i;
                    while(copy1+1 < program.size() && (program[copy1+1].size() == 0 || program[copy1+1].size() == 1) ){
                        copy1++;
                    }
                    int copy2 = copy1+1;
                    while(copy2+1 < program.size() && (program[copy2+1].size() == 0 || program[copy2+1].size() == 1)){
                        copy2++;
                    }


                    if(reg1 == "null"){             // if bne,beq (or) j just add a stall
                        rememberStalls[copy1+1][0] = 1;
                        rememberStalls[copy1+1][1] = PC;
                        instructionStalls[copy1+1]++;
                        stalls++;
                        return;
                    }

                    if(operation == "lw" || operation == "la"){
                        // copy1 ..........
                        if(copy1+1 < program.size() && (program[copy1+1][0] == "add" || program[copy1+1][0] == "slt") && (program[copy1+1][5] == reg1 || program[copy1+1][8] == reg1)){
                            if(rememberStalls[copy1+1][0] == 0){
                                rememberStalls[copy1+1][0] = 1;
                                rememberStalls[copy1+1][1] = PC;
                                instructionStalls[copy1+1]++;
                                stalls++;
                            }
                            return;
                        }
                        if(copy1+1 < program.size() && program[copy1+1][0] == "sub") {
                            if(program[copy1+1].size()== 9 && (program[copy1+1][5] == reg1 || program[copy1+1][8] == reg1)){        // generic sub operation
                                if(rememberStalls[copy1+1][0] == 0){
                                    rememberStalls[copy1+1][0] = 1;
                                    rememberStalls[copy1+1][1] = PC;
                                    instructionStalls[copy1+1]++;
                                    stalls++;
                                }
                            }
                            if(program[copy1+1].size()== 8 && program[copy1+1][5] == reg1){           // immediate sub operation
                                if(rememberStalls[copy1+1][0] == 0){
                                    rememberStalls[copy1+1][0] = 1;
                                    rememberStalls[copy1+1][1] = PC;
                                    instructionStalls[copy1+1]++;
                                    stalls++;
                                }
                            }
                            return;
                        }
                        if(copy1+1 < program.size() && program[copy1+1][0] == "addi" && program[copy1+1][5] == reg1){
                            if(rememberStalls[copy1+1][0] == 0){
                                rememberStalls[copy1+1][0] = 1;
                                rememberStalls[copy1+1][1] = PC;
                                instructionStalls[copy1+1]++;
                                stalls++;
                            }
                            return;
                        }
                        if(copy1+1 < program.size() && program[copy1+1][0] == "sw" && program[copy1+1][7] == reg1){
                            if(rememberStalls[copy1+1][0] < 1){
                                rememberStalls[copy1+1][0] = 1;
                                rememberStalls[copy1+1][1] = PC;
                                instructionStalls[copy1+1]++;
                                stalls++;
                            }
                            return;
                        }
                        if(copy1+1 < program.size() && program[copy1+1][0] == "lw" && program[copy1+1][7] == reg1){
                            if(rememberStalls[copy1+1][0] < 1){
                                rememberStalls[copy1+1][0] = 1;
                                rememberStalls[copy1+1][1] = PC;
                                instructionStalls[copy1+1]++;
                                stalls++;
                            }
                            return;
                        }
                        if(copy1+1 < program.size() && (program[copy1+1][0] == "bne" || program[copy1+1][0] == "beq") && (program[copy1+1][2] == reg1 || program[copy1+1][5] == reg1)){
                            if(rememberStalls[copy1+1][0] < 2){
                                rememberStalls[copy1+1][0] == 0 ? stalls +=2 : stalls++;
                                rememberStalls[copy1+1][0] == 0 ? instructionStalls[copy1+1] +=2 : instructionStalls[copy1+1]++;
                                rememberStalls[copy1+1][0] = 2;
                                rememberStalls[copy1+1][1] = PC;
                            }
                            return;
                        }
                        // copy2 ..........
                        if(copy2+1 < program.size() && (program[copy2+1][0] == "bne" || program[copy2+1][0] == "beq") && (program[copy2+1][2] == reg1 || program[copy2+1][5] == reg1)){
                            if(rememberStalls[copy2+1][0] == 0){
                                rememberStalls[copy2+1][0] = 1;
                                rememberStalls[copy2+1][1] = PC;
                                instructionStalls[copy2+1]++;
                                stalls++;
                            }
                            return;
                        }
                    }

                    if(operation == "add" || operation == "slt"){
                        // copy1 .......
                        if(copy1+1 < program.size() && (program[copy1+1][0] == "bne" || program[copy1+1][0] == "beq") && (program[copy1+1][2] == reg1 || program[copy1+1][5] == reg1)){
                            if(rememberStalls[copy1+1][0] == 0){
                                rememberStalls[copy1+1][0] = 1;
                                rememberStalls[copy1+1][1] = PC;
                                instructionStalls[copy1+1]++;
                                stalls++;
                            }
                            return;
                        }
                    }
                    if(operation == "sub"){
                        // copy1 .......
                        if(program[copy1+1].size() == 9){
                            if(copy1+1 < program.size() && (program[copy1+1][0] == "bne" || program[copy1+1][0] == "beq") && (program[copy1+1][2] == reg1 || program[copy1+1][5] == reg1)){
                                if(rememberStalls[copy1+1][0] == 0){
                                    rememberStalls[copy1+1][0] = 1;
                                    rememberStalls[copy1+1][1] = PC;
                                    instructionStalls[copy1+1]++;
                                    stalls++;
                                }
                            }
                        }
                        if(program[copy1+1].size() == 8){
                            if(copy1+1 < program.size() && (program[copy1+1][0] == "bne" || program[copy1+1][0] == "beq") && program[copy1+1][2] == reg1){
                                if(rememberStalls[copy1+1][0] == 0){
                                    rememberStalls[copy1+1][0] = 1;
                                    rememberStalls[copy1+1][1] = PC;
                                    instructionStalls[copy1+1]++;
                                    stalls++;
                                }
                            }
                        }
                        return;
                    }
                    if(operation == "addi"){
                        // copy1 .......
                        if(copy1+1 < program.size() && (program[copy1+1][0] == "bne" || program[copy1+1][0] == "beq") && (program[copy1+1][2] == reg1 || program[copy1+1][5] == reg1)){
                            if(rememberStalls[copy1+1][0] == 0){
                                rememberStalls[copy1+1][0] = 1;
                                rememberStalls[copy1+1][1] = PC;
                                instructionStalls[copy1+1]++;
                                stalls++;
                            }
                            return;
                        }
                    }

                }

        void find_data(MainWindow* m){
            vector<vector<string>>::iterator itr;
            for(itr = program.begin(); itr != program.end();  itr++,programCounter++){
                if((*itr).size() == 0)
                    continue;
                else if((*itr)[0] == ".data"){
                    for(itr++,programCounter++; (*itr).size() == 0 || data_types.find((*itr)[0])!=data_types.end() || ((*itr).size()>1 && data_types.find((*itr)[1])!=data_types.end()); itr++,programCounter++){
                        if((*itr).size() == 0)
                            continue;
                        if((*itr)[1] == ".word" || (*itr)[0] == ".word"){

                            int flag = 0;
                            if((*itr)[1] == ".word"){
                                flag = 1;
                                int size = (*itr)[0].size();
                                if((*itr)[0][size-1] == ':'){
                                    if(freeMemoryAvailable >= 4)
                                        labels[(*itr)[0].substr(0,size-1)] = current_mem_address;
                                    else{
                                        cout << "memory limit exceeded" << endl;
                                        m->showMessage(QString::fromStdString("memory limit exceeded"));
                                        exit(1);
                                    }
                                }
                                else{
                                    cout << "Error in line " << programCounter+1 << "." << endl;
                                    string temp = "Error in line "+to_string(programCounter+1);
                                    m->showMessage(QString::fromStdString(temp));
                                    exit(1);
                                }
                            }
                            for(int j=flag+1; j<(*itr).size(); j++){
                                if(freeMemoryAvailable >= 4){
                                    memory[current_mem_address][0] = (*itr)[j];
                                    memory[current_mem_address][1] = "word";
                                    current_mem_address++;
                                    freeMemoryAvailable -= 4;
                                }
                                else{
                                        cout << "memory limit exceeded" << endl;
                                        m->showMessage(QString::fromStdString("memory limit exceeded"));
                                        exit(1);
                                }
                                if(++j < (*itr).size()){
                                    if((*itr)[j] == ",")
                                        continue;
                                    else {
                                        cout << "Error in line " << programCounter+1 << "." << endl;
                                        string temp = "Error in line "+to_string(programCounter+1);
                                        m->showMessage(QString::fromStdString(temp));
                                        exit(1);
                                    }
                                }

                            }
                        }
                        if((*itr)[1] == ".asciiz" || (*itr)[0] == ".asciiz"){
                            // did only for one string initialization i.e .asciiz "abk" <-only one string
                            int flag = 0;
                            if((*itr).size() > 0 && (*itr)[1] == ".asciiz"){
                                flag = 1;
                                int size = (*itr)[0].size();
                                if((*itr)[0][size-1] == ':'){
                                    if(freeMemoryAvailable >= (*itr)[flag+1].size())
                                        labels[(*itr)[0].substr(0,size-1)] = current_mem_address;
                                    else{
                                        cout << "memory limit exceeded" << endl;
                                        m->showMessage(QString::fromStdString("memory limit exceeded"));
                                        exit(1);
                                    }
                                }
                                else{
                                    cout << "Error in line " << programCounter+1 << "." << endl;
                                    string temp = "Error in line "+to_string(programCounter+1);
                                    m->showMessage(QString::fromStdString(temp));
                                    exit(1);
                                }
                            }
                            if(freeMemoryAvailable >= (*itr)[flag+1].size()){
                                memory[current_mem_address][0] = (*itr)[flag+1];
                                memory[current_mem_address][1] = "asciiz";
                                freeMemoryAvailable -= (*itr)[flag+1].size();
                            }
                            int cma = current_mem_address;
                            int len = (*itr)[flag+1].length();

                            /* if (*itr)[flag+1] = "abcdefgh"
                               memory[4][0] = "abcdefgh"; memory[4][1] = type;
                               memory[5][0] = "4" // index of memory where string is stored
                               memory[5][1] = "NULL";
                            */

                            if(len > 4){
                                for(int p=4; len > p; p+=4){
                                    current_mem_address++;
                                    memory[current_mem_address][0] = to_string(cma);
                                    memory[current_mem_address][1] = "NULL";
                                }
                            }
                            current_mem_address++;
                        }
                    }
                    break; // since we assumed that only one .data can be written(if we remove break ,I think code will work fine if we have consecutive .data)
                }
                else{
                    return; // since we assumed, .data can be written only at starting
                }
                programCounter++;
            }
        }


};

void MainWindow::on_pushButton_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this, "open file", "*.s");
    QFile file(file_name);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::warning(this,"","File is not found");
        return;
    }

    vector<string> program;
    QTextStream in(&file);
    while (!in.atEnd()) {
        program.push_back(in.readLine().toStdString());
    }
    mipsSimulator mips(program, this);

    pair<map<string, int>, map<int, string>> result;
    if(ui->checkBox->isChecked())
        result = mips.execute_1(this);
    else
        result = mips.execute_2(this);

    string s = "Registers : \n\n";
    for(auto itr = result.first.begin(); itr != result.first.end(); itr++){
        s += itr->first;
        s += "\t";
        s += to_string(itr->second);
        s += "\n";
    }
    s += "\n------------------\nData Section(Memory) :\n\n";
    for(auto itr = result.second.begin(); itr != result.second.end(); itr++){
        s += to_string(itr->first);
        s += "\t";
        s += itr->second;
        s += "\n";
    }
    ui->textEdit->setPlainText(QString::fromStdString(s));
    string t = "Text Section\n\n";
    for(int i=0; i<program.size(); i++){
        t += program[i];
        t += "\n";
    }
    ui->textEdit_2->setPlainText(QString::fromStdString(t));
}
void MainWindow::on_checkBox_stateChanged(int arg1)
{

}

