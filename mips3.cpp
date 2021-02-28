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
        set<string> data_label_types = {".word", ".asciiz", ".ascii"};
		vector<vector<string>> program;
		int maxLength;					// I think it's related to size limit mentioned(Please Check)
		int programCounter = 0;				// to store current line
		string current_command;			// points to current command line
		int TotalLines = 0;				// total no. of commands in program(basically no. of lines)
		// All commands can be made private but for now let's go with public to make life easy
        map<string, vector<int>> map_word;
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
                cout << "1" << endl;
                find_data(program);
                cout << "2" << endl;
                Memdisplay();
                cout << "3" << endl;
                // execution()
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
                    temp+=' ';
                    // continue;
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


        // void execute(){
        //     while(programCounter < commandCount){
        //         // program vector loop, 
		// 		/*current_command = program[programCounter] */
        //         //removeTabsSpaces(current_command);	// return current_command(trimmed)						
        //         if(current_command == ""){
        //             programCounter ++;
        //             continue;
        //         }
        //         int operationToBePerformed = getOperation(current_command);              // also remove command so only registers and memory remain
        //         //lineByLineExecute(operationToBePerformed);
        //     }
        // }

        int getOperation(string current_commandCopy){
            int operationSize;
            for(operationSize=0; operationSize<4; operationSize++){
                if(current_commandCopy[operationSize] == ' '){
                    break;
                }             
            }
            string operationString;
            operationString = current_command.substr(0, operationSize);
            current_command = current_command.substr(operationSize+1);
            int operationNumberFormat = -1;
            for(int i=0; i<6; i++){
                if(operationString == commandsList[i]){
                    operationNumberFormat = i;
                    break;
                }
            }
            if(operationNumberFormat == -1){
                cout << "Invalid Operator" << endl;
                exit(1);
            }
            return operationNumberFormat;
            // // check for R-format or I-format like operationNumberFormat < 7 then R-format
            // // if R-format add, sub
            // for(int i=0; i<3; i++){
            //     //removeTabsSpaces(current_command);
            //     //getRegistor
            //     //removeComma
            // }
        }

        void lineByLineExecute(int operation){
				/*switch
					case:0
						{
							string a, b, c
							a = findRegister // {spaces, next comma,}
							comma removal
							b= same
							comma removal
							c = same
							
						}
				*/
        }

        void find_data(vector<vector<string>> v){
            vector<vector<string>>::iterator itr1;
            for(itr1 = v.begin(); itr1!=v.end();  itr1++){
                cout << "4" << endl;
                if((*itr1)[0] == ".data"){
                    cout << "5" << endl;
                    for(itr1++; data_label_types.find((*itr1)[1])!=data_label_types.end(); itr1++){
                        cout << "6" << endl;
                        if((*itr1)[1] == ".word"){
                            cout << "7" << endl;
                            vector<int> v1;
                            for(int j=2; j<(*itr1).size(); j++){
                                cout << "8" << endl;
                                int temp1 = stoi((*itr1)[j]);
                                cout << "//" << temp1 << endl;
                                v1.push_back(temp1);
                            }
                            map_word[(*itr1)[0]] = v1;
                            cout << "//" << (*itr1)[0] << endl;
                    }
                }
            }
            map<string, vector<int>>::iterator itr;
            for(itr = map_word.begin(); itr != map_word.end(); itr++){
                cout << itr -> first << endl;
                for(auto y: itr -> second){
                    cout << y << endl;
                }
            }
            // for(int i=0; i<program.size(); i++){
            //         for(int j=0; j<program[i].size(); j++){
            //             cout << program[i][j] << " ";
            //         }
            //         cout << endl;
            // }
        }

        void Memdisplay(){
            map<string, vector<int>>::iterator itr;
            for(itr = map_word.begin(); itr != map_word.end(); itr++){
                cout << itr -> first << endl;
                for(auto y: itr -> second){
                    cout << y << endl;
                }
            }
        }
};

int main() {
	cout << "MIPS Simulator" << endl;
	// int option                  // for mode selection(Step by Step execution / Whole execution)
	// we can also open file from here
	ofstream myFile("myFile3.txt");
	if (!myFile.is_open()) {
		cout << "Error occured, file cannot be open" << endl;
	}
	string str1 = ".data\n";
	string str2 = "Label: .word 1, 2, 3, 4\n";
    string str3 = ".text\n";
    string str4 = "main:\n";
    string str5 = "addi $s1, $zero, 4\n";
    string str6 = "j L1\n";
    string str7 = "Ll: add $s2, $zero, $s1\n";
    string str8 = "jr $ra";
	myFile << str1 << str2 << str3 << str4 << str5 << str6 << str7 << str8;
	myFile.close();
	mipsSimulator mips("myFile3.txt");
	// mips.execute();
	return 0;
}