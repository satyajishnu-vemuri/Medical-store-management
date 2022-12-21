//final code
#include<iostream>
#include<string.h>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
using namespace std;
fstream file;
fstream temp;
class customer;
class medicine
{   string name;
    string date;
    int quantity;
    float price;
    public:
    medicine()
    { }
    medicine(string n,int q,string d,float p)
    {
        name=n;
        quantity=q;
        date=d;
        price=p;
    }
    void addmedicine();
    void deletemedicine();
    int display();
    void friend billing(medicine,customer);
    void update_bill(string,int);
    void update(string,int);
    void get()
    {   cout<<"Enter the details:"<<endl;
        cout<<"Name:";
        cin>>name;
        cout<<"Quantity:";
        cin>>quantity;
        cout<<"Expiry date:";
        cin>>date;
        cout<<"Price:";
        cin>>price;
    };
};
void medicine:: addmedicine()
{  file.open("MEDICINES",ios::app);
   if(file)
   { 
     file<<name<<" "<<quantity<<" "<<date<<" "<<price<<endl;
     cout<<"Medicine added successfully"<<endl;
   }
   else{
    cout<<"Error in opening file"<<endl;
   }
   file.close();   
} 
void medicine :: deletemedicine()
{   string search,input;
    display();
    cout<<"Enter the medicine name: ";
    cin>>search;
    file.open("MEDICINES",ios::in);
    temp.open("TEMP",ios::app);
   if(file)
   { 
       while(!file.eof())
      { getline(file,input);
        if(input.empty())
        {
          continue;
        }
        if(input.find(search)==string::npos)
        {  temp<<input<<endl;
        }
      }
      temp.close();
      file.close();
      remove("MEDICINES");
      rename("TEMP","MEDICINES");  
      cout<<"Medicine deleted successfullly"<<endl;       
   }
   
   else
    { cout<<"file for input not open"<<endl;
    }      
}
int medicine :: display()
{
    string data;
    file.open("MEDICINES",ios::in);
    if(!file)
    {
        cout<<"Error occurred"<<endl;
        return 0;
    }
    cout<<"MEDICINES:"<<endl;
    while(file.eof()==0)
    {   getline(file,data);
        cout<<data<<endl;
    }
    file.close();
    return 0;
}
void medicine:: update_bill(string name,int quantity)
{  string input,line;
   string n,d;
   int q=0;
   float p;
   int original=0;
   file.open("MEDICINES",ios::in);
   temp.open("TEMP",ios::app);
   if(file)
   {
      while(!file.eof())
      { getline(file,input);
        if(input.empty())
        {
          continue;
        }
        if(input.find(name)==string::npos)
        {  temp<<input<<endl;
        }
        else
        { stringstream ss(input);
            ss>>n>>q>>d>>p;
            {q-=quantity;
            temp<<n<<" "<<q<<" "<<d<<" "<<p<<" "<<endl;
            }
        }
      }
      temp.close();
      file.close();
      remove("MEDICINES");
      rename("TEMP","MEDICINES"); 
      return ;          
   }
   else{
        cout<<"file for input not open"<<endl;
    }
}
float readprice(string name)
{ string input,line;
  file.open("MEDICINES",ios::in);
  if(file)
  {
    while(!file.eof())
    {
        getline(file,input);
        if(input.find(name)==string::npos)
        {
            continue;
        }
        else
        {   stringstream ss(input);
            string n,d;
            int q;
            float p;
            ss>>n>>q>>d>>p;
            file.close();
            return p;
        }
    }
  } 
  else{
        cout<<"file for input not open"<<endl;
    }
    
}
void medicine:: update(string med_name,int new_q)
{  string input,n,d;
   int q;
   float p;
   file.open("MEDICINES",ios::in);
   temp.open("TEMP",ios::app);
   if(file)
   {
      while(!file.eof())
      { getline(file,input);
       if(input.empty())
        {
          continue;
        }
        if(input.find(med_name)==string::npos)
        {  temp<<input<<endl;
        }
        else
        { stringstream ss(input);
            ss>>n>>q>>d>>p;
            q=new_q;
            temp<<n<<" "<<q<<" "<<d<<" "<<p<<" "<<endl;
        }
      }
      temp.close();
      file.close();
      remove("MEDICINES");
      rename("TEMP","MEDICINES");
      cout<<"Medicine quantity updated successfullly"<<endl;       
    }
    else{
        cout<<"file for input not open"<<endl;
        }
}
class customer
{  string name;
   string phone;
   string purchase_date;
   public:
   void get();  
   void display();   
   void friend billing(medicine,customer);
   void sale(string,int,float);
};
void customer::get()
 {      cout<<"Enter the date:";
        cin>>purchase_date;
        cout<<"Enter the customer details:"<<endl;
        cout<<"Name:";
        cin>>name;
        cout<<"Phone Number:";
        cin>>phone;
        file.open("CUSTOMER INFO",ios::app);
        if(!file)
       {  cout<<"\n Error occurred"<<endl;
        return ;}
        else
        {file<<name<<" "<<phone<<endl; 
        file.close();}         
   }
void customer:: display()
{ string data;
      file.open("CUSTOMER INFO",ios::in);
      if(!file)
       {  cout<<"\n Error occurred"<<endl;
        return;}
        else
        {
            while(file.eof()==0)
            {
                getline(file,data);
                cout<<data<<endl;
            }
        }  file.close();    
}
void customer :: sale(string med_name,int quantity,float price)
{
    file.open("SALE",ios::app);
    if(file)
    { file<<purchase_date<<" "<<med_name<<" "<<quantity<<" "<<price<<endl;
      file.close();
    }
    else{
        cout<<"Error in opening file"<<endl;
    }
}
void billing(medicine m, customer c)
{  c.get();
   int i;
   string option;
   float total=0,p=0;
   cout<<"Enter the items:"<<endl;
   do {
    cout<<"Name:";
    cin>>m.name;
    cout<<"Quantity:";
    cin>>m.quantity;
    m.update_bill(m.name,m.quantity);
    cout<<"Price:";
    p=readprice(m.name);
    cout<<p;
    cout<<endl;
    total+=p*m.quantity;
    c.sale(m.name,m.quantity,p*m.quantity);
    cout<<"Do you want to add another medicine(enter Y or N):";
    cin>>option;
   }while(option!="N");
   
   cout<<"Total:"<<total<<endl;
   cout<<"************************************************************************************************"<<endl;
}
class supplier
{  string date;
   string sname;
   string email;
   string phone;
   vector <string> medicines;
   vector<int> quantities;
   vector<float> prices;
   vector<string>exdate;
   float total;
   int number_med;
   public:
   void calculatetotal();   
   void printbill();
   void update_supply(string,int,float,string);
   void get();   
   void supplier_info();   
   void display_supplier_info(); 
   void display_bills();  
};
void supplier :: calculatetotal()
{   int i;
    total=0;
     for(i=0;i<number_med;i++)
     {total= total+ prices[i]*quantities[i]; }
}
void supplier :: printbill()
{ int i;
     file.open("SUPPLIER BILLS",ios::app);
     if(file)
     {
     file<<date<<endl;
     file<<sname<<endl;
     for(i=0;i<number_med;i++)
     {
        file<<medicines[i]<<" "<<quantities[i]<<" "<<exdate[i]<<" Rs"<<prices[i]<<endl;        
     }
     file<<"-------------------------------------------------------------------"<<endl;
     calculatetotal();
     file<<"Total: Rs"<<total<<endl;
     file<<"-------------------------------------------------------------------"<<endl;
     file.close();
     }
     else
     cout<<"Error in openeing file"<<endl;
}
void supplier:: update_supply(string med_name,int new_q, float new_p,string date)
{string input,n,d;
   int q;
   string check="NF";
   float p;
   file.open("MEDICINES",ios::in);
   temp.open("TEMP",ios::app);
   if(file)
   {
      while(!file.eof())
      { getline(file,input);
        if(input.empty())
        {
          continue;
        }
        if(input.find(med_name)==string::npos)
        {  temp<<input<<endl;
        }
        else if(input.find(med_name)!=string::npos)
        { stringstream ss(input);
            ss>>n>>q>>d>>p;
            q+=new_q;
            p=new_p+1;
            temp<<n<<" "<<q<<" "<<d<<","<<date<<" "<<p<<" "<<endl;
            cout<<"Medicine quantity updated successfullly"<<endl;  
            check="F";
        }
      }
      temp.close();
      file.close();
      remove("MEDICINES");
      rename("TEMP","MEDICINES");
      if(check=="NF")
      { medicine m1(med_name,new_q,date,new_p+1);
        m1.addmedicine();
      }
           
    }
    else{
        cout<<"file for input not open"<<endl;
        }
}
void supplier:: get()
{ int i;
    string name;
    int quantity;
    float price;
    string date;
    cout<<"Enter the date:";
    cin>>date;
    cout<<"Enter the supplier's name:";
    cin>>sname;
    cout<<"Enter the number of different types of medicines being supplied:";
    cin>>number_med;
    for(i=0;i<number_med;i++)
    {  cout<<"Enter medicine name:";
        cin>>name;
        medicines.push_back(name);
        cout<<"Enter the quantity:";
        cin>>quantity;
        quantities.push_back(quantity);
        cout<<"Enter the price:";
        cin>>price;
        prices.push_back(price);
        cout<<"Enter the expiry date:";
        cin>>date;
        exdate.push_back(date);
        update_supply(name,quantity,price,date);
    }
     printbill();
     cout<<"TOTAL: Rs"<<total<<endl; 
   } 
void supplier:: display_bills()
{  string input;
    file.open("SUPPLIER BILLS",ios::in);
    if(file)
    {
        while(file.eof()==0)
        {   getline(file,input);
            cout<<input<<endl;
        }file.close();
    }
    else
    cout<<"Error in opening file"<<endl;
}
void supplier :: supplier_info()
{file.open("SUPPLIER INFO",ios::app);
     cout<<"Enter supplier details:"<<endl;
     cout<<"Name:";
     cin>>sname;
     cout<<"Phone number:";
     cin>>phone;
     cout<<"Email id:";
     cin>>email;
     if(file)
     {
     file<<sname<<endl;
     file<<phone<<endl;
     file<<email<<endl;
     file<<".............................................................................................."<<endl;
     file.close();
     cout<<"Supplier information added successfully"<<endl;
     }
     else
     cout<<"Error in opening file"<<endl;
}
void supplier:: display_supplier_info()
{ string input;
      file.open("SUPPLIER INFO",ios::in);
      if(file)
      {
        while(file.eof()==0)
        {   getline(file,input);
            cout<<input<<endl;
        }
        file.close();
      }
      else
      cout<<"Error in opening file"<<endl;
}
void print_sale(string date)
{ string input,n,d;
  int q;
  float p,total=0;
    file.open("SALE",ios::in);
    if(file)
    { while(!file.eof())
      {
        getline(file,input);
        if(input.find(date)==string::npos)
        {
            continue;
        }
        else
        {  stringstream ss(input);
           ss>>d>>n>>q>>p;
            cout<<n<<" "<<q<<" Rs"<<p<<endl;
            total+=p;
        }
      }
      cout<<"Total: Rs"<<total<<endl;
      file.close();
    }
    else
    {
        cout<<"Error in opening file"<<endl;
    }
}
int main()
{ int choice,quantity,option;
  string name;
  do
  {
    cout<<"MAIN MENU:"<<endl;
    cout<<"1.MEDICINE STOCK MANAGEMENT"<<endl;
    cout<<"2.CUSTOMER INFORMATION AND BILLING SYSTEM"<<endl;
    cout<<"3.SALE AND SUPPLIER MANAGEMENT"<<endl;
    cout<<"4.EXIT"<<endl;
    cout<<"Enter your choice:";
    cin>>choice;
    cout<<"------------------------------------------------------------------------------------------------"<<endl;
    string date;
    medicine m;
    customer c;
    supplier s;
    switch(choice)
    {
        case 1: do
                  { cout<<"************************************************************************************************"<<endl;
                    cout<<"SUB MENU:"<<endl;
                    cout<<"1.Add a medicine"<<endl;
                    cout<<"2.Delete a medicine"<<endl;
                    cout<<"3.Update a medicine quantity"<<endl;
                    cout<<"4.Display all medicines"<<endl;
                    cout<<"5.Exit to main menu"<<endl;
                    cout<<"Enter your choice:";
                    cin>>choice;
                    cout<<"------------------------------------------------------------------------------------------------"<<endl;
                    switch(choice)
                    {   case 1: m.get();
                                m.addmedicine();
                                break;
                        case 2: m.deletemedicine();
                                break;
                        case 3: cout<<"Enter the medicine name:";
                                cin>>name;
                                cout<<"Quantity:";
                                cin>>quantity;
                                cout<<endl;
                                m.update(name,quantity);
                                break;
                        case 4: m.display();
                                break;

                        case 5: continue;
                                
                        default: cout<<"Enter a valid choice"<<endl;
                                break;
                    }     
                  }while(choice!=5);
                  break;
        case 2:   do
                    { cout<<"************************************************************************************************"<<endl;
                    cout<<"SUB MENU:"<<endl;
                    cout<<"1.Customer information"<<endl;
                    cout<<"2.Billing"<<endl;
                    cout<<"3.Exit to main menu"<<endl;
                    cout<<"Enter your choice:";
                    cin>>choice;
                    cout<<"------------------------------------------------------------------------------------------------"<<endl;
                    switch(choice)
                    {   case 1: c.display();
                                break;
                        case 2: billing(m,c);
                                break;
                        case 3: continue;
                        default: cout<<"Enter a valid choice"<<endl;
                                 break;                        
                    }
                     }while(choice!=3);
                    break;
        case 3:     do
                    {cout<<"************************************************************************************************"<<endl;
                     cout<<"SUB MENU:"<<endl;
                     cout<<"1.Supplier information"<<endl;
                     cout<<"2.Add stock"<<endl;
                     cout<<"3.Display supply bills"<<endl;
                     cout<<"4.Sales of the shop"<<endl;
                     cout<<"5.Exit to main menu"<<endl;
                     cout<<"Enter your choice:";
                     cin>>choice;
                     cout<<"------------------------------------------------------------------------------------------------"<<endl;
                     switch(choice)
                    {   case 1: do
                                {cout<<"************************************************************************************************"<<endl;
                                cout<<"SUB MENU:"<<endl;
                                cout<<"1.Add supplier information"<<endl;
                                cout<<"2.Display supplier information"<<endl;
                                cout<<"3.Exit to sub menu"<<endl;
                                cout<<"Enter your choice:";
                                cin>>option;
                                cout<<"------------------------------------------------------------------------------------------------"<<endl;
                                switch(option)
                                {
                                    case 1: s.supplier_info();
                                            break;
                                    case 2: s.display_supplier_info();
                                            break;
                                    case 3:continue;
                                    default:cout<<"Enter a valid choice"<<endl;
                                            break; 
                                }
                                }while(option!=3);
                                break;
                        case 2: s.get();
                                break;
                        case 3: s.display_bills();
                                break;
                        case 4: cout<<"Enter a date:";
                                cin>>date;
                                print_sale(date);
                                break;

                        case 5: continue;
                                
                        default: cout<<"Enter a valid choice"<<endl;
                                break;
                    } 
                    }while(choice!=5);
                    break;
        case 4: exit(1);
                break;
        default:cout<<"Enter a valid choice"<<endl;
                break;
                  
    }    
}while(choice!=4);
return 0;
}
