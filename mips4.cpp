#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<map>

using namespace std;

class mipsSimulator {
	private:
		string registerNames[32] = {"zero", "at", "v0", "v1", "a0", "a1", "a2", "a3", "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7", "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7", "t8", "t9", "k0", "k1", "gp", "sp", "fp", "ra"};
		map<string, int> map_instructions;
		string commandsList[7] = {"add", "addi", "sub", "j", "bne", "lw", "sw"};			// Add, sub, jump, bne, lw, sw(modify accordingly)
		vector<vector<string>> program;
		int maxLength;					// I think it's related to size limit mentioned(Please Check)
		int programCounter;				// to store current line
		string current_command;			// points to current command line
		int TotalLines;				// total no. of commands in program(basically no. of lines)
		// All commands can be made private but for now let's go with public to make life easy
	public:
		mipsSimulator(string filePath) {
			TotalLines = 0;
			programCounter = 0;
			maxLength = 10000;
			string lineInput;
			ifstream file(filePath);      // File path is basically file name including .txt(I think both file and program needs to be in same directory)
			if (file.is_open()) {			// opens file and check if it's there or not
				while (getline(file, lineInput)) {
					TotalLines++;
					if (TotalLines > maxLength) {
						cout << "File is too large" << endl;
						exit(1);
					}
					program.push_back(subVector(lineInput));		// now entire program is stored line by line, no file business anymore
				}
				file.close();
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

        vector<string> subVector(string s){
            vector<string> v;
            string temp = "";
            for(int i=0; i<s.size(); i++){
                if(s[i] == ',' || s[i] == '$'){
                    continue;
                }
                else{
                    temp += s[i];
                }
            }
            return getWords(temp);  
        }


        vector<string> getWords(string temp){
            vector<string> v;
            string word = "";
            for (auto x : temp)  
            { 
                if (x == ' ' || x == '\t') 
                {
                    if(word!="")
                        v.push_back(word); 
                    word = ""; 
                } 
                else { 
                    word = word + x; 
                } 
            }
            if(word!="") 
                v.push_back(word); 
            return v;
        }

        void execute(){
            int i = 0;
            for(i=0; i<program.size(); i++){
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
            // cout << "ProgramCounter: " << programCounter << endl;
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
            // cout << "ProgramCounter: " << programCounter << endl;
            for(i=programCounter; i<program.size(); i++){
                if(program[i].size()!=0){
                    string instruction = program[i][0];
                    // cout << instruction << endl;
                    if(instruction == "add"){
                        add(program[i]);
                    }
                    else if(instruction == "addi"){
                        addi(program[i]);
                    }
                    else if(instruction == "sub"){
                        sub(program[i]);
                    }
                    else if(instruction == "j"){
                        i =  j(program[i]);
                        programCounter = i;
                    }
                    else if(instruction == "bne"){
                        int tempi;
                        tempi = bne(program[i]);
                        if(tempi != -1){
                            i = tempi;
                            programCounter = i;
                        }
                    }
                    else{
                        continue;
                    }
                }
                // cout <<"hi: "<< programCounter << endl; 
                programCounter++;
                // cout <<"bye: "<< programCounter << endl;    
            }
            registerDisplay();
            cout << programCounter << endl;
        }

        void registerDisplay(){
                map<string, int>::iterator itr;
                for(itr = map_instructions.begin(); itr!=map_instructions.end(); itr++)
                    cout << "\t" << itr -> first << "\t" << itr -> second << endl;
        }

        void initialize(){
            string temp = "";
            for(int i=0; i<32; i++){
                temp = registerNames[i];
                map_instructions.insert(pair<string, int>(temp, 0));
            }
            // string registerNames[32] = {"zero", "at", "v0", "v1", "a0", "a1", "a2", "a3", "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7", "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7", "t8", "t9", "k0", "k1", "gp", "sp", "fp", "ra"};
        }

        void add(vector<string> v){
            int a = map_instructions.find(v[2]) -> second;
            int b = map_instructions.find(v[3]) -> second;
            int c = a + b;
            map_instructions.find(v[1]) -> second = c;
            // programCounter++;
        }

        void sub(vector<string> v){
            int a = map_instructions.find(v[2]) -> second;
            int b = map_instructions.find(v[3]) -> second;
            int c = a - b;
            map_instructions.find(v[1]) -> second = c;
            // programCounter++;
        }

        void addi(vector<string> v){
            int a = map_instructions.find(v[2]) -> second;
            int b = stoi(v[3]);
            int c = a + b;
            map_instructions.find(v[1]) -> second = c;
            // programCounter++;
        }

        int j(vector<string> v){
            string label = v[1] + ":";
            int i;
            for(i=0; i<program.size(); i++){
                if(program[i].size() != 0){
                    if(program[i][0] == label)
                        break;
                }
            }
            return i;
        }

        int bne(vector<string> v){
            string label = v[3] + ":";
            int a = map_instructions.find(v[1]) -> second;
            int b = map_instructions.find(v[2]) -> second;
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
};

int main() {
	cout << "MIPS Simulator" << endl;
	// int option                  // for mode selection(Step by Step execution / Whole execution)
	// we can also open file from here
	/*ofstream myFile("myFile3.txt");
	if (!myFile.is_open()) {
		cout << "Error occured, file cannot be open" << endl;
	}
    string str0 = "\n";
    string str1 = ".text\n";
    string str2 = "\n";
    string str3 = ".main\n";
    string str4 = "\n";
	string str5 = "addi $s1, $s2, 3\n";
    string str6 = "\n";
	string str7 = "sub $s4, $s1, $s6";
	myFile << str0 << str1 << str2 << str3 << str4 << str5 << str6 << str7;
	myFile.close();*/
	mipsSimulator mips("myFile3.txt");
	mips.execute();
	return 0;
}