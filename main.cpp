#include<iostream>
#include<string>
#define MAX_SIZE 10
using namespace std;

std::string maze[MAX_SIZE][MAX_SIZE];
int levelNumber = 1;
int stopUpdate = 0;
std::string maxFillValue;
int maxFillValueInt;
int reachedT = 0;
int decrement_max_value = 0;

void inputMaze(){
	cout<<"input maze"<<endl;
	for(int i=0;i<MAX_SIZE;i++){
		for(int j=0;j<MAX_SIZE;j++){
			maze[i][j]="*";
		}
	}
	maze[7][6]="S";
	maze[2][3]="T";
}

void printMaze(){
	for(int i=0;i<MAX_SIZE;i++){
		for(int j=0;j<MAX_SIZE;j++){
			cout<<maze[i][j]<<"\t";
		}
		cout<<endl;
	}
}

void levelUpdate(std::string findChar, std::string updatedChar){
	cout<<"\nLevel "<<levelNumber<<" update"<<endl;
	int inside_if = 0;
	for(int i=0;i<MAX_SIZE;i++){
		for(int j=0;j<MAX_SIZE;j++){
			if(maze[i][j]==findChar){
				if(i-1>=0){
                    if(maze[i-1][j]=="*"){
                        maze[i-1][j]=updatedChar;
                        inside_if = 1;
                    }
                    else if(maze[i-1][j]=="T")
                        reachedT = 1;

                }
				if(i+1<MAX_SIZE){
                    if(maze[i+1][j]=="*"){
                        maze[i+1][j]=updatedChar;
                        inside_if = 1;
                    }
                    else if(maze[i+1][j]=="T")
                        reachedT = 1;
				}
				if(j-1>=0){
                    if(maze[i][j-1]=="*"){
                        maze[i][j-1]=updatedChar;
                        inside_if = 1;
                    }
                    else if(maze[i][j-1]=="T")
                        reachedT = 1;
				}
				if(j+1<MAX_SIZE){
                    if(maze[i][j+1]=="*"){
                        maze[i][j+1]=updatedChar;
                        inside_if = 1;
                    }
                    else if(maze[i][j+1]=="T")
                        reachedT = 1;
				}
			}
		}
	}
	if(reachedT == 1 && inside_if == 1){
        decrement_max_value = 1;
	}
	levelNumber+=1;
}

std::string findMaxFill(){
    std::string max_value = "";
    int max_value_int;
    for(int i=0;i<MAX_SIZE;i++){
		for(int j=0;j<MAX_SIZE;j++){
            if(maze[i][j]>max_value && maze[i][j] != "T" && maze[i][j] != "S" && maze[i][j] != "*")
                max_value = maze[i][j];
		}
    }
    max_value_int = stoi(max_value);
    if(decrement_max_value == 1){
        max_value_int-=1;
        max_value = to_string(max_value_int);
    }

    cout<<"\nMax fill value: "<<max_value<<endl;
    return max_value;
}

void backTrack(std::string check_string){
    cout<<"\nbacktracking:"<<endl;
    for(int i=0;i<MAX_SIZE;i++){
		for(int j=0;j<MAX_SIZE;j++){
            if(maze[i][j]==check_string){
                maze[i][j] = "#";
                if(i-1>=0 && maze[i-1][j]==maxFillValue){
					maze[i-1][j]="#";
					maxFillValueInt-=1;
					maxFillValue = to_string(maxFillValueInt);
					return;
                }
				if(i+1<MAX_SIZE && maze[i+1][j]==maxFillValue){
					maze[i+1][j]="#";
					maxFillValueInt-=1;
					maxFillValue = to_string(maxFillValueInt);
					return;
				}
				if(j-1>=0 && maze[i][j-1]==maxFillValue){
					maze[i][j-1]="#";
					maxFillValueInt-=1;
					maxFillValue = to_string(maxFillValueInt);
					return;
				}
				if(j+1<MAX_SIZE && maze[i][j+1]==maxFillValue){
					maze[i][j+1]="#";
					maxFillValueInt-=1;
					maxFillValue = to_string(maxFillValueInt);
					return;
				}
            }
		}
    }
}

int main(){
	std::string str_level_number,str_level_number1;
	inputMaze();
	printMaze();

	levelUpdate("S","2");
	printMaze();

	while(reachedT == 0){
        str_level_number = to_string(levelNumber);
        levelNumber+=1;
        str_level_number1 = to_string(levelNumber);
        levelNumber-=1;
		levelUpdate(str_level_number,str_level_number1);
		printMaze();
	}
    maxFillValue = findMaxFill();
    maxFillValueInt = stoi(maxFillValue);
	backTrack("T");
	printMaze();
	while(maxFillValueInt >= 2){
        backTrack("#");
        printMaze();
    }

    cout<<"\nbacktracking:"<<endl;
    for(int i=0;i<MAX_SIZE;i++){
		for(int j=0;j<MAX_SIZE;j++){
            if(maze[i][j] == "S")
                maze[i][j] = "#";
		}
    }
    printMaze();
	return 0;
}
