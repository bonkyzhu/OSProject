#include <iostream>
#include <vector>
#include <queue>

using namespace std;
class disk{
	public:
		int swap(int thread_id,int datasize,string message,string name){};
		int DelSwap(int thread_id){};
		friend class Memory;
};
class Data{
	public:
		Data(){
			datasize=0;
			message="NULL";
			name="NULL";
			sign=0;
			thread_id=NULL;
		}
	int datasize;//数据大小，多少字节
	string message;//数据信息
	string name;//文件名
	int sign;//标志位
	int thread_id;//所属线程id 
	void set(){
		datasize=0;
			message="NULL";
			name="NULL";
			sign=0;
			thread_id=NULL;
	}
};
class Memory{//内存
public:
	Data Mem [16];

	int free=16;//空闲块数 
	queue<int> q;//符合FIFO算法的调出队列 
    vector<int> Alloc(int Mb_num,int thread_id){//申请内存块，从空闲块中找或者对换
        //Mb_num 申请的内存块数    thread_id  线程id
        //return 内存块号的数组
      
        
          vector<int> iv(Mb_num);
          if(Mb_num<=free) {
          	for(int i=0;i<Mb_num;i++){
          		for(int j=0;j<16;j++){
          			if(Mem[j].sign==0){
          				iv[i]=j;
          				Mem[j].thread_id=thread_id;
          				Mem[j].sign=1;
          				q.push(j);
          				break;
					  }
				  }
			  }
			  free=free-Mb_num;
		  } else{//需要置换 
		  	int i=0;
		  	for(i=0;i<free;i++){
          		for(int j=0;j<16;j++){
          			if(Mem[j].sign==0){
          				iv[i]=j;
          				Mem[j].thread_id=thread_id;
          				Mem[j].sign=1;
          				q.push(j);
          				break;
					  }
				  }
			  }
			  for(int j=0;j<Mb_num-free;j++){
			  	int z=q.front();//要置换出去的块号 
			  	//disk::swap(thread_id,Mem[z].datasize,Mem[z].message,Mem[z].name);//换到置换区
				q.pop(); 
			  	Mem[z].set();
			  	Mem[z].thread_id=thread_id;
			  	Mem[z].sign=1;
			  	q.push(z);
			  	iv[i]=z;
			  	i++;
			  }
			free=0;
		  }
          
        return iv;        
   }
    int Write(int thread_id,int data_id,int datasize,string message,string name){//写内存块
        // thread_id 线程id（用于比对）   data_id内存块号  
        //return 0/1   失败（id不匹配）/成功     
        if(Mem[data_id].thread_id==thread_id&&datasize<=4) {//匹配线程id 数据大小不超过4字节 
        	Mem[data_id].datasize=datasize;
        	Mem[data_id].message=message;
        	Mem[data_id].name=name;
        	return 1;
		} else
		return 0;
    }
    int Delete(int thread_id){//释放内存
        //  (int thread_id)
        //thread_id  线程id   将所有与threadid一样的块删了回收，通知磁盘删了对换区
        //return 0/1  失败/成功   失
        int F=q.front();
        int G=free;
       for(int i=0;i<16-G;i++){//删除回收，修改free、队列q 
        	int a=q.front();
        	q.pop();
        	if(Mem[a].thread_id==thread_id){
        		Mem[a].set();
        		free++;
			}
			else q.push(a); 
		}
		//if(disk::DelSwap(thread_id))//调用磁盘管理的函数 兑换区删除成功，返回1 
			//return 1;
		//else
			return 0;
    }
    int InMem(string name){//判断文件是否在内存 
    	for(int i=0;i<16;i++){
    		if(Mem[i].name==name)
    			return 1;
		}
		return 0;
	}
	void show(){//显示内存数据 
		for(int i=0;i<16;i++){
			cout<<i<<" "<<Mem[i].sign<<" "<<Mem[i].thread_id<<" "<<Mem[i].name<<" "<<Mem[i].datasize<<" "<<Mem[i].message<<endl;
		}
	} 
	
}; 
int main(){//我把调用磁盘管理的两个函数注释了，不然不能执行 
		Memory a;//创建内存对象a 
		
		vector<int> iv(3);//创建数组用于存放Alloc函数返回值 即分配的内存块ID 
		iv=a.Alloc(3,2); //调用Alloc函数为线程2分配三个内存块  如果还剩的内存块不够分配，会实行全局置换FIFO 自动调出内存块到兑换区，为此线程分配足够的内存块 
		
		
		
		a.Write(2,iv[0],3,"afhahf","aaa");//调用Write函数将文件写入内存  参数依次是线程ID 对应的内存块ID  文件多少字节大小  数据信息  文件名 
		a.Write(2,iv[1],4,"hijacf","bbb");
		a.Write(2,iv[2],3,"kshafa","ccc");
		a.show();//显示内存数据  显示数据依次为内存块序号 是否占用标志位 所属线程Id 文件名 文件大小 数据信息 
		cout<<endl;
		
		vector<int> iv1(14);
		iv1=a.Alloc(10,3);//为线程3分配10块内存 
		a.Write(3,iv1[9],3,"dhdhdk","fff");//文件写入内存 
		a.Write(3,iv1[0],3,"dhdhdk","fff");
		a.Write(3,iv1[5],3,"dhdhdk","fff");
		a.show();
		cout<<endl;
		
		
		a.Delete(2);//删除线程2占用的内存块 
		a.show();
		cout<<endl;
		

		vector<int> iv2(3); 
		iv2=a.Alloc(7,4);//为线程4分配内存块 
		
		a.Write(4,iv2[0],3,"kshafa","ggg");
		a.Write(4,iv2[1],3,"kshafa","ggg");
		a.Write(4,iv2[3],4,"kshafa","ggg");
		a.show();
		
		cout<<a.InMem("sgf");//用文件命查看此文件是否调入内存 
		return 0;
}
