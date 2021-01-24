#include<bits/stdc++.h>
#define NULL_VALUE -99999
#define PRIMENUM 709

using namespace std;

string generate()
{
    string letters = "abcdefghijklmnopqrstuvwxyz";
    int randNum;
    string str;
    for (int j = 0; j < 7; j++)
    {
        randNum = rand() % 26;
        str += letters[randNum];
    }
    return str;
}

class ListNode
{
public:
    string item;
    ListNode * next;
};

class LinkedList
{

    ListNode * list;
    int length;

public:
    LinkedList()
    {
        list=0;
        length=0;
    }

    int getLength()
    {
        return length;
    }

    void insertItem(string item)
    {
        ListNode * newNode = new ListNode() ;
        newNode->item = item ;
        newNode->next = list ;
        list = newNode ;
        length++;
    }

    void deleteItem(string item)
    {
        ListNode *temp, *prev ;
        temp = list ;
        while (temp != 0)
        {
            if (temp->item.compare(item)==0)
                break ;
            prev = temp;
            temp = temp->next ;
        }
        if (temp == 0)
            return ;
        if (temp == list)
        {
            list = list->next ;
            length--;
        }
        else
        {
            prev->next = temp->next ;
            length--;
        }
    }
    string  getItemAt(int pos)
    {
        string s;
        if(pos>length)
        {
            printf("\n\tInvalid input!!!\n");
        }
        else
        {
            ListNode *current = new ListNode();
            current=list;
            int counter=0;
            while(counter!=NULL_VALUE)
            {
                if(counter==pos)
                {
                    s=current->item;
                    return s;
                }
                counter++;
                current=current->next;
            }
        }
    }
    ListNode * searchItem(string item)
    {
        ListNode * temp ;
        temp = list ;
        while (temp != 0)
        {
            if (temp->item.compare(item)==0)
                return temp ;
            temp = temp->next ;
        }
        return 0 ;
    }
    int countItem(string item)
    {
        int counter=1;
        ListNode * temp ;
        temp = list ;
        while (temp != 0)
        {
            if (temp->item.compare(item)==0)
                break;
            temp = temp->next ;
            counter++;
        }
        return counter ;
    }
    ~LinkedList()
    {
        ListNode *temp,*temp2;
        temp=list;
        while(temp!=0)
        {
            temp2=temp->next;
            delete temp;
            temp=new ListNode();
            temp=temp2;
        }
    }
};

class data_string
{
public:
    string word;
    int hash_index;
    int value;
    data_string(string word,int value)
    {
        this->word = word;
        this->value =value;
    }
    data_string()
    {

    }
    void setword(string s)
    {
        word = s;
    }
    string getword()
    {
        return word;
    }
    void sethash_index(int h_idx)
    {
        hash_index = h_idx;
    }
    int gethash_index()
    {
        return hash_index;
    }
    void setvalue(int v)
    {
        value = v;
    }
    int getvalue()
    {
        return value;
    }
};
class chaining
{
    LinkedList *l;
    int size;
    int length=0;
    int count = 0;
    data_string *str;
public:
    chaining(int size)
    {
        this->size = size;
        l = new LinkedList[size];
        str = new data_string[10000];
    }
    int hash1(string s1)
    {
        long long value = 0;
        for(int j=0; j<7; j++)
        {
            value = value + s1.at(j)*pow(31,j);
        }
        int idx = int(value % size);
        return idx;
    }
    int hash2(string s2)
    {
        long long value = 0;
        for(int i=0; i<7; i++)
        {
            value = value + pow(s2.at(i),2);
        }
        int idx = int(size - (value%size));
        return idx;
    }
    bool search_hash1(string s)
    {
        int idx = hash1(s);
        ListNode *ln=new ListNode();
        ln=l[idx].searchItem(s);
        if(ln == NULL)
            return false;
        else
            return true;
    }
    bool search_hash2(string s)
    {
        int idx = hash2(s);
        ListNode *ln=new ListNode();
        ln=l[idx].searchItem(s);
        if(ln == NULL)
            return false;
        else
            return true;
    }
    void insert_hash1()
    {
        string s = generate();
        cout<<s<<endl;
        if(search_hash1(s))
        {
            return;
        }
        else
        {
            int index = hash1(s);
            l[index].insertItem(s);
            str[count].setword(s);
            str[count].setvalue(length+1);
            count++;
            length++;
        }
    }

    void insert_hash2()
    {
        string s = generate();
        if(search_hash2(s))
        {
            return;
        }
        else
        {
            int index = hash2(s);
            l[index].insertItem(s);
            str[count].setword(s);
            str[count].setvalue(length +1);
            count++;
            length++;
        }
    }
    void delete_hash1(string s)
    {
        if(!search_hash1(s))
            return;
        else
        {
            int idx = hash1(s);
            l[idx].deleteItem(s);
        }
    }
    void delete_hash2(string s)
    {
        if(!search_hash2(s))
            return;
        else
        {
            int idx = hash2(s);
            l[idx].deleteItem(s);
        }
    }
    double  avg_Hit()
    {
        long long value=0;
        for(int i=0; i<10000; i++)
        {
            string s=str[i].word;
            int  index=str[i].hash_index;
            value=value+l[index].countItem(s);
        }
        double output=double(value*1.0/10000);
        return output;
    }
    long long countCollision_chaining()
    {
        long long sum=0,counter=0;
        for(int i=0; i<size; i++)
        {
            if(l[i].getLength()!=0)
            {
                sum=sum+l[i].getLength();
                counter++;
            }
        }
        return (sum-counter);
    }

    void print_chain()
    {
        for(int i=0; i<size; i++)
        {
            for(int j=0; j<l[i].getLength(); j++)
            {
                string s=l[i].getItemAt(j);
                cout<<s<<endl;
            }
        }
    }
};
class double_hashing
{
    string *s;
    int len=0,counter=0;
    int size;
    data_string *ds;
    long long c_collision = 0;
    int *checkdlt;
    long long c_avghit = 0;
public:
    double_hashing(int m)
    {
        size = 2*m;
        s = new string[size];
        ds = new data_string[size];
        checkdlt = new int[size];
        for(int i=0; i<size; i++)
        {
            checkdlt[i] = -1;
        }
        for(int j = 0; j<size; j++)
        {
            s[j]="$";
        }
    }
    int aux_hash(string s_aux)
    {
        long long value =0;
        for(int i=0; i<6; i++)
        {
            value = value + s_aux.at(i)*s_aux.at(i+1);
        }
        int idx = int (PRIMENUM-value%PRIMENUM);
        return idx;
    }
    int hash1(string s1)
    {
        long long value = 0;
        for(int j=0; j<7; j++)
        {
            value = value + s1.at(j)*pow(31,j);
        }
        int idx = int(value % size);
        return idx;
    }
    int hash2(string s2)
    {
        long long value = 0;
        for(int i=0; i<7; i++)
        {
            value = value + pow(s2.at(i),2);
        }
        int idx = int(size - (value%size));
        return idx;
    }
    int db_hash1(string s_db1,int i)
    {
        int idx = ((hash1(s_db1))+(i*aux_hash(s_db1)))%size;
        return idx;
    }
    int db_hash2(string s_db2,int i)
    {
        int idx = ((hash2(s_db2))+(i*aux_hash(s_db2)))%size;
        return idx;
    }
    bool search_db1(string str)
    {
        int  count=0,i=0;
        while(count<=size)
        {
            int idx=db_hash1(str,i);
            if(checkdlt[idx]==1)
            {
                return false;
            }
            else
            {
                if(s[idx].compare(str)==0)
                    return true;
            }
            i++;
            count++;
        }
        return false;
    }
    void insert_db1()
    {
        string str=generate();
        if(search_db1(str))
            return;
        else
        {
            int counter=0,i=0;
            while(i<=size)
            {
                int idx=db_hash1(str,i);
                if(s[idx].compare("$")!=0)
                {
                    s[idx]=str;
                    ds[counter].word=str;
                    ds[counter].value=len+1;
                    ds[counter].hash_index=idx;
                    checkdlt[idx]=-1;
                    len++;
                    counter++;
                    return;
                }
                i++;
                c_collision++;
            }
        }
    }
    void delete_db1(string str)
    {
        int counter=0,i=0;
        while(i<=size)
        {
            int index=db_hash1(str,i);
            if(s[index].compare(str)==0)
            {
                s[index]="$";
                checkdlt[index]=1;
                return;
            }
            else
            {
                i++;
            }
        }
    }
    bool search_db2(string str)
    {
        int  count=0;
        int i = 0;
        while(counter<=size)
        {
            int idx=db_hash2(str,i);
            if(checkdlt[idx]==1)
            {
                return false;
            }
            else
            {
                if(s[idx].compare(str)==0)
                    return true;
            }
            i++;
            count++;
        }
        return false;
    }
    void insert_db2()
    {
        string str=generate();
        if(search_db2(str))
            return;
        else
        {
            int counter=0,i=0;
            while(i<=size)
            {
                int idx=db_hash2(str,i);
                if(s[idx].compare("$")==0)
                {
                    s[idx]=str;
                    ds[counter].word=str;
                    ds[counter].value=len+1;
                    ds[counter].hash_index=idx;
                    checkdlt[idx]=-1;
                    len++;
                    counter++;
                    return;
                }
                i++;
                c_collision++;
            }
        }
    }
    void delete_db2(string str)
    {
        int counter=0,i=0;
        while(i<=size)
        {
            int index=db_hash2(str,i);
            if(s[index].compare(str)==0)
            {
                s[index]="$";
                checkdlt[index]=1;
                return;
            }
            else
            {
                i++;
            }
        }
    }
    void averagehit1()
    {
        for(int p=0; p<10000; p++)
        {
            string str=ds[p].word;
            int  counter=0,i=0;
            while(counter<=size)
            {
                int index=db_hash1(str,i);
                if(s[index].compare(str)==0)
                {
                    break;
                }
                i++;
                counter++;
                c_avghit++;
            }
        }
    }
    void averagehit2()
    {
        for(int p=0; p<10000; p++)
        {
            string str=ds[p].word;
            int  counter=0,i=0;
            while(counter<=size)
            {
                int index=db_hash2(str,i);
                if(s[index].compare(str)==0)
                {
                    break;
                }
                i++;
                counter++;
                c_avghit++;
            }
        }
    }
    double avghit()
    {
        return (c_avghit*1.0)/10000;
    }
    long long getcollision()
    {
        return c_collision;
    }
    void print_dbhash()
    {
        for(int  i=0; i<10; i++)
        {
            if(s[ds[i].hash_index]!="$")
                cout<<ds[i].word<<ds[i].hash_index<<ds[i].value<<endl;
        }
    }
};
    class customhashing
    {
        string *str;
        int size;
        int length=0;
        data_string *sd;
        int  c=0;
        int *checkdeletion;
        long long countavghit=0;
    public:
        customhashing(int n)
        {
            size=2*n;
            str=new  string[size];
            sd=new data_string[size];
            checkdeletion=new int[size];
            for(int i=0; i<size; i++)
            {
                checkdeletion[i]=-1;
            }
            for(int i=0; i<size; i++)
            {
                str[i]="s";
            }
        }
        int hash1(string s1)
        {
            long long value = 0;
            for(int j=0; j<7; j++)
            {
                value = value + s1.at(j)*pow(31,j);
            }
            int idx = int(value % size);
            return idx;
        }
        int hash2(string s2)
        {
            long long value = 0;
            for(int i=0; i<7; i++)
            {
                value = value + pow(s2.at(i),2);
            }
            int idx = int(size - (value%size));
            return idx;
        }
        int aux_hash(string s_aux)
        {
            long long value =0;
            for(int i=0; i<6; i++)
            {
                value = value + s_aux.at(i)*s_aux.at(i+1);
            }
            int idx = int (PRIMENUM-value%PRIMENUM);
            return idx;
        }
        int  customhashFunc1(string word,int i)
        {
            long long s=(hash1(word)+(701*i*aux_hash(word))+(709*i*i));
            int index=s%size;
            return index;
        }

        int customhashFunc2(string word,int i)
        {
            int index=(hash2(word)+(701*i*aux_hash(word))+(709*i*i))%size;
            return index;
        }
        bool search_chash1(string word)
        {
            int  counter=0,i=0;
            while(counter<=size)
            {
                int index=customhashFunc1(word,i);
                if(checkdeletion[i]==1)
                {
                    return false;
                }
                else
                {
                    if(str[index].compare(word)==0)
                        return true;
                }
                i++;
                counter++;
            }
            return false;
        }
        void insert_chash1()
        {
            string s=generate();
            int counter=0,i=0;
            while(i<=size)
            {
                int index=customhashFunc1(s,i);
                if(str[index].compare("s")==0)
                {
                    str[index]=s;
                    sd[c].word=s;
                    sd[c].value=length+1;
                    sd[c].hash_index=index;
                    checkdeletion[index]=-1;
                    length++;
                    c++;
                    return;
                }
                i++;
            }
        }
        void delete_chash1(string word)
        {
            int counter=0,i=0;
            while(i<=size)
            {
                int index=customhashFunc1(word,i);
                if(str[index].compare(word)==0)
                {
                    str[index]="s";
                    checkdeletion[index]=1;
                    return;
                }
                else
                {
                    i++;
                }
            }
        }
        bool search_chash2(string word)
        {
            int  counter=0,i=0;
            while(counter<=size)
            {
                int index=customhashFunc2(word,i);
                if(checkdeletion[i]==1)
                {
                    return false;
                }
                else
                {
                    if(str[index].compare(word)==0)
                        return true;
                }
                i++;
                counter++;
            }
            return false;
        }
        void insert_chash2()
        {
            string s=generate();
            int counter=0,i=0;
            while(i<=size)
            {
                int index=customhashFunc2(s,i);
                if(str[index].compare("s")==0)
                {
                    str[index]=s;
                    sd[c].word=s;
                    sd[c].value=length+1;
                    sd[c].hash_index=index;
                    checkdeletion[index]=-1;
                    length++;
                    c++;
                    return;
                }
                i++;
            }
        }
        void delete_chash2(string word)
        {
            int counter=0,i=0;
            while(i<=size)
            {
                int index=customhashFunc2(word,i);
                if(str[index].compare(word)==0)
                {
                    str[index]="s";
                    checkdeletion[index]=1;
                    return;
                }
                else
                {
                    i++;
                }
            }
        }
        void averagehit1()
        {
            for(int p=0; p<10000; p++)
            {
                string s=sd[p].word;
                int  counter=0,i=0;
                while(counter<=size)
                {
                    int index=customhashFunc1(s,i);
                    if(str[index].compare(s)==0)
                    {
                        break;
                    }
                    i++;
                    counter++;
                    countavghit++;
                }
            }
        }
        void averagehit2()
        {
            for(int p=0; p<10000; p++)
            {
                string s=sd[p].word;
                int  counter=0,i=0;
                while(counter<=size)
                {
                    int index=customhashFunc2(s,i);
                    if(str[index].compare(s)==0)
                    {
                        break;
                    }
                    i++;
                    counter++;
                    countavghit++;
                }
            }
        }
        double avghit()
        {
            return (countavghit*1.0)/10000;
        }
        void print_chash()
        {
            for(int  i=0; i<length; i++)
            {
                if(str[sd[i].hash_index]!="s")
                    cout<<sd[i].word<<" "<<sd[i].value<<" "<<sd[i].hash_index<<endl;
            }
        }
};
    int main()
    {
        ios::sync_with_stdio(false);
        int size;
        cout<<"enter size: "<<endl;
        cin>>size;
        customhashing c(size);
        int in;
        while(1)
        {
            cout<<"1.Chaining 2.Chaining with 2nd function 3.Double Hashing"<<endl;
            cout<<" 4.Double Hashing with 2nd function 5.Custom hashing 6.Custom hashing with 2nd function"<<endl;
            cin>>in;
            if(in==1)
            {
                chaining c(size);
                for(int i=0; i<10000; i++)
                {
                    c.insert_hash1();
                }
                c.print_chain();
                cout<<"search item"<<endl;
                string n;
                cin>>n;
                cout<<c.search_hash1(n)<<endl;
                cout<<c.countCollision_chaining()<<endl;
                cout<<c.avg_Hit()<<endl;
            }
            else if(in==2)
            {
                chaining c(size);
                for(int i=0; i<10000; i++)
                {
                    c.insert_hash2();
                }
                c.print_chain();
                cout<<"search item"<<endl;
                string n;
                cin>>n;
                cout<<c.search_hash2(n)<<endl;
                cout<<c.countCollision_chaining()<<endl;
                cout<<c.avg_Hit()<<endl;
            }
            else if(in==3)
            {
                double_hashing c(size);
                for(int i=0; i<10; i++)
                {
                    c.insert_db1();
                }
                c.print_dbhash();
                cout<<c.getcollision()<<endl;
                cout<<"search item"<<endl;
                string n;
                cin>>n;
                cout<<c.search_db1(n)<<endl;
                c.averagehit1();
                cout<<c.getcollision()<<endl;
                cout<<c.avghit()<<endl;
            }
            else if(in==4)
            {
                double_hashing c(size);
                for(int i=0; i<10000; i++)
                {
                    c.insert_db2();
                }
                c.print_dbhash();
                cout<<c.getcollision()<<endl;
                cout<<"search item"<<endl;
                string n;
                cin>>n;
                cout<<c.search_db2(n)<<endl;
                c.averagehit2();
                cout<<c.avghit()<<endl;
            }
            else if(in==5)
            {
                customhashing c(size);
                for(int i=0; i<10000; i++)
                {
                    c.insert_chash1();
                }
                c.print_chash();
                cout<<"search item"<<endl;
                string n;
                cin>>n;
                cout<<c.search_chash1(n)<<endl;
                c.averagehit1();
                cout<<c.avghit()<<endl;
            }
            else if(in==6)
            {
                customhashing c(size);
                for(int i=0; i<10000; i++)
                {
                    c.insert_chash2();
                }
                c.print_chash();
                cout<<"search item"<<endl;
                string n;
                cin>>n;
                cout<<c.search_chash2(n)<<endl;
                c.averagehit1();
                cout<<c.avghit()<<endl;
            }
            else
            {
                break;
            }
        }
    }
