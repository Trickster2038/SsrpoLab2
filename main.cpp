#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>

using namespace std;

enum Fraction
{
    FRACTION_EDRO,
    FRACTION_YABLOKO,
    FRACTION_LDPR,
    FRACTION_NOVYE_LUDI,
    FRACTION_KPRF
};

class Converter
{
private:
    static inline map<Fraction, string> fraction_to_string = {{FRACTION_EDRO, "EDRO"},
                                                              {FRACTION_YABLOKO, "YABLOKO"},
                                                              {FRACTION_LDPR, "LDPR"},
                                                              {FRACTION_NOVYE_LUDI, "NOVIE LUDI"},
                                                              {FRACTION_KPRF, "KPRF"}};

public:
    static const string &toString(Fraction fraction_code)
    {
        return fraction_to_string.find(fraction_code)->second;
    }
};

struct ICandidate
{
    virtual void printInfo() const = 0;
    virtual ~ICandidate() {}
};

struct CandidateGosdumi : ICandidate
{

private:
    string fio;
    uint age;
    float income;
    Fraction fraction;
    uint voices;

public:
    CandidateGosdumi(string _fio, uint _age, uint _income,
                     Fraction _fraction, uint _voices)
    {
        fio = _fio;
        age = _age;
        income = _income;
        fraction = _fraction;
        voices = _voices;
    };

    string getFio() const { return fio; };
    uint getAge() const { return age; };
    uint getIncome() const { return income; };
    Fraction getFraction() const { return fraction; };
    uint getVoices() const { return voices; };
    void printInfo() const override
    {
        cout << fio << endl
             << "Age: " << age << endl;
        printf("Income: %.2f \n", income);
        cout << "Fraction: " << Converter::toString(fraction) << endl
             << "Voices: " << voices << endl
             << endl
             << endl;
    };
};

struct CandidateMunicipal : ICandidate
{

private:
    string fio;
    uint age;
    float income;
    Fraction fraction;
    uint voices;

public:
    CandidateMunicipal(string _fio, uint _age, uint _income,
                       Fraction _fraction, uint _voices)
    {
        fio = _fio;
        age = _age;
        income = _income;
        fraction = _fraction;
        voices = _voices;
    };

    string getFio() const { return fio; };
    uint getAge() const { return age; };
    Fraction getFraction() const { return fraction; };
    uint getVoices() const { return voices; };
    void printInfo() const override
    {
        cout << fio << endl
             << "Age: " << age << endl
             << "Fraction ID: " << Converter::toString(fraction) << endl
             << "Voices: " << voices << endl
             << endl
             << endl;
    };
};

struct IFActoryMethod
{
    virtual shared_ptr<ICandidate> create(string _fio, uint _age,
                               uint _income, Fraction _fraction, uint _voices) = 0;
    virtual ~IFActoryMethod() = default;
};

struct CandidateGosdumiFM : IFActoryMethod
{
    shared_ptr<ICandidate> create(string _fio, uint _age, uint _income,
                       Fraction _fraction, uint _voices) override
    {
        return make_shared<CandidateGosdumi>(_fio, _age, _income,
                                    _fraction, _voices);
    };
};

struct CandidateMunicipalFM : IFActoryMethod
{
    shared_ptr<ICandidate> create(string _fio, uint _age, uint _income,
                       Fraction _fraction, uint _voices) override
    {
        return make_shared<CandidateMunicipal>(_fio, _age, _income,
                                      _fraction, _voices);
    };
};

struct VotingList: public enable_shared_from_this<VotingList>
{
private:
    vector<shared_ptr<ICandidate>> candidates;
    shared_ptr<IFActoryMethod> fm;

public:
    VotingList(IFActoryMethod* fm_)
    {
        shared_ptr<IFActoryMethod> shared_fm(fm_);
        fm = move(shared_fm);
    }
    void addCandidate(string _fio, uint _age, uint _income,
                      Fraction _fraction, uint _voices)
    {
        candidates.push_back(move(fm->create(_fio, _age, _income,
                                        _fraction, _voices)));
    }
    void printList()
    {
        for (const auto cand : candidates)
        {
            cand->printInfo();
        }
    }
};

int main()
{
    CandidateGosdumiFM* candidateGosdumiCreator = new CandidateGosdumiFM();
    VotingList gosdumaVoting(candidateGosdumiCreator);
    gosdumaVoting.addCandidate("Zhirinovsky V.V.", 75, 20000156, FRACTION_LDPR, 42345);
    gosdumaVoting.addCandidate("Kaz M.E", 36, 10000003, FRACTION_YABLOKO, 12043);
    gosdumaVoting.addCandidate("Zyganov G.A", 77, 15000002, FRACTION_KPRF, 24021);

    cout << "Gosduma list:\n"
         << endl;
    gosdumaVoting.printList();

    CandidateMunicipalFM* candidateMunicipalCreator = new CandidateMunicipalFM();
    VotingList municipalVoting(candidateMunicipalCreator);
    municipalVoting.addCandidate("Urov S.G.", 38, 150202, FRACTION_EDRO, 8021);
    municipalVoting.addCandidate("Zhirkov E.I.", 61, 190213, FRACTION_EDRO, 7022);

    cout << "Municipal list:\n"
         << endl;
    municipalVoting.printList();

    return 0;
}