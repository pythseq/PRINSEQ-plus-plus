#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef REGEX
#define REGEX
#include <regex>
#endif

#include "reads.h"

using namespace std;
        single_read::single_read(istream &is): file1(is)  { 
            fastq_to_fasta.assign("^@");
        }

        int single_read::set_outputs(ostream& bad_out_file, ostream& single_out_file, ostream& good_out_file) {
            bad_out=bad_out_file.rdbuf();
            single_out=single_out_file.rdbuf();
            good_out=good_out_file.rdbuf();
        }

        int single_read::read_read(void) {
        read_status=0;
            if (getline(file1,seq_name, '\n')) {
                getline(file1, seq_seq, '\n');
                getline(file1, seq_sep, '\n');
                getline(file1, seq_qual, '\n');
                return 1;
            } else {
                return 0;
            }
        }

        int single_read::seq_match(regex pattern,int ns_max_n) {
            int hit_num=distance(sregex_iterator(seq_seq.begin(), seq_seq.end(), pattern),sregex_iterator());
     //       std::cout << hit_num << " matches found in :" << seq_seq << std::endl;
            if ( hit_num > ns_max_n ) {
              read_status=2;
                return 1;
            } else {
                return 0;
            }
        }

        void single_read::print(int out_form) {
            if (read_status==2) {
                cout.rdbuf(bad_out);
            } else if (read_status==1) {
                cout.rdbuf(single_out);
            } else if (read_status==0) {
                cout.rdbuf(good_out);
            }
            if (out_form==0) {
                cout << seq_name << endl << seq_seq << endl << seq_sep << endl << seq_qual << endl;
            } else if (out_form==1) {
                cout << regex_replace(seq_name,fastq_to_fasta, ">") << endl << seq_seq << endl;
            }
            cout.rdbuf(back_stdout);
        }

        int single_read::min_qual_score(int min_qual) {
            string temp_seq_qual=seq_qual;
            char base;
            int score;
            for(std::string::size_type i = seq_qual.size()-1; i > 0; --i) {
                score=int(seq_qual[i])-33;
    //            cout << "char is " << seq_qual[i] << " i is " << i << " score is " << score << " and minqual " << min_qual  << endl;
                if (score < min_qual) { return 1 ;}
            }
            return 0;
        }    

        int single_read::get_read_status(void) {
            return read_status;
        }

        void single_read::set_read_status(int status) {
            if (status > read_status) {read_status=status;}
        }


        pair_read::pair_read(istream &is1, istream &is2): file1(is1),file2(is2)  {

        read1= new single_read(file1);
        read2= new single_read(file2);
    }

    int pair_read::read_read(void) {
        return read1->read_read() * read2->read_read();
    }


    void pair_read::print(void) {
        read1->print(out_form);
        read2->print(out_form);
    }


    int pair_read::set_outputs(ostream& bad_out_file1, ostream& single_out_file1, ostream& good_out_file1,
                    ostream& bad_out_file2, ostream& single_out_file2, ostream& good_out_file2) {
        read1->set_outputs(bad_out_file1, single_out_file1, good_out_file1);
        read2->set_outputs(bad_out_file2, single_out_file2, good_out_file2);
    }

    int pair_read::seq_match(regex pattern,int ns_max_n) {
        int match1= read1->seq_match(pattern, ns_max_n);
        int match2= read2->seq_match(pattern, ns_max_n);
        if ( !match1 && !match2 ) {
            read1->set_read_status(0);
            read2->set_read_status(0);
        } else if ( !match1 && match2 ) {
            read1->set_read_status(1);
            read2->set_read_status(2);
        } else if ( match1 && !match2 ) {
            read1->set_read_status(2);
            read2->set_read_status(1);
        } else { 
            read1->set_read_status(2);
            read2->set_read_status(2);
        }
    }

    int pair_read::min_qual_score(int min_qual) {
        int match1= read1->min_qual_score(min_qual);
        int match2= read2->min_qual_score(min_qual);
        if ( !match1 && !match2 ) {
            read1->set_read_status(0);
            read2->set_read_status(0);
        } else if ( !match1 && match2 ) {
            read1->set_read_status(1);
            read2->set_read_status(2);
        } else if ( match1 && !match2 ) {
            read1->set_read_status(2);
            read2->set_read_status(1);
        } else {
            read1->set_read_status(2);
            read2->set_read_status(2);
        }
    }


    void pair_read::set_out_format(int format) {
        out_form=format;
    }    

string random_string( size_t length )
{
    auto randchar = []() -> char
    {
        const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[ rand() % max_index ];
    };
    srand (time(NULL));
    std::string str(length,0);
    std::generate_n( str.begin(), length, randchar );
    return str;
}