#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef REGEX
#define REGEX
#include <regex>
#endif

#ifndef MATH
#define MATH
#include <math.h>
#endif

#ifndef PTHREAD
#define PTHREAD
#include <pthread.h>
#endif



using namespace std;

/** \brief Most important class of PRINSEQ++, stores, filter and trim, reads.
 * 
 * This class can get one dna read from a fastq files and store it. It can also 
 * performs all trimming, filtering and printing operation.
 * 
 */
class single_read {
    public:
        single_read(istream &is, int mode);
        single_read(void);
        void set_inputs(istream &is);
        void set_outputs(ostream& bad_out_file, ostream& single_out_file, ostream& good_out_file);
        int read_read(pthread_mutex_t * read_mutex, int format);
        //filter
        int ns_max_n(int ns_max_n);
      //  int max_n_p(int ns_max_p);
        
        int min_qual_score(int min_qual);
        int min_qual_mean(int min_qual);
        int noiupac(void);        
        int min_len(unsigned int len); 
        int max_len(unsigned int len);
        int max_gc(float max_gc);
        int min_gc(float min_gc);
        int entropy(float threshold); 
        int dust(float threshold);
        
        
        // type min* mean max sum // rule lt* gt eq 
        int trim_qual_right(string type, string rule, int step, int window_size, float threshold );  
        int trim_qual_left(string type, string rule, int step, int window_size, float threshold );
        void rm_header(void);
        int trim_tail_left(int num);
        int trim_tail_right(int num);
        int trim_left(int num);
        int trim_right(int num);
        void print(int out_form);
        
        int qual_mode;
        int get_read_status(void);
        void set_read_status(int status);
        
        string seq_name;
        string seq_seq;
        string seq_sep;
        string seq_qual;
        
        std::ostream* out_stream;

    protected:
        regex fastq_to_fasta;
        int read_status=0; //0 good, 1 single ,2 bad
        istream& file1;
        //ofstream out_stream();
        
        streambuf *back_stdout=NULL;
        streambuf *bad_out=NULL;
        streambuf *single_out=NULL;
        streambuf *good_out=NULL;
};         

/** \brief Class containing two single_read
 * 
 * Most methods just call the homonymous method in both reads
 * and then calls pair_read::auto_set_read_status
 * 
 */
class pair_read {
    public:
        pair_read(istream &is1, istream &is2, int mode);
        pair_read(void);
        void set_inputs(istream &read_f,istream &read_r);
        int read_read(pthread_mutex_t* read_mutex_1, pthread_mutex_t* read_mutex_2,pthread_mutex_t* read_mutex3, int format);
        void print(void);
        void set_outputs(ostream& bad_out_file1, ostream& single_out_file1, ostream& good_out_file1,
                    ostream& bad_out_file2, ostream& single_out_file2, ostream& good_out_file2);
        int ns_max_n(int ns_max_n);
        int min_qual_score(int min_qual);
        int min_qual_mean(int min_qual);
        void set_out_format(int format);
        int max_n_p(int ns_max_p);
        void set_read_status(int match1, int match2);
        int noiupac(void);   
        int min_len(unsigned int len); 
        int max_len(unsigned int len);
        int max_gc(float max_gc);
        int min_gc(float min_gc);
        int entropy(float threshold);
        int dust(float threshold);
        void auto_set_read_status(void);
        // type min* mean max sum // rule lt* gt eq 
        int trim_qual_right(string type, string rule, int step, int window_size, float threshold );         
        int trim_qual_left(string type, string rule, int step, int window_size, float threshold );
        void rm_header(void);
        int trim_tail_left(int num);
        int trim_tail_right(int num);
        int trim_left(int num);
        int trim_right(int num);
        
        
        single_read* read1;
        single_read* read2;


    protected:
        istream& file1;
        istream& file2;

        int out_form=0;    //0 fastq , 1 fasta

};                    

string random_string( size_t length );


