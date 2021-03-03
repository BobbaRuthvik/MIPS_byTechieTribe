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
		int registerValues[32] = {};    // empty brace kept to initialize with 0
		string commandsList[6] = {"add", "sub", "jump", "bne", "lw", "sw"};			// Add, sub, jump, bne, lw, sw(modify accordingly)
        set<string> data_types = {".word", ".asciiz", ".ascii"};
		vector<vector<string>> program;
		int maxLength;					// I think it's related to size limit mentioned(Please Check)
		int programCounter = 0;			// to store current line
		string current_command;			// points to current command line
		int TotalLines = 0;				// total no. of commands in program(basically no. of lines)
		// All commands can be made private but for now let's go with public to make life easy
        map<string, vector<int>> map_word;

        string memory[1024][2];  // arr[I][0] = "10100" arr[][1] = type
        map<string, int> labels; // for storing address associated with label
        int current_mem_address = 0;

	public:
		mipsSimulator(string filePath) {
			TotalLines = 0;
			programCounter = 0;
			maxLength = 10000;
			string lineInput;
			ifstream file(filePath);      // File path is basically file name including .txt(I think both file and program needs to be in same directory)
			if (file.is_open()) {			// opens file and check if it's there or not

				while (getline(file, lineInput)) {
					TotalLines++;       // no need
					if (TotalLines > maxLength) {
						cout << "File is too large" << endl;
						exit(1);
					}
                    /*Check empty line */
					program.push_back(subVector(lineInput));		// now entire program is stored line by line, no file business anymore
				}

				file.close();
                TotalLines = program.size();
                cout << "Total No. of lines: " << TotalLines << endl;

				for(int i=0; i<program.size(); i++){
                    for(int j=0; j<program[i].size(); j++){
                        cout << program[i][j] << " ";
                    }
                    cout << endl;
                }

                find_data();
                cout << "curr_mem : " << current_mem_address << endl;
                for(auto x : labels){
                    cout << x.first << " " << x.second << endl;
                }
                Memdisplay();
                // execution()
			}
			else {
				cout << "File does not exist" << endl;
				exit(1);
			}
		}

        void Memdisplay(){
            for(int i=0; i<current_mem_address; i++){
                cout << memory[i][0] << " " << memory[i][1] << endl;
            }
        }

        vector<string> subVector(string s){
            vector<string> v;
            string temp = "";
            for(int i=0; i<s.size(); i++){
                if(s[i] == ',' || s[i] == '$'){     // (resolved) if someone writes add $s0 $s1 $s2 still it works...
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


        vector<string> getWords(string temp){
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
                if (temp[i] == ' ' || temp[i] == '\t') 
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


        void execute(){
            while(programCounter < TotalLines){
                // discard label name and do execution
                // atleast one label should be present after .text

                // int operationToBePerformed = getOperation(current_command);              // also remove command so only registers and memory remain
                //lineByLineExecute(operationToBePerformed);
            }
        }

        // (resolved) to do : check .data if it is in first line 
        // (resolved) assumption : label names should be in next line after .data (resolved : now it may not be next line i.e we can have empty lines in between)
        // assumption : .word/.asciiz should be followed by label name
        // to do : check for reserved keywords is not done
        // assumption : strings after .word are of only of decimal type. I think it can have any character(storing its ascii value) or integers in hexadecimal form or labels etc
        // assumption : only one .data is considered
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
                                if((*itr)[0][size-1] == ':')
                                    labels[(*itr)[0]] = current_mem_address;
                                else{
                                    cout << "error in line ...";
                                    exit(1);
                                }
                            }
                            for(int j=flag+1; j<(*itr).size(); j++){
                                memory[current_mem_address][0] = (*itr)[j];  
                                memory[current_mem_address][1] = "word";
                                current_mem_address++; 
                                if(++j < (*itr).size()){    // in QTspim if we write ',' or ' ', code is working, but now our code will work fine only if integers are seperated by ',' only
                                    if((*itr)[j] == ",")
                                        continue;
                                    else {
                                        cout << "error in line (No comma',')";
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
                                if((*itr)[0][size-1] == ':')
                                    labels[(*itr)[0]] = current_mem_address;
                                else{
                                    cout << "error in line ...";
                                    exit(1);
                                }
                            }
                            memory[current_mem_address][0] = (*itr)[flag+1];
                            memory[current_mem_address][1] = "asciiz";   // how to differentiate asciiz and ascii
                            current_mem_address++;
                            
                        }
                    }
                    cout << "PC : " << programCounter << endl;
                    break; // since we assumed that only one .data can be written(if we remove break ,I think code will work fine if we have consecutive .data)
                }
                else{
                    return; // since we assumed, .data can be written only at starting
                }
                programCounter++;
            }
        }
};

int main() {
	
	ofstream myFile("myFile3.txt");
	if (!myFile.is_open()) {
		cout << "Error occured, file cannot be open" << endl;
	}
	string str =   ".data\n"
                    "label1: .word 1, 2, 3, 4\n"
                    "Label2: .asciiz \"Hello World!\"\n"
                    ".text\n" 
                    "main:\n" 
                    "addi $s1, $zero, 4\n" 
                    "j L1\n" 
                    "L1:" 
                    "add $s2, $zero, $s1\n" 
                    "jr $ra\n";
	myFile << str;
	myFile.close();
	mipsSimulator mips("myFile3.txt");
	// mips.execute();
	return 0;
}
//lw $s0, 0($s0);  stoi(memory[8+(8/4)][0]); | | | | | | | | | | | | | 
// where .data can be written?
// for me now code is running if we put .data only at either starting or ending
// for time being make assumption of having .data only at starting
// we cannot access part of the string i.e. character by character