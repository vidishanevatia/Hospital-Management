#include<iostream.h>
#include<fstream.h>
#include<string.h>
#include<stdio.h>
#include<iomanip.h>
#include<stdlib.h>
#include<conio.h>
#include<ctype.h>

fstream f,fo,file,fs;
int choice,opt,pos = 0,cho,id,docid,roomid,testid,patientid,rn,flag=0,g,total;
char i,ans,type[30],doc[30],date[11],dte[11],docname[20];
float fees,rfees,cost;



class doctors
{
    int did;
    char name[30];
    char speciality[30];
    float cost;
    long int phn;
    char tests[200];
    char refdoc[30];
    public :
    void insert(int);
    void modify();
    void display();
    int  ret_did()
    {
	return did;
    }
    char * ret_speciality()
    {
	return speciality;
    }
    char* ret_name()
    {
	return name;
    }
    float ret_fees()
    {
	return cost;
    }
} ;

class rooms
{
    int rid;
    char room_type[30];
    float cost;
    char status;
public:
    void insert(int);
    void modify();
    char rstatus()
    {
	return status;
    }
    void display();
    int ret_rid()
    {
	return rid;
    }
    char * ret_type()
    {
	return room_type;
    }
    void changestat()
    {
	status='N';
    }
    char ret_stat()
    {
	return status;
    }
    float ret_cost()
    {
	return cost;
    }

};


class tests
{
    int tid;
    char test_type[30];
    float cost;
public:
    void insert(int);
    void modify();
    void display();
    int ret_tid()
    {
	return tid;
    }
    char* ret_type()
    {
	return test_type;
    }
    float ret_cost()
    {
	return cost;
    }

};

class patient
{
    int pid;
    char name[20];
    char bloodgroup[5];
    char dateofadmission[11];
    char dateofdischarge[11];
    char illness[20];
    float fees;
    float room_fee;
    char refdoc[30];
    int rid;
    long int phn;
    int proom;
    int days;
public:
    void insert(int);
    void insertt(float,char*,int,float);
    void modify();
    void display();
    int  ret_pid()
    {
        return pid;
    }
    char * ret_illness()
    {
        return illness;
    }
    int no_of_days(char*,char*);
    char* ret_name()
    {
        return name;
    }
    char* ret_docname()
    {
        return refdoc;
    }
    float ret_fees()
    {
	return fees;
    }
    float ret_rfees()
    {
        return room_fee;
    }
    void dod(char dt[11])
    {
        strcpy(dateofdischarge,dt);
    }
    char* doa()
    {
        return dateofadmission;
    }
};

doctors d;
rooms r;
tests t;
patient p;


int dateval(char dt[11])
{
    char yy[5],mm[3],mm3[3];
    int dd1,mm1,yy1,m1,m2;
    char array[]={31,28,31,30,31,30,31,31,30,31,30,31};
    m1=atoi((itoa(dt[3],mm,10)))-48;
    m2=atoi((itoa(dt[4],mm3,10)))-48;
    mm1=m1*10+m2;
    yy1=atoi(strcpy(yy,dt+6));
    dd1=atoi(dt);
    if(yy1%400==0 || yy1%4==0)
	array[1]=29;
    if(dd1>=array[mm1-1]||mm1>12)
	return 0;
    else
	return 1;
}


void doctors::insert(int id)
{   did=id;
    cout<<"\nDoctor ID : "<<did;
    cout<<"\nEnter doctor name : ";
    gets(name);
    cout<<"Enter the speciality of the doctor : ";
    gets(speciality);
    cout<<"Enter doctor fees : ";
    cin>>cost;
    cout<<"Enter doctor phone number : ";
    cin>>phn;
}

void doctors::modify()
{
    char tname[30],type[30];float fees;long int phone;

    cout<<"\n1.Enter new name of the doctor or enter . to retain old one : ";
    gets(tname);
    if(strcmp(tname,".")!=0)
	strcpy(name,tname);
    cout<<"2.Enter the new speciality of the doctor or enter . to retain the old one : ";
    gets(type);
    if(strcmp(".",type)!=0)
	strcpy(speciality,type);
    cout<<"Enter the new fees of the doctor or enter -1 to retain the old one : ";
    cin>>fees;
    if(fees!=-1)
	cost=fees;
    cout<<"\nEnter the new phone number of the doctor or press -1 to retain the old one : ";
    cin>>phone;
    if(phone!=-1)
	phn=phone;
}

void doctors::display()
{
    cout<<setw(10)<<did<<setw(15)<<name<<setw(20)<<speciality<<setw(12)<<cost<<setw(19)<<phn<<endl;
}

void rooms::insert(int id)
{   rid=id;
    cout<<"\nRoom ID : "<<rid;
    cout<<"\nEnter room type : ";
    gets(room_type);
    status= 'A';
    cout<<"Enter room cost : ";
    cin>>cost;
}


void rooms::modify()
{   char type[30];float price;
    cout<<"Enter the new room type or press . to retain the old one : ";
    gets(type);
    if(strcmp(type,".")!=0)
	strcpy(room_type,type);
    cout<<"Enter the new room cost or press -1 to retain the old one : ";
    cin>>price;
    if(price!=-1)
	cost=price;
}

void rooms::display()
{   cout<<setw(15)<<rid<<setw(18)<<room_type<<" "<<setw(20)<<status<<" "<<setw(5)<<cost<<endl;
}

void tests::insert(int id)
{
    tid=id;
    cout<<"\nTest ID : "<<tid;
    cout<<"\nEnter the test name : ";
    gets(test_type);
    cout<<"Enter the cost of the test : ";
    cin>>cost;
}

void tests::modify()
{   char name[30];float fees;
    cout<<"\nEnter the new test name or enter . to retain the orignal one : ";
    gets(name);
    if(strcmp(name,".")!=0)
	strcpy(test_type,name);
    cout<<"Enter the cost of the test or enter -1 to retain the orignal one : ";
    cin>>fees;
    if(fees!=-1)
	cost=fees;
}
void tests::display()
{
    cout<<setw(20)<<tid<<setw(25)<<test_type<<setw(18)<<cost<<endl;
}

void patient::insert(int id)
{
    //f.open("rooms.dat",ios::out|ios::binary);
    pid=id;
    cout<<"\nPatient ID : "<<pid;
    cout<<"\nEnter Patient Name : ";
    gets(name);
    cout<<"Enter Patient illness : ";
    gets(illness);
    cout<<"Enter Patient Blood Group : ";
    gets(bloodgroup);
    cout<<"Enter Patient Phone  : ";
    cin>>phn;
e:
    cout<<"Enter the date of admission of patient : ";
    gets(dateofadmission);
    if (dateval(dateofadmission)!=1)
    {
	cout<<"Invalid date.";
	goto e;
    }
    fs.open("doctor.dat",ios::in|ios::binary);
    fs.seekg(0,ios::beg);
    clrscr();
    cout<<"\nLIST OF DOCTORS : \n";
    while(fs.read((char*)&d,sizeof(d)))
    {
	if(fs.eof())
	    break;

	cout<<d.ret_did()<<"\t"<<d.ret_name() <<endl;
    }

    cout<<"\nEnter doctor ID : ";
    cin>>docid;
    //cout<<docid;
    fs.close();
    fs.open("doctor.dat",ios::in|ios::binary);
    while(!fs.eof())
    {

	fs.read((char*)&d,sizeof(d));
	if(fs.eof())
	    break;
	if(docid==d.ret_did())
	{
	    fees=d.ret_fees();
	    strcpy(refdoc,d.ret_name());


	    break;
	}
    }
    flag=0;
    file.open("rooms.dat",ios::in|ios::binary);
    file.seekg(0,ios::beg);
    cout<<"\nLIST OF AVAILABLE ROOMS : \n";
    while(file.read((char*)&r,sizeof(r)))
    {
	if(file.eof())
	    break;

	if(r.rstatus()=='A')
	    cout<<r.ret_rid()<<"\t"<<r.ret_type() <<endl;
    }
    file.close();
    file.open("rooms.dat",ios::in|ios::binary);

    cout<<"\nEnter room ID : ";
    cin>>roomid;
    file.read((char*)&r,sizeof(r));
    while(!file.eof())
    {
	if(roomid==r.ret_rid())
	{
	    pos = file.tellg() - sizeof(r);
	    rid=roomid;
	room_fee=r.ret_cost();
	    flag = 1;
	    break;
	}
	file.read((char*)&r,sizeof(r));
    }
    if(flag ==1)
    { r.changestat();
	file.seekg(pos);
	file.write((char*)&r,sizeof(r));

	fs.close();
	file.close();

    }

}


void patient::modify()
{
    char tname[30],type[30],blood[7],date[11];
    long int phone;
    cout<<"\n1.Enter new name of the patient or enter . to retain old one : ";
    gets(tname);
    if(strcmp(name, ".")!=0)
	strcpy(name,tname);
    cout<<"2.Enter the illness of the patient or enter . to retain the old one : ";
    gets(type);
    if(strcmp(".", type)!=0)
	strcpy(illness,type);
    cout<<"Enter the blood group of the patient or enter . to retain the old one : ";
    gets(blood);
    if(strcmp(blood, ".")!=0)
	strcpy(bloodgroup,blood);
    cout<<"Enter the new phone number of the patient or press -1 to retain the old one : ";
    cin>>phone;
    if(phn!=-1)
	phn=phone;
a:
    cout<<"\nEnter the date of admission of the patient or press . to retain the old one : ";
    gets(date);
    if(date!=".")
    { strcpy(dateofadmission,date);
	if(dateval(dateofadmission)!=1)
	{
	    cout<<"Invalid date.";
	    goto a;
	}
    }
}

void patient::display()
{
    cout<<setw(4)<<pid<<setw(7)<<name<<setw(11)<<illness<<setw(8)<<bloodgroup<<setw(17)<<phn<<setw(16)<<dateofadmission<<setw(7)<<rid<<setw(8)<<refdoc<<endl;
}

int patient::no_of_days(char dt1[11],char dt2[11])
{    	  char array[]={31,28,31,30,31,30,31,31,30,31,30,31};
    char array2[]={31,28,31,30,31,30,31,31,30,31,30,31};

    char yy[5],mm[3],mm3[3], yy3[5],mm5[3],mm7[3];
    int dd1,dd2,mm1,mm2,yy1,yy2,m1,m2,m3,m4;
    m1=atoi((itoa(dt1[3],mm,10)))-48;
    m2=atoi((itoa(dt1[4],mm3,10)))-48;
    mm1=m1*10+m2;
    yy1=atoi(strcpy(yy,dt1+6));
    dd1=atoi(dt1);
    if(yy1%400==0 || yy1%4==0)
	array[1]=29;
    m3=atoi((itoa(dt2[3],mm5,10)))-48;
    m4=atoi((itoa(dt2[4],mm7,10)))-48;
    mm2=m3*10+m4;
    yy2=atoi(strcpy(yy3,dt2+6));
    dd2=atoi(dt2);
    if(yy2%400==0 || yy2%4==0)
	array2[1]=29;
    int days=0,i;
    int m[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    if(yy1 == yy2)
    {
	if(mm1 == mm2)
	    days = dd2 - dd1;
	else
	{
	    for(i = mm1; i <mm2-1;i++)
		days += m[i];
	    days += m[mm1-1] - dd1 +dd2;
	}
    }
    else
    {
	for(i = 0; i < mm2-1; i++)
	    days += m[i];
	for(i = mm1; i < 12; i++)
	    days += m[i];
	if(yy2 - yy1 >= 0)
	    days += (yy2 - yy1- 1)*365 +
	    m[mm1-1] - dd1 + dd2;
    }
    return days;



}

void main()
{    textcolor(BLACK);
     textbackground(WHITE);


    do
    {  clrscr();
	cout<<"\n________________________________________________________________________________";
	cout<<"\n\n                            HOSPITAL MANAGEMENT SYSTEM                                               ";
	cout<<"\n________________________________________________________________________________";
	cout<<"\n\n\n";
	cout<<"\nMAIN MENU :\n \n1.Doctors\n2.Rooms\n3.Tests\n4.Patients\n5.Reports\n0.Exit\n\nEnter your Choice : ";
	cin>>choice;
	switch(choice)
	{
	    case 1 : do
	    {
		clrscr();
	    y:
		clrscr();
		cout<<"\n\n\n\n\n\n";
		cout<<"\nMENU FOR DOCTORS :\n \n1.Add \n2.Modify \n3.Delete\n0.Back to Main Menu\n\nEnter your Choice : ";
		cin>>opt;
		switch(opt)
		{
		    case 1: f.open("doctor.dat",ios::in|ios::app|ios::binary);
			f.clear();
			f.seekg(0,ios::end);
			pos=f.tellg();
			f.seekg(pos-sizeof(d));

			if(pos==0)
			    docid=100;
			else
			{
			    f.read((char*)&d,sizeof(d));
			    f.seekg(pos-sizeof(d));
			    docid=d.ret_did()+1;
			}
			d.insert(docid);
			f.seekg(0,ios::end);
			f.write((char*)&d,sizeof(d));
			cout<<"\nPress any key to continue.";
			getch();
			f.close();
			break;
		    case 2: i='n';
			f.open("doctor.dat",ios::out|ios::in|ios::binary);
			f.clear();
			f.seekg(0,ios::beg);
			cout<<"\nLIST OF DOCTORS : \n";
			while(f.read((char*)&d,sizeof(d)))
			{
			    if(f.eof())
				break;

			    cout<<d.ret_did()<<"\t"<<d.ret_name() <<endl;
			}
			cout<<"\nEnter the doctor ID of the doctor whose details is to be modified : ";
			cin>>id;
			f.clear();
			f.seekg(0,ios::beg);
			while(!f.eof())
			{
			    pos=f.tellg();
			    f.read((char*)&d,sizeof(d));
			    if(id==d.ret_did())
			    {
				i='y';
				cout.setf(ios::left);
				clrscr();
				cout<<"________________________________________________________________________________"<<endl;
				cout<<setw(10)<<"ID"<<setw(15)<<"NAME"<<setw(20)<<"SPECIALITY"<<setw(12)<<"FEES"<<setw(19)<<"PHONE NUMBER"<<endl;
				cout<<"________________________________________________________________________________"<<endl;
				cout<<endl;
				d.display();
				cout<<"\nAre you sure you want to modify this record? (y/n) : ";
				cin>>ans;
				if (ans=='y'||ans=='Y')
				{
				    d.modify();
				    f.seekg(pos,ios::beg);
				    f.write((char*)&d,sizeof(d));
				    break;
				}
				else if (ans=='n'||ans=='N')
				    break;
			    }
			}
			if (i=='n'||i=='N')
			    cout<<"\nRecord not found. ";
			cout<<"\nPress any key to continue.";
			getch();
			f.close();
			goto y;
		    case 3:  i='n';
			f.open("doctor.dat",ios::in|ios::binary);
			file.open("Temp.dat",ios::app|ios::binary);
			f.clear();
			f.seekg(0,ios::beg);
			cout<<"\nLIST OF DOCTORS : \n";
			while(f.read((char*)&d,sizeof(d)))
			{
			    if(f.eof())
				break;

			    cout<<d.ret_did()<<"\t"<<d.ret_name() <<endl;
			}

			cout<<"\nEnter the doctor id of the doctor to be removed: ";
			cin>>id;
			f.clear();
			f.seekg(0,ios::beg);
			while(f.read((char*)&d,sizeof(d)))
			{
			    if(f.eof())
				break;
			    if(id==d.ret_did())
			    {
				i='y';
				cout.setf(ios::left);
				clrscr();
				cout<<"________________________________________________________________________________"<<endl;
				cout<<setw(10)<<"ID"<<setw(15)<<"NAME"<<setw(20)<<"SPECIALITY"<<setw(12)<<"FEES"<<setw(19)<<"PHONE NUMBER"<<endl;
				cout<<"________________________________________________________________________________"<<endl;
				d.display();
				cout<<"\nAre you sure you want to delete this record? (y/n) : ";
				cin>>ans;

				if (ans=='y'||ans=='Y')
				    break;
				else
				    file.write((char*)&d,sizeof(d));
			    }
			    else
				file.write((char*)&d,sizeof(d));
			}
			if (i=='n'||i=='N')
			    cout<<"\nRecord not found. ";
			cout<<"\nPress any key to continue. ";
			getch();

			file.close();
			f.close();
			if(ans=='y'||ans=='Y')
			{
			    remove("doctor.dat");
			    rename("Temp.dat","doctor.dat");
			}
			goto y;
		    case 0:  break;
		}
	    }while(opt!=0);
		break;
	    case 2:  do
	    {
		clrscr();
	    s:
		clrscr();
		cout<<"\n\n\n\n\n\n";
		cout<<"\nMenu for Rooms :\n \n1.Add \n2.Modify \n3.Delete\n0.Back to Main Menu\n\nEnter your Choice : ";
		cin>>opt;
		switch(opt)
		{
		    case 1: f.open("rooms.dat",ios::in|ios::app|ios::binary);
			f.clear();
			f.seekg(0,ios::end);
			pos=f.tellg();
			f.seekg(pos-sizeof(r));

			if(pos==0)
			    roomid=100;
			else
			{
			    f.read((char*)&r,sizeof(r));
			    f.seekg(pos-sizeof(r));
			    roomid=r.ret_rid()+1;
			}
			r.insert(roomid);
			f.seekg(0,ios::end);
			f.write((char*)&r,sizeof(r));
			cout<<"\nPress any key to continue.";
			getch();
			f.close();
			break;
		    case 2:i='n';
			f.open("rooms.dat",ios::out|ios::in|ios::binary);
			f.clear();
			f.seekg(0,ios::beg);
			cout<<"\nLIST OF ROOMS : \n";
			while(f.read((char*)&r,sizeof(r)))
			{
			    if(f.eof())
				break;

			    cout<<r.ret_rid()<<"\t"<<r.ret_type() <<endl;
			}
			cout<<"\nEnter the room ID of the room whose details is to be modified : ";
			cin>>id;
			f.clear();
			f.seekg(0,ios::beg);
			while(!f.eof())
			{
			    pos=f.tellg();
			    f.read((char *)&r,sizeof(r));
			    if(id==r.ret_rid())
			    {
				i='y';
				cout.setf(ios::left);
				clrscr();
				cout<<"________________________________________________________________________________"<<endl;
				cout<<setw(15)<<"ROOM NO"<<setw(18)<<"ROOM TYPE"<<setw(20)<<"ROOM STATUS"<<setw(22)<<"ROOM CHARGES"<<endl;;
				cout<<"________________________________________________________________________________"<<endl;
				cout<<endl;
				r.display();
				cout<<"\nAre you sure you want to modify this record? (y/n) : ";
				cin>>ans;
				if (ans=='y'||ans=='Y')
				{
				    r.modify();
				    f.seekg(pos,ios::beg);
				    f.write((char*)&r,sizeof(r));
				    break;
				}
				else if (ans=='n'||ans=='N')
				    break;
			    }
			}
			if (i=='n'||i=='N')
			    cout<<"\nRecord not found. ";
			cout<<"\nPress any key to continue.";
			getch();
			f.close();
			goto s;

		    case 3: i='n';
			f.open("rooms.dat",ios::in|ios::binary);
			file.open("Temp.dat",ios::app|ios::binary);
			f.clear();
			f.seekg(0,ios::beg);
			cout<<"\nLIST OF ROOM : \n";
			while(f.read((char*)&r,sizeof(r)))
			{
			    if(f.eof())
				break;

			    cout<<r.ret_rid()<<"\t"<<r.ret_type()<<endl;
			}

			cout<<"\nEnter the room id of the room to be removed: ";
			cin>>id;
			f.clear();
			f.seekg(0,ios::beg);
			while(f.read((char*)&r,sizeof(r)))
			{
			    if(f.eof())
				break;
			    if(id==r.ret_rid())
			    {
				i='y';
				cout.setf(ios::left);
				clrscr();
				cout<<"________________________________________________________________________________"<<endl;
				cout<<setw(15)<<"ROOM NO"<<setw(18)<<"ROOM TYPE"<<setw(20)<<"ROOM STATUS"<<setw(22)<<"ROOM CHARGES"<<endl;
				cout<<"________________________________________________________________________________"<<endl;
				r.display();
				cout<<"\nAre you sure you want to delete this record? (y/n) : ";
				cin>>ans;

				if (ans=='y'||ans=='Y')
				    break;
				else
				    file.write((char*)&d,sizeof(d));
			    }
			    else
				file.write((char*)&r,sizeof(r));
			}
			if (i=='n'||i=='N')
			    cout<<"\nRecord not found. ";
			cout<<"\nPress any key to continue. ";
			getch();

			file.close();
			f.close();
			if(ans=='y'||ans=='Y')
			{
			    remove("rooms.dat");
			    rename("Temp.dat","rooms.dat");
			}
			goto s;
		    case 0:break;

		}
	    }while(opt!=0);
		break;
	    case 3: do
	    {
		clrscr();
	    z:
		clrscr();
		cout<<"\n\n\n\n\n\n";
		cout<<"\nMenu for Tests : \n\n1.Add \n2.Modify \n3.Delete\n0.Back to Main Menu\n\nEnter your Choice : ";
		cin>>opt;
		switch(opt)
		{
		    case 1:f.open("test.dat",ios::in|ios::app|ios::binary);
			f.clear();
			f.seekg(0,ios::end);
			pos=f.tellg();
			f.seekg(pos-sizeof(t));

			if(pos==0)
			    testid=100;
			else
			{
			    f.read((char*)&t,sizeof(t));
			    f.seekg(pos-sizeof(t));
			    testid=t.ret_tid()+1;
			}
			t.insert(testid);
			f.seekg(0,ios::end);
			f.write((char*)&t,sizeof(t));
			cout<<"\nPress any key to continue.";
			getch();
			f.close();
			break;
		    case 2: f.open("test.dat",ios::out|ios::in|ios::binary);
			f.clear();
			f.seekg(0,ios::beg);
			cout<<"\nLIST OF TESTS : \n";
			f.read((char*)&t,sizeof(t));
			while(!f.eof())
			{
			    cout<<t.ret_tid()<<"\t"<<t.ret_type() <<endl;
			    f.read((char*)&t,sizeof(t));


			}
			cout<<"\nEnter the test ID of the test whose details is to be modified : ";
			cin>>id;
			f.clear();
			f.seekg(0,ios::beg);
			while(!f.eof())
			{
			    pos=f.tellg();
			    f.read((char*)&t,sizeof(t));
			    if(id==t.ret_tid())
			    {
				i='y';
				cout.setf(ios::left);
				clrscr();
				cout<<"________________________________________________________________________________"<<endl;
				cout<<setw(20)<<"TEST NO"<<setw(25)<<"TEST TYPE"<<setw(18)<<"RATE"<<endl;
				cout<<"________________________________________________________________________________"<<endl;
				t.display();
				cout<<"\nAre you sure you want to modify this record? (y/n) : ";
				cin>>ans;
				if (ans=='y'||ans=='Y')
				{
				    t.modify();
				    f.seekg(pos,ios::beg);
				    f.write((char*)&t,sizeof(t));
				    break;
				}
				else if (ans=='n'||ans=='N')
				    break;

			    }
			}
			if (i=='n'||i=='N')
			    cout<<"\nRecord not found. ";
			cout<<"\nPress any key to continue.";
			getch();
			f.close();
			goto z;
		    case 3: i='n';
			f.open("test.dat",ios::in|ios::binary);
			file.open("Temp.dat",ios::app|ios::binary);
			f.clear();
			f.seekg(0,ios::beg);
			cout<<"\nLIST OF TESTS : \n";
			f.read((char*)&t,sizeof(t));
			while(!f.eof())
			{
			    cout<<t.ret_tid()<<"\t"<<t.ret_type() <<endl;
			    f.read((char*)&t,sizeof(t));


			}

			cout<<"\nEnter the test id of the test to be removed: ";
			cin>>id;
			f.clear();
			f.seekg(0,ios::beg);
			while(f.read((char*)&t,sizeof(t)))
			{
			    if(f.eof())
				break;
			    if(id==t.ret_tid())
			    {
				i='y';
				cout.setf(ios::left);
				clrscr();
				cout<<"________________________________________________________________________________"<<endl;
				cout<<setw(20)<<"TEST NO"<<setw(25)<<"TEST TYPE"<<setw(18)<<"RATE"<<endl;
				cout<<"________________________________________________________________________________"<<endl;
				t.display();
				cout<<"\nAre you sure you want to delete this record? (y/n) : ";
				cin>>ans;

				if (ans=='y'||ans=='Y')
				    break;
				else
				    file.write((char*)&d,sizeof(d));
			    }
			    else
				file.write((char*)&t,sizeof(t));
			}
			if (i=='n'||i=='N')
			    cout<<"\nRecord not found. ";
			cout<<"\nPress any key to continue. ";
			getch();

			file.close();
			f.close();
			if(ans=='y'||ans=='Y')
			{
			    remove("test.dat");
			    rename("Temp.dat","test.dat");
			}
			goto z;

		    case 0:break;

		}
	    }while(opt!=0);
		break;
	    case 4: do
	    {
		clrscr();
	    w:
		clrscr();
		cout<<"\n\n\n\n\n\n";
		cout<<"MENU for Patients : \n 1.Add \n 2.Modify \n 3.Delete  \n 0.Back to Main Menu\n\n Enter your choice : ";
		cin>>opt;
		switch(opt)
		{
		    case 1: f.open("patient.dat",ios::in|ios::app|ios::binary);
			f.clear();
			f.seekg(0,ios::end);
			pos=f.tellg();
			f.seekg(pos-sizeof(p));

			if(pos==0)
			    patientid=100;
			else
			{
			    f.read((char*)&p,sizeof(p));
			    f.seekg(pos-sizeof(p));
			    patientid=p.ret_pid()+1;
			}
			cout<<endl;
			p.insert(patientid);
			f.write((char*)&p,sizeof(p));
			f.close();
			cout<<"\nPress any key to continue.";
			getch();
			goto w;
			break;

		    case 2: f.open("patient.dat",ios::out|ios::in|ios::binary);
			f.clear();
			f.seekg(0,ios::beg);
			cout<<"\nLIST OF PATIENTS : \n";
			while(f.read((char*)&p,sizeof(p)))
			{
			    if(f.eof())
				break;

			    cout<<p.ret_pid()<<"\t"<<p.ret_name() <<endl;
			}
			cout<<"\nEnter the patient ID of the patient whose details is to be modified : ";
			cin>>id;
			f.clear();
			f.seekg(0,ios::beg);
			while(!f.eof())
			{
			    pos=f.tellg();
			    f.read((char*)&p,sizeof(p));
			    if(id==p.ret_pid())
			    {
				i='y';
				cout.setf(ios::left);
				clrscr();
				cout<<"________________________________________________________________________________"<<endl;
				cout<<setw(4)<<"ID"<<setw(7)<<"NAME"<<setw(10)<<"ILLNESS"<<setw(12)<<"BLOODGROUP"<<setw(14)<<"PHONE NUMBER"<<setw(16)<<"ADMISSIONDATE"<<setw(7)<<"ROOM"<<setw(8)<<"REFDOC"<<endl;
				cout<<"________________________________________________________________________________"<<endl;
				cout<<endl;

				p.display();
				cout<<"\nAre you sure you want to modify this record? (y/n) : ";
				cin>>ans;
				if (ans=='y'||ans=='Y')
				{
				    p.modify();
				    f.seekg(pos,ios::beg);
				    f.write((char*)&p,sizeof(p));
				    break;
				}
				else if (ans=='n'||ans=='N')
				    break;

			    }
			}
			if (i=='n'||i=='N')
			    cout<<"\nRecord not found. ";
			cout<<"\nPress any key to continue.";
			getch();
			f.close();
			goto w;

		    case 3: i='n';
			f.open("patient.dat",ios::in|ios::binary);
			file.open("Temp.dat",ios::app|ios::binary);
			f.clear();
			f.seekg(0,ios::beg);
			cout<<"\nLIST OF PATIENTS : \n";
			while(f.read((char*)&p,sizeof(p)))
			{
			    if(f.eof())
				break;

			    cout<<p.ret_pid()<<"\t"<<p.ret_name() <<endl;
			}

			cout<<"\nEnter the patient id of the patient to be removed: ";
			cin>>id;
			f.clear();
			f.seekg(0,ios::beg);
			while(f.read((char*)&p,sizeof(p)))
			{
			    if(f.eof())
				break;
			    if(id==p.ret_pid())
			    {
				i='y';
				cout.setf(ios::left);
				cout.setf(ios::left);
				cout<<"________________________________________________________________________________"<<endl;
				cout<<setw(4)<<"ID"<<setw(7)<<"NAME"<<setw(10)<<"ILLNESS"<<setw(12)<<"BLOODGROUP"<<setw(14)<<"PHONE NUMBER"<<setw(16)<<"ADMISSIONDATE"<<setw(7)<<"ROOM"<<setw(8)<<"REFDOC"<<endl;
				cout<<"________________________________________________________________________________"<<endl;p.display();
				cout<<"\nAre you sure you want to delete this record? (y/n) : ";
				cin>>ans;

				if (ans=='y'||ans=='Y')
				    break;
				else
				    file.write((char*)&d,sizeof(d));
			    }
			    else
				file.write((char*)&p,sizeof(p));
			}
			if (i=='n'||i=='N')
			    cout<<"\nRecord not found. ";
			cout<<"\nPress any key to continue. ";
			getch();

			file.close();
			f.close();
			if(ans=='y'||ans=='Y')
			{
			    remove("patient.dat");
			    rename("Temp.dat","patient.dat");
			}
			goto w;

		    case 0:break;

		}
	    }while(opt!=0);
		break;
	    case 5 :do
	    {

	    m:
		clrscr();
		cout<<"\n\n\n\n\n\n";
		cout<<"\nMENU FOR REPORTS:\n1.Reports based on doctors\n2.Reports based on rooms\n3.Reports based on tests\n4.Reports based on patients\n5.Generate Bill\n0.To go back to main menu\nEnter your Choice : " ;
		cin>>cho;
		switch(cho)
		{
		    case 1: l:
			clrscr();
			cout<<"\n\n\n\n\n\n";
			cout<<"\nDOCTOR REPORTS --\n\n1.To display all doctors\n2.To display doctors based the speciality\nPress 0 to go back to the reports menu \n\nEnter Your Choice : ";
			cin>>opt;
			switch(opt)
		    {
			case 1: f.open("doctor.dat",ios::in|ios::binary);
			    f.clear();
			    f.seekg(0,ios::beg);
			    cout<<"\nDOCTORS DETAILS OF ALL DOCTORS OF THE HOSPITAL : \n";
			    cout<<"________________________________________________________________________________"<<endl;
			    cout<<setw(10)<<"ID"<<setw(15)<<"NAME"<<setw(20)<<"SPECIALITY"<<setw(12)<<"FEES"<<setw(19)<<"PHONE NUMBER"<<endl;
			    cout<<"________________________________________________________________________________"<<endl;
			    cout<<endl;
			    while(f.read((char*)&d,sizeof(d)))
			    {
				if(f.eof())
				    break;
				d.display();

			    }

			    cout<<"\nPress any key to continue.";
			    getch();
			    f.close();
			    goto l;
			case 2:  f.open("doctor.dat",ios::in|ios::binary);
			    f.clear();
			    cout<<"\nLIST OF SPECIALITIES : \n";
			    while(f.read((char*)&d,sizeof(d)))
			    {
				if(f.eof())
				    break;

				cout<<d.ret_speciality()<<endl;
			    }

			    cout<<"\nEnter the speciality for which all doctor details are to be displayed : ";
			    gets(type);

			    f.close();
			    f.open("doctor.dat",ios::in|ios::binary);
			    f.seekg(0,ios::beg);
			    clrscr();
			    cout<<"\nALL DOCTORS OF "<<type<<" DEPARTMENT : \n";
			    cout<<"________________________________________________________________________________"<<endl;
			    cout<<setw(10)<<"ID"<<setw(15)<<"NAME"<<setw(20)<<"SPECIALITY"<<setw(12)<<"FEES"<<setw(19)<<"PHONE NUMBER"<<endl;
			    cout<<"________________________________________________________________________________"<<endl;
			    while(f.read((char*)&d,sizeof(d)))
			    {
				if(f.eof())
				    break;
				if(strcmp(d.ret_speciality(),type)==0)
				    d.display();

			    }
			    cout<<"\nPress any key to continue.  ";
			    getch();
			    f.close();
			    goto l;
			case 0:goto m;
			default:break;
		    }
		    case 2:p:
			clrscr();
			cout<<"\n\n\n\n\n\n";
			cout<<"\nROOM REPORTS --\n\n1.To display all rooms\n2.To display all rooms of a particular type\n3.To display all available/occupied rooms\nPress 0 to go back to the reports menu\n\nEnter your choice : ";
			cin>>opt;
			switch (opt)
		    {
			case 1: cout<<"\nROOM DETAILS OF ALL ROOMS IN THE HOSPITAL : \n";
			    cout<<"________________________________________________________________________________"<<endl;
			    cout<<setw(15)<<"ROOM NO"<<setw(18)<<"ROOM TYPE"<<setw(20)<<"ROOM STATUS"<<setw(22)<<"ROOM CHARGES"<<endl;
			    cout<<"________________________________________________________________________________"<<endl;
			    cout<<endl;
			    f.open("rooms.dat",ios::in|ios::binary);
			    f.clear();
			    f.seekg(0,ios::beg);
			    while(f.read((char*)&r,sizeof(r)))
			    {
				if(f.eof())
				    break;
				r.display();
			    }

			    cout<<"\nPress any key to continue.";
			    getch();
			    f.close();
			    goto p;
			case 2: f.open("rooms.dat",ios::in|ios::binary);
			    f.clear();
			    while(f.read((char*)&r,sizeof(r)))
			{
			    if(f.eof())
				break;

			    cout<<r.ret_type()<<endl;
			}
		    f.close();
			    cout<<"\nEnter the room type for which details of all rooms are to be displayed :";
			    gets(type);
			    cout<<"\nROOM DETAILS OF ALL "<<type<<" ROOMS IN THE HOSPITAL : \n";
			    cout<<"________________________________________________________________________________"<<endl;
			    cout<<setw(15)<<"ROOM NO"<<setw(18)<<"ROOM TYPE"<<setw(20)<<"ROOM STATUS"<<setw(22)<<"ROOM CHARGES"<<endl;
			    cout<<"________________________________________________________________________________"<<endl;cout<<endl;
			    f.open("rooms.dat",ios::in|ios::binary);
			    f.clear();
			    f.seekg(0,ios::beg);
			    while(f.read((char*)&r,sizeof(r)))
			    {
				if(f.eof())
				    break;
				if(strcmp(type,r.ret_type())==0)
				    r.display();
			    }
			    cout<<"\nPress any key to continue. ";
			    getch();
			    f.close();
			    goto p;
			case 3:  cout<<"press A to display all available rooms and N to display all occupied rooms(case sensitive) :  ";
			    cin>>ans;
			    cout<<"\nROOM DETAILS OF ALL "<<ans <<" ROOMS IN THE HOSPITAL : \n";
			    cout<<"________________________________________________________________________________"<<endl;
			    cout<<setw(15)<<"ROOM NO"<<setw(18)<<"ROOM TYPE"<<setw(20)<<"ROOM STATUS"<<setw(22)<<"ROOM CHARGES"<<endl;
			    cout<<"________________________________________________________________________________"<<endl;
			    cout<<endl;
			    f.open("rooms.dat",ios::in|ios::binary);
			    f.clear();
			    f.seekg(0,ios::beg);
			    while(f.read((char*)&r,sizeof(r)))
			    {
				if(f.eof())
				    break;
				if(ans==r.rstatus())
				    r.display();
			    }

			    cout<<"\nPress any key to continue.  ";
			    getch();
			    f.close();
			    goto p;
			case 0: goto m;
			default:break;
		    }
		    case 3:clrscr();
			cout<<"\n\n\n\n\n\n";
			cout<<"\nTEST REPORTS--: \n";
			cout<<"________________________________________________________________________________"<<endl;
			cout<<setw(20)<<"TEST NO"<<setw(25)<<"TEST TYPE"<<setw(18)<<"RATE"<<endl;
			cout<<"________________________________________________________________________________"<<endl;
			cout<<endl;

			f.open("test.dat",ios::in|ios::binary);
			f.clear();
			f.seekg(0,ios::beg);
			while(f.read((char*)&t,sizeof(t)))
			{
			    if(f.eof())
				break;
			    t.display();
			}
			cout<<"\nPress any key to continue.  ";
			getch();
			f.close();

			goto m;
		    case 4: q:
			clrscr();
			cout<<"\n\n\n\n\n\n";
			cout<<"\nPATIENT REPORTS-- \n\n1.To display all patient details\n2.To display patients based on illness\nPress 0 to go back to the reports menu\n\nEnter Your Choice : ";
			cin>>opt;
			switch(opt)
		    {

			case 1: cout<<"\nALL PATIENT DETAILS : \n";
			    cout<<"________________________________________________________________________________"<<endl;
			    cout<<setw(4)<<"ID"<<setw(7)<<"NAME"<<setw(10)<<"ILLNESS"<<setw(12)<<"BLOODGROUP"<<setw(14)<<"PHONE NUMBER"<<setw(16)<<"ADMISSIONDATE"<<setw(7)<<"ROOM"<<setw(8)<<"REFDOC"<<endl;
			    cout<<"________________________________________________________________________________"<<endl;
			    cout<<endl;
			    f.open("patient.dat",ios::in|ios::binary);
			    f.clear();
			    f.seekg(0,ios::beg);
			    while(f.read((char*)&p,sizeof(p)))
			    {
				if(f.eof())
				    break;
				p.display();
			    }

			    cout<<"\nPress any key to continue. ";
			    getch();
			    f.close();
			    goto q;
			case 2:f.open("patient.dat",ios::in|ios::binary);

			    f.clear();
			    while(f.read((char*)&p,sizeof(p)))
			{
			    if(f.eof())
				break;

			    cout<<p.ret_illness()<<endl;
			}
			    cout<<"\nEnter illness of the patients whose all details are to be displayed : ";
			    gets(type);
			    clrscr();
			    cout<<"\nALL PATIENT DETAILS  WITH "<<type<<" : \n";
			    cout<<"________________________________________________________________________________"<<endl;
			    cout<<setw(4)<<"ID"<<setw(7)<<"NAME"<<setw(10)<<"ILLNESS"<<setw(12)<<"BLOODGROUP"<<setw(14)<<"PHONE NUMBER"<<setw(16)<<"ADMISSIONDATE"<<setw(7)<<"ROOM"<<setw(8)<<"REFDOC"<<endl;
			    cout<<"________________________________________________________________________________"<<endl;
			    cout<<endl;
			    f.close();
			    f.open("patient.dat",ios::in|ios::binary);
		    f.clear();
			    //f.seekg(0,ios::beg);
			    while(f.read((char*)&p,sizeof(p)))
			    {
				if(f.eof())
				    break;
				if(strcmp(type,p.ret_illness())==0)
				    p.display();
			    }
			    cout<<"\nPress any key to continue.";
			    getch();
			    f.close();
			    goto q;
			case 0: goto m;
			default:break;
		    }
		    case 5:
			i='n';
			clrscr();
			f.open("patient.dat",ios::in|ios::binary);
			cout<<"\n\n\n\n\n\n";
			cout<<"\nBILL GENERATION --\n";
			cout<<"\nLIST OF PATIENTS : \n";


			while(f.read((char*)&p,sizeof(p)))
			{

			    if(f.eof())
				break;

			    cout<<p.ret_pid()<<"\t"<<p.ret_name()<<endl;
			}
			cout<<"Enter the patient id of the patient getting discharged : ";
			cin>>id;

			f.clear();
			f.seekg(0,ios::beg);
			while(f.read((char*)&p,sizeof(p)))
			{
			    if(f.eof())
				break;
			    if(id==p.ret_pid())
			    {  i='y';
				pos=f.tellg();
				break;
			    }
			}
			if(i=='n')
			{
			    cout<<"\nRecord not found";
			    break;
			}

		    e:
			cout<<"\nEnter date of discharge of the patient : ";
			gets(date);
			if(dateval(date)!=1)
			{
			    cout<<"\nInvalid date.";
			    goto e;
			}
			else
			{
			    f.seekg(pos-sizeof(p));
			    fs.open("rooms.dat",ios::binary);
			    fs.seekg(pos-sizeof(p));
			    p.dod(date);
			    strcpy(dte,p.doa());
			    g=p.no_of_days(dte,date);
                            
                        }
                        total=0;
                        flag=0;
                    tp:
                        cout<<"\nAny tests done by the patients (y/n) : ";
                        cin>>ans;
                        
                        if(ans=='y'||ans=='Y')
                        {
                            fo.open("test.dat",ios::out|ios::in|ios::binary);
                            fo.clear();
                            fo.seekg(0,ios::beg);
                            cout<<"\nLIST OF TESTS : \n";
                            fo.read((char*)&t,sizeof(t));
                            while(!fo.eof())
                            {
                                cout<<t.ret_tid()<<"\t"<<t.ret_type() <<endl;
                                fo.read((char*)&t,sizeof(t));
                                
                                
                            }
                            cout<<"\nEnter test id : ";
                            cin>>testid;
                            fo.close();
                            
                            fo.open("test.dat",ios::out|ios::in|ios::binary);
                            fo.clear();
                            fo.seekg(0,ios::beg);
                            fo.read((char*)&t,sizeof(t));
                            while(!fo.eof())
                            {
                                pos=fo.tellg();
                           
                                if(testid==t.ret_tid())
                                {
                                    total+=t.ret_cost();
                                    flag=1;
                                }
                                fo.read((char*)&t,sizeof(t));
                                
                                
                                
                            }
                            if(flag!=1)
                                cout<<"\nInvalid Input : ";
                            goto tp;
                        }
                        
			  clrscr();
                        
                        
                        cout<<"\n________________________________________________________________________________"<<endl;
                        cout<<"                                                                             "<<endl;
                        cout<<"  \t\tBill Number :"<<"B"<< f.tellg()<<"                                             "<<endl;
                        cout<<"  \t\tPatient Name :"<<p.ret_name()<<"                                            "<<endl;
                        cout<<"\t\tNo of days in between the two dates : "<<g<<"                   "<<endl;
                        cout<<"\t\tRoom Charges : "<<p.ret_rfees()<<"                                          "<<endl;
                        cout<<"\t\tDoctor Name: "<<p.ret_docname()<<"                                       "<<endl;
                        cout<<"\t\tDoctor fees : "<<p.ret_fees()<<"                                         "<<endl;
                        cout<<"\t\tTest charges : "<<total<<"                                              "<<endl;
                        cout<<"\t\tTax : 5%"<<"                                                  "<<endl;
			cout<<"\t\tTotal Bill Amount : Rs."<<(r.ret_cost()*g*1.0)+ p.ret_fees()+total+ 0.05*((r.ret_cost()*g*1.0)+ p.ret_fees()+total)<<"                                    "<<endl;
                        cout<<"\t\tTHANK YOU!                                                    "<<endl;
                        cout<<"________________________________________________________________________________"<<endl;
                        fo.close();
                        fs.close();
                        f.close();
                        cout<<"\nPress any key to continue.";
                        getch();
                        goto m;
                }
            }while(cho!=0);
        }
    }while(choice!=0);
    
}
