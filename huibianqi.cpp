//写代码时必须严格按照格式来写，不然会出错
//寄存器规定必须是三位




#include<iostream>
#include<stdio.h>
#include<memory.h>
#include<cstring>
#include<fstream>
#include<iomanip>
#include<cstdlib>
#include<string>
using namespace std;


//int转string 
 string toString(int r){
 	if(r==0)return "0";
	else if(r==1)return "1";
	else if(r==2)return "2";
	else if(r==3)return "3";
	else if(r==4)return "4";
	else if(r==5)return "5";
	else if(r==6)return "6";
	else if(r==7)return "7";
	else if(r==8)return "8";
	else if(r==9)return "9";
 }

  string totoString(int n){
 	string s;
 	int m=n;
 	while(m!=0){
 		s=toString(m%10)+s;
 		m=m/10;
		}
 	if(n<0)s="-"+s;
 	return s;
 }

//去掉string的空格 
void trim(string &s)
{
    int index = 0;
    if( !s.empty())
    {
        while( (index = s.find(" ",index)) != string::npos)
        {
            s.erase(index,1);
        }
    }
}
 


//改大小写 
string tolower(string s) {
	int len = s.size();
    for (int i=0; i<len; i++) {
        if ( s[i] >= 'A' && s[i] <= 'Z' ) {
            s[i] += ('a' - 'A' ) ;
        }
    }
    return s;
}


string getHead(string hb){
	int loc;
	loc=hb.find(" ");
	string k;
	k=hb.substr(0,loc+1);
	return tolower(k);
}




//k是head 
string FindOp(string k){
	if(k=="bltz"||k=="bgez") return "000001";
	else if(k=="j") return "000010";
	else if(k=="jal") return "000011";
	else if(k=="beq") return "000100";
	else if(k=="bne") return "000101";
	else if(k=="blez") return "000110";
	else if(k=="bgtz") return "000111";
	else if(k=="addi") return "001000";
	else if(k=="addiu") return "001001";
	else if(k=="slti") return "001010";
	else if(k=="sltiu") return "001011";
	else if(k=="andi") return "001100";
	else if(k=="ori") return "001101";
	else if(k=="xori") return "001110";
	else if(k=="lui") return "001111";
	else if(k=="mul") return "011100";
	else if(k=="lb") return "100000";
	else if(k=="lh") return "100001"; 
	else if(k=="lw") return "100011";
	else if(k=="lbu") return "100100";
	else if(k=="lhu") return "100101";
	else if(k=="sb") return "101000";
	else if(k=="sh") return "101001";
	else if(k=="sw") return "101011";
	else return "000000";
}


//k是head 
string FindFunct(string k){
	if(k=="sll")return "000000";
	else if(k=="srl"||k=="mul")return "000010";
	else if(k=="sra")return "000011";
	else if(k=="sllv")return "000100";
	else if(k=="srlv")return "000110";
	else if(k=="srav")return "000111";
	else if(k=="jr")return "001000";
	else if(k=="jalr")return "001001";
	else if(k=="mfhi")return "010000";
	else if(k=="mthi")return "010001";
	else if(k=="mflo")return "010010";
	else if(k=="mtlo")return "010011";
	else if(k=="mult")return "011000";
	else if(k=="multu")return "011001";
	else if(k=="div")return "011010";
	else if(k=="divu")return "011011";
	else if(k=="add")return "100000";
	else if(k=="addu")return "100001";
	else if(k=="sub")return "100010";
	else if(k=="subu")return "100011";
	else if(k=="and")return "100100";
	else if(k=="or")return "100101";
	else if(k=="xor")return "100110";
	else if(k=="nor")return "100111";
	else if(k=="slt")return "101010";
	else if(k=="sltu") return "101011";
	else return "";
}



string WhatKind(string k){
	if(k=="addi"||k=="addiu"||k=="slti"||k=="sltiu"||k=="andi"||k=="ori"||k=="xori")return "rt,rs,imm";
    else if(k=="lb"||k=="lh"||k=="lw"||k=="lbu"||k=="lhu"||k=="sb"||k=="sh"||k=="sw"||k=="lwcl"||k=="sh"||k=="sh") return"rt,imm(rs)";
	else if(k=="j"||k=="jal") return "label";
	else if(k=="bltz"||k=="bgez"||k=="blez"||k=="bgtz")return "rs,label";
	else if(k=="beq"||k=="bne")return "rs,rt,label";
	else if(k=="sll"||k=="srl"||k=="sra")return "rd,rt,shamt";
	else if(k=="sllv"||k=="srlv"||k=="srav")return "rd,rt,rs";
	else if(k=="jr"||k=="jalr"||k=="mthi"||k=="mtlo")return "rs";
    else if(k=="mflo"||k=="mfhi")return "rd";
	else if(k=="mult"||k=="multu"||k=="div"||k=="divu")return "rs,rt";
	else if(k=="add"||k=="addu"||k=="sub"||k=="subu"||k=="and"||k=="or"||k=="xor"||k=="nor"||k=="slt"||k=="sltu"||k=="mul")return "rd,rs,rt";
	else if(k=="mov")return "mov";
	else if(k=="nop")return "nop";
	else return "";
}





//得到寄存器编号 
//r是寄存器 $xx 或整数 
int translater(string r){
	if((r.substr(0,1)>="0"&&r.substr(0,1)<="9")||r.substr(0,1)=="-"){
		trim(r);
		int k=atoi(r.c_str());
		return k;
	} 
	if(r.substr(1,1)=="0") return 0;
	else if(r.substr(1,1)=="a"){
			if(r.substr(2,1)=="t")return 1;
			else if(r.substr(2,1)=="0")return 4;
			else if(r.substr(2,1)=="1")return 5;
			else if(r.substr(2,1)=="2")return 6;
			else if(r.substr(2,1)=="3")return 7;	
		}
		else if(r.substr(1,1)=="v"){
			if(r.substr(2,1)=="0")return 2;
			else if(r.substr(2,1)=="1")return 3;
					
		}
		else if(r.substr(1,1)=="t"){
			if(r.substr(2,1)=="0")return 8;
			else if(r.substr(2,1)=="1")return 9;
			else if(r.substr(2,1)=="2")return 10;
			else if(r.substr(2,1)=="3")return 11;
			else if(r.substr(2,1)=="4")return 12;
			else if(r.substr(2,1)=="5")return 13;
			else if(r.substr(2,1)=="6")return 14;
			else if(r.substr(2,1)=="7")return 15;
			else if(r.substr(2,1)=="8")return 24;
			else if(r.substr(2,1)=="9")return 25;
			
		}
		else if(r.substr(1,1)=="s"){
			if(r.substr(2,1)=="0")return 16;
			else if(r.substr(2,1)=="1")return 17;
			else if(r.substr(2,1)=="2")return 18;
			else if(r.substr(2,1)=="3")return 19;
			else if(r.substr(2,1)=="4")return 20;
			else if(r.substr(2,1)=="5")return 21;
			else if(r.substr(2,1)=="6")return 22;
			else if(r.substr(2,1)=="7")return 23;
			else if(r.substr(2,1)=="p")return 29;
				
		}
		else if(r.substr(1,1)=="k"){
			if(r.substr(2,1)=="0")return 26;
			else if(r.substr(2,1)=="1")return 27;
			
		}
		else if(r.substr(1,1)=="g"&&r.substr(2,1)=="p")return 28;
		
		else if(r.substr(1,1)=="f"&&r.substr(2,1)=="p")return 30;
		else if(r.substr(1,1)=="r"&&r.substr(2,1)=="a")return 31;
}



//转换为五位的二进制机器码，或者也有的是十六位的二进制机器码，自定义函数： 
string inttobinary(int t, int choose) {
	int i = 0;
	if(choose==1) {
		string q;
		for(i = 4; i >=0; i--) {
			q=toString(t%2)+q;
			t=t/2;
		}
		return q;
	} else if(choose==0){
		bool check = 0;
		if(t<0) {
			check = 1;
			t = -t;
		}
		string p;
		for(i = 15; i >= 0; i--) {
			p=toString(t%2)+p;
			t=t/2;
		}
		if(check) {
			for(i = 15; i >= 0; i--) {
				if(p.substr(i,1) =="0") p.replace(i,1,"1");
				
				else p.replace(i,1,"0");
			}
			int j = 15;
			while(p.substr(j,1) != "0") {
				p.replace(j,1,"0");
				j--;
			}
			while(j>=0&&p.substr(j,1)=="0") {
				p.replace(j,1,"1");
				j--;
			}
		}
		return p;
	}else if(choose==2){
		bool check = 0;
		if(t<0) {
			check = 1;
			t = -t;
		}
		string p;
		for(i = 31; i >= 0; i--) {
			p=toString(t%2)+p;
			t=t/2;
		}
		if(check) {
			for(i = 31; i >= 0; i--) {
				if(p.substr(i,1) =="0") p.replace(i,1,"1");
				
				else p.replace(i,1,"0");
			}
			int j = 31;
			while(p.substr(j,1) != "0") {
				p.replace(j,1,"0");
				j--;
			}
			while(j>=0&&p.substr(j,1)=="0") {
				p.replace(j,1,"1");
				j--;
			}
		}
		return p; 
	}
	//return str;
}



string toHex(string r){
	if(r=="0000")return "0";
	else if(r=="0001")return "1";
	else if(r=="0010")return "2";
	else if(r=="0011")return "3";
	else if(r=="0100")return "4";
	else if(r=="0101")return "5";
	else if(r=="0110")return "6";
	else if(r=="0111")return "7";
	else if(r=="1000")return "8";
	else if(r=="1001")return "9";
	else if(r=="1010")return "A";
	else if(r=="1011")return "B";
	else if(r=="1100")return "C";
	else if(r=="1101")return "D";
	else if(r=="1110")return "E";
	else if(r=="1111")return "F";
}

/*string toBinary(string r){
	if(r=="0")return "0000";
	else if(r=="1")return "0001";
	else if(r=="2")return "0010";
	else if(r=="3")return "0011";
	else if(r=="4")return "0100";
	else if(r=="5")return "0101";
	else if(r=="6")return "0110";
	else if(r=="7")return "0111";
	else if(r=="8")return "1000";
	else if(r=="9")return "1001";
	else if(r=="A")return "1010";
	else if(r=="B")return "1011";
	else if(r=="C")return "1100";
	else if(r=="D")return "1101";
	else if(r=="E")return "1110";
	else if(r=="F")return "1111";
}

struct key{
	string s;
	int ad;
};
*/

int main() {
	string binary[100];
	string bi;
	ifstream fin;
	//ifstream fon;
	fin.open("D:/玄学攻略/mips.txt", ios_base::in);
	//fon.open("D:/玄学攻略/mips.txt", ios_base::in);
	if(!fin) {
		cerr << "Open Error!" << endl;
		exit(1);
	}
	int i,j;
	char buffer[256];
	char* q = NULL;
	char* head;
	string head_;
	string buf;
	string op;
	string funct;
	string shamt;
	j = 0;
	/*key KEY[256];
	while(!fon.eof()){
		int r=100;
		int a=0;
		int a1=1;
		int b;
		int dizhi1=0x10000000;
		int dizhi2=0x00400000;
		fon.getline(buffer, 100);//读取100个字符写入buffer中 
		buf=buffer;
		int e=buf.find(":");
		head = strtok(buffer, ":");//由:把buffer分开 
		head_ = head;
		if(buffer[0] != 0){
			if(buf==".data")r=0;
			else if(buf==".text")r=1;
			if(r==0){
				if(a==0)a1=0;
				KEY[a].ad=dizhi1+a1*4;
				KEY[a].s=buf.substr(0,e);
				
				a++;
			}
			else if(r==1){
				if(a==0)a1=0;
				KEY[a].ad=dizhi2+a1*4;
				KEY[a].s=buf.substr(0,e);
				cout<<KEY[a].ad<<endl;
				a++;
			}
		}
	}
	*/
	while(!fin.eof()) {
		fin.getline(buffer, 100);//读取100个字符写入buffer中 
		buf=buffer;
		
		if(buffer[0] != 0){
			q = NULL;
			head = strtok(buffer, "，$（）,() ");//由 ，$（）,() 把buffer分开 
			head_ = head;
			int h=head_.find(":");
			string fuhao=head_.substr(0,h);
			head_=head_.substr(h+1,100);//滤掉:前的命令 
			
			//if()...
			//解析 
		    op= FindOp(head_);
		    funct=FindFunct(head_);
		    
		    buf=buf.substr(buf.find(":")+1,100);
		    //cout<<op<<" "<<buf<<endl;
			//rd,rs,rt
			/*string std[3];
		    buf=buf.substr(loc+1,256);
		    buffer=buf;*/
		    if(WhatKind(head_)=="rt,rs,imm"){//addi...
		        string rs,rt,imm;
		        int loc=buf.find(" ");
		    	rt=inttobinary(translater(buf.substr(loc+1,3)),1);
		    	cout<<translater("$sp")<<endl;
		    	rs=inttobinary(translater(buf.substr(loc+5,3)),1);
		    	imm=inttobinary(translater(buf.substr(loc+9,3)),0);
		    	bi=op+rs+rt+imm;
			}
			
		    else if(WhatKind(head_)=="rt,imm(rs)"){//lw...
		        string rt,imm,rs;
		        int loc=buf.find(" ");
		        int l1=buf.find("(");
		        int l2=buf.find(")");
		        rt=inttobinary(translater(buf.substr(loc+1,3)),1);
		        imm=inttobinary(translater(buf.substr(loc+5,l1-loc-5)),0);
		    	rs=inttobinary(translater(buf.substr(l1+1,l2-l1)),1);
		    	bi=op+rs+rt+imm;
			}
			
			else if(WhatKind(head_)=="label"){//j...
		        string label;
		        int loc=buf.find(" ");
		        label=inttobinary(translater(buf.substr(loc+1,100)),2).substr(4,26);
		    	bi=op+label;
			}
			
			else if(WhatKind(head_)=="rs,label"){//bltz...
		        string rs,label;
		        int loc=buf.find(" ");
		        rs=inttobinary(translater(buf.substr(loc+1,3)),1);
		        label=inttobinary(translater(buf.substr(loc+5,100)),2);
		    	/*string s=buf.substr(loc+5,100);
		    	for(int i=0;i<256;i++){
		        	if(KEY[i].s==s) label=inttobinary(translater(totoString(KEY[i].ad)),2);
				}*/
		    	bi=op+rs+"00000"+label;
			}
			
			else if(WhatKind(head_)=="rs,rt,label"){//beq...
		        string rs,rt,label;
		        int loc=buf.find(" ");
		    	rs=inttobinary(translater(buf.substr(loc+1,3)),1);
		    	rt=inttobinary(translater(buf.substr(loc+5,3)),1);
		    	label=inttobinary(translater(buf.substr(loc+9,100)),2);
		    	/*string s=buf.substr(loc+9,100);
		        for(int i=0;i<256;i++){
		        	if(KEY[i].s==s) label=inttobinary(translater(totoString(KEY[i].ad)),2);
				}*/
		    	bi=op+rs+rt+label;
			}
			
			else if(WhatKind(head_)=="rd,rt,shamt"){//sll...
		        string rd,rt,shamt;
		        int loc=buf.find(" ");
		    	rd=inttobinary(translater(buf.substr(loc+1,3)),1);
		    	rt=inttobinary(translater(buf.substr(loc+5,3)),1);
		    	shamt=inttobinary(translater(buf.substr(loc+9,3)),1);;
		    	bi=op+"00000"+rt+rd+shamt+funct;
			}
			
			else if(WhatKind(head_)=="rd,rt,rs"){//sllv...
		    	string rs,rt,rd;
		    	int loc=buf.find(" ");
				rd=inttobinary(translater(buf.substr(loc+1,3)),1);
		        rt=inttobinary(translater(buf.substr(loc+5,3)),1);
		        rs=inttobinary(translater(buf.substr(loc+9,3)),1);
		        shamt="000000";
		        bi=op+rs+rt+rd+shamt+funct;
		    }
		    
		    else if(WhatKind(head_)=="rs"){//jr...
		    	string rs;
		    	int loc=buf.find(" ");
				rs=inttobinary(translater(buf.substr(loc+1,3)),1);
		        bi=op+rs+"000000000000000"+funct;
		    }
		    
		    else if(WhatKind(head_)=="rd"){//mflo...
		    	string rd;
		    	int loc=buf.find(" ");
				rd=inttobinary(translater(buf.substr(loc+1,3)),1);
		        bi=op+"0000000000"+rd+"00000"+funct;
		    }
		    
		    else if(WhatKind(head_)=="rs,rt"){//mult...
		    	string rs,rt;
		    	int loc=buf.find(" ");
				rs=inttobinary(translater(buf.substr(loc+1,3)),1);
				rt=inttobinary(translater(buf.substr(loc+5,3)),1);
		        bi=op+rs+rt+"0000000000"+funct;
		    }
			
		    else if(WhatKind(head_)=="rd,rs,rt"){//add...
		    	string rs,rt,rd;
		    	int loc=buf.find(" ");
				rd=inttobinary(translater(buf.substr(loc+1,3)),1);
				//string s=buf.substr(loc+9,3);
		        rs=inttobinary(translater(buf.substr(loc+5,3)),1);
		        rt=inttobinary(translater(buf.substr(loc+9,3)),1);
		        shamt="00000";
		        bi=op+rs+rt+rd+shamt+funct;
		    }
		    
		    else if(WhatKind(head_)=="mov"){//mov
		    	string rd,rs;
		    	int loc=buf.find(" ");
				rd=inttobinary(translater(buf.substr(loc+1,3)),1);
		        rs=inttobinary(translater(buf.substr(loc+5,3)),1);
		        bi=op+rs+"00000"+rd+"00000"+funct;
		    }
		    
		    else if(WhatKind(head_)=="nop"){//nop...
		    	bi=op+"00000000000000000000"+funct;
			}
			else bi="";
			//cout<<bi<<endl; 
		    for(int k=0;k<32;k+=4){
		    	binary[j]=binary[j]+toHex(bi.substr(k,4));
		    	//cout<<binary[j]<<endl;
			}
		}
		j++;
	}
	int count = j;
	/*write to txt*/
	ofstream out;
	out.open("D:/玄学攻略/data.txt", ios::out|ios::trunc);
	if(out.is_open()) {
		for(i = 0; i < count; i++) {
			out << binary[i];
			out<<"\n";
	    }
			if(i != count - 1) {
				out << "\n";
			}
		}
		cout << "compile success!" <<endl;
		out.close();
	}

	
