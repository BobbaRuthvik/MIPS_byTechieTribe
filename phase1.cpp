#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<map>
#include<set>

using namespace std;

class mipsSimulator {
	private:
		string registerNames[32] = {"zero", "at", "v0", "v1", "a0", "a1", "a2", "a3", "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7", "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7", "t8", "t9", "k0", "k1", "gp", "sp", "fp", "ra"};
		map<string, int> map_instructions;
		vector<vector<string>> program; // entire program is stored line by line
        set<string> data_types = {".word", ".asciiz"};
		int programCounter;				// to store current line
		int TotalLines;				// total no. of commands in program(basically no. of lines)
        map<string, vector<int>> map_word;
        string memory[1024][2];  // arr[I][0] = value arr[][1] = type
        int freeMemoryAvailable = 1024*4; // bytes
        map<string, int> labels; // for storing address associated with label
        int current_mem_address = 0;
	public:
		mipsSimulator(string filePath) {            // constructor checks size
            std::ifstream in(filePath, std::ifstream::ate | std::ifstream::binary);
            int a = in.tellg();
            cout << a << " bytes file." << endl;
            if (a > freeMemoryAvailable) {
						cout << "File is too large" << endl;
						exit(1);
					}
            freeMemoryAvailable -= a;
			TotalLines = 0;
			programCounter = 0;
			string lineInput;
			ifstream file(filePath);      // File path is basically file name including .txt(I think both file and program needs to be in same directory)
			if (file.is_open()) {			// opens file and check if it's there or not
				while (getline(file, lineInput)) {
					TotalLines++;
					program.push_back(subVector(lineInput));		// now entire program is stored line by line, no file business anymore
				}
				file.close();
                cout << "Code:" << endl;
				for(int i=0; i<program.size(); i++){
                    for(int j=0; j<program[i].size(); j++){
                        cout << program[i][j] << " ";
                    }
                    cout << endl;
                }
                
			}
			else {
				cout << "File does not exist" << endl;
				exit(1);
			}
		}

        void Memdisplay(){                      // dislays memory occupied
            for(int i=0; i<current_mem_address; i++){
                cout << memory[i][0] << " " << memory[i][1] << endl;
            }
        }

        vector<string> subVector(string s){     // separates all neccesory keywords(essentials of instruction) by space
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
            return getWords(temp);  
        }


        vector<string> getWords(string temp){       // returns vector of keywords
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

        void stepByStepEecute(){        // executes step by step
            find_data();
            int i;
            for(i=programCounter; i<program.size(); i++){
                if(program[i].size()!=0){
                    if(program[i][0] == ".text")
                        break;
                }
            }
            if(i==program.size()){
                cout << "Error please mention .text" << endl;
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
                exit(1);
            }
            programCounter = ++i;
            cout <<"start:"<< programCounter << endl;
            int opt1 = 1;
            i=programCounter;
            while(i<program.size()){
                if(program[i].size()!=0){
                    string instruction = program[i][0];
                    if(instruction == "add"){
                        add(program[i], i);
                    }
                    else if(instruction == "addi"){
                        addi(program[i], i);
                    }
                    else if(instruction == "sub"){
                        sub(program[i], i);
                    }
                    else if(instruction == "j"){
                        i =  j(program[i], i);
                        programCounter = i;
                    }
                    else if(instruction == "bne"){
                        int tempi;
                        tempi = bne(program[i], i);
                        if(tempi==program.size()){
                            cout << "Label not found " << endl;
                            exit(1);
                        }
                        if(tempi != -1){
                            i = tempi;
                            programCounter = i;
                        }
                    }
                    else if(instruction == "beq"){
                        int tempi;
                        tempi = beq(program[i], i);
                        if(tempi==program.size()){
                            cout << "Label not found " << endl;
                            exit(1);
                        }
                        if(tempi != -1){
                            i = tempi;
                            programCounter = i;
                        }
                    }
                    else if(instruction == "lw"){
                        lw(program[i], i);
                    }
                    else if(instruction == "sw"){
                        sw(program[i], i);
                    }
                    else if(instruction == "li"){
                        li(program[i], i);
                    }
                    else if(instruction == "la"){
                        la(program[i], i);
                    }
                    else if(instruction == "slt"){
                        slt(program[i], i);
                    }
                    else if(instruction == "syscall"){
                        syscall(i);
                    }
                    else{
                        if(program[i].size() == 1 && instruction[instruction.length()-1] == ':') // since label name is single string and ending with ':'
                            continue;
                        else{
                            cout << "Error in line " << i+1 << "." << endl;
                            exit(1);
                        } 
                    }
                }
                // cout <<"hi: "<< programCounter << endl; 
                programCounter++;
                // cout <<"bye: "<< programCounter << endl;   
                if(i+1 == program.size()){ // assumption :  there must be a syscall for exit else there will be an error
                    cout << "No exit call" << endl;
                    exit(1);
                }
                registerDisplay();
                cout << "----------" << endl;
                Memdisplay();
                cout << programCounter << endl;
                cout << "Enter -continue execution, any other key to stop." << endl;
                if (cin.get() == '\n')
                    i++; 
                else
                    exit(1);
            }
        }

        void execute(){                 // Executes program
            find_data();
            int i;
            for(i=programCounter; i<program.size(); i++){
                if(program[i].size()!=0){
                    if(program[i][0] == ".text")
                        break;
                }
            }
            if(i==program.size()){
                cout << "Error please mention .text" << endl;
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
                exit(1);
            }
            programCounter = ++i;
            cout <<"start:"<< programCounter << endl;
            for(i=programCounter; i<program.size(); i++){
                if(program[i].size()!=0){
                    string instruction = program[i][0];
                    if(instruction == "add"){
                        add(program[i], i);
                    }
                    else if(instruction == "addi"){
                        addi(program[i], i);
                    }
                    else if(instruction == "sub"){
                        sub(program[i], i);
                    }
                    else if(instruction == "j"){
                        i =  j(program[i], i);
                        programCounter = i;
                    }
                    else if(instruction == "bne"){
                        int tempi;
                        tempi = bne(program[i], i);
                        if(tempi==program.size()){
                            cout << "Label not found " << endl;
                            exit(1);
                        }
                        if(tempi != -1){
                            i = tempi;
                            programCounter = i;
                        }
                    }
                    else if(instruction == "beq"){
                        int tempi;
                        tempi = beq(program[i], i);
                        if(tempi==program.size()){
                            cout << "Label not found " << endl;
                            exit(1);
                        }
                        if(tempi != -1){
                            i = tempi;
                            programCounter = i;
                        }
                    }
                    else if(instruction == "lw"){
                        lw(program[i], i);
                    }
                    else if(instruction == "sw"){
                        sw(program[i], i);
                    }
                    else if(instruction == "li"){
                        li(program[i], i);
                    }
                    else if(instruction == "la"){
                        la(program[i], i);
                    }
                    else if(instruction == "slt"){
                        slt(program[i], i);
                    }
                    else if(instruction == "syscall"){
                        syscall(i);
                    }
                    else{
                        if(program[i].size() == 1 && instruction[instruction.length()-1] == ':') // since label name is single string and ending with ':'
                            continue;
                        else{
                            cout << "Error in line " << i+1 << "." << endl;
                            exit(1);
                        } 
                    }
                }
                // cout <<"hi: "<< programCounter << endl; 
                programCounter++;
                // cout <<"bye: "<< programCounter << endl;   
                if(i+1 == program.size()){ // assumption :  there must be a syscall for exit else there will be an error
                    cout << "No exit call" << endl;
                    exit(1);
                } 
            }
            registerDisplay();
            cout << "----------" << endl;
            Memdisplay();
            cout << programCounter << endl;
        }

        void registerDisplay(){
                map<string, int>::iterator itr;
                for(itr = map_instructions.begin(); itr!=map_instructions.end(); itr++)
                    cout << "\t" << itr -> first << "\t" << itr -> second << endl;
        }

        void initialize(){              // refreshes register values
            string temp = "";
            for(int i=0; i<32; i++){
                temp = registerNames[i];
                map_instructions.insert(pair<string, int>(temp, 0));
            }
            // string registerNames[32] = {"zero", "at", "v0", "v1", "a0", "a1", "a2", "a3", "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7", "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7", "t8", "t9", "k0", "k1", "gp", "sp", "fp", "ra"};
        }

        void add(vector<string> v, int pc){  
            if(v.size() == 9 && v[1] == "$" && v[4] == "$" && v[7] == "$" && v[3] == "," && v[6] == ","){
                int a = map_instructions.find(v[5]) -> second;
                int b = map_instructions.find(v[8]) -> second;
                int c = a + b;
                map_instructions.find(v[2]) -> second = c;
            }
            else{
                cout << "Error in line " << pc+1 << "." << endl;
                exit(1);
            }
        }

        // sub $ s0 , $ s2 , $ s3 // assumption : v[7] should be either '$' or an integer
        void sub(vector<string> v, int pc){
            if((v.size() == 9 || v.size() == 8) && v[1] == "$" && v[4] == "$"  && v[3] == "," && v[6] == ","){
                if(v.size() == 9 && v[7] == "$"){
                    int a = map_instructions.find(v[5]) -> second;
                    int b = map_instructions.find(v[8]) -> second;
                    int c = a - b;
                    map_instructions.find(v[2]) -> second = c;
                }
                else{
                    int a = map_instructions.find(v[5]) -> second;
                    int c = a - stoi(v[7]);
                    map_instructions.find(v[2]) -> second = c;
                }
            }
            else{
                cout << "Error in line " << pc+1 << "." << endl;
                exit(1);
            }
        }

        void addi(vector<string> v, int pc){
            if(v.size() == 8 && v[1] == "$" && v[4] == "$" && v[3] == "," && v[6] == ","){
                int a = map_instructions.find(v[5]) -> second;
                int b = stoi(v[7]);
                int c = a + b;
                map_instructions.find(v[2]) -> second = c;
            }
            else{
                cout << "Error in line " << pc+1 << "." << endl;
                exit(1);
            }
        }

        int j(vector<string> v, int pc){
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
                exit(1);
            }
        }

        // bne $ s0 , $ s8 , label
        int bne(vector<string> v, int pc){
            if(v.size() == 8 && v[1] == "$" && v[4] == "$" && v[3] == "," && v[6] == ","){
                string label = v[7] + ":";
                int a = map_instructions.find(v[2]) -> second;
                int b = map_instructions.find(v[5]) -> second;
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
                exit(1);
            }
        }

        int beq(vector<string> v, int pc){
            if(v.size() == 8 && v[1] == "$" && v[4] == "$" && v[3] == "," && v[6] == ","){
                string label = v[7] + ":";
                int a = map_instructions.find(v[2]) -> second;
                int b = map_instructions.find(v[5]) -> second;
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
                exit(1);
            }
        }

        void lw(vector<string> v, int pc){
            // lw $s0, 0($s2)
            if(v.size() == 9 && v[1] == "$" && v[3] == "," && v[5] == "(" && v[6] == "$" && v[8] == ")"){
                int b = stoi(v[4]);
                int c = map_instructions.find(v[7]) -> second;
                if(b%4 != 0 && memory[(b + c)/4][1] != "word" && c%4 != 0){
                    cout << "Error in line " << pc+1 << "." << endl;
                    exit(1);
                }
                map_instructions[v[2]] = stoi(memory[(b + c)/4][0]);
                
            }
            else{
                cout << "Error in line " << pc+1 << "." << endl;
                exit(1);
            }
        }

        void sw(vector<string> v, int pc){
            // sw $s0, 0($s2)
            if(v.size() == 9 && v[1] == "$" && v[3] == "," && v[5] == "(" && v[6] == "$" && v[8] == ")"){
                int a = map_instructions.find(v[2]) -> second;
                int b = stoi(v[4]);
                int c = map_instructions.find(v[7]) -> second;
                if(b%4 != 0 && memory[(b + c)/4][1] != "word" && c%4 != 0){
                    cout << "Error in line " << pc+1 << "." << endl;
                    exit(1);
                }
                memory[(b + c)/4][0] = to_string(a);
            }
            else{
                cout << "Error in line " << pc+1 << "." << endl;
                exit(1);
            }
        }

        void la(vector<string> v, int pc){
            // la $ s0 , label
            if(v.size() == 5 && v[1] == "$" && v[3] == ","){
                if(labels.find(v[4]) != labels.end()){
                    map_instructions[v[2]] = labels.find(v[4]) -> second;
                }
                else{
                cout << "Error in line " << pc+1 << "." << endl;
                exit(1);
                }
            }
            else{
                cout << "Error in line " << pc+1 << "." << endl;
                exit(1);
            }
        }
        // li $ v0 , 10
        void li(vector<string> v, int pc){
            if(v.size() == 5 && v[1] == "$" && v[3] == ","){
                map_instructions.find(v[2]) -> second = stoi(v[4]);
            }
            else{
                cout << "Error in line " << pc+1 << "." << endl;
                exit(1);
            }
        }



        void slt(vector<string> v, int pc){
            // slt $ t2 , $ t0 , $ t1
            if(v.size() == 9 && v[1] == "$" && v[4] == "$" && v[7] == "$" && v[3] == "," && v[6] == ","){
                int b = map_instructions.find(v[5]) -> second;
                int c = map_instructions.find(v[8]) -> second;

                if(b<c)
                    map_instructions[v[2]] = 1;
                else
                    map_instructions[v[2]] = 0;
            }
            else{
                cout << "Error in line " << pc+1 << "." << endl;
                exit(1);
            }
        }

        // assumption : syscall is used only for exit. therefore before calling syscall v0 should be 10 else syntax error
        void syscall(int pc){
            if(map_instructions.find("v0") -> second == 10){
                cout << "Registers: " << endl;
                registerDisplay();
                cout << "--------------------" << endl;
                cout << "Memory: " << endl;
                Memdisplay();
                // cout << programCounter << endl;
                exit(1);
            }
            // if(map_instructions.find("v0") -> second == 1){
            //     cout << (map_instructions.find("a0") -> second) << endl;
            //     registerDisplay();
            //     cout << "--------------------" << endl;
            //     Memdisplay();
            //     // cout << programCounter << endl;
            //     exit(1);
            // }
            else{
                cout << "Error in line " << pc+1 << "." << endl;
                exit(1);
            }
        }

        void find_data(){
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
                                        exit(1);
                                    }
                                }
                                else{
                                    cout << "Error in line " << programCounter+1 << "." << endl;
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
                                        exit(1);
                                    }
                                if(++j < (*itr).size()){    // in QTspim if we write ',' or ' ', code is working, but now our code will work fine only if integers are seperated by ',' only
                                    if((*itr)[j] == ",")
                                        continue;
                                    else {
                                        cout << "Error in line " << programCounter+1 << "." << endl;
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
                                    if(freeMemoryAvailable >>= (*itr)[flag+1].size())
                                        labels[(*itr)[0].substr(0,size-1)] = current_mem_address;
                                    else{
                                        cout << "memory limit exceeded" << endl;
                                        exit(1);
                                    }
                                }
                                else{
                                    cout << "Error in line " << programCounter+1 << "." << endl;
                                    exit(1);
                                }
                            }
                            if(freeMemoryAvailable >= (*itr)[flag+1].size()){
                                memory[current_mem_address][0] = (*itr)[flag+1];
                                memory[current_mem_address][1] = "asciiz";   // how to differentiate asciiz and 
                                freeMemoryAvailable -= (*itr)[flag+1].size();
                            }
                            int cma = current_mem_address;
                            int len = (*itr)[flag+1].length();
                            // abcdefgh
                            // memory[4][0] = "abcdefgh"; memory[4][1] = type;
                            // memory[5][0] = "4"; memory[5][1] = "NULL";
                            if(len > 4){
                                for(int p=4; len > p; p+=4){
                                    current_mem_address++;
                                    memory[current_mem_address][0] = to_string(cma = 4);
                                    memory[current_mem_address][1] = "NULL"; 
                                }
                            }
                            current_mem_address++;
                        }
                    }
                    // cout << "PC : " << programCounter << endl;
                    break; // since we assumed that only one .data can be written(if we remove break ,I think code will work fine if we have consecutive .data)
                }
                else{
                    return; // since we assumed, .data can be written only at starting
                }
                programCounter++;
            }
        }


};

// std::ifstream::pos_type filesize(const char* filename)
// {
//     std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
//     return in.tellg(); 
// }

int main() {
	cout << "/******MIPS Simulator******/\nEnter your file's name: \n";
    string s;
    cin >> s;
    mipsSimulator mips(s);
    int opt;
    cout << "\n1- stepByStep execution\n2- Execution\nAny other key to exit\n";
    cin >> opt;
    switch (opt)
    {
    case 1:
        mips.stepByStepEecute();
        break;

    case 2:
        mips.execute();
        break;    
    
    default:
        break;
    } 
	return 0;
}