#include <iostream>
#include <string>
#include <vector>
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
    vector<ICandidate*> candidates;
    CandidateFM candidateCreator;
    candidates.push_back(candidateCreator.create("Zhirinovsky V.V.", 75, 
        20000156, FRACTION_LDPR, 42345));
    candidates.push_back(candidateCreator.create("Kaz M.E", 36, 
        10000003, FRACTION_YABLOKO, 12043));
    candidates.push_back(candidateCreator.create("Zyganov G.A", 77, 
        15000002,FRACTION_KPRF, 24021));

    for(const auto cand: candidates){
        cout << cand->getFio() << endl
        << "Age: " << cand->getAge() << endl
        << "Income: " << cand->getIncome() << endl
        << "Fraction: " << cand->getFraction() << endl
        << "Voices: " << cand->getVoices() << endl
        << endl << endl;
    }

    return 0;
}