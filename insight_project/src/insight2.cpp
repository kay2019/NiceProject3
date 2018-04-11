/*

Project: Insight fellow project
Author: Dr. Kiyoumars Sohrabi Anaraki 
comment:If you want to change directories, you need to modify the following lines: Line 112, Line 189, Line 371, Line 420
*/

#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <deque>
#include <algorithm>
#include <climits>
#include <limits>
#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <stdbool.h>
using namespace std; 
#define maxElements 4 // Fixed for the data of this project


// class for reading the CSV file
class CSVRow{
    public:
        std::string const& operator[](std::size_t index) const{
            return m_data[index];
        }
        std::size_t size() const{
            return m_data.size();
        }
        void readNextRow(std::istream& str){
            std::string line;
            std::getline(str,line);

            std::stringstream   lineStream(line);
            std::string cell;

            m_data.clear();
            while(std::getline(lineStream, cell, ',')){
                m_data.push_back(cell);
            }
            // This checks for a trailing comma with no data after it.
            if (!lineStream && cell.empty()){
                // If there was a trailing comma then add an empty element.
                m_data.push_back("");
            }
        }
    private:
        std::vector<std::string>    m_data;
};


std::istream& operator>>(std::istream& str, CSVRow& data)
{
    data.readNextRow(str);
    return str;
}   

// Definition of the unrolled-linked list
struct Node
{
    int numElements;
    string temp[maxElements];
    struct Node *next;
};


// For going up and down in the CSV file
std::ifstream& GotoLine(std::ifstream& file, unsigned int num){
    file.seekg(std::ios::beg);
    for(int i=0; i < num - 1; ++i){
        file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    return file;
}

// Transforms the format of 00:00:02 into a number in seconds
int GimeTime(string coltemp){
     int h, m, s= 0;
     int sec;
     if (sscanf(coltemp.c_str(), "%d:%d:%d", &h, &m, &s) >= 2){
                sec = h *3600 + m*60 + s;  
    }
    return sec;
}


// A function that transforms integers to strings
string IntToString(int n){
    string str;          
    ostringstream temp;  
    temp<<n;
    str=temp.str(); 
    return str;
}

// A function that transforms strings to integers
int StringToInt(string s){

    stringstream geek(s);
    int x = 0;
    geek >> x;
    return x;
}

// Counting number of lines in the CSV file 
int CSVLineCount(){
    std::ifstream myfile("../input/log.csv");
    // new lines will be skipped unless we stop it from happening:    
    myfile.unsetf(std::ios_base::skipws);
    // count the newlines with an algorithm specialized for counting:
    int line_count = std::count(std::istream_iterator<char>(myfile), std::istream_iterator<char>(),'\n');
    return line_count;
}

// A function to check if the vector contains a number 
bool InArray(int val, vector<int> done, int size){
    int i;
    for (i=0; i < size; i++) {
        if (done[i] == val)
            return true;
    }
    return false;
}





int main()
{
    int inactivity;

    // reading the number of lines
    int line_count;
    line_count=CSVLineCount()-1;


    // reading the inactivity period file
    ifstream textfile;
    textfile.clear();
    textfile.open("../input/inactivity_period.txt");
    string sLine;
    getline(textfile, sLine);
    inactivity=StringToInt(sLine);
    //textfile.close();
   

    // unrolled-linked list
    struct Node* head[line_count][line_count];
    for (int i = 0; i<line_count; i++){
        for(int j=0;j<line_count;j++){
            head[i][j] = NULL;
        }
    }
    
    for (int i = 0; i<line_count; i++){
        for(int j=0;j<line_count;j++){ 
            head[i][j] = (struct Node*)malloc(sizeof(struct Node));
        }
    }



    CSVRow col;


    // list of variables used in main part of the program below
    int sec1,sec2,sec3,i1,j,s,article,maxsec;
    int linekeeper=1;
    string ip1,ip2,ip3,date1,date2,date3,time1,time2,time3;
    i1=2;
    j=0;
    s=-1;
    vector <int> done;
    vector <int> papers;
    vector <int> length;
    vector <string> dead;
    bool flag,flag1,flag2,flag3;



    // reading the CSV file
    ifstream file;
    file.open("../input/log.csv");
    file.ignore ( std::numeric_limits<std::streamsize>::max(), '\n' ); //skip the first line



    // the main part of the program starts here
    i1=2;

    // goes through all the lines of the CSV file
    while (file>>col){// start 1
        flag3=false;
        flag1=true;
        flag=true;
        
        ip1=col[0];


        // skip current sessions
        if ( std::find(dead.begin(), dead.end(), ip1) != dead.end() ){
            flag1=true;
        }
        else{
            for (int k=0;k<line_count;k++){
                if (head[k][0]->temp[0] == ip1){
                    flag1= false;
                }
            }
        }

        if (flag1){// start flag1

            // end of the file, session ends
            if (i1>line_count){ 
                s=s+1;
                head[j][s]->numElements=4;
                head[j][s]->temp[0]=ip1;
                head[j][s]->temp[1]=col[1];
                head[j][s]->temp[2]=col[2];
                head[j][s]->temp[3]="1";//article=1;
                head[j][s]->next=NULL;
                maxsec=GimeTime(col[2]);
                break;}        
        

            // read information for each line
            time1=col[2];
            sec1=GimeTime(time1);
            date1=col[1];


            // create all nodes for a session
            while (file>>col){// start 2
                article=1;
                flag2=false;

                // read information of the next line 
                ip2=col[0];
                time2=col[2];
                sec2=GimeTime(time2);
                date2=col[1];                                                        
                




                // find the number of articles in this loop 
                if (ip1==ip2){// start 3
                                        
                    // if condition matches add +1 article 
                    if (time2==time1) {
                        article=article+1;
                    }

                    // this is a child node, save its parent
                    if (time2!=time1 && flag){
                        article=1;
                        sec1=sec2;
                        s=s+1;
                        head[j][s]->numElements=4;
                        head[j][s]->temp[0]=ip1;
                        head[j][s]->temp[1]=date1;
                        head[j][s]->temp[2]=time1;
                        head[j][s]->temp[3]=IntToString(article);
                        head[j][s]->next=head[j][s+1];
                    }

                    // it's a child node for an old root
                    if (time2!=time1 && flag){
                        article=1;
                        sec1=sec2;
                    }


               
                    while (file>>col) {
                        ip3=col[0];
                        time3=col[2];
                        date3=col[1];
                        sec3=GimeTime(time3);

                        // it's a child node, save the parent node
                        if(ip3==ip2 && time3!=time2){
                            s=s+1;
                            head[j][s]->numElements=4;
                            head[j][s]->temp[0]=ip2;
                            head[j][s]->temp[1]=date2;
                            head[j][s]->temp[2]=time2;
                            head[j][s]->temp[3]=IntToString(article);
                            head[j][s]->next=head[j][s+1];
                            ip1=ip3;
                            time1=time3;
                            date1=date3;
                            sec1=sec3;
                            flag3=true;
                            break;
                        }

                        if (ip3!=ip2){ 
                            flag2=true;
                            break;}
                        
                        // add to the article number of the root
                        article=article+1;
                        ip2=ip3;
                        time2=time3;
                        date2=date3;                                   
                        }
                }// end 3

                // this branch has terminated, save the root
                else if(flag){
                    article=1;
                    s=s+1;
                    head[j][s]->numElements=4;
                    head[j][s]->temp[0]=ip1;
                    head[j][s]->temp[1]=date1;
                    head[j][s]->temp[2]=time1;
                    head[j][s]->temp[3]=IntToString(article);
                    head[j][s]->next=head[j][s+1];
                    flag=false;
                }
                // this branch has terminated, save the parent
                else if(flag3){
                    s=s+1;
                    head[j][s]->numElements=4;
                    head[j][s]->temp[0]=ip1;
                    head[j][s]->temp[1]=date1;
                    head[j][s]->temp[2]=time1;
                    head[j][s]->temp[3]=IntToString(article);
                    head[j][s]->next=head[j][s+1];
                    flag3=false;
                }
        
                // this branch has terminated, save the last child
                if(flag2){
                    s=s+1;
                    head[j][s]->numElements=4;
                    head[j][s]->temp[0]=ip2;
                    head[j][s]->temp[1]=date2;
                    head[j][s]->temp[2]=time2;
                    head[j][s]->temp[3]=IntToString(article);
                    head[j][s]->next=head[j][s+1];
                    flag2=false;
                    ip1=ip2;
                    date1=date2;
                    time1=time2;
                    sec1=GimeTime(time1);
                }

                // this branch has expired
                if ((sec2-sec1) > inactivity){
                    dead.push_back(ip1);
                    break;
                }

                flag=false;
            }// end 2



            file.close();
            file.clear();
            file.open("../input/log.csv");   

            head[j][s]->next=NULL;
            j=j+1; 
            s=-1;



        }// end flag1

        i1=i1+1;
        
        GotoLine(file, i1);
           
    }//end 1

    file.close();
    file.clear();



    // duration of each session
    int count;
    for (int i=0;i<line_count;i++){
        count=0;
        for(int j=0;j<line_count;j++){
            if (head[i][j]->temp[3]!="") ++count;
        }
        length.push_back(count);    
    }

    // Article number of each unrolled-linked list
    for (int i=0;i<line_count;i++){
        count=0;
        for(int j=0;j<line_count;j++){
            if (head[i][j]->temp[3]!="") count=count+ StringToInt(head[i][j]->temp[3]);
        }
        papers.push_back(count);    
    }



    int p;
    p=0;
    int t=inactivity;


    // open the output file and write info
    ofstream output;
    output.open ("../output/sessionization.txt");
    

    // t below is the time, a criteria for printing outputs
    while(t<maxsec+1){

        // end of the time, print final sessions
        if (t==maxsec){

            for(int i=0;(i<line_count) ; i++){
                
                if (!InArray(i, done, p)){    
                
                    if(head[i][0]->temp[0] =="") break;
                    
                    // write to file
                    output<<head[i][0]->temp[0]<<","<<head[i][0]->temp[1]<<" "<<head[i][0]->temp[2]<<
                    ","<<head[i][length[i]-1]->temp[1]<<" "<<head[i][length[i]-1]->temp[2]<<","<<
                    GimeTime(head[i][length[i]-1]->temp[2])-GimeTime(head[i][0]->temp[2])+1<<","<<papers[i]<<endl;
                    
                    done.push_back(i);
                    p = done.size();
                }
            }
            break;
        }
        
        // printing sessions that satisfy inactivity period 
        for(int i=0;(i<line_count) ; i++){
                
            if (!InArray(i, done, p)){    
                
                if(head[i][0]->temp[0] =="") break;

                if( length[i]+GimeTime(head[i][0]->temp[2])<=t){
                    
                    // write to file
                    output<<head[i][0]->temp[0]<<","<<head[i][0]->temp[1]<<" "<<head[i][0]->temp[2]<<
                    ","<<head[i][length[i]-1]->temp[1]<<" "<<head[i][length[i]-1]->temp[2]<<","<<
                    GimeTime(head[i][length[i]-1]->temp[2])-GimeTime(head[i][0]->temp[2])+1<<","<<papers[i]<<endl;

                    done.push_back(i);
                    p = done.size();

                }

            }
        }

        t=t+1;   
    }




    output.close();




}//end main



