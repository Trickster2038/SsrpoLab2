#include <iostream>
#include <string>
#include <list>
#include <iomanip>

using namespace std;

enum Fraction {
    FRACTION_EDRO,
    FRACTION_YABLOKO,
    FRACTION_LDPR,
    FRACTION_NOVYE_LUDI,
    FRACTION_KPRF
};

struct ICandidate{
    virtual string getFio() const = 0;
    virtual uint getAge() const = 0;
    virtual uint getIncome() const = 0;
    virtual Fraction getFraction() const = 0;
    virtual uint getVoices() const = 0;
    virtual ~ICandidate(){}
};

struct Candidate: ICandidate{
    private:
        string fio;
        uint age;
        float income;
        Fraction fraction;
        uint voices;

    public:
        Candidate(string _fio, uint _age, uint _income,
        Fraction _fraction, uint _voices){
            fio = _fio;
            age = _age;
            income = _income;
            fraction = _fraction;
            voices = _voices;
        };

        string getFio() const override {return fio;};
        uint getAge() const override {return age;};
        uint getIncome() const override {return income;};
        Fraction getFraction() const override {return fraction;};
        uint getVoices() const override {return voices;};
};

struct IFabricMethod{
    virtual ICandidate* create(string _fio, uint _age, 
        uint _income, Fraction _fraction, uint _voices) = 0;
};

struct CandidateFM: IFabricMethod{
    ICandidate* create(string _fio, uint _age, uint _income,
        Fraction _fraction, uint _voices) override { 
        return new Candidate(_fio, _age, _income, 
            _fraction, _voices);
    }; 
};

int main(){
    Candidate a("gg", 22, 234, FRACTION_EDRO, 345);
    CandidateFM candidateCreator;
    ICandidate* b = candidateCreator.create("gg2", 22, 234, FRACTION_EDRO, 345);
    cout << a.getFio() << endl;
    cout << b->getFio() << endl;
    cout << "hello" << endl;
    return 0;
}