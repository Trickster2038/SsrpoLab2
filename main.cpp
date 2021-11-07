#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum Fraction
{
    FRACTION_EDRO,
    FRACTION_YABLOKO,
    FRACTION_LDPR,
    FRACTION_NOVYE_LUDI,
    FRACTION_KPRF
};

struct ICandidate
{
    virtual string getFio() const = 0;
    virtual uint getAge() const = 0;
    virtual uint getIncome() const = 0;
    virtual Fraction getFraction() const = 0;
    virtual uint getVoices() const = 0;
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

    string getFio() const override { return fio; };
    uint getAge() const override { return age; };
    uint getIncome() const override { return income; };
    Fraction getFraction() const override { return fraction; };
    uint getVoices() const override { return voices; };
    void printInfo() const override
    {
        cout << fio << endl
             << "Age: " << age << endl;
        printf("Income: %.2f \n", income);
        cout << "Fraction ID: " << fraction << endl
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
    uint getIncome() const override { return income; };

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

    string getFio() const override { return fio; };
    uint getAge() const override { return age; };
    Fraction getFraction() const override { return fraction; };
    uint getVoices() const override { return voices; };
    void printInfo() const override
    {
        cout << fio << endl
             << "Age: " << age << endl
             << "Fraction ID: " << fraction << endl
             << "Voices: " << voices << endl
             << endl
             << endl;
    };
};

struct IFabricMethod
{
    virtual ICandidate *create(string _fio, uint _age,
                               uint _income, Fraction _fraction, uint _voices) = 0;
};

struct CandidateGosdumiFM : IFabricMethod
{
    ICandidate *create(string _fio, uint _age, uint _income,
                       Fraction _fraction, uint _voices) override
    {
        return new CandidateGosdumi(_fio, _age, _income,
                                    _fraction, _voices);
    };
};

struct CandidateMunicipalFM : IFabricMethod
{
    ICandidate *create(string _fio, uint _age, uint _income,
                       Fraction _fraction, uint _voices) override
    {
        return new CandidateMunicipal(_fio, _age, _income,
                                      _fraction, _voices);
    };
};

struct VotingList
{
private:
    vector<ICandidate *> candidates;
    IFabricMethod *fm;

public:
    VotingList(IFabricMethod *fm_)
    {
        fm = fm_;
    }
    void addCandidate(string _fio, uint _age, uint _income,
                      Fraction _fraction, uint _voices)
    {
        candidates.push_back(fm->create(_fio, _age, _income,
                                        _fraction, _voices));
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
    CandidateGosdumiFM candidateGosdumiCreator;
    VotingList gosdumaVoting(&candidateGosdumiCreator);
    gosdumaVoting.addCandidate("Zhirinovsky V.V.", 75, 20000156, FRACTION_LDPR, 42345);
    gosdumaVoting.addCandidate("Kaz M.E", 36, 10000003, FRACTION_YABLOKO, 12043);
    gosdumaVoting.addCandidate("Zyganov G.A", 77, 15000002, FRACTION_KPRF, 24021);

    cout << "Gosduma list:\n"
         << endl;
    gosdumaVoting.printList();

    CandidateMunicipalFM candidateMunicipalCreator;
    VotingList municipalVoting(&candidateMunicipalCreator);
    municipalVoting.addCandidate("Urov S.G.", 38, 150202, FRACTION_EDRO, 8021);
    municipalVoting.addCandidate("Zhirkov E.I.", 61, 190213, FRACTION_EDRO, 7022);

    cout << "Municipal list:\n"
         << endl;
    municipalVoting.printList();

    return 0;
}