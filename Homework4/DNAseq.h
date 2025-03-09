//
// Created by Ege Tan on 8.04.2024.
//
#ifndef HOMEWORK4_DNASEQ_H
#define HOMEWORK4_DNASEQ_H
#include <string>


enum Nucleotide {A, C, G, T};
class DNAseq {
private:
    unsigned int length;
    Nucleotide* sequence;
    void convert (const DNAseq &, std::string &) const;
public:
    DNAseq();
    ~DNAseq();
    DNAseq(const std::string &);
    DNAseq(const DNAseq &);
    bool operator<= (const DNAseq &);
    DNAseq operator * (const int &);
    int operator % (const Nucleotide &)const;
    DNAseq operator!() const;
    const DNAseq & operator=(const DNAseq &);
    DNAseq operator+(const DNAseq &);
    DNAseq & operator+=(const DNAseq &);
    std::string get_sequence() const;
    int get_length()const;
};

DNAseq operator+(const Nucleotide& , const DNAseq& );
DNAseq operator-(const DNAseq& , const DNAseq&);
std::ostream & operator << (std::ostream & , const DNAseq&);
std::string enum_to_string(const Nucleotide &);

#endif //HOMEWORK4_DNASEQ_H
