#include <iostream>
#include <vector>
#include <queue>

using namespace std;

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
class Memory{
public:
	Data Mem [16];

	int free=16;//空闲块数 
	queue<int> q;//符合FIFO算法的调出队列 
    vector<int> Alloc(int Mb_num,int thread_id){//申请内存块 返回分配的内存块数组 
        //Mb_num 申请的内存块数    thread_id  线程id
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
			  	disk::swap(thread_id,Mem[z].datasize,Mem[z].message,Mem[z].name);//换到置换区
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
    int Write(int thread_id,int data_id,int datasize,string message,string name){//写内存块 成功返回1 
        // thread_id 线程id  data_id 内存块号      
        if(Mem[data_id].thread_id==thread_id&&datasize<=4) {//匹配线程id 数据大小不超过4字节 
        	Mem[data_id].datasize=datasize;
        	Mem[data_id].message=message;
        	Mem[data_id].name=name;
        	return 1;
		} else
		return 0;
    }
    int Delete(int thread_id){//释放内存
        //thread_id  线程id 将此线程占用的内存块回收，并删除对换区里有关的数据 
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
		if(disk::DelSwap(thread_id))//调用磁盘管理的函数 兑换区删除成功，返回1 
			return 1;
		else
			return 0;
    }
    int InMem(string name){//判断文件是否在内存  成功返回1 
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
