#include "OP_miniPY.hpp"
//#include "mainhead.hpp"

vector<VarNode> VARS;
vector<VarNode> ITERATIONS;
VarNode add(VarNode a,VarNode b)
{
	VarNode temp={0};
	double x,y;
	if ((a._ID_defined == 0 && a._type == ID_type) || (b._ID_defined == 0 && b._type == ID_type))
	{
		cout << "a or b not defined "<<endl;
	}
	else if (a._type == STRING_type && b._type == STRING_type)
	{
		temp._type =STRING_type;
		temp._STRING = a._STRING+b._STRING;
	}
	else if(a._type == LIST_type && b._type == LIST_type)
	{
		temp._type =LIST_type;
		if (a._iteration != 0)
		temp._LIST.assign(ITERATIONS[a._iteration-1]._LIST.begin(),ITERATIONS[a._iteration-1]._LIST.end());
		else 
		temp._LIST.assign(a._LIST.begin(),a._LIST.end());
		if (b._iteration == 0)
		temp._LIST.insert(temp._LIST.end(),b._LIST.begin(), b._LIST.end());
		else 
		temp._LIST.insert(temp._LIST.end(),ITERATIONS[b._iteration-1]._LIST.begin(),ITERATIONS[b._iteration-1]._LIST.end());
		temp._ID.clear();
		temp._ID_defined=0;
		temp._iteration = 0;
		temp._TUPLE = 0; 
	}
	else if (a._type == STRING_type && b._type != STRING_type) 
	{
		printf("the second should be a STRING\n");
		temp._type=ERROR_type;
	}
	else if (a._type != STRING_type && b._type == STRING_type) 
	{
		printf("the first should be a STRING\n");
		temp._type=ERROR_type;
	}
	else if (a._type == LIST_type && b._type != LIST_type)
	{
		printf("the second should be a LIST\n");
		temp._type=ERROR_type;
	}
	else if (a._type != LIST_type && b._type == LIST_type)
	{
		printf("the second should be a LIST\n");
		temp._type=ERROR_type;
	}
	else if (a._type != STRING_type && b._type != STRING_type && a._type != LIST_type && b._type !=LIST_type)
	{
		if (a._type == REAL_type) x = a._REAL;
		if (a._type == INT_type)  x = a._INT;
		if (b._type == REAL_type) y = b._REAL;
		if (b._type == INT_type)  y = b._INT;
		x = x + y;
		if (a._type == INT_type && b._type == INT_type)
		{
			temp._type = INT_type;
			temp._INT = (int) x;
		}
		else 
		{
			temp._type = REAL_type;
			temp._REAL =  x;
		}
		
	}
	return temp;
}

VarNode sub(VarNode a,VarNode b)
{
	VarNode temp={0};
	double x,y;
	if ((a._ID_defined == 0 && a._type == ID_type) || (b._ID_defined == 0 && b._type == ID_type))
	{
		cout << "a or b not defined "<< endl;
	}
	else if (a._type == LIST_type || a._type == STRING_type || b._type == LIST_type || b._type == STRING_type  )
	{
		temp._type = ERROR_type;
		printf("don't suppose this var type to run sub function\n"); 
	}
	else
	{
		if (a._type == REAL_type) x = a._REAL;
		if (a._type == INT_type)  x = a._INT;
		if (b._type == REAL_type) y = b._REAL;
		if (b._type == INT_type)  y = b._INT;
		x = x - y;
		if (a._type == INT_type && b._type == INT_type)
		{
			temp._type = INT_type;
			temp._INT = (int) x;
		}
		else 
		{
			temp._type = REAL_type;
			temp._REAL =  x;
		}
	}
	return temp;
}

void out_assignExpr(VarNode a)
{
	out_VarNode(a);
	cout<<endl;	
}
void out_VarNode(VarNode a)
{
	if (a._type != ERROR_type) 
	{
		if (a._type == REAL_type ) cout<<a._REAL;
		if (a._type == INT_type ) cout<<a._INT;
		if (a._type == STRING_type ) cout<< a._STRING;
		if (a._type == LIST_type && a._TUPLE == 0 && a._iteration != 0)
		{ 
			printLIST(ITERATIONS[a._iteration-1]._LIST,ITERATIONS[a._iteration-1]);
		}
		if (a._type == LIST_type && a._TUPLE == 0 && a._iteration == 0) {printLIST(a._LIST,a);}
		if (a._type == LIST_type && a._TUPLE > 0 && a._iteration == 0) printTUPLE(a._LIST);
		if (a._type == LIST_type && a._TUPLE > 0 && a._iteration != 0) printTUPLE(ITERATIONS[a._iteration-1]._LIST);
		if (a._type == ID_type) cout<< "error! no defination!";
	}	
}

VarNode mul(VarNode a,VarNode b)
{
    VarNode temp;
    double x,y;
	int i;
	if ((a._ID_defined == 0 && a._type == ID_type) || (b._ID_defined == 0 && b._type == ID_type))
	{
		cout << "a or b not defined "<<endl;
	}
	else if (a._type == STRING_type || b._type == STRING_type) 
	{
		temp._type = ERROR_type;
		printf("don't suppose this var type to run sub function\n"); 
	}
	else if( a._type == LIST_type || b._type == LIST_type  )
	{	
		if( a._type == LIST_type && b._type == LIST_type  )
		{
			printf("error!Invalid mul operation for two list!\n");
			temp._type = ERROR_type;
		}
		else
		{	if (a._type == REAL_type || b._type == REAL_type) 
			{
				printf("error!Invalid mul operation for float!\n");
				temp._type = ERROR_type;
			}
			else
			if (a._type == LIST_type && b._type == INT_type)
			{
				temp._type =LIST_type;
				temp._LIST.clear();
				for (i=0;i<b._INT;i++)	
				{
					if (a._iteration == 0)		
					temp._LIST.insert(temp._LIST.end(),a._LIST.begin(), a._LIST.end());
					else
			          temp._LIST.insert(temp._LIST.end(),ITERATIONS[a._iteration-1]._LIST.begin(),ITERATIONS[a._iteration-1]._LIST.end());
				}
			}
			else 
			if (b._type == LIST_type && a._type == INT_type)
			{
				temp._type =LIST_type;
				temp._LIST.clear();
				for (i=0;i<a._INT;i++)	
				if (b._iteration == 0)		
				temp._LIST.insert(temp._LIST.end(),b._LIST.begin(), b._LIST.end());
temp._LIST.insert(temp._LIST.end(),ITERATIONS[b._iteration-1]._LIST.begin(),ITERATIONS[b._iteration-1]._LIST.end());
			}
		}
	}
	else 
	{
    		if (a._type == REAL_type) x = a._REAL;
    		if (a._type == INT_type)  x = a._INT;
    		if (b._type == REAL_type) y = b._REAL;
    		if (b._type == INT_type)  y = b._INT;
    		x = x * y;
    		if (a._type == INT_type && b._type == INT_type)
    		{
       			temp._type = INT_type;
        		temp._INT = (int) x;
    		}
   		 else
    		{
        		temp._type = REAL_type;
        		temp._REAL =  x;
    		}
	}
    	return temp;
}

VarNode div(VarNode a,VarNode b)
{
    VarNode temp;
    double x,y;
	if (a._type == LIST_type || a._type == STRING_type || b._type == LIST_type || b._type == STRING_type ||
	 (a._ID_defined == 0 && a._type == ID_type) || (b._ID_defined == 0 && b._type == ID_type))
	{
		temp._type = ERROR_type;
		printf("don't suppose this var type to run sub function\n"); 
	}
    if (a._type == REAL_type) x = a._REAL;
    if (a._type == INT_type)  x = a._INT;
    if (b._type == REAL_type) y = b._REAL;
    if (b._type == INT_type)  y = b._INT;
    if (fabs(y-0)<1e-9) { printf("error! can't div zero\n");temp._type=ERROR_type;}
    else 
    {
	x = x / y;
    	temp._type = REAL_type;
    	temp._REAL =  x;
    }
    return temp;
}

VarNode mod(VarNode a,VarNode b)
{
    VarNode temp;
    int x,y;
    	if ((a._ID_defined == 0 && a._type == ID_type) || (b._ID_defined == 0 && b._type == ID_type))
    	{
		cout << "a or b not defined ";
    	}
    	else if (a._type == LIST_type || a._type == STRING_type || b._type == LIST_type || b._type == STRING_type  )
	{
		temp._type = ERROR_type;
		printf("don't suppose this var type to run sub function\n"); 
	}
    	else if (a._type == REAL_type || b._type == REAL_type)
    	{
        	printf("error! can't be a real type\n");
		temp._type=ERROR_type;
    	}
    	else
    	{	
        	x = a._INT;
        	y = b._INT;
		if (y == 0) 
		{
			printf("error! can't div  zero\n");
			temp._type=ERROR_type;
		}
        	else 
		{
			x = x % y;
	        	temp._type = INT_type;
    			temp._INT =  x;
    		}
    	}
    	return temp;
}

VarNode Call_CreateEmptyList(void){
	VarNode terminal;
	terminal._type = LIST_type;
	terminal._iteration =0;
	terminal._TUPLE=0;
	terminal._LIST.clear();
	terminal._List_Arg.clear();
	return terminal;
}

VarNode CreateList(VarNode a)
{
	VarNode temp={0};
	temp._type = LIST_type;
	temp._LIST.clear();
	temp._iteration =0;
	temp._TUPLE=0;
	if (a._type == INT_type) temp._LIST.insert(temp._LIST.end(),a);
	else if (a._type == REAL_type) temp._LIST.insert(temp._LIST.end(),a);
	else if (a._type == LIST_type)
	{
		temp._LIST.insert(temp._LIST.end(),a);
		temp._LIST[0]._TUPLE = a._TUPLE;
	}
	else if (a._type == STRING_type) temp._LIST.insert(temp._LIST.end(),a);
	else cout<<"error,Not a legal List member";
	return temp;
}

VarNode AddListMember(VarNode a,VarNode b)
{	
	if (b._type == INT_type) a._LIST.insert(a._LIST.end(),b);
	else if (b._type == REAL_type) a._LIST.insert(a._LIST.end(),b);
	else if (b._type == LIST_type)
	{
		a._LIST.insert(a._LIST.end(),b);
		a._LIST[a._LIST.size()-1]._TUPLE = b._TUPLE;
	}
	else if (b._type == STRING_type) a._LIST.insert(a._LIST.end(),b);
	else cout<<"error,Not a legal List member";
	return a;
}

VarNode CreateArgList(VarNode a)
{
	VarNode temp={0};
	temp._type = ArgLIST_type;
	temp._LIST.clear();
	if (a._type == INT_type) temp._LIST.insert(temp._LIST.end(),a);
	else if (a._type == REAL_type) temp._LIST.insert(temp._LIST.end(),a);
	else if (a._type == LIST_type)
	{
		temp._LIST.insert(temp._LIST.end(),a);
		temp._LIST[0]._TUPLE = a._TUPLE;
	}
	else if (a._type == STRING_type) temp._LIST.insert(temp._LIST.end(),a);
	else cout<<"error,Not a legal List member";
	return temp;
}

VarNode AddArgListMember(VarNode a,VarNode b)
{	
	if (b._type == INT_type) a._LIST.insert(a._LIST.end(),b);
	else if (b._type == REAL_type) a._LIST.insert(a._LIST.end(),b);
	else if (b._type == LIST_type)
	{
		a._LIST.insert(a._LIST.end(),b);
		a._LIST[a._LIST.size()-1]._TUPLE = b._TUPLE;
	}
	else if (b._type == STRING_type) a._LIST.insert(a._LIST.end(),b);
	else cout<<"error,Not a legal List member";
	return a;
}

void printLIST(vector<VarNode> LP,VarNode a){
	int i = 0;
	vector<VarNode> LP_sub;
	if(LP.size() == 0){
		cout << '[' << ']' ;
		return;
	}
	else{
		cout << '[';
		for(i = 0; i < LP.size() - 1; i++){
			switch(LP[i]._type){
				case 0: cout << LP[i]._INT; break;
				case 1: cout << LP[i]._REAL; break;
				case 2: cout << LP[i]._STRING; break;
				case 3: 
				{
					if (LP[i]._iteration !=0 && LP[i]._iteration == a._iteration)
					{
						
						cout << "[...]";
					}
					else if (LP[i]._iteration != 0)
					{
						
						printLIST(ITERATIONS[LP[i]._iteration-1]._LIST,ITERATIONS[LP[i]._iteration-1]);
						
					}
					else
					{
						if(LP[i]._TUPLE == 0) printLIST(LP[i]._LIST,LP[i]); 
						else printTUPLE(LP_sub);
					}
				}
				break;
				default: cout << "error type" << endl;
			}
			cout << ", ";
		}//for
		switch(LP[i]._type){
			case 0: cout << LP[i]._INT; break;
			case 1: cout << LP[i]._REAL; break;
			case 2: cout << LP[i]._STRING; break;
			case 3: 
				{
					if (LP[i]._iteration !=0 && LP[i]._iteration == a._iteration)
					{
						cout << "[...]";
					}
					else if (LP[i]._iteration != 0)
					{
						
						printLIST(ITERATIONS[LP[i]._iteration-1]._LIST,ITERATIONS[LP[i]._iteration-1]);
						
					}
					else
					{
						if(LP[i]._TUPLE == 0) printLIST(LP[i]._LIST,LP[i]); 
						else printTUPLE(LP_sub);
					}
					break;
				}
			default: cout << "error type" << endl;
		}//switch
		cout << ']';
	}//else
}//printLIST 

void printTUPLE(vector<VarNode> LP){
	int i = 0;
	vector<VarNode> LP_sub;
	if(LP.size() == 0){
		cout << '(' << ')' ;
		return;
	}
	else{
		cout << '(';
		for(i = 0; i < LP.size() - 1; i++){
			switch(LP[i]._type){
				case 0: cout << LP[i]._INT; break;
				case 1: cout << LP[i]._REAL; break;
				case 2: cout << LP[i]._STRING; break;
				case 3: 
				{
					LP_sub = LP[i]._LIST;
					printLIST(LP_sub,LP[i]); 
					break;
				}
				default: cout << "error type" << endl;
			}
			cout << ", ";
		}//for
		switch(LP[i]._type){
			case 0: cout << LP[i]._INT; break;
			case 1: cout << LP[i]._REAL; break;
			case 2: cout << LP[i]._STRING; break;
			case 3: 
				{
					LP_sub = LP[i]._LIST;
					printLIST(LP_sub,LP[i]); 
					break;
				}
			default: cout << "error type" << endl;
		}//switch
		cout << ')';
	}//else
}//printTUPLE

VarNode Call_Assign(VarNode leftval, VarNode rightval)
{
	int i,j,k;
	int a,b,c,d,num,flag=0,count,xx,t;
	VarNode temp={0};
	string searchstr = leftval._ID;
	vector<VarNode> *p ;
	vector<VarNode>::iterator it;
	if (rightval._type == ERROR_type) return (rightval);
	if (leftval._TUPLE == 1) return (leftval);
	if (leftval._ID_defined == 1)
	{
		for (i=0;i<VARS.size();i++)
		if(VARS[i]._ID == leftval._ID) break;
		if (leftval._List_Arg.size()==0)
		{
			VARS[i]=rightval;
			VARS[i]._ID = leftval._ID;
			VARS[i]._ID_defined=1;
			VARS[i]._List_Arg.clear();
			//cout <<i << " "<< VARS[i]._ID<< " "<<VARS[i]._iteration<<endl;
			//out_VarNode(VARS[i]);
		}	
		else 
		{
			p=&VARS[i]._LIST;
			if (VARS[i]._iteration !=0)
			{
				p=&ITERATIONS[VARS[i]._iteration-1]._LIST;
				cout << "change iterations"<<endl;
			}
			for (i=0;i<leftval._List_Arg.size();i++)
			{	
				it=p->begin();
				
				if (leftval._List_Arg[i]._type == INT_type)
				{
					flag=0;
					//cout << leftval._List_Arg[i]._INT << endl;
					for (j=0;j<leftval._List_Arg[i]._INT;j++) it++;
					//cout <<(*it)._INT << " "<< (*it)._iteration <<endl;
					if ((*it)._iteration !=0)
					{
						p=&ITERATIONS[(*it)._iteration-1]._LIST;
					}					
					else 
					p=&(*it)._LIST;
				}
				else 
				{
					flag=1;
					a=leftval._List_Arg[i]._LIST[0]._INT;
					b=leftval._List_Arg[i]._LIST[1]._INT;
					c=leftval._List_Arg[i]._LIST[2]._INT;
					if (i+1==leftval._List_Arg.size())
					{
						if (rightval._type != LIST_type)
						{
							leftval._type == ERROR_type;
							cout << "rightval error"<<endl;
							return leftval;
						}
						else
						{
							num=(b-a)/c;
							if ((b-a)%c != 0) num++;
							if (c!=1 && rightval._LIST.size()!=num)
							{
								leftval._type == ERROR_type;
								cout << "number isn't correct"<<endl;
								return leftval;
							}
							else
							{
								if (num<rightval._LIST.size()) t=num; else t=rightval._LIST.size();
								if (c>0)
								{	
									for (j=0;j<a;j++) it++;
									
									for (k=0;k<t;k++)
									{	
										(*it)=rightval._LIST[k];
										(*it)._ID.clear();
										(*it)._ID_defined=0;
										(*it)._List_Arg.clear();
										for (j=0;j<c;j++) it++;
									}
								}
								else
								{
									it=p->end();
									for (j=0;j<b;j++) it--;
									for (k=0;k<t;k++)
									{
										(*it)=rightval._LIST[k];
										(*it)._ID.clear();
										(*it)._ID_defined=0;
										(*it)._List_Arg.clear();
										for (j=0;j<c;j++) it--;
									}	
								}
								if(c==1 && rightval._LIST.size()!=num)
								{
									xx=rightval._LIST.size()-num;
									cout << xx <<endl;
										if (xx >0)
										{
											temp._LIST.clear();
											it=p->begin();
											for (i=0;i<b;i++)
											{ temp._LIST.push_back((*it));it++; }
											for (i=num;i<num+xx;i++)
											temp._LIST.push_back(rightval._LIST[i]);
											for (;it!=p->end();it++)
											temp._LIST.push_back((*it));
											p->assign(temp._LIST.begin(),temp._LIST.end());
										}
										else
										{
											temp._LIST.clear();
											it=p->begin();
											for (i=0;i<b-abs(xx);i++)
											{ temp._LIST.push_back((*it));it++;}
											
											for (i=0;i<abs(xx);i++) it++;
											
											for (;it!=p->end();it++)
											{ temp._LIST.push_back((*it));}
											p->assign(temp._LIST.begin(),temp._LIST.end());
										}
								}
								
							}
							
						}
					}
					else 
					{	
						i++;
						if (leftval._List_Arg[i]._type == INT_type)
						{
							d=leftval._List_Arg[i]._INT;
							if (c>0)
							{
								for (j=0;j<a;j++) it++;
								for (j=0;j<d*c;j++) it++;
								p=&(*it)._LIST;	
								//out_assignExpr(*it);
							}
							else
							{
								it=p->end();
								for (j=0;j<b;j++) it--;
								for (j=0;j<d*c;j++) it--;
								p=&(*it)._LIST;	
								//out_assignExpr(*it);
							}
						}
						else 
						{	return (rightval);
						}
					}
				}
			}
			if (flag==0)
			{
				//cout << "change the data"<<endl;
				(*it)=rightval;
				(*it)._ID.clear();
				(*it)._ID_defined=0;
				(*it)._List_Arg.clear();
			}
		}
	}
	else
	if (leftval._ID_defined == 0 && leftval._type == ID_type)
	{
		if (rightval._ID_defined == 0 && rightval._type == ID_type) 
		{
			leftval._type == ERROR_type;
			cout << "rightval error"<<endl;
		}
		else
		{
			leftval=rightval;
			leftval._ID = searchstr;
			leftval._ID_defined = 1;
			leftval._List_Arg.clear();
			//cout <<"first defined "<< leftval._ID << ".iteration=" <<  leftval._iteration<<endl;
			VARS.push_back(leftval);
		}
	}
	else 
	{
		leftval._type == ERROR_type;
		cout << "leftval error"<<endl;
	}
	return (leftval);
}

VarNode search_table(VarNode a)
{	
	int i;
	bool flag = false; // not found in VARS
	string searchstr = a._ID;
	
	for (i=0;i<VARS.size();i++)
	if(VARS[i]._ID == searchstr)
	{
		flag = true;
		break;
	}
	if (flag) return(VARS[i]);
	else return(a);
}

VarNode LEN(VarNode a)
{
	VarNode temp={0};
	if (a._type == ArgLIST_type)
	{
		temp._type = INT_type;
		if (a._LIST.size()!=1 )
		{
			cout << "error! too many Arg." <<endl;
			temp._type = ERROR_type;
		}
		else
		{ 
			if (a._LIST[0]._type == STRING_type) 
				temp._INT = a._LIST[0]._STRING.size();
			else if (a._LIST[0]._type == LIST_type) 
				temp._INT = a._LIST[0]._LIST.size();
		else 
		{
			cout << "error! Not a correct." <<endl;
			temp._type = ERROR_type;
		}
		}
	}
	else 
	{	
		temp._type = ERROR_type;
	}
	return temp;
}

VarNode EmptyVarNode(void)
{	
	VarNode temp={0};
  	temp._type=ERROR_type;
	return temp;
}

VarNode PRINT(VarNode a)
{
	int i;
	VarNode temp={0};
	for (i=0;i<a._LIST.size()-1;i++)
	{
		out_VarNode(a._LIST[i]);
		cout << " ";
	}
	out_VarNode(a._LIST[a._LIST.size()-1]);
	temp=EmptyVarNode();
	return temp;
}

VarNode LIST_CUT(VarNode a,VarNode b,VarNode c,VarNode d)
{
	VarNode temp={0};
	VarNode arg={0};
	int i;
	if (a._type!= LIST_type)
	{
		cout << "error! invalid operator for not a list." <<endl;
		temp._type = ERROR_type;
	}
	else if (b._type != INT_type || c._type != INT_type ||d._type != INT_type )
	{
		cout << "error! invalid operator for not a INT." <<endl;
		temp._type = ERROR_type;
	}
	else
	{
		temp = a;
		temp._iteration =0;
		temp._LIST.clear();
		if (a._iteration !=0)
		a._LIST.assign(ITERATIONS[a._iteration-1]._LIST.begin(),ITERATIONS[a._iteration-1]._LIST.end());
		while (b._INT<0) b._INT+= a._LIST.size();
		while (c._INT<0) c._INT+= a._LIST.size();
		if (c._INT>a._LIST.size()) c._INT= a._LIST.size();
		if (d._INT==0)
		{
			cout<<"error! step should not be zero."<<endl;
			temp._type = ERROR_type;
		}
		else 
		{
			if (d._INT>0)
			{
				for (i=b._INT;i<c._INT;i+=d._INT)
				temp._LIST.push_back(a._LIST[i]);
				//out_VarNode(a._LIST[i]);
			}
			else
			{
				for (i=a._LIST.size()-c._INT-1;i>a._LIST.size()-b._INT-1;i+=d._INT)
				temp._LIST.push_back(a._LIST[i]);
			}
			arg._type=LIST_type;
			arg._LIST.clear();
			arg._LIST.push_back(b);
			arg._LIST.push_back(c);
			arg._LIST.push_back(d);
			temp._List_Arg.push_back(arg);
			/*for (i=0;i<temp._List_Arg.size();i++)
			{
				out_assignExpr(temp._List_Arg[i]);
			}*/
		}
	}
	return temp;
}

VarNode LIST_SUB(VarNode a,VarNode b)
{
	VarNode temp={0};
	VarNode arg={0};

	int i;
	if (a._type!= LIST_type)
	{
		cout << "error! invalid operator for not a list." <<endl;
		temp._type = ERROR_type;
	}
	else if (b._type != INT_type)
	{
		cout << "error! invalid operator for not a INT." <<endl;
		temp._type = ERROR_type;
	}
	else
	{
		if (a._iteration !=0)
		{
			temp=ITERATIONS[a._iteration-1]._LIST[b._INT];
			temp._ID=a._ID;
			temp._ID_defined=a._ID_defined;
			temp._List_Arg.assign(a._List_Arg.begin(), a._List_Arg.end());
			arg._type=INT_type;
			arg._INT= b._INT;
			temp._List_Arg.push_back(arg);
			
		}
		else
		if (b._INT<a._LIST.size())
		{
			temp=a._LIST[b._INT];
			temp._ID=a._ID;
			temp._ID_defined=a._ID_defined;
			temp._List_Arg.assign(a._List_Arg.begin(), a._List_Arg.end());
			arg._type=INT_type;
			arg._INT= b._INT;
			temp._List_Arg.push_back(arg);
		}
		else 	
		{
			cout << "error! out of range." <<endl;
			temp._type = ERROR_type;
		}	
	}
	return temp;
}

VarNode RANGE(VarNode a)
{
	VarNode temp={0};
	if (a._type == ArgLIST_type)
	{
		temp._type = LIST_type;
		if (a._LIST.size() == 1)
		{
			int n;
			if(a._LIST[0]._type != INT_type)
			{
				cout << "error! Not a correct." <<endl;
				temp._type = ERROR_type;
				return temp;
			}
			n = a._LIST[0]._INT;
			for(int i = 0; i < n; i++)
			{
				VarNode temp1;
				temp1._type = INT_type;
				temp1._INT = i;
				temp._LIST.push_back(temp1);
			}
		}
		else if (a._LIST.size() == 2)
		{
			int i0,n;
			if(a._LIST[0]._type != INT_type || a._LIST[1]._type != INT_type)
			{
				cout << "error! Not a correct." <<endl;
				temp._type = ERROR_type;
				return temp;
			}
			i0 = a._LIST[0]._INT;
			n = a._LIST[1]._INT;
			for(int i = i0; i < n; i++)
			{
				VarNode temp1;
				temp1._type = INT_type;
				temp1._INT = i;
				temp._LIST.push_back(temp1);
			}
		}
		else if(a._LIST.size() == 3)
		{
			int i0,n,k;
			if(a._LIST[0]._type != INT_type || a._LIST[1]._type != INT_type || a._LIST[2]._type != INT_type)
			{
				cout << "error! Not a correct." <<endl;
				temp._type = ERROR_type;
				return temp;
			}
			i0 = a._LIST[0]._INT;
			n = a._LIST[1]._INT;
			k = a._LIST[2]._INT;
			if( k >=0 )
			{
				for(int i = i0; i < n; i = i+k)
				{
					VarNode temp1;
					temp1._type = INT_type;
					temp1._INT = i;
					temp._LIST.push_back(temp1);
				}
			}
			else
			{
				for(int i = i0; i > n; i = i+k)
				{
					VarNode temp1;
					temp1._type = INT_type;
					temp1._INT = i;
					temp._LIST.push_back(temp1);
				}
			}
		}
		else 
		{
			cout << "error! Not a correct." <<endl;
			temp._type = ERROR_type;
		}
	}
	else
	{
		cout << "error! Not a correct." <<endl;
		temp._type = ERROR_type;
	}
}

VarNode create_ITERATION(VarNode a)
{
	VarNode temp={0};
	VarNode temp2={0};
	int i;
	
	temp._type = LIST_type;
	temp._LIST.assign(a._LIST.begin(),a._LIST.end());
	temp._ID=ITERATIONS.size();
	temp._iteration=ITERATIONS.size()+1;
	
	temp2._ID=ITERATIONS.size();
	temp2._type=LIST_type;
	temp2._iteration=ITERATIONS.size()+1;
	temp._LIST.push_back(temp2);
	ITERATIONS.push_back(temp);
	return (temp);
}

VarNode APPEND(VarNode a,VarNode b)
{
	VarNode temp={0};
	int i,j,w,flag=0;
	vector <VarNode> *p;
	vector <VarNode> :: iterator it;
	if (b._type == ArgLIST_type)
	{
		if (b._LIST.size()!=1 )
		{
			cout << "error! too many Arg." <<endl;
			temp._type = ERROR_type;
			return temp;
		}
		if (a._iteration !=0 )
		{
			//cout << a._ID <<endl;
			ITERATIONS[a._iteration-1]._LIST.push_back(b._LIST[0]);
			
		}
		else 
		if (b._LIST[0]._ID == a._ID && a._List_Arg.size()==b._LIST[0]._List_Arg.size())
		{
			//cout << "append self" <<endl;
			temp=create_ITERATION(a);
			flag=1;
		}
		else 
		{
			//cout << "ordinary append"<<endl;
			//temp=a;
			temp._type = LIST_type;
			temp._ID = a._ID;
			temp._iteration = a._iteration;
			temp._LIST.assign(a._LIST.begin(),a._LIST.end());
    			temp._LIST.push_back(b._LIST[0]);
		}
	}
	else 
	{
		cout << "error! Not a correct using for append." <<endl;
		temp._type = ERROR_type;
		return temp;
	}
	string searchstr = a._ID;
	for (i=0; i<VARS.size(); i++)
		if(VARS[i]._ID == a._ID) break;
	//cout << VARS[i]._ID << " " << VARS[i]._iteration <<endl;
	//cout << i<<endl;
	if (flag) VARS[i]._iteration = temp._iteration;
	//cout << VARS[i]._ID << " " << VARS[i]._iteration <<endl;
	w=i;
	p=&VARS[i]._LIST;
	for (i=0;i<a._List_Arg.size();i++)
	{	
		it=p->begin();
		if (a._List_Arg[i]._type == INT_type)
		{
			for (j=0;j<a._List_Arg[i]._INT;j++) it++;
			p=&(*it)._LIST;
		}
		else 
		{
			temp._type=ERROR_type;
			return temp;
		}	
	}
	if (a._List_Arg.size()!=0)
	{
		(*it)._LIST.assign(temp._LIST.begin(),temp._LIST.end());
		(*it)._type = LIST_type;
	}
	else 
	{
		VARS[w]._LIST.assign(temp._LIST.begin(),temp._LIST.end());
		VARS[w]._type=LIST_type;	
	}
	return temp;
}

VarNode TUPLE(VarNode a)
{
	VarNode temp;
	int i,j;
	int l,k;
	if (a._type == ArgLIST_type)
	{
		if (a._LIST.size()!=1)
		{
			cout << "error! too many Arg." <<endl;
			temp._type = ERROR_type;
			return temp;
		}
		else if(a._LIST[0]._type != LIST_type)
		{
			cout << "error! Not a correct using for tuple." <<endl;
			temp._type = ERROR_type;
			return temp;
		}
		else
		{
			if (a._LIST[0]._TUPLE == 1)
			{
				cout << "invalid operation!" << endl;
				return a._LIST[0];
			}
			/*for (i=0; i<VARS.size(); i++)
				if(VARS[i]._ID == a._LIST[0]._ID) break;
			l = a._LIST[0]._List_Arg.size();
			if (l == 0)
			{
				temp = VARS[i];
				temp._TUPLE = 1;
				for (j=0; j<temp._LIST.size(); j++)
					temp._LIST[j]._TUPLE = 1;
				//Tuple_Turn(&VARS[i]);
			}
			else
			{
				k = a._LIST[0]._List_Arg[l-1]._INT;
				temp = VARS[i]._LIST[k];
				temp._TUPLE = 1;
				for (j=0; j<temp._LIST.size(); j++)
					temp._LIST[j]._TUPLE = 1;
				//Tuple_Turn(&VARS[i]._LIST[k]);	
			}*/
			temp = a._LIST[0];
			temp._TUPLE = 2;
			for (j=0; j<temp._LIST.size(); j++)
				temp._LIST[j]._TUPLE = 1;
		}
	}
	else
	{
		temp._type = ERROR_type;
		return temp;
	}
	return temp;
}

void Tuple_Turn(VarNode *a)
{
	int i;
	a->_TUPLE = 1;
	for(i=0;i<a->_LIST.size();i++)
	{
		if(a->_LIST[i]._type != LIST_type)
			a->_LIST[i]._TUPLE = 1;
		else
		{
			Tuple_Turn(&a->_LIST[i]);
		}
	}
}

VarNode LIST(VarNode a)
{
	VarNode temp;
	int i,j;
	int l,k;
	if (a._type == ArgLIST_type)
	{
		if (a._LIST.size()!=1)
		{
			cout << "error! too many Arg." <<endl;
			temp._type = ERROR_type;
			return temp;
		}
		else if(a._LIST[0]._type != LIST_type)
		{
			cout << "error! Not a correct using for list." <<endl;
			temp._type = ERROR_type;
			return temp;
		}
		else
		{
			if (a._LIST[0]._TUPLE == 0)
			{
				cout << "invalid operation!" << endl;
				return a._LIST[0];
			}
			/*for (i=0; i<VARS.size(); i++)
				if(VARS[i]._ID == a._LIST[0]._ID) break;
			l = a._LIST[0]._List_Arg.size();
			if (l == 0)
			{
				temp = VARS[i];
				temp._TUPLE = 0;
				for (j=0; j<temp._LIST.size(); j++)
					temp._LIST[j]._TUPLE = 0;
				//List_Turn(&VARS[i]);
				
			}
			else
			{
				k = a._LIST[0]._List_Arg[l-1]._INT;
				temp = VARS[i]._LIST[k];
				temp._TUPLE = 0;
				for (j=0; j<temp._LIST.size(); j++)
					temp._LIST[j]._TUPLE = 0;
				//List_Turn(&VARS[i]._LIST[k]);
				
			}*/
			temp = a._LIST[0];
			temp._TUPLE = 0;
			for (j=0; j<temp._LIST.size(); j++)
				temp._LIST[j]._TUPLE = 0;
		}
	}
	else
	{
		temp._type = ERROR_type;
		return temp;
	}
	return temp;
}

void List_Turn(VarNode *a)
{
	int i;
	a->_TUPLE = 0;
	for(i=0;i<a->_LIST.size();i++)
	{
		if(a->_LIST[i]._type != LIST_type)
			a->_LIST[i]._TUPLE = 0 ;
		else
		{
			List_Turn(&a->_LIST[i]);
		}
	}
}
