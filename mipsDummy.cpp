#include<iostream>
#include<vector>
#include<fstream>
#include<string>

using namespace std;

class mipsSimulator {
	private:
		string registerNames[32] = {"zero", "at", "v0", "v1", "a0", "a1", "a2", "a3", "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7", "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7", "t8", "t9", "k0", "k1", "gp", "sp", "fp", "ra"};
		int registerValues[32] = {};    // empty brace kept to initialize with 0
		string commandsList[6] = {"add", "sub", "jump", "bne", "lw", "sw"};			// Add, sub, jump, bne, lw, sw(modify accordingly)
		vector<vector<string>> program;
		int maxLength;					// I think it's related to size limit mentioned(Please Check)
		int programCounter;				// to store current line
		string current_command;			// points to current command line
		int commandCount;				// total no. of commands in program(basically no. of lines)
		// All commands can be made private but for now let's go with public to make life easy
	public:
		mipsSimulator(string filePath) {
			commandCount = 0;
			programCounter = 0;
			maxLength = 10000;
			string lineInput;
			ifstream file(filePath);      // File path is basically file name including .txt(I think both file and program needs to be in same directory)
			if (file.is_open()) {			// opens file and check if it's there or not
				while (getline(file, lineInput)) {
					commandCount++;
					if (commandCount > maxLength) {
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

// vector<vector<string>>
        void execute(){
            while(programCounter < commandCount){
                // program vector loop, 
				/*current_command = program[programCounter] */
                //removeTabsSpaces(current_command);	// return current_command(trimmed)						
                if(current_command == ""){
                    programCounter ++;
                    continue;
                }
                int operationToBePerformed = getOperation(current_command);              // also remove command so only registers and memory remain
                //lineByLineExecute(operationToBePerformed);
            }
        }

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
                cout << "Invalid Operator" << endl;\
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

        void display(){

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
	string str1 = "add $s1, $s2, $s3\n";
	string str2 = "sub $s4, $s5, $s6";
	myFile << str1 << str2;
	myFile.close();
	mipsSimulator mips("myFile3.txt");
	// mips.execute();
	return 0;
}