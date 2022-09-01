#include <iostream>
#include <cmath>
#include <vector>
#include <numeric>

using namespace std;

class KeyGeneration{

    private:
        unsigned p;
        unsigned q;
        unsigned n;
        unsigned phi_n;
        unsigned e;
        unsigned d;
        int text;

    public:
        void prompter();
        void primality_check();
        int isprime(unsigned n);
        unsigned power(unsigned a , unsigned b);
        unsigned gcd(unsigned a, unsigned b);
        unsigned calculate_n();
        unsigned calculate_phi();
        unsigned calculate_e();
        unsigned calculate_d();
        void getmessage();
        unsigned encrypt();
        unsigned decrypt(unsigned);
       

      
};

void KeyGeneration:: prompter(){
    cout<<"Please enter the prime number p: "<<endl;
    cin>>p;
    cout<<"Please enter the prime number q: "<<endl;
    cin>>q;
}

int KeyGeneration:: isprime(unsigned n){
    int num=n-1,flag=1;
    while(num>1){
        if(n%num==0){
            flag=0;
            break;
        }
        num--;
    }
    if(flag){
        return 1;
    }else{
        return 0;
    }
}

unsigned KeyGeneration::gcd(unsigned a, unsigned b){
    unsigned result = min(a, b); 
    while (result > 0) {
        if (a % result == 0 && b % result == 0) {
            break;
        }
        result--;
    }
    return result; 
}

void KeyGeneration::primality_check(){
    if(!isprime(p) && !isprime(q)){
        throw (runtime_error("Non prime imput!"));
    }

}

unsigned KeyGeneration::calculate_n(){
    n=p*q;
    return n;
}

unsigned KeyGeneration::calculate_phi(){
    phi_n = (p-1)*(q-1);
    return phi_n;
}

unsigned KeyGeneration::calculate_e(){
    unsigned i=2;
    while(gcd(i,phi_n)!=1){
        i++;
    }
    e=i;
    if(e>=phi_n){
        throw (runtime_error("e is greater than or equal to phi n"));
        
    }
    return e;
}

unsigned KeyGeneration::calculate_d(){
    unsigned k=1;
    while(((k*phi_n)+1)%e!=0){
        k++;
    }
    d = ((k*phi_n)+1)/e;
    return d;
}

unsigned KeyGeneration::power(unsigned a , unsigned b){
    unsigned result=1;
    while(b--){
        result*=a;
    }
    return result;
}

unsigned KeyGeneration::encrypt(){
    unsigned cipher = power(text,calculate_e())%calculate_n();
    return cipher;
}

unsigned KeyGeneration::decrypt(unsigned cipher){
    unsigned decode = power(cipher,calculate_d())%calculate_n();
    return decode;
}

void KeyGeneration::getmessage(){
    cout<<"Enter the text "<<endl;
    cin>>text;

}



int main(){
    try{
        KeyGeneration keyGeneration;
        keyGeneration.prompter();
        keyGeneration.primality_check();
        cout << "The value of n : "<<keyGeneration.calculate_n() <<endl;
        cout << "The value of phi : "<<keyGeneration.calculate_phi() <<endl;
        cout << "The value of e : "<<keyGeneration.calculate_e() <<endl;
        cout << "The value of d : "<<keyGeneration.calculate_d() <<endl;
        keyGeneration.getmessage();
        unsigned c = keyGeneration.encrypt() ;
        // cout<<"Check"<<keyGeneration.power(2,2)<<endl;
        cout << "The value of encrypt message is : "<< c <<endl;
        cout<< "The value of decrypt message is : " << keyGeneration.decrypt(c)<<endl;

    }catch(runtime_error & s){
        cout<< s.what()<<endl;
    }
    return 0;
}