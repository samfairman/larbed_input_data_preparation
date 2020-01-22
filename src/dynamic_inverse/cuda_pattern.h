#ifndef _CUDA_PATTERN_H_INCLUDED_DFOPHIASLFK39Y8AFLHJUASLKASJHSAFDO9UY8H4KLJHFSDF
#define _CUDA_PATTERN_H_INCLUDED_DFOPHIASLFK39Y8AFLHJUASLKASJHSAFDO9UY8H4KLJHFSDF

//device
struct individual_pattern
{
    unsigned long dim;
    double* ug_thickness; //ug_size * 2 + 1
    unsigned long* ar;
    double* diag;
    double* I_exp;
    double* I_sim;
    double2* A;
    double2* S;
    double2* S0;
    double2* S1;
    double2* S2;
    double2* S3;
    double2* S4;
    double2* S5;
    double2* S6;
    double2* S7;
    double2* S8;
    double2* S9;
    double2* S10;
};

//host
struct pattern_on_gpu
{
    int gpu_id;
    int pattern_id_start;
    int pattern_id_end;
    individual_pattern* ip; // cpu ...
    individual_pattern* ip_gpu; // gpu ...

    double* ug_thickness; //gpu
};

//host
struct cuda_pattern
{
    unsigned long total_ug_size; //--> count as complex type
    unsigned long total_cuda_pattern;
    int total_gpu;
    pattern_on_gpu* pog; //cpu
};

void make_individual_pattern( int gpu_id, individual_pattern* ip, unsigned long dim, unsigned long* ar, double* diag, double* intensity, double* ug_thickness )
void make_individual_pattern( individual_pattern* ip )
void make_pattern_on_gpu( pattern_on_gpu* pog, int const gpu_id_, int const pattern_id_start_, int const pattern_id_end_  )
cuda_pattern* make_cuda_pattern( unsigned long n, unsigned long ug_size; )

#endif//_CUDA_PATTERN_H_INCLUDED_DFOPHIASLFK39Y8AFLHJUASLKASJHSAFDO9UY8H4KLJHFSDF

