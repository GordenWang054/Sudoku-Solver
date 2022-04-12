#include <iostream>
#include <string>
using namespace std;
bool check(int num,int arr[9][9],int r,int c){
    for(int i=0;i<9;i++){
        if(num==arr[r][i])
            return false;
        if(num==arr[i][c])
            return false;
    }
    int posr = (r/3)*3;
    int posc = (c/3)*3;
    for(int i=0;i<9;i++)
        if(arr[posr+(i/3)][posc+(i%3)]==num)
        return false;
    return true;
}
bool check(int num,int** arr,int r,int c){
    for(int i=0;i<9;i++){
        if(num==arr[r][i])
            return false;
        if(num==arr[i][c])
            return false;
    }
    int posr = (r/3)*3;
    int posc = (c/3)*3;
    for(int i=0;i<9;i++)
        if(arr[posr+(i/3)][posc+(i%3)]==num)
        return false;
    return true;
}

int statistic1(int arr[9][9]){//九宫格最大数搜查法(比较失败)
	int maxBlock=0;
	int maxcount=0;
	int count=0;
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			if(arr[(i%3)*3+(j/3)][(i/3)*3+(j%3)]!=0){
				count++;
			}
		}
		if(maxcount<count){
			maxcount=count;
			maxBlock=i;
		}
		count=0;
	}
	return 9*maxBlock;
}
int statistic2(int arr[9][9]){//行最大数搜查法(比较失败)
	int maxRows;
	int count=0;
	int maxcount=0;
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			if(arr[i][j]!=0){
				count++;
			}
		}
		if(maxcount<count){
			maxcount=count;
			maxRows=i;
		}
		count=0;
	}
	return 9*maxRows;
}
int statistic3(int arr[9][9]){//逐格最小可能性搜查法(一般成功)/////////////////////////
    int minPossibility;
    int r = 0;
    int c = 0;
    int count=0;
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            count=0;
            for(int k=1;k<=9;k++){
                if(check(k, arr, i, j)){
                    count++;
                }
            }
            if(minPossibility>count){
                minPossibility=count;
                r = i;
                c = j;
            }
        }
    }
    return r*9+c;
}
int statistic4(int arr[9][9]){//逐行最小可能性搜查法(比较失败)
    int minPossibility;
    int arrtmp[9][9];
    int r = 0;
    int c = 0;
    int count=0;
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            count=0;
            for(int k=1;k<=9;k++){
                if(check(k, arr, i, j)){
                    count++;
                }
            }
            arrtmp[i][j]=count;
        }
    }
    int minIndex=81;
    for(int i=0;i<9;i++){
        int count=0;
        for(int j=0;j<9;j++){
            count+=arrtmp[i][j];
        }
        if(count<minIndex){
            minIndex=i;
        }
    }
    int minNum=9;
    for(int i=0;i<9;i++){
        if(minNum>arrtmp[minIndex][i]){
            minNum=arrtmp[minIndex][i];
        }
    }
    return minIndex*9+minNum;
}
int statistic5(int arr[9][9]){//逐九宫格最小可能性(巨无比失败)
    int minBlock=0;
    int mincount=0;
    int count=0;
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            for(int k=0;k<9;k++){
                if(check(k,arr,(i%3)*3+(j/3),(i/3)*3+(j%3))){
                    count++;
                }
            }
        }
        if(mincount>count){
            mincount=count;
            minBlock=i;
        }
        count=0;
    }
    return 9*minBlock;
}
int statistic6(int arr[9][9]){//九宫格最小数搜查法(比较失败)
    int minBlock=0;
    int mincount=9;
    int count=0;
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(arr[(i%3)*3+(j/3)][(i/3)*3+(j%3)]!=0){
                count++;
            }
        }
        if(mincount>count){
            mincount=count;
            minBlock=i;
        }
        count=0;
    }
    return 9*minBlock;
}



bool solve1(int arr[9][9],int count,int initConditions){//逐九宫格填写/////////////////////
    if(count==81)
        return true;
    if(arr[((count+initConditions)/3)%9][(((count+initConditions)%81)/27)*3+(count+initConditions)%3]==0)
        for(int i=1;i<=9;i++){
            if(check(i,arr,((count+initConditions)/3)%9,(((count+initConditions)%81)/27)*3+(count+initConditions)%3)){
                arr[((count+initConditions)/3)%9][(((count+initConditions)%81)/27)*3+(count+initConditions)%3] = i;
                if(solve1(arr,count+1,initConditions))
                    return true;   
            }
        }
    else
        return solve1(arr,count+1,initConditions);
    arr[((count+initConditions)/3)%9][(((count+initConditions)%81)/27)*3+(count+initConditions)%3] = 0;
    return false;
}
bool solve2(int arr[9][9],int count,int initConditions){//逐行填写
    if(count==81)
        return true;
    if(arr[((count+initConditions)%81)/9][count%9]==0)
        for(int i=1;i<=9;i++){
            if(check(i,arr,((count+initConditions)%81)/9,count%9)){
                arr[((count+initConditions)%81)/9][count%9] = i;
                if(solve2(arr,count+1,initConditions))
                    return true;   
            }
        }
    else
        return solve2(arr,count+1,initConditions);
    arr[((count+initConditions)%81)/9][count%9] = 0;
    return false;
}
void initSudoku(string s,int arrTest[9][9]){
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
            if(s[i*9+j]!='.')
                arrTest[i][j] = s[i*9+j]-48;
            else
                arrTest[i][j] = 0;
}
void print1(int arrTest[9][9]){
    for(int i = 0;i<9;i++){
        for(int j = 0;j<9;j++){
            cout<<arrTest[i][j]<<" ";
            if(j==2||j==5)
            	cout<<" ";
            if((i==2&&j==8)||(i==5&&j==8))
            	cout<<endl;
		}
        cout<<endl;
    }
    cout<<endl;
}
void print2(int arrTest[9][9]){
    for(int i = 0;i<9;i++){
        for(int j = 0;j<9;j++){
            cout<<arrTest[i][j];
        }
    }
}
void solveSudoku1(string s){
    int arrTest[9][9];
    string s8 = "...21......73......58......43.......2.......8.......76......25......73......98...";
    string s7 = "........1.......23..4..5......1.........3.6....7...58.....67....1...4...52.......";
    int count=0;
    int select=0;
    initSudoku(s, arrTest);
    select=3;
    
    if(s==s7||s==s8){
        cout<<"Origin:"<<endl;
        print1(arrTest);
        //cout<<endl<<statistic2(arrTest)<<endl;
        cout<<endl<<"Solved:"<<endl;
        solve2(arrTest, count, 27);//statistic1(arrTest)
        print1(arrTest);
        return ;
    }
    
    switch(select){
    	case 1:{//行最大数填法
    		cout<<"Origin:"<<endl;
    		print1(arrTest);
    		//cout<<endl<<statistic1(arrTest)<<endl;
			cout<<endl<<"Solved:"<<endl;
    		solve1(arrTest, count, 0);//statistic2(arrTest)
    		print1(arrTest);
    		break;
		}
		case 2:{//九宫格最大数填法
			cout<<"Origin:"<<endl;
    		print1(arrTest);
    		//cout<<endl<<statistic2(arrTest)<<endl;
			cout<<endl<<"Solved:"<<endl;
    		solve2(arrTest, count, 27);//statistic1(arrTest)
    		print1(arrTest);
			break;
		}
        case 3:{//最小可能性填法
            cout<<"Origin:"<<endl;
            print1(arrTest);
            cout<<endl<<"Solved:"<<endl;
            solve1(arrTest, count, statistic3(arrTest));//statistic3(arrTest)
            print1(arrTest);
            break;
        }
        case 4:{//
            cout<<"Origin:"<<endl;
            print1(arrTest);
            cout<<endl<<"Solved:"<<endl;
            //cout<<statistic4(arrTest)<<endl;
            solve1(arrTest, count, statistic4(arrTest));//statistic4(arrTest)
            print1(arrTest);
            break;
        }
        case 5:{
            cout<<"Origin:"<<endl;
            print1(arrTest);
            cout<<endl<<"Solved:"<<endl;
            //cout<<statistic4(arrTest)<<endl;
            solve2(arrTest, count, statistic5(arrTest));//statistic1(arrTest)
            print1(arrTest);
            break;
        }
        case 6:{//
            cout<<"Origin:"<<endl;
            print1(arrTest);
            cout<<endl<<"Solved:"<<endl;
            //cout<<statistic6(arrTest)<<endl;
            solve2(arrTest, count, statistic6(arrTest));//statistic6(arrTest)
            print1(arrTest);
            break;
        }
	}
    
}
void solveSudoku2(string s){
    int arrTest[9][9];
    string s8 = "...21......73......58......43.......2.......8.......76......25......73......98...";
    string s7 = "........1.......23..4..5......1.........3.6....7...58.....67....1...4...52.......";
    int count=0;
    int select=0;
    initSudoku(s, arrTest);
    select=3;
    
    if(s==s7||s==s8){
        cout<<"Origin:"<<endl;
        print2(arrTest);
        //cout<<endl<<statistic2(arrTest)<<endl;
        cout<<endl<<"Solved:"<<endl;
        solve2(arrTest, count, 0);//statistic1(arrTest)
        print2(arrTest);
        return ;
    }
    
    switch(select){
        case 1:{//行最大数填法
            cout<<"Origin:"<<endl;
            print2(arrTest);
            //cout<<endl<<statistic1(arrTest)<<endl;
            cout<<endl<<"Solved:"<<endl;
            solve1(arrTest, count, 27);//statistic2(arrTest)
            print2(arrTest);
            break;
        }
        case 2:{//九宫格最大数填法
            cout<<"Origin:"<<endl;
            print2(arrTest);
            //cout<<endl<<statistic2(arrTest)<<endl;
            cout<<endl<<"Solved:"<<endl;
            solve2(arrTest, count, 27);//statistic1(arrTest)
            print2(arrTest);
            break;
        }
        case 3:{//最小可能性填法
            cout<<"Origin:"<<endl;
            print2(arrTest);
            cout<<endl<<"Solved:"<<endl;
            solve1(arrTest, count, statistic3(arrTest));//statistic1(arrTest)
            print2(arrTest);
            break;
        }
        case 4:{//
            cout<<"Origin:"<<endl;
            print2(arrTest);
            cout<<endl<<"Solved:"<<endl;
            //cout<<statistic4(arrTest)<<endl;
            solve1(arrTest, count, statistic4(arrTest));//statistic1(arrTest)
            print2(arrTest);
            break;
        }
        case 5:{
            cout<<"Origin:"<<endl;
            print2(arrTest);
            cout<<endl<<"Solved:"<<endl;
            //cout<<statistic4(arrTest)<<endl;
            solve2(arrTest, count, statistic5(arrTest));//statistic1(arrTest)
            print2(arrTest);
            break;
        }
        case 6:{//
            cout<<"Origin:"<<endl;
            print2(arrTest);
            cout<<endl<<"Solved:"<<endl;
            //cout<<statistic6(arrTest)<<endl;
            solve2(arrTest, count, statistic6(arrTest));//statistic6(arrTest)
            print2(arrTest);
            break;
        }
    }
    
}

void solveSudoku(string s){
    int choice = 0;
    cout<<"Please choose your output mode:"<<endl;
    cin>>choice;
    if(choice==1)
        solveSudoku2(s);
    else
        solveSudoku1(s);   
}

int main(){
    string s1 = "..8...2...3.8.2.6.7...9...5.5.....1...4...6...2.....7.4...8...6.7.1.3.9...1...8..";
    string s2 = ".....3.4..594......7...5..1137.....56...8....2..5..1....3.........92..3.......8.2";
    string s3 = "....9.1..81.....52...2...3..8..3.52.5..6.......1.2.6......89..4..34......4..1....";
    string s4 = "..5..3...1...5.82........9.4.......3.2...648.....8...92...3.15.........4.6.7.....";
    string s5 = "8..........36......7..9.2...5...7.......457.....1...3...1....68..85...1..9....4..";
    string s6 = "..5.......62....3.37..2.......2......18.9.5.44.6....8..3.6...9........2...75.936.";
    string s7 = "........1.......23..4..5......1.........3.6....7...58.....67....1...4...52.......";
    string s8 = "...21......73......58......43.......2.......8.......76......25......73......98...";
    string s9 = ".....2.5..78...3.......4...5..............1......3.7.82......4......5.9..1..7....";
    string s10 = ".3...7..46.2.41....5..3.967.4...3..6.87...35.9..7...2.718.2..4....16.8.94..5...3.";
    string s11 = "..8...2...3.8.2.6.7...9...5.5.....1...4...6...2.....7.4...8...6.7.1.3.9...1...8..";
    string s12 = "..89...7..53...............76.1...9.2............8........2.8.54....7.........3..";
    //string s10 = "22...2.5..78...3.......4...5..............1......3.7.82......4......5.9..1..7....";

    
    //solveSudoku(s2);
    //cout<<endl;
    //solveSudoku(s1);
    //cout<<endl;
    //solveSudoku(s3);
    //cout<<endl;
    solveSudoku(s9);
    return 0;
}
//目前为止，case3是比较好的，在人为规定case2的参数为27时是最快的，不知道是什么原理
