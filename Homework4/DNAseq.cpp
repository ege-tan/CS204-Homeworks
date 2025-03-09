//
// Created by Ege Tan on 8.04.2024.
//
#include "DNAseq.h"

//default constructor
DNAseq::DNAseq()
{
    length = 0;
    sequence = nullptr;
}

//parametrized constructor that takes string and creates new DNAseq object
DNAseq::DNAseq(const std::string & nucleotides)
{
    if (nucleotides.empty())
    {
        length = 0;
        sequence = new Nucleotide[length];
    }
    else
    {
        length = nucleotides.length();
        sequence = new Nucleotide[length];
        for (unsigned int i = 0 ; i < length ; i++)
        {
            sequence[i] = Nucleotide(nucleotides[i]);
        }
    }
}

//deep-copy constructor
DNAseq::DNAseq(const DNAseq & rhs)
{
    //they will have equal length and same elements
    this->length = rhs.length;
    this->sequence = new Nucleotide[this->length];
    //make elements same
    for (unsigned int i = 0; i < rhs.length ; i++)
    {
        this->sequence[i] = rhs.sequence[i];
    }
}

//destructor
DNAseq::~DNAseq()
{
    //delete the dynamically allocated array
    delete [] sequence;
}

//this function is a member function and checks whether the lhs is a subset of rhs or not
bool DNAseq::operator<=(const DNAseq & rhs)
{
    std::string lhs_seq = "";
    std::string rhs_seq = "";

    convert(rhs,rhs_seq);
    convert(*this,lhs_seq);

    //if lhs and rhs are same
    if (lhs_seq == rhs_seq)
    {
        return true;
    }
    else
    {
        //if lhs is a subset of rhs
        if (rhs_seq.find(lhs_seq) != std::string::npos)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

//this function is a member function and takes string and object , returns object's nucleotide sequence with reference
void DNAseq::convert(const DNAseq & obj, std::string & seq) const {
    for (unsigned int i = 0; i < obj.get_length() ; i++)
    {
        seq += obj.sequence[i];
    }
}

//this function is a member function and takes an integer ,returns multiplied times nucleotides
DNAseq DNAseq::operator*(const int & times)
{
    DNAseq newseq;
    newseq.length = this->length * times;
    newseq.sequence = new Nucleotide[newseq.length];
    int count = 0; //in terms of don't losing the position.
    for (unsigned int i = 0; i < times ; i++)
    {
        for (unsigned int j = 0; j < this->length ; j++)
        {
            newseq.sequence[count] = this->sequence[j];//create new DNAseq and add times nucleotides to that object
            count++;
        }
    }
    return newseq; //and return it
}

//this function is a member function and returns the count of rhs Nucleotride in current obj
int DNAseq::operator%(const Nucleotide & rhs)const
{
    std::string lhs_seq;
    int count{0},next_pos{0};
    convert(*this,lhs_seq);
    std::string nuc = enum_to_string(rhs);
    next_pos = lhs_seq.find(nuc, next_pos);

    while (next_pos != std::string::npos) {
        count++; //increment count for each occurrence
        next_pos = lhs_seq.find(nuc, next_pos + 1); //move to the next position after the current found
    }
    return count;
}

//this function is a member function , it returns a string of nucleotid sequence of the current object
std::string DNAseq::get_sequence()const {
    std::string seq ;
    convert(*this,seq);
    return seq;
}

//this function is a member function and it takes the complement of the current obj's sequence
DNAseq DNAseq::operator!() const
{
    std::string nucleotides;
    for (unsigned int i = 0; i < length ; ++i)
    {
        //take each nucleotide and add the complement of them to the string
        if (this->sequence[i] == Nucleotide('A'))
        {
            nucleotides += Nucleotide('T');
        }
        else if (this->sequence[i] == Nucleotide('T'))
        {
            nucleotides += Nucleotide('A');
        }
        else if (this->sequence[i] == Nucleotide('G'))
        {
            nucleotides += Nucleotide('C');
        }
        else if (this->sequence[i] == Nucleotide('C'))
        {
            nucleotides += Nucleotide('G');
        }
    }
    //in the end create a new object with that string
    DNAseq newobj(nucleotides);
    return newobj;
}

//this function is a member function and it assigns rhs to lhs
const DNAseq & DNAseq::operator=(const DNAseq & rhs)
{
    //first get the sequences of each object
    std::string lhs_seq = this->get_sequence();
    std::string rhs_seq = rhs.get_sequence();
    //check their equality condition
    if (this != &rhs)
    {
        if (lhs_seq == rhs_seq)
        {
            return *this;
        }
        //if they are not equal , set their length to same
        this->length =  rhs.length;
        //first delete this
        delete [] this->sequence;
        //create new sequence
        this->sequence = new Nucleotide[rhs.length];
        for (unsigned int i = 0; i < rhs.length ; i++)
        {
            //assign everything same to the this obj.
            this->sequence[i] = rhs.sequence[i];
        }
    }

    //since this function returns the allready existing object , it returns const reference object
    return *this;
}

//this function is a member function and adds to object sequences according to some rules
DNAseq DNAseq::operator+(const DNAseq & rhs)
{
    std::string lhs_seq;
    std::string rhs_seq;
    convert(*this,lhs_seq);
    convert(rhs,rhs_seq);
    //get the sequences as a string

    if (rhs.sequence != nullptr)//check wheter rhs is empty or not
    {
        if (lhs_seq.find(rhs.sequence[0]) != std::string::npos)//check the first condition for '+' operation (wheter the first nucleotide of rhs exists in lhs or not)
        {
            int index = lhs_seq.find(rhs.sequence[0]);
            lhs_seq = lhs_seq.substr(0,index+1)+ rhs_seq +lhs_seq.substr(index+1);
        }
        else
        {
            lhs_seq = lhs_seq + rhs_seq;
        }
    }
    //create a new obj with lhs_seq sequence
    DNAseq newseq(lhs_seq);
    return newseq;
}

//this function is a member function and add rhs to current object and assigns to the lhs one
DNAseq &DNAseq::operator+=(const DNAseq & rhs)
{
    //we use the '+' operator according to directives in the homework
    *this = *this + rhs;
    return *this;
}

//this function is a member function and gets the length of the current object
int DNAseq::get_length() const {
    return this->length;
}

//this function is a free function and adds lhs(nucleotide) and rhs(DNAseq obj)
DNAseq operator+(const Nucleotide& lhs, const DNAseq& rhs)
{
    std::string rhs_seq = rhs.get_sequence();
    std::string nuc = enum_to_string(lhs);
    //get the string versions of nucleotide and DNAseq
    nuc += rhs_seq;
    //create new DNAseq obj and return it
    DNAseq newseq(nuc);
    return newseq;
}

//this function is a free function and subtracts rhs from lhs
DNAseq operator-(const DNAseq& lhs,const DNAseq& rhs)
{
    //remove rhs from lhs
    std::string rhs_seq = rhs.get_sequence();
    std::string lhs_seq = lhs.get_sequence();
    if (lhs_seq.find(rhs_seq) != std::string::npos)//if rhs is a subset of lhs
    {
        int index = lhs_seq.find(rhs_seq);
        lhs_seq = lhs_seq.substr(0,index) + lhs_seq.substr(index+rhs_seq.length());
    }
    //create new object and return it
    DNAseq newseq(lhs_seq);
    return newseq;
}

//this function is a free function and it provide us to print the object's sequence to the screen
std::ostream & operator << (std::ostream & os, const DNAseq& rhs)
{
    std::string seq =  rhs.get_sequence();
    os<<seq;
    return os;
}

//this function is a free function and returns the string version of the Nucleotide
std::string enum_to_string(const Nucleotide & rhs)
{
    if (rhs == A)
    {
        return "A";
    }
    else if (rhs == T)
    {
        return "T";
    }
    else if (rhs == G)
    {
        return "G";
    }
    else if (rhs == C)
    {
        return "C";
    }
    //case for handling the unexpected Nucleotides
    else
    {
        return "";
    }
}