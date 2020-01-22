#CXX           = g++-6

CXX           = clang++
#CXX           = g++

#CXX           = g++-7
#GXX           = g++
#GXX           = g++-feng
#CXXFLAGS        = -std=c++1z -stdlib=libc++ -Wfatal-errors -pg -Wall -O0
#CXXFLAGS        = -std=c++1z -stdlib=libc++ -O3 -ferror-limit=2  -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-sign-conversion -Wno-exit-time-destructors -Wno-float-equal -Wno-global-constructors -Wno-missing-declarations -Wno-unused-parameter -Wno-padded -Wno-shadow -Wno-weak-vtables -Wno-missing-prototypes -Wno-string-conversion -ferror-limit=2 -Wno-covered-switch-default -Wno-documentation -Wno-conversion -Wno-old-style-cast -Wno-non-virtual-dtor -Wno-deprecated
#CXXFLAGS        = -std=c++1z -stdlib=libc++ -O3 -ferror-limit=2 -Weverything
#CXXFLAGS        = -std=c++1z -stdlib=libc++ -O3 -ferror-limit=2 -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-sign-conversion -Wno-exit-time-destructors -Wno-float-equal -Wno-global-constructors -Wno-missing-declarations -Wno-unused-parameter -Wno-padded -Wno-shadow -Wno-weak-vtables -Wno-missing-prototypes -Wno-unused-variable -ferror-limit=1 -Wno-deprecated -Wno-conversion -Wno-double-promotion
#CXXFLAGS        = -g -std=c++17 -stdlib=libc++ -O0 -Wfatal-errors -DDEBUG

CXXFLAGS        = -std=c++14 -stdlib=libc++ -O3 -ferror-limit=2 -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-sign-conversion -Wno-exit-time-destructors -Wno-float-equal -Wno-global-constructors -Wno-missing-declarations -Wno-unused-parameter -Wno-padded -Wno-shadow -Wno-weak-vtables -Wno-missing-prototypes -Wno-unused-variable -ferror-limit=1 -Wno-deprecated -Wno-conversion -Wno-double-promotion
#CXXFLAGS        = -O2 -std=c++17 -Wall -Wextra -fmax-errors=2


#CXXFLAGS        = -p -g3 -std=c++17 -O0 -Wfatal-errors -Wall
#CXXFLAGS        = -std=c++17 -O2 -Wfatal-errors -Wall
#CXXFLAGS        = -std=c++11 -O3 -march=corei7-avx #gcc 4.8 only
#GXXFLAGS        = -g -std=c++11 -O0 -Wfatal-errors
#GXXFLAGS        = -mtune=corei7 -march=corei7 -std=c++11 -O3 -mmmx -msse -msse2 -msse3 -mssse3 -msse4.1 -msse4.2 -msse4 -pipe -Wall -Wextra -fPIC -fmax-errors=1
#GXXFLAGS        = -mtune=corei7 -march=corei7 -O3 -mmmx -msse -msse2 -msse3 -mssse3 -msse4.1 -msse4.2 -msse4 -pipe -std=c++11 -Wall -Wfatal-errors -Wextra

INCPATH       = -Iinclude -I/usr/local/cuda/include -I/usr/local/include -I/usr/include/c++/v1 
#INCPATH       = -Iinclude -I/usr/local/cuda-7.0/include -I/opt/cuda/include -I/opt/local/include -I/usr/local/cuda/include -I/home/fengwang/usr/include -I/home/fengwang/opt/cuda/include -I/usr/local/include  -I/usr/local/cuda-7.0/include

LINK          = $(CXX)
#GLINK          = $(GXX)
#LFLAGS        = -lc++ -lc++abi -pg -pthread
#linux on the server
#LFLAGS        = ./binary/libc++.a ./binary/libc++abi.a -O3 -pthread
#mac
#LFLAGS        = -lc++ -lc++abi -O3 -pthread
#LFLAGS 	  = -static -g3 -O0

LFLAGS	  = -lc++ -lc++abi -O3 -pthread
#LFLAGS 	  = -O2 -pthread

GLFLAGS        =
#GLFLAGS        = -g -O0
DEL_FILE      = rm -f
DEL_DIR       = rmdir
MOVE          = mv -f
MAKE_DIR      = mkdir

####### CUDA
CUDACXX      = nvcc
CUDACXX64      = nvcc
#CUDACXX64      = /usr/local/cuda-7.0/bin/nvcc
#CUDACXXFLAGS = -m64 -gencode arch=compute_35,code=sm_35 -O2

CUDACXXFLAGS = -m64 -gencode arch=compute_70,code=sm_70 -O2 -Iinclude
#CUDACXXFLAGS = -m64 -gencode arch=compute_35,code=sm_35 -O2 -Iinclude

CUDALIB   = -L/usr/local/cuda/lib64 -L/usr/local/cuda/lib 
#CUDALIB   = -L/opt/cuda/lib64 -L/usr/local/cuda-7.0/lib64 -L/usr/local/cuda/lib -L/home/fengwang/opt/cuda/lib64 -L/Developer/NVIDIA/CUDA-7.0/lib


CUDALFLAGS   = -L/usr/local/cuda/lib64 -L/usr/local/cuda/lib -lcudart -lcurand -lcublas
#CUDALFLAGS   = -L/opt/cuda/lib64 -L/usr/local/cuda-7.0/lib64 -L/usr/local/cuda/lib -L/home/fengwang/opt/cuda/lib64 -L/Developer/NVIDIA/CUDA-7.5/lib -lcudart -lcurand -lcublas

CUDALIB64   = -L/usr/local/cuda/lib64
#CUDALIB64   = -L/opt/cuda/lib64 -L/usr/local/cuda-7.0/lib64 -L/usr/local/cuda/lib -L/home/fengwang/opt/cuda/lib64 -L/Developer/NVIDIA/CUDA-7.5/lib
#CUDALIB64    = -L/usr/local/cuda-7.0/lib64 -L/Developer/NVIDIA/CUDA-7.0/lib
CUDALINK     = g++

CUDALIB64   = -L/usr/local/cuda/lib64

####### Output directory
OBJECTS_DIR   = ./obj
BIN_DIR       = ./bin
LIB_DIR       = ./lib
LOG_DIR       = ./log

#default: pattern_to_image_test

#default: lib
#default: make_ar_test
#default: make_diag_test
#default: dump_ug_test
default: simulate_intensity_test


lib: zmatrix_eye_impl.o  zmatrix_memcpy_real_imag_impl.o zmatrix_poly4_eval.o expm_cu.o cm_eye.o 
	ar cr $(LIB_DIR)/libf.a $(OBJECTS_DIR)/zmatrix_eye_impl.o
	ar cr $(LIB_DIR)/libf.a $(OBJECTS_DIR)/zmatrix_memcpy_real_imag_impl.o
	ar cr $(LIB_DIR)/libf.a $(OBJECTS_DIR)/zmatrix_poly4_eval.o
	ar cr $(LIB_DIR)/libf.a $(OBJECTS_DIR)/expm_cu.o
	ar cr $(LIB_DIR)/libf.a $(OBJECTS_DIR)/cm_eye.o
	ranlib $(LIB_DIR)/libf.a
	$(CXX) -shared -o $(LIB_DIR)/libf.so $(OBJECTS_DIR)/zmatrix_eye_impl.o $(OBJECTS_DIR)/zmatrix_memcpy_real_imag_impl.o  $(OBJECTS_DIR)/zmatrix_poly4_eval.o $(CUDALFLAGS)

all: alpha_beta_tilted_reverse_homotopy_cuda_pattern

device: device_cm

thickness: thickness_test

algorithm: min max swap

labeled_loop: test/labeled_loop/labeled_loop.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/labeled_loop.o test/labeled_loop/labeled_loop.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/labeled_loop $(OBJECTS_DIR)/labeled_loop.o

min: test/algorithm/min.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/min.o test/algorithm/min.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/min $(OBJECTS_DIR)/min.o

logger_test: test/logger/logger.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/logger_test.o test/logger/logger.cc -DDEBUG
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/logger_test $(OBJECTS_DIR)/logger_test.o

nllsf_sincos: test/nlsf/sincos.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/nllsf_sincos.o test/nlsf/sincos.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/nllsf_sincos $(OBJECTS_DIR)/nllsf_sincos.o

nllsf_exp9: test/nlsf/exp9.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/nllsf_exp9.o test/nlsf/exp9.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/nllsf_exp9 $(OBJECTS_DIR)/nllsf_exp9.o

nllsf_exp: test/nlsf/exp.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/nllsf_exp.o test/nlsf/exp.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/nllsf_exp $(OBJECTS_DIR)/nllsf_exp.o

nllsf_exp12: test/nlsf/exp12.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/nllsf_exp12.o test/nlsf/exp12.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/nllsf_exp12 $(OBJECTS_DIR)/nllsf_exp12.o

nllsf_eq1: test/nlsf/eq1.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/nllsf_eq1.o test/nlsf/eq1.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/nllsf_eq1 $(OBJECTS_DIR)/nllsf_eq1.o

nllsf_eqx: test/nlsf/eqx.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/nllsf_eqx.o test/nlsf/eqx.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/nllsf_eqx $(OBJECTS_DIR)/nllsf_eqx.o

nllsf_eq3: test/nlsf/eq3.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/nllsf_eq3.o test/nlsf/eq3.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/nllsf_eq3 $(OBJECTS_DIR)/nllsf_eq3.o

nllsf_si49: test/nlsf/si49.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/nllsf_si49.o test/nlsf/si49.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/nllsf_si49 $(OBJECTS_DIR)/nllsf_si49.o

nllsf_expm: test/nlsf/expm.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/nllsf_expm.o test/nlsf/expm.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/nllsf_expm $(OBJECTS_DIR)/nllsf_expm.o

nllsf_eq2: test/nlsf/eq2.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/nllsf_eq2.o test/nlsf/eq2.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/nllsf_eq2 $(OBJECTS_DIR)/nllsf_eq2.o

nllsf_leq2: test/nlsf/leq2.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/nllsf_leq2.o test/nlsf/leq2.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/nllsf_leq2 $(OBJECTS_DIR)/nllsf_leq2.o

nllsf_sc: test/nlsf/sc.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/nllsf_sc.o test/nlsf/sc.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/nllsf_sc $(OBJECTS_DIR)/nllsf_sc.o

swap: test/algorithm/swap.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/swap.o test/algorithm/swap.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/swap $(OBJECTS_DIR)/swap.o

max: test/algorithm/max.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/max.o test/algorithm/max.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/max $(OBJECTS_DIR)/max.o

thickness_test: test/thickness/thickness.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/thickness_test.o test/thickness/thickness.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/thickness_test $(OBJECTS_DIR)/thickness_test.o

template: oscillate_function_test template_double_oscillate_function_test

derivative: derivative_stepper_test derivative_test rural_derivative combine

window_test: test/window/window.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/window_test.o test/window/window.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/window_test $(OBJECTS_DIR)/window_test.o

derivative_stepper_test: test/derivative/stepper.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/derivative_stepper_test.o test/derivative/stepper.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/derivative_stepper_test $(OBJECTS_DIR)/derivative_stepper_test.o

rural_derivative: test/derivative/rural_derivative.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/rural_derivative.o test/derivative/rural_derivative.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/rural_derivative $(OBJECTS_DIR)/rural_derivative.o

second_derivative: test/derivative/second_derivative.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/second_derivative.o test/derivative/second_derivative.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/second_derivative $(OBJECTS_DIR)/second_derivative.o

combine: test/derivative/combine.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/combine.o test/derivative/combine.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/combine $(OBJECTS_DIR)/combine.o

sd1: test/derivative/sd1.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/sd1.o test/derivative/sd1.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/sd1 $(OBJECTS_DIR)/sd1.o

d1: test/derivative/d1.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/d1.o test/derivative/d1.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/d1 $(OBJECTS_DIR)/d1.o

d2: test/derivative/d2.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/d2.o test/derivative/d2.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/d2 $(OBJECTS_DIR)/d2.o

d2_: test/derivative/d2_.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/d2_.o test/derivative/d2_.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/d2_ $(OBJECTS_DIR)/d2_.o

derivative_test: test/derivative/derivative.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/derivative_test.o test/derivative/derivative.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/derivative_test $(OBJECTS_DIR)/derivative_test.o

secondary_derivative_test: test/derivative/secondary_derivative.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/secondary_derivative_test.o test/derivative/secondary_derivative.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/secondary_derivative_test $(OBJECTS_DIR)/secondary_derivative_test.o

template_oscillate_function_test: test/template/oscillate_function_test.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/oscillate_function_test.o test/template/oscillate_function_test.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/template_oscillate_function_test $(OBJECTS_DIR)/oscillate_function_test.o

template_double_oscillate_function_test: test/template/double_oscillate_function_test.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/double_oscillate_function_test.o test/template/double_oscillate_function_test.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/template_double_oscillate_function_test $(OBJECTS_DIR)/double_oscillate_function_test.o

#qeda: Crystal.o qeda.o readparams.o lib
qeda: qeda.o readparams.o lib
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/qeda  $(OBJECTS_DIR)/qeda.o $(OBJECTS_DIR)/readparams.o  $(LIB_DIR)/libf.a $(CUDALFLAGS)

clean:
	rm -rf $(OBJECTS_DIR)/*
	rm -rf $(BIN_DIR)/*
	rm -rf $(LIB_DIR)/*

expm_cm: lib
	$(GXX) -c $(GXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/expm_cm.o test/expm/cm.cc
	$(GLINK) $(GLFLAGS) -o $(BIN_DIR)/expm_cm  $(OBJECTS_DIR)/expm_cm.o  $(LIB_DIR)/libf.a $(CUDALFLAGS)

expm_bench: lib
	$(GXX) -c $(GXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/expm_bench.o test/expm/bench.cc
	$(GLINK) $(GLFLAGS) -o $(BIN_DIR)/expm_bench  $(OBJECTS_DIR)/expm_bench.o  $(LIB_DIR)/libf.a $(CUDALFLAGS)

Crystal.o: src/qeda/Crystal.cpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/Crystal.o src/qeda/Crystal.cpp

pattern_loader_parser.o: src/qeda/pattern_loader_parser.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/pattern_loader_parser.o src/qeda/pattern_loader_parser.cc

pattern_loader.o: src/qeda/pattern_loader.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/pattern_loader.o src/qeda/pattern_loader.cc

pattern_loader_test.o: test/qeda/pattern_loader_test.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/pattern_loader_test.o test/qeda/pattern_loader_test.cc

pattern_loader_test: pattern_loader_test.o pattern_loader.o pattern_loader_parser.o
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/pattern_loader_test  $(OBJECTS_DIR)/pattern_loader_test.o $(OBJECTS_DIR)/pattern_loader.o  $(OBJECTS_DIR)/pattern_loader_parser.o

qeda.o: src/qeda/qeda.cpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/qeda.o src/qeda/qeda.cpp

readparams.o: src/qeda/readparams.cpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/readparams.o src/qeda/readparams.cpp

binary_test1: test/binary/binary_test1.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/binary_test1.o test/binary/binary_test1.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/binary_test1 $(OBJECTS_DIR)/binary_test1.o

buffered_allocator_vector: test/buffered_allocator/buffered_allocator_vector.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/buffered_allocator_vector.o test/buffered_allocator/buffered_allocator_vector.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/buffered_allocator_vector $(OBJECTS_DIR)/buffered_allocator_vector.o

allocator_vector: test/buffered_allocator/allocator_vector.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/allocator_vector.o test/buffered_allocator/allocator_vector.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/allocator_vector $(OBJECTS_DIR)/allocator_vector.o

singleton_test1: test/singleton/singleton_test1.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/singleton_test1.o test/singleton/singleton_test1.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/singleton_test1 $(OBJECTS_DIR)/singleton_test1.o

signal_chain: test/signal/chain.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/signal_chain.o test/signal/chain.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/signal_chain $(OBJECTS_DIR)/signal_chain.o

signal_test1: test/signal/test1.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/signal_test1.o test/signal/test1.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/signal_test1 $(OBJECTS_DIR)/signal_test1.o

signal_doc_view: test/signal/doc_view.cpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/signal_doc_view.o test/signal/doc_view.cpp
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/signal_doc_view $(OBJECTS_DIR)/signal_doc_view.o

signal_sample: test/signal/sample.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/signal_sample.o test/signal/sample.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/signal_sample $(OBJECTS_DIR)/signal_sample.o

laplace_1d: test/matrix/laplace_1d.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/laplace_1d.o test/matrix/laplace_1d.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/laplace_1d $(OBJECTS_DIR)/laplace_1d.o

matrix_inverse: test/matrix/matrix_inverse.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/matrix_inverse.o test/matrix/matrix_inverse.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/matrix_inverse $(OBJECTS_DIR)/matrix_inverse.o

matrix_value_plus: test/matrix/matrix_value_plus.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/matrix_value_plus.o test/matrix/matrix_value_plus.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/matrix_value_plus $(OBJECTS_DIR)/matrix_value_plus.o

matrix_value_minus: test/matrix/matrix_value_minus.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/matrix_value_minus.o test/matrix/matrix_value_minus.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/matrix_value_minus $(OBJECTS_DIR)/matrix_value_minus.o

matrix_value_divide: test/matrix/matrix_value_divide.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/matrix_value_divide.o test/matrix/matrix_value_divide.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/matrix_value_divide $(OBJECTS_DIR)/matrix_value_divide.o

value_matrix_minus: test/matrix/value_matrix_minus.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/value_matrix_minus.o test/matrix/value_matrix_minus.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/value_matrix_minus $(OBJECTS_DIR)/value_matrix_minus.o

matrix_load: test/matrix/matrix_load.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/matrix_load.o test/matrix/matrix_load.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/matrix_load $(OBJECTS_DIR)/matrix_load.o

matrix_value_multiply: test/matrix/matrix_value_multiply.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/matrix_value_multiply.o test/matrix/matrix_value_multiply.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/matrix_value_multiply $(OBJECTS_DIR)/matrix_value_multiply.o

matrix_matrix_plus: test/matrix/matrix_matrix_plus.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/matrix_matrix_plus.o test/matrix/matrix_matrix_plus.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/matrix_matrix_plus $(OBJECTS_DIR)/matrix_matrix_plus.o

matrix_matrix_minus: test/matrix/matrix_matrix_minus.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/matrix_matrix_minus.o test/matrix/matrix_matrix_minus.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/matrix_matrix_minus $(OBJECTS_DIR)/matrix_matrix_minus.o

matrix_prefix_minus: test/matrix/matrix_prefix_minus.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/matrix_prefix_minus.o test/matrix/matrix_prefix_minus.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/matrix_prefix_minus $(OBJECTS_DIR)/matrix_prefix_minus.o

matrix_prefix_plus: test/matrix/matrix_prefix_plus.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/matrix_prefix_plus.o test/matrix/matrix_prefix_plus.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/matrix_prefix_plus $(OBJECTS_DIR)/matrix_prefix_plus.o

matrix_construct: test/matrix/matrix_construct.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/matrix_construct.o test/matrix/matrix_construct.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/matrix_construct $(OBJECTS_DIR)/matrix_construct.o

matrix_llsf: test/matrix/matrix_llsf.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/matrix_llsf.o test/matrix/matrix_llsf.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/matrix_llsf $(OBJECTS_DIR)/matrix_llsf.o

cc_solve: test/matrix/solve.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/solve.o test/matrix/solve.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/cc_solve $(OBJECTS_DIR)/solve.o

matrix_nlsf: test/matrix/matrix_nlsf.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/matrix_nlsf.o test/matrix/matrix_nlsf.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/matrix_nlsf $(OBJECTS_DIR)/matrix_nlsf.o

exp_nlsf: test/matrix/exp_nlsf.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/exp_nlsf.o test/matrix/exp_nlsf.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/exp_nlsf $(OBJECTS_DIR)/exp_nlsf.o

matrix_backward_substitution: test/matrix/matrix_backward_substitution.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/matrix_backward_substitution.o test/matrix/matrix_backward_substitution.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/matrix_backward_substitution $(OBJECTS_DIR)/matrix_backward_substitution.o

matrix_expm: test/matrix/matrix_expm.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/matrix_expm.o test/matrix/matrix_expm.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/matrix_expm $(OBJECTS_DIR)/matrix_expm.o

ir_expm: test/matrix/ir_expm.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/ir_expm.o test/matrix/ir_expm.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/ir_expm $(OBJECTS_DIR)/ir_expm.o

matrix_abs: test/matrix/matrix_abs.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/matrix_abs.o test/matrix/matrix_abs.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/matrix_abs $(OBJECTS_DIR)/matrix_abs.o

matrix_range_for: test/matrix/matrix_range_for.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/matrix_range_for.o test/matrix/matrix_range_for.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/matrix_range_for $(OBJECTS_DIR)/matrix_range_for.o

matrix_reshape: test/matrix/matrix_reshape.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/matrix_reshape.o test/matrix/matrix_reshape.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/matrix_reshape $(OBJECTS_DIR)/matrix_reshape.o

matrix_matrix_multiplication: test/matrix/matrix_matrix_multiplication.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/matrix_matrix_multiplication.o test/matrix/matrix_matrix_multiplication.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/matrix_matrix_multiplication $(OBJECTS_DIR)/matrix_matrix_multiplication.o

matrix_matrix_swap: test/matrix/matrix_matrix_swap.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/matrix_matrix_swap.o test/matrix/matrix_matrix_swap.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/matrix_matrix_swap $(OBJECTS_DIR)/matrix_matrix_swap.o

matrix_lu: test/matrix/matrix_lu.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/matrix_lu.o test/matrix/matrix_lu.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/matrix_lu $(OBJECTS_DIR)/matrix_lu.o

matrix_svd: test/matrix/matrix_svd.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/matrix_svd.o test/matrix/matrix_svd.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/matrix_svd $(OBJECTS_DIR)/matrix_svd.o

matrix_clear: test/matrix/matrix_clear.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/matrix_clear.o test/matrix/matrix_clear.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/matrix_clear $(OBJECTS_DIR)/matrix_clear.o

matrix_shrink_to_size: test/matrix/matrix_shrink_to_size.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/matrix_shrink_to_size.o test/matrix/matrix_shrink_to_size.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/matrix_shrink_to_size $(OBJECTS_DIR)/matrix_shrink_to_size.o

variate_generator_an: test/variate_generator/an.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/variate_generator_an.o test/variate_generator/an.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/variate_generator_an $(OBJECTS_DIR)/variate_generator_an.o

variate_generator_uniform: test/variate_generator/uniform.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/variate_generator_uniform.o test/variate_generator/uniform.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/variate_generator_uniform $(OBJECTS_DIR)/variate_generator_uniform.o

variate_generator_arcsine: test/variate_generator/arcsine.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/variate_generator_arcsine.o test/variate_generator/arcsine.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/variate_generator_arcsine $(OBJECTS_DIR)/variate_generator_arcsine.o

variate_generator_bernoulli: test/variate_generator/bernoulli.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/variate_generator_bernoulli.o test/variate_generator/bernoulli.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/variate_generator_bernoulli $(OBJECTS_DIR)/variate_generator_bernoulli.o

variate_generator_gaussian: test/variate_generator/gaussian.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/variate_generator_gaussian.o test/variate_generator/gaussian.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/variate_generator_gaussian $(OBJECTS_DIR)/variate_generator_gaussian.o

variate_generator_normal: test/variate_generator/normal.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/variate_generator_normal.o test/variate_generator/normal.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/variate_generator_normal $(OBJECTS_DIR)/variate_generator_normal.o

genetic_algorithm_sin: test/genetic_algorithm/sin.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/genetic_algorithm_sin.o test/genetic_algorithm/sin.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/genetic_algorithm_sin $(OBJECTS_DIR)/genetic_algorithm_sin.o -pthread

exp_9: test/genetic_algorithm/exp_9.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/exp_9.o test/genetic_algorithm/exp_9.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/exp_9 $(OBJECTS_DIR)/exp_9.o -pthread

exp_16: test/genetic_algorithm/exp_16.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/exp_16.o test/genetic_algorithm/exp_16.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/exp_16 $(OBJECTS_DIR)/exp_16.o -pthread

mm_4_int: test/genetic_algorithm/mm_4_int.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/mm_4_int.o test/genetic_algorithm/mm_4_int.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/mm_4_int $(OBJECTS_DIR)/mm_4_int.o -pthread

mm_4_bigint: test/genetic_algorithm/mm_4_bigint.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/mm_4_bigint.o test/genetic_algorithm/mm_4_bigint.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/mm_4_bigint $(OBJECTS_DIR)/mm_4_bigint.o -pthread

mm_4_bi: test/genetic_algorithm/mm_4_bi.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/mm_4_bi.o test/genetic_algorithm/mm_4_bi.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/mm_4_bi $(OBJECTS_DIR)/mm_4_bi.o -pthread

mm_4_float: test/genetic_algorithm/mm_4_float.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/mm_4_float.o test/genetic_algorithm/mm_4_float.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/mm_4_float $(OBJECTS_DIR)/mm_4_float.o -pthread

mm_4_symbol: test/genetic_algorithm/mm_4_symbol.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/mm_4_symbol.o test/genetic_algorithm/mm_4_symbol.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/mm_4_symbol $(OBJECTS_DIR)/mm_4_symbol.o -pthread

cuda_matrix_matrix_multiplication: test/device_matrix/matrix_matrix_multiplication.cu
	$(CUDACXX) -c $(CUDACXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/cuda_matrix_matrix_multiplication.o test/device_matrix/matrix_matrix_multiplication.cu
	$(CUDALINK) $(CUDALFLAGS) -o $(BIN_DIR)/cuda_matrix_matrix_multiplication $(OBJECTS_DIR)/cuda_matrix_matrix_multiplication.o

cuda_device_matrix_multiplication_test: test/device_matrix/device_matrix_multiplication_test.cu
	$(CUDACXX) -c $(CUDACXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/cuda_device_matrix_multiplication_test.o test/device_matrix/device_matrix_multiplication_test.cu
	$(CUDALINK) $(CUDALFLAGS) -o $(BIN_DIR)/cuda_device_matrix_multiplication_test $(OBJECTS_DIR)/cuda_device_matrix_multiplication_test.o

cuda_5k_mm: test/device_matrix/5k_mm.cu
	$(CUDACXX) -c $(CUDACXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/cuda_5k_mm.o test/device_matrix/5k_mm.cu
	$(CUDALINK) $(CUDALFLAGS) -o $(BIN_DIR)/cuda_5k_mm $(OBJECTS_DIR)/cuda_5k_mm.o

timer: test/timer/timer.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/timer.o test/timer/timer.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/timer $(OBJECTS_DIR)/timer.o

cm_eye.o: src/cuda/cm_eye.cu
	$(CUDACXX) -c $(CUDACXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/cm_eye.o src/cuda/cm_eye.cu --ptxas-options=-v --compiler-options '-fPIC' --shared

zmatrix_eye_impl.o: src/device/kernel/device_matrix/zmatrix_eye_impl.cu
	$(CUDACXX) -c $(CUDACXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/zmatrix_eye_impl.o src/device/kernel/device_matrix/zmatrix_eye_impl.cu --ptxas-options=-v --compiler-options '-fPIC' --shared

zmatrix_poly4_eval.o: src/device/kernel/device_matrix/zmatrix_poly4_eval.cu
	$(CUDACXX) -c $(CUDACXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/zmatrix_poly4_eval.o src/device/kernel/device_matrix/zmatrix_poly4_eval.cu --ptxas-options=-v --compiler-options '-fPIC' --shared

zmatrix_memcpy_real_imag_impl.o: src/device/kernel/device_matrix/zmatrix_memcpy_real_imag_impl.cu
	$(CUDACXX) -c $(CUDACXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/zmatrix_memcpy_real_imag_impl.o src/device/kernel/device_matrix/zmatrix_memcpy_real_imag_impl.cu --ptxas-options=-v --compiler-options '-fPIC' --shared

expm_cu.o: src/expm/expm.cc
	$(CXX) -c $(GXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/expm_cu.o src/expm/expm.cc

device_allocator_test: test/device_allocator/test.cc
	$(GXX) -c $(GXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/device_allocator_test.o test/device_allocator/test.cc
	$(CUDALINK) $(CUDALFLAGS) -o $(BIN_DIR)/device_allocator_test $(OBJECTS_DIR)/device_allocator_test.o

coefficient_test: test/coefficient/co.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/coefficient_test.o test/coefficient/co.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/coefficient_test $(OBJECTS_DIR)/coefficient_test.o

marker_pair_builder_test: test/coefficient/marker_pair_builder_test.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/marker_pair_builder_test.o test/coefficient/marker_pair_builder_test.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/marker_pair_builder_test $(OBJECTS_DIR)/marker_pair_builder_test.o

matrix_symmetric_transform_test: test/coefficient/matrix_symmetric_transform.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/mst.o test/coefficient/matrix_symmetric_transform.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/matrix_symmetric_transform_test $(OBJECTS_DIR)/mst.o

amplitude_test: test/coefficient/amplitude.cc pattern_loader.o pattern_loader_parser.o
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/amplitude_test.o test/coefficient/amplitude.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/amplitude_test $(OBJECTS_DIR)/amplitude_test.o $(OBJECTS_DIR)/pattern_loader.o $(OBJECTS_DIR)/pattern_loader_parser.o

function_test: test/function/function.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/function_test.o test/function/function.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/function_test $(OBJECTS_DIR)/function_test.o

triplet_test: test/triplet/test1.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/triplet_test.o test/triplet/test1.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/triplet_test $(OBJECTS_DIR)/triplet_test.o

term_test: test/polynomial/term_test.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/term_test.o test/polynomial/term_test.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/term_test $(OBJECTS_DIR)/term_test.o

polynomial_test: test/polynomial/polynomial_test.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/polynomial_test.o test/polynomial/polynomial_test.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/polynomial_test $(OBJECTS_DIR)/polynomial_test.o

device_expm_benchmark: test/device/expm.cc lib
	$(GXX) -c $(GXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/device_expm_benchmark.o test/device/expm.cc
	$(CUDALINK) $(CUDALFLAGS) -o $(BIN_DIR)/device_expm_benchmark $(OBJECTS_DIR)/device_expm_benchmark.o ./lib/libf.a

device_cuda_devices: test/device/expm.cc
	$(GXX) -c $(GXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/device_cuda_devices.o test/device/cuda_devices.cc
	$(GXX) $(CUDALFLAGS) -o $(BIN_DIR)/device_cuda_devices $(OBJECTS_DIR)/device_cuda_devices.o

newton_test: test/nonlinear_optimization/newton_test.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/newton_test.o test/nonlinear_optimization/newton_test.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/newton_test $(OBJECTS_DIR)/newton_test.o

sp_newton_test: test/nonlinear_optimization/sp_newton_test.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/sp_newton_test.o test/nonlinear_optimization/sp_newton_test.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/sp_newton_test $(OBJECTS_DIR)/sp_newton_test.o

silicon_newton_test: test/nonlinear_optimization/silicon.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/silicon.o test/nonlinear_optimization/silicon.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/silicon_newton_test $(OBJECTS_DIR)/silicon.o

radius_only_newton_test: test/nonlinear_optimization/radius_only.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/radius_only.o test/nonlinear_optimization/radius_only.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/radius_only_newton_test $(OBJECTS_DIR)/radius_only.o

radius_split_newton_test: test/nonlinear_optimization/radius_split.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/radius_split.o test/nonlinear_optimization/radius_split.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/radius_split_newton_test $(OBJECTS_DIR)/radius_split.o

radius_sto_newton_test: test/nonlinear_optimization/radius_sto.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/radius_sto.o test/nonlinear_optimization/radius_sto.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/radius_sto_newton_test $(OBJECTS_DIR)/radius_sto.o

radius_sto_se_newton_test: test/nonlinear_optimization/radius_sto_se.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/radius_sto_se.o test/nonlinear_optimization/radius_sto_se.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/radius_sto_se_newton_test $(OBJECTS_DIR)/radius_sto_se.o

matrix_test: test/nonlinear_optimization/matrix_test.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/matrix_test.o test/nonlinear_optimization/matrix_test.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/matrix_test $(OBJECTS_DIR)/matrix_test.o

matrix_test_60: test/nonlinear_optimization/matrix_test_60.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/matrix_test_60.o test/nonlinear_optimization/matrix_test_60.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/matrix_test_60 $(OBJECTS_DIR)/matrix_test_60.o

test_test: test/test/test.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/test_test.o test/test/test.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/test_test $(OBJECTS_DIR)/test_test.o

test_stride_vector: test/stride_vector/stride_vector.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/test_stride_vector.o test/stride_vector/stride_vector.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/test_stride_vector $(OBJECTS_DIR)/test_stride_vector.o

test_elementary_pattern: test/pattern/elementary_pattern.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/test_elementary_pattern.o test/pattern/elementary_pattern.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/test_elementary_pattern $(OBJECTS_DIR)/test_elementary_pattern.o

test_coefficient_composer: test/pattern/coefficient_composer.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/test_coefficient_composer.o test/pattern/coefficient_composer.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/test_coefficient_composer $(OBJECTS_DIR)/test_coefficient_composer.o

test_silicon_pattern: test/pattern/silicon_pattern.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/test_silicon_pattern.o test/pattern/silicon_pattern.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/test_silicon_pattern $(OBJECTS_DIR)/test_silicon_pattern.o

test_index_maker: test/pattern/index_maker.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/test_index_maker.o test/pattern/index_maker.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/test_index_maker $(OBJECTS_DIR)/test_index_maker.o

test_double_square_solver: test/pattern/double_square_solver.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/test_double_square_solver.o test/pattern/double_square_solver.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/test_double_square_solver $(OBJECTS_DIR)/test_double_square_solver.o

test_simple_polynomial: test/pattern/simple_polynomial.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/test_simple_polynomial.o test/pattern/simple_polynomial.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/test_simple_polynomial $(OBJECTS_DIR)/test_simple_polynomial.o

test_array: test/array/array.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/test_array.o test/array/array.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/test_array $(OBJECTS_DIR)/test_array.o

test_ssto: test/pattern/ssto.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/test_ssto.o test/pattern/ssto.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/test_ssto $(OBJECTS_DIR)/test_ssto.o

test_second_order_approximation: test/pattern/second_order_approximation.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/test_second_order_approximation.o test/pattern/second_order_approximation.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/test_second_order_approximation $(OBJECTS_DIR)/test_second_order_approximation.o

test_mono_pattern: test/pattern/mono_pattern.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/test_mono_pattern.o test/pattern/mono_pattern.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/test_mono_pattern $(OBJECTS_DIR)/test_mono_pattern.o

test_simple_c2_polynomial: test/pattern/simple_c2_polynomial.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/test_simple_c2_polynomial.o test/pattern/simple_c2_polynomial.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/test_simple_c2_polynomial $(OBJECTS_DIR)/test_simple_c2_polynomial.o

matrix_clone: test/matrix/matrix_clone.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/matrix_clone.o test/matrix/matrix_clone.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/matrix_clone $(OBJECTS_DIR)/matrix_clone.o

matrix_conjugate_gradient_squared: test/matrix/matrix_conjugate_gradient_squared.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/matrix_conjugate_gradient_squared.o test/matrix/matrix_conjugate_gradient_squared.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/matrix_conjugate_gradient_squared $(OBJECTS_DIR)/matrix_conjugate_gradient_squared.o

test_dynamic_inverse: test/dynamic_inverse/dynamic_inverse.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/test_dynamic_inverse.o test/dynamic_inverse/dynamic_inverse.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/test_dynamic_inverse $(OBJECTS_DIR)/test_dynamic_inverse.o

test_c1_matrix: test/dynamic_inverse/c1_matrix.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/test_c1_matrix.o test/dynamic_inverse/c1_matrix.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/test_c1_matrix $(OBJECTS_DIR)/test_c1_matrix.o

test_double_square_coef_matrix: test/dynamic_inverse/double_square_coef_matrix.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/test_double_square_coef_matrix.o test/dynamic_inverse/double_square_coef_matrix.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/test_double_square_coef_matrix $(OBJECTS_DIR)/test_double_square_coef_matrix.o

test_double_square_ug_fitting: test/dynamic_inverse/double_square_ug_fitting.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/test_double_square_ug_fitting.o test/dynamic_inverse/double_square_ug_fitting.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/test_double_square_ug_fitting $(OBJECTS_DIR)/test_double_square_ug_fitting.o

test_double_square_ug_coef_fitting: test/dynamic_inverse/double_square_ug_coef_fitting.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/test_double_square_ug_coef_fitting.o test/dynamic_inverse/double_square_ug_coef_fitting.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/test_double_square_ug_coef_fitting $(OBJECTS_DIR)/test_double_square_ug_coef_fitting.o

test_range: test/range/range.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/test_range.o test/range/range.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/test_range $(OBJECTS_DIR)/test_range.o

test_printer: test/printer/printer.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/test_printer.o test/printer/printer.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/test_printer $(OBJECTS_DIR)/test_printer.o

matrix_biconjugate_gradient_stablized_method: test/matrix/matrix_biconjugate_gradient_stablized_method.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/matrix_biconjugate_gradient_stablized_method.o test/matrix/matrix_biconjugate_gradient_stablized_method.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/matrix_biconjugate_gradient_stablized_method $(OBJECTS_DIR)/matrix_biconjugate_gradient_stablized_method.o

matrix_function: test/matrix/matrix_function.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/matrix_function.o test/matrix/matrix_function.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/matrix_function $(OBJECTS_DIR)/matrix_function.o

levenberg_marquardt: test/optimization/levenberg_marquardt.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/levenberg_marquardt.o test/optimization/levenberg_marquardt.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/levenberg_marquardt $(OBJECTS_DIR)/levenberg_marquardt.o

llsf1: test/optimization/llsf1.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/llsf1.o test/optimization/llsf1.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/llsf1 $(OBJECTS_DIR)/llsf1.o

basic_nl: test/optimization/basic_nl.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/basic_nl.o test/optimization/basic_nl.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/basic_nl $(OBJECTS_DIR)/basic_nl.o

modified_nl: test/optimization/modified_nl.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/modified_nl.o test/optimization/modified_nl.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/modified_nl $(OBJECTS_DIR)/modified_nl.o

experimental_nl: test/optimization/experimental_nl.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/experimental_nl.o test/optimization/experimental_nl.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/experimental_nl $(OBJECTS_DIR)/experimental_nl.o

simulated_annealing: test/optimization/simulated_annealing.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/simulated_annealing.o test/optimization/simulated_annealing.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/simulated_annealing $(OBJECTS_DIR)/simulated_annealing.o

test_two_layers_homotopy: test/dynamic_inverse/two_layers_homotopy.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/test_two_layers_homotopy.o test/dynamic_inverse/two_layers_homotopy.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/test_two_layers_homotopy $(OBJECTS_DIR)/test_two_layers_homotopy.o

test_two_layers_homotopy_se: test/dynamic_inverse/two_layers_homotopy_se.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/test_two_layers_homotopy_se.o test/dynamic_inverse/two_layers_homotopy_se.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/test_two_layers_homotopy_se $(OBJECTS_DIR)/test_two_layers_homotopy_se.o

expm_ssto2_test: test/coefficient/expm_ssto2.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/expm_ssto2_test.o test/coefficient/expm_ssto2.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/expm_ssto2_test $(OBJECTS_DIR)/expm_ssto2_test.o

test_isolate_data: test/dynamic_inverse/isolate_data.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/test_isolate_data.o test/dynamic_inverse/isolate_data.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/test_isolate_data $(OBJECTS_DIR)/test_isolate_data.o

test_ssto2_two_layers_homotopy: test/dynamic_inverse/ssto2_two_layers_homotopy.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/test_ssto2_two_layers_homotopy.o test/dynamic_inverse/ssto2_two_layers_homotopy.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/test_ssto2_two_layers_homotopy $(OBJECTS_DIR)/test_ssto2_two_layers_homotopy.o

matrix_verify: test/polynomial/matrix_verify.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/matrix_verify.o test/polynomial/matrix_verify.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/matrix_verify $(OBJECTS_DIR)/matrix_verify.o

coefficient_matrix_test: test/coefficient/coefficient_matrix.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/coefficient_matrix_test.o test/coefficient/coefficient_matrix.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/coefficient_matrix_test $(OBJECTS_DIR)/coefficient_matrix_test.o

numeric_matrix_clear: test/numeric/matrix_clear.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/numeric_matrix_clear.o test/numeric/matrix_clear.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/numeric_matrix_clear $(OBJECTS_DIR)/numeric_matrix_clear.o

numeric_matrix_row: test/numeric/matrix_row.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/numeric_matrix_row.o test/numeric/matrix_row.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/numeric_matrix_row $(OBJECTS_DIR)/numeric_matrix_row.o

numeric_matrix_col: test/numeric/matrix_col.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/numeric_matrix_col.o test/numeric/matrix_col.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/numeric_matrix_col $(OBJECTS_DIR)/numeric_matrix_col.o

numeric_matrix_diag: test/numeric/matrix_diag.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/numeric_matrix_diag.o test/numeric/matrix_diag.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/numeric_matrix_diag $(OBJECTS_DIR)/numeric_matrix_diag.o

numeric_matrix_transpose: test/numeric/matrix_transpose.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/numeric_matrix_transpose.o test/numeric/matrix_transpose.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/numeric_matrix_transpose $(OBJECTS_DIR)/numeric_matrix_transpose.o

numeric_matrix_norm: test/numeric/matrix_norm.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/numeric_matrix_norm.o test/numeric/matrix_norm.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/numeric_matrix_norm $(OBJECTS_DIR)/numeric_matrix_norm.o -pthread

numeric_matrix_function: test/numeric/matrix_function.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/numeric_matrix_function.o test/numeric/matrix_function.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/numeric_matrix_function $(OBJECTS_DIR)/numeric_matrix_function.o -pthread

numeric_matrix_operator_plus: test/numeric/matrix_operator_plus.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/numeric_matrix_operator_plus.o test/numeric/matrix_operator_plus.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/numeric_matrix_operator_plus $(OBJECTS_DIR)/numeric_matrix_operator_plus.o -pthread

numeric_matrix_operator_minus: test/numeric/matrix_operator_minus.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/numeric_matrix_operator_minus.o test/numeric/matrix_operator_minus.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/numeric_matrix_operator_minus $(OBJECTS_DIR)/numeric_matrix_operator_minus.o -pthread

numeric_matrix_minus_operator: test/numeric/matrix_minus_operator.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/numeric_matrix_minus_operator.o test/numeric/matrix_minus_operator.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/numeric_matrix_minus_operator $(OBJECTS_DIR)/numeric_matrix_minus_operator.o -pthread

test_backward_homotopy: test/dynamic_inverse/backward_homotopy.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/test_backward_homotopy.o test/dynamic_inverse/backward_homotopy.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/test_backward_homotopy $(OBJECTS_DIR)/test_backward_homotopy.o

test_double_square_modeling: test/dynamic_inverse/double_square_modeling.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/test_double_square_modeling.o test/dynamic_inverse/double_square_modeling.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/test_double_square_modeling $(OBJECTS_DIR)/test_double_square_modeling.o

test_extract_inner_product_coefficients: test/dynamic_inverse/extract_inner_product_coefficients.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/test_extract_inner_product_coefficients.o test/dynamic_inverse/extract_inner_product_coefficients.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/test_extract_inner_product_coefficients $(OBJECTS_DIR)/test_extract_inner_product_coefficients.o

test_forward_homotopy_fitting: test/dynamic_inverse/forward_homotopy_fitting.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/test_forward_homotopy_fitting.o test/dynamic_inverse/forward_homotopy_fitting.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/test_forward_homotopy_fitting $(OBJECTS_DIR)/test_forward_homotopy_fitting.o

test_homogeneous_forward_homotopy: test/dynamic_inverse/homogeneous_forward_homotopy.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/test_homogeneous_forward_homotopy.o test/dynamic_inverse/homogeneous_forward_homotopy.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/test_homogeneous_forward_homotopy $(OBJECTS_DIR)/test_homogeneous_forward_homotopy.o

test_homogeneous_forward_homotopy_se: test/dynamic_inverse/homogeneous_forward_homotopy_se.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/test_homogeneous_forward_homotopy_se.o test/dynamic_inverse/homogeneous_forward_homotopy_se.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/test_homogeneous_forward_homotopy_se $(OBJECTS_DIR)/test_homogeneous_forward_homotopy_se.o

test_triple_homotopy: test/dynamic_inverse/triple_homotopy.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/test_triple_homotopy.o test/dynamic_inverse/triple_homotopy.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/test_triple_homotopy $(OBJECTS_DIR)/test_triple_homotopy.o

test_double_homotopy: test/dynamic_inverse/double_homotopy.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/test_double_homotopy.o test/dynamic_inverse/double_homotopy.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/test_double_homotopy $(OBJECTS_DIR)/test_double_homotopy.o

numeric_test: test/numeric/test.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/numeric_test.o test/numeric/test.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/numeric_test $(OBJECTS_DIR)/numeric_test.o

numeric_matrix_copy: test/numeric/matrix_copy.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/numeric_matrix_copy.o test/numeric/matrix_copy.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/numeric_matrix_copy $(OBJECTS_DIR)/numeric_matrix_copy.o

numeric_matrix_fill: test/numeric/matrix_fill.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/numeric_matrix_fill.o test/numeric/matrix_fill.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/numeric_matrix_fill $(OBJECTS_DIR)/numeric_matrix_fill.o

test_rosenbrock_homotopy: test/dynamic_inverse/rosenbrock_homotopy.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/test_rosenbrock_homotopy.o test/dynamic_inverse/rosenbrock_homotopy.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/test_rosenbrock_homotopy $(OBJECTS_DIR)/test_rosenbrock_homotopy.o

test_c2_fitting: test/dynamic_inverse/c2_fitting.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/test_c2_fitting.o test/dynamic_inverse/c2_fitting.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/test_c2_fitting $(OBJECTS_DIR)/test_c2_fitting.o

numeric_matrix_lu: test/numeric/matrix_lu.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/numeric_matrix_lu.o test/numeric/matrix_lu.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/numeric_matrix_lu $(OBJECTS_DIR)/numeric_matrix_lu.o

expm_2_test: test/coefficient/expm_2.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/expm_2.o test/coefficient/expm_2.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/expm_2 $(OBJECTS_DIR)/expm_2.o

recursive_lambda_test: test/recursive_lambda/recursive_lambda.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/recursive_lambda.o test/recursive_lambda/recursive_lambda.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/recursive_lambda $(OBJECTS_DIR)/recursive_lambda.o

steepest_descent: test/optimization/steepest_descent.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/steepest_descent.o test/optimization/steepest_descent.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/steepest_descent $(OBJECTS_DIR)/steepest_descent.o

steepest_descent_se: test/optimization/steepest_descent_se.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/steepest_descent_se.o test/optimization/steepest_descent_se.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/steepest_descent_se $(OBJECTS_DIR)/steepest_descent_se.o

steepest_descent_rd: test/optimization/steepest_descent_rd.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/steepest_descent_rd.o test/optimization/steepest_descent_rd.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/steepest_descent_rd $(OBJECTS_DIR)/steepest_descent_rd.o

steepest_descent_4th: test/optimization/steepest_descent_4th.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/steepest_descent_4th.o test/optimization/steepest_descent_4th.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/steepest_descent_4th $(OBJECTS_DIR)/steepest_descent_4th.o

pattern_test: test/pattern/pattern.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/pattern.o test/pattern/pattern.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/pattern_test $(OBJECTS_DIR)/pattern.o

xpattern_test: test/pattern/xpattern.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/xpattern.o test/pattern/xpattern.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/xpattern_test $(OBJECTS_DIR)/xpattern.o

test_c1_homotopy: test/dynamic_inverse/c1_homotopy.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/test_c1_homotopy.o test/dynamic_inverse/c1_homotopy.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/test_c1_homotopy $(OBJECTS_DIR)/test_c1_homotopy.o

test_direct_sd: test/dynamic_inverse/direct_sd.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/test_direct_sd.o test/dynamic_inverse/direct_sd.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/test_direct_sd $(OBJECTS_DIR)/test_direct_sd.o

test_new_direct_sd: test/dynamic_inverse/new_direct_sd.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/test_new_direct_sd.o test/dynamic_inverse/new_direct_sd.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/test_new_direct_sd $(OBJECTS_DIR)/test_new_direct_sd.o

test_extract_intensity: test/dynamic_inverse/extract_intensity.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/test_extract_intensity.o test/dynamic_inverse/extract_intensity.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/test_extract_intensity $(OBJECTS_DIR)/test_extract_intensity.o

test_initialized_direct_sd: test/dynamic_inverse/initialized_direct_sd.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/test_initialized_direct_sd.o test/dynamic_inverse/initialized_direct_sd.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/test_initialized_direct_sd $(OBJECTS_DIR)/test_initialized_direct_sd.o

daemon: test/daemon/daemon.c
	$(CC) -c $(CFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/daemon.o test/daemon/daemon.c
	$(CC) $(LFLAGS) -o $(BIN_DIR)/daemon $(OBJECTS_DIR)/daemon.o

repository: test/repository/repository.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/repository.o test/repository/repository.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/repository $(OBJECTS_DIR)/repository.o

beam_restore: test/testdata/beam_restore.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/beam_restore.o test/testdata/beam_restore.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/beam_restore $(OBJECTS_DIR)/beam_restore.o

show_intensity: test/testdata/show_intensity.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/show_intensity.o test/testdata/show_intensity.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/show_intensity $(OBJECTS_DIR)/show_intensity.o

restore_k: test/testdata/restore_k.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/restore_k.o test/testdata/restore_k.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/restore_k $(OBJECTS_DIR)/restore_k.o

parser: test/parser/parser.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/parser.o test/parser/parser.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/parser $(OBJECTS_DIR)/parser.o

makepasswd: test/parser/makepasswd.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/makepasswd.o test/parser/makepasswd.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/makepasswd $(OBJECTS_DIR)/makepasswd.o

lm: test/optimization/lm.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/lm.o test/optimization/lm.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/lm $(OBJECTS_DIR)/lm.o

lm_se: test/optimization/lm_se.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/lm_se.o test/optimization/lm_se.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/lm_se $(OBJECTS_DIR)/lm_se.o

lm_rd: test/optimization/lm_rd.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/lm_rd.o test/optimization/lm_rd.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/lm_rd $(OBJECTS_DIR)/lm_rd.o

restore_k_lm: test/testdata/restore_k_lm.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/restore_k_lm.o test/testdata/restore_k_lm.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/restore_k_lm $(OBJECTS_DIR)/restore_k_lm.o

restore_k_lm_se: test/testdata/restore_k_lm_se.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/restore_k_lm_se.o test/testdata/restore_k_lm_se.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/restore_k_lm_se $(OBJECTS_DIR)/restore_k_lm_se.o

restore_lm: test/testdata/restore_lm.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/restore_lm.o test/testdata/restore_lm.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/restore_lm $(OBJECTS_DIR)/restore_lm.o

mm_6_symbol: test/genetic_algorithm/mm_6_symbol.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/mm_6_symbol.o test/genetic_algorithm/mm_6_symbol.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/mm_6_symbol $(OBJECTS_DIR)/mm_6_symbol.o -pthread

restore_k_gaussian: test/testdata/restore_k_gaussian.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/restore_k_gaussian.o test/testdata/restore_k_gaussian.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/restore_k_gaussian $(OBJECTS_DIR)/restore_k_gaussian.o

restore_gaussian_test: test/testdata/restore_gaussian_test.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/restore_gaussian_test.o test/testdata/restore_gaussian_test.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/restore_gaussian_test $(OBJECTS_DIR)/restore_gaussian_test.o

restore_gaussian_sg: test/testdata/restore_gaussian_sg.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/restore_gaussian_sg.o test/testdata/restore_gaussian_sg.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/restore_gaussian_sg $(OBJECTS_DIR)/restore_gaussian_sg.o

variate_generator_house: test/variate_generator/house.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/variate_generator_house.o test/variate_generator/house.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/variate_generator_house $(OBJECTS_DIR)/variate_generator_house.o

restore_gaussian_test_se: test/testdata/restore_gaussian_test_se.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/restore_gaussian_test_se.o test/testdata/restore_gaussian_test_se.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/restore_gaussian_test_se $(OBJECTS_DIR)/restore_gaussian_test_se.o

restore_gaussian_hm: test/testdata/restore_gaussian_hm.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/restore_gaussian_hm.o test/testdata/restore_gaussian_hm.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/restore_gaussian_hm $(OBJECTS_DIR)/restore_gaussian_hm.o

restore_k_hm: test/testdata/restore_k_hm.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/restore_k_hm.o test/testdata/restore_k_hm.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/restore_k_hm $(OBJECTS_DIR)/restore_k_hm.o

catan: test/variate_generator/catan.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/catan.o test/variate_generator/catan.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/catan $(OBJECTS_DIR)/catan.o

exp_sim_beams: test/testdata/exp_sim_beams.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/exp_sim_beams.o test/testdata/exp_sim_beams.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/exp_sim_beams $(OBJECTS_DIR)/exp_sim_beams.o

test_direct_thickness: test/dynamic_inverse/direct_thickness.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/test_direct_thickness.o test/dynamic_inverse/direct_thickness.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/test_direct_thickness $(OBJECTS_DIR)/test_direct_thickness.o

merge_img: test/testdata/merge_img.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -I/opt/X11/include -o $(OBJECTS_DIR)/merge_img.o test/testdata/merge_img.cc
	$(CXX) $(LFLAGS) -L/opt/X11/lib -lm -lX11 -o $(BIN_DIR)/merge_img $(OBJECTS_DIR)/merge_img.o

test_pattern_simulate: cuda_pattern/src/test_sp.cc
	$(CUDACXX) -c  cuda_pattern/src/simulate_pattern.cu $(CUDACXXFLAGS) -o $(OBJECTS_DIR)/simulate_pattern.o $(INCPATH) -g -G
	$(CXX) $(CXXFLAGS) -c cuda_pattern/src/test_sp.cc -o $(OBJECTS_DIR)/test_pc.o $(INCPATH) -g
	$(CXX) -o $(BIN_DIR)/test_pattern_simulate  $(OBJECTS_DIR)/test_pc.o $(OBJECTS_DIR)/simulate_pattern.o  $(CUDALFLAGS) $(LFLAGS) -g

single_cuda_pattern: test/cuda_pattern/single_cuda_pattern.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/single_cuda_pattern.cc -o $(OBJECTS_DIR)/single_cuda_pattern.o $(INCPATH) -g
	$(CUDACXX) src/cuda_pattern/cuda_pattern.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true -g -G
	$(CUDACXX) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt -lcublas -lcublas_device $(CUDALIB) -rdc=true -g -G
	$(CXX) -o $(BIN_DIR)/single_cuda_pattern $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/single_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o  -lcudadevrt -lcublas -lcublas_device -lcudart -m64 $(CUDALIB) $(LFLAGS) -g

direct_cuda_pattern: test/cuda_pattern/direct_cuda_pattern.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/direct_cuda_pattern.cc -o $(OBJECTS_DIR)/direct_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/cuda_pattern.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt $(CUDALIB64) -rdc=true -Xptxas -v
	$(CXX) -o $(BIN_DIR)/direct_cuda_pattern $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/direct_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o  -lcudadevrt -lcublas -lcudart -m64 $(CUDALIB64) $(LFLAGS)

test_pattern_simulate_se: cuda_pattern/src/test_sp.cc
	$(CUDACXX) -c  cuda_pattern/src/cuda_pattern_se.cu $(CUDACXXFLAGS) -o $(OBJECTS_DIR)/simulate_pattern.o $(INCPATH) -g -G
	$(CXX) $(CXXFLAGS) -c cuda_pattern/src/test_sp.cc -o $(OBJECTS_DIR)/test_pc.o $(INCPATH) -g
	$(CXX) -o $(BIN_DIR)/test_pattern_simulate  $(OBJECTS_DIR)/test_pc.o $(OBJECTS_DIR)/simulate_pattern.o  $(CUDALFLAGS) $(LFLAGS) -g

test_pattern_simulate_rd: cuda_pattern/src/test_sp.cc
	$(CUDACXX) -c  cuda_pattern/src/cuda_pattern_rd.cu $(CUDACXXFLAGS) -o $(OBJECTS_DIR)/simulate_pattern.o $(INCPATH) -g -G
	$(CXX) $(CXXFLAGS) -c cuda_pattern/src/test_sp.cc -o $(OBJECTS_DIR)/test_pc.o $(INCPATH) -g
	$(CXX) -o $(BIN_DIR)/test_pattern_simulate  $(OBJECTS_DIR)/test_pc.o $(OBJECTS_DIR)/simulate_pattern.o  $(CUDALFLAGS) $(LFLAGS) -g

direct_cuda_pattern_new: test/cuda_pattern/direct_cuda_pattern.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/direct_cuda_pattern.cc -o $(OBJECTS_DIR)/direct_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/cuda_pattern_new.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true -O2  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt -lcublas $(CUDALIB64) -rdc=true -O2  -Xptxas -v
	$(CXX) -o $(BIN_DIR)/direct_cuda_pattern $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/direct_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o -lcublas -lcudadevrt -lcudart -m64 $(CUDALIB64) $(LFLAGS)

cuda_pattern_test: test/cuda_pattern/cuda_pattern_test.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/cuda_pattern_test.cc -o $(OBJECTS_DIR)/direct_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/cuda_pattern_new.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true -O2  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt -lcublas $(CUDALIB64) -rdc=true -O2  -Xptxas -v
	$(CXX) -o $(BIN_DIR)/cuda_pattern_test $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/direct_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o -lcublas -lcudadevrt -lcudart -m64 $(CUDALIB64) $(LFLAGS)

sort_tilt: test/testdata/sort_tilt.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/sort_tilt.o test/testdata/sort_tilt.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/sort_tilt $(OBJECTS_DIR)/sort_tilt.o

test_direct_thickness_20: test/dynamic_inverse/direct_thickness_20.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/test_direct_thickness_20.o test/dynamic_inverse/direct_thickness_20.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/test_direct_thickness_20 $(OBJECTS_DIR)/test_direct_thickness_20.o

test_direct_thickness_40: test/dynamic_inverse/direct_thickness_40.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/test_direct_thickness_40.o test/dynamic_inverse/direct_thickness_40.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/test_direct_thickness_40 $(OBJECTS_DIR)/test_direct_thickness_40.o

test_direct_thickness_60: test/dynamic_inverse/direct_thickness_60.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/test_direct_thickness_60.o test/dynamic_inverse/direct_thickness_60.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/test_direct_thickness_60 $(OBJECTS_DIR)/test_direct_thickness_60.o

cuda_pattern_dump: test/cuda_pattern/cuda_pattern_dump.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/cuda_pattern_dump.cc -o $(OBJECTS_DIR)/direct_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/cuda_pattern_new.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true -O2  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt -lcublas $(CUDALIB64) -rdc=true -O2  -Xptxas -v
	$(CXX) -o $(BIN_DIR)/cuda_pattern_dump $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/direct_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o -lcublas -lcudadevrt -lcudart -m64 $(CUDALIB64) $(LFLAGS)

test_direct_thickness_n: test/dynamic_inverse/direct_thickness_n.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/test_direct_thickness_n.o test/dynamic_inverse/direct_thickness_n.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/test_direct_thickness_n $(OBJECTS_DIR)/test_direct_thickness_n.o

mm_fit: test/mm_fit/mm_fit.cc
	$(CXX) $(CXXFLAGS) -c test/mm_fit/mm_fit.cc -o $(OBJECTS_DIR)/mm_fit.o $(INCPATH)
	$(CUDACXX64) -c src/mm_fit/mm_fit.cu -o $(OBJECTS_DIR)/_mm_fit.o $(INCPATH) -m64  -gencode arch=compute_30,code=sm_30 -O2  -Xptxas -v
	$(CXX) -o $(BIN_DIR)/mm_fit $(OBJECTS_DIR)/_mm_fit.o $(OBJECTS_DIR)/mm_fit.o -lcublas -lcudadevrt -lcudart -m64 $(CUDALIB64) $(LFLAGS)

direct_cuda_pattern_exclude_central: test/cuda_pattern/direct_cuda_pattern.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/direct_cuda_pattern.cc -o $(OBJECTS_DIR)/direct_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/cuda_pattern_exclude_central.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true -O2  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt -lcublas $(CUDALIB64) -rdc=true -O2  -Xptxas -v
	$(CXX) -o $(BIN_DIR)/direct_cuda_pattern $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/direct_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o -lcublas -lcudadevrt -lcudart -m64 $(CUDALIB64) $(LFLAGS)

test_pattern_extraction: test/pattern/pattern_extraction.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/test_pattern_extraction.o test/pattern/pattern_extraction.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/test_pattern_extraction $(OBJECTS_DIR)/test_pattern_extraction.o

steepest_descent_rd: test/pattern/steepest_descent_rd.cc
	#(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/steepest_descent_rd.o test/optimization/steepest_descent_rd.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/steepest_descent_rd $(OBJECTS_DIR)/steepest_descent_rd.o

steepest_descent_4th: test/optimization/steepest_descent_4th.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/steepest_descent_4th.o test/optimization/steepest_descent_4th.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/steepest_descent_4th $(OBJECTS_DIR)/steepest_descent_4th.o

pattern_test: test/pattern/pattern.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/pattern.o test/pattern/pattern.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/pattern_test $(OBJECTS_DIR)/pattern.o

xpattern_test: test/pattern/xpattern.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/xpattern.o test/pattern/xpattern.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/xpattern_test $(OBJECTS_DIR)/xpattern.o

test_c1_homotopy: test/dynamic_inverse/c1_homotopy.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/test_c1_homotopy.o test/dynamic_inverse/c1_h -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true -O2  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt -lcublas $(CUDALIB64) -rdc=true -O2  -Xptxas -v
	$(CXX) -o $(BIN_DIR)/direct_cuda_extraction $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/direct_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o -lcublas -lcudadevrt -lcudart -m64 $(CUDALIB64) $(LFLAGS)

cond_pattern_test: test/pattern/cond_pattern.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/cond_pattern.o test/pattern/cond_pattern.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/cond_pattern_test $(OBJECTS_DIR)/cond_pattern.o

test_multi_c1: test/dynamic_inverse/multi_c1.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/test_multi_c1.o test/dynamic_inverse/multi_c1.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/test_multi_c1 $(OBJECTS_DIR)/test_multi_c1.o

test_direct_multi_c1: test/dynamic_inverse/direct_multi_c1.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/test_direct_multi_c1.o test/dynamic_inverse/direct_multi_c1.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/test_direct_multi_c1 $(OBJECTS_DIR)/test_direct_multi_c1.o

direct_random_cuda_pattern: test/cuda_pattern/direct_random_cuda_pattern.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/direct_random_cuda_pattern.cc -o $(OBJECTS_DIR)/direct_random_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/cuda_pattern_new.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt $(CUDALIB64) -rdc=true -Xptxas -v
	$(CXX) -o $(BIN_DIR)/direct_random_cuda_pattern $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/direct_random_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o  -lcudadevrt -lcublas  -lcudart -m64 $(CUDALIB64) $(LFLAGS)

line_search_rd: test/optimization/line_search_rd.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/line_search_rd.o test/optimization/line_search_rd.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/line_search_rd $(OBJECTS_DIR)/line_search_rd.o

direct_random_cuda_pattern_weighed: test/cuda_pattern/direct_random_cuda_pattern_weighed.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/direct_random_cuda_pattern_weighed.cc -o $(OBJECTS_DIR)/direct_random_cuda_pattern_weighed.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/cuda_pattern_new.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt -lcublas -lcublas_device $(CUDALIB64) -rdc=true -Xptxas -v
	$(CXX) -o $(BIN_DIR)/direct_random_cuda_pattern_weighed $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/direct_random_cuda_pattern_weighed.o $(OBJECTS_DIR)/cuda_pattern.o  -lcudadevrt -lcublas -lcublas_device -lcudart -m64 $(CUDALIB64) $(LFLAGS)

test_multi_c1_test: test/dynamic_inverse/multi_c1_test.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/test_multi_c1_test.o test/dynamic_inverse/multi_c1_test.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/test_multi_c1_test $(OBJECTS_DIR)/test_multi_c1_test.o

direct_random_cuda_pattern_step_weighed: test/cuda_pattern/direct_random_cuda_pattern_step_weighed.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/direct_random_cuda_pattern_step_weighed.cc -o $(OBJECTS_DIR)/direct_random_cuda_pattern_step_weighed.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/cuda_pattern_new.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt -lcublas -lcublas_device $(CUDALIB64) -rdc=true -Xptxas -v
	$(CXX) -o $(BIN_DIR)/direct_random_cuda_pattern_step_weighed $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/direct_random_cuda_pattern_step_weighed.o $(OBJECTS_DIR)/cuda_pattern.o  -lcudadevrt -lcublas -lcublas_device -lcudart -m64 $(CUDALIB64) $(LFLAGS)

direct_random_cuda_pattern_exp_weighed: test/cuda_pattern/direct_random_cuda_pattern_exp_weighed.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/direct_random_cuda_pattern_exp_weighed.cc -o $(OBJECTS_DIR)/direct_random_cuda_pattern_exp_weighed.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/cuda_pattern_new.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt $(CUDALIB64) -rdc=true -Xptxas -v
	$(CXX) -o $(BIN_DIR)/direct_random_cuda_pattern_exp_weighed $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/direct_random_cuda_pattern_exp_weighed.o $(OBJECTS_DIR)/cuda_pattern.o  -lcudadevrt -lcublas -lcudart -m64 $(CUDALIB64) $(LFLAGS)

direct_cuda_pattern_cv: test/cuda_pattern/direct_cuda_pattern_cv.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/direct_cuda_pattern_cv.cc -o $(OBJECTS_DIR)/direct_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/cuda_pattern_new.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true  -Xptxas -v -O2
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt -lcublas $(CUDALIB64) -rdc=true   -Xptxas -v -O2
	$(CXX) -o $(BIN_DIR)/direct_cuda_pattern_cv $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/direct_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o -lcublas -lcudadevrt -lcudart -m64 $(CUDALIB64) $(LFLAGS)

matrix_initializer_list: test/matrix/matrix_initializer_list.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/matrix_initializer_list.o test/matrix/matrix_initializer_list.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/matrix_initializer_list $(OBJECTS_DIR)/matrix_initializer_list.o

direct_cuda_pattern_cv_without_offset: test/cuda_pattern/direct_cuda_pattern_cv_without_offset.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/direct_cuda_pattern_cv_without_offset.cc -o $(OBJECTS_DIR)/direct_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/cuda_pattern.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true  -Xptxas -v -O2
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt -lcublas $(CUDALIB64) -rdc=true   -Xptxas -v -O2
	$(CXX) -o $(BIN_DIR)/direct_cuda_pattern_cv_without_offset $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/direct_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o -lcublas -lcudadevrt -lcudart -m64 $(CUDALIB64) $(LFLAGS)

direct_cuda_pattern_sigmoid: test/cuda_pattern/direct_cuda_pattern_sigmoid.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/direct_cuda_pattern_sigmoid.cc -o $(OBJECTS_DIR)/direct_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/cuda_pattern_sigmoid.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true -O2  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt -lcublas $(CUDALIB64) -rdc=true -O2  -Xptxas -v
	$(CXX) -o $(BIN_DIR)/direct_cuda_pattern_sigmoid $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/direct_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o -lcublas -lcudadevrt -lcudart -m64 $(CUDALIB64) $(LFLAGS)

direct_cuda_pattern_cv_without_offset_sigmoid: test/cuda_pattern/direct_cuda_pattern_cv_without_offset.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/direct_cuda_pattern_cv_without_offset.cc -o $(OBJECTS_DIR)/direct_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/cuda_pattern_sigmoid.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true  -Xptxas -v -O2
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt -lcublas $(CUDALIB64) -rdc=true   -Xptxas -v -O2
	$(CXX) -o $(BIN_DIR)/direct_cuda_pattern_cv_without_offset_sigmoid $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/direct_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o -lcublas -lcudadevrt -lcudart -m64 $(CUDALIB64) $(LFLAGS)

direct_random_cuda_pattern_sigmoid: test/cuda_pattern/direct_random_cuda_pattern_sigmoid.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/direct_random_cuda_pattern_sigmoid.cc -o $(OBJECTS_DIR)/direct_random_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/cuda_pattern_sigmoid.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt $(CUDALIB64) -rdc=true -Xptxas -v
	$(CXX) -o $(BIN_DIR)/direct_random_cuda_pattern_sigmoid $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/direct_random_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o  -lcudadevrt -lcublas  -lcudart -m64 $(CUDALIB64) $(LFLAGS)

date_to_string_test: test/date/date_to_string.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/date_to_string_test.o test/date/date_to_string.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/date_to_string_test $(OBJECTS_DIR)/date_to_string_test.o

test_random_cuda_pattern_sigmoid: test/cuda_pattern/test_random_cuda_pattern_sigmoid.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/test_random_cuda_pattern_sigmoid.cc -o $(OBJECTS_DIR)/test_random_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/cuda_pattern_sigmoid.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt $(CUDALIB64) -rdc=true -Xptxas -v
	$(CXX) -o $(BIN_DIR)/test_random_cuda_pattern_sigmoid $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/test_random_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o  -lcudadevrt -lcublas  -lcudart -m64 $(CUDALIB64) $(LFLAGS)

test_cuda_pattern_sigmoid: test/cuda_pattern/test_cuda_pattern_sigmoid.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/test_cuda_pattern_sigmoid.cc -o $(OBJECTS_DIR)/test_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/cuda_pattern_sigmoid.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true -O2  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt -lcublas $(CUDALIB64) -rdc=true -O2  -Xptxas -v
	$(CXX) -o $(BIN_DIR)/test_cuda_pattern_sigmoid $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/test_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o -lcublas -lcudadevrt -lcudart -m64 $(CUDALIB64) $(LFLAGS)

random_cuda_pattern_sigmoid: test/cuda_pattern/random_cuda_pattern_sigmoid.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/random_cuda_pattern_sigmoid.cc -o $(OBJECTS_DIR)/random_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/cuda_pattern_sigmoid.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true -O2  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt -lcublas $(CUDALIB64) -rdc=true -O2  -Xptxas -v
	$(CXX) -o $(BIN_DIR)/random_cuda_pattern_sigmoid $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/random_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o -lcublas -lcudadevrt -lcudart -m64 $(CUDALIB64) $(LFLAGS)

pure_random_cuda_pattern_sigmoid: test/cuda_pattern/pure_random_cuda_pattern_sigmoid.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/pure_random_cuda_pattern_sigmoid.cc -o $(OBJECTS_DIR)/pure_random_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/cuda_pattern_sigmoid.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true -O2  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt -lcublas $(CUDALIB64) -rdc=true -O2  -Xptxas -v
	$(CXX) -o $(BIN_DIR)/pure_random_cuda_pattern_sigmoid $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/pure_random_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o -lcublas -lcudadevrt -lcudart -m64 $(CUDALIB64) $(LFLAGS)

zigmoid_random_cuda_pattern: test/cuda_pattern/zigmoid_random_cuda_pattern.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/zigmoid_random_cuda_pattern.cc -o $(OBJECTS_DIR)/zigmoid_random_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/zigmoid_cuda_pattern.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true -O2  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt -lcublas $(CUDALIB64) -rdc=true -O2  -Xptxas -v
	$(CXX) -o $(BIN_DIR)/zigmoid_random_cuda_pattern $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/zigmoid_random_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o -lcublas -lcudadevrt -lcudart -m64 $(CUDALIB64) $(LFLAGS)

zigmoid_homotopy_cuda_pattern: test/cuda_pattern/zigmoid_homotopy_cuda_pattern.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/zigmoid_homotopy_cuda_pattern.cc -o $(OBJECTS_DIR)/zigmoid_homotopy_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/zigmoid_cuda_pattern.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true -O2  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt -lcublas $(CUDALIB64) -rdc=true -O2  -Xptxas -v
	$(CXX) -o $(BIN_DIR)/zigmoid_homotopy_cuda_pattern $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/zigmoid_homotopy_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o -lcublas -lcudadevrt -lcudart -m64 $(CUDALIB64) $(LFLAGS)

zigmoid_random_cuda_pattern_cv: test/cuda_pattern/zigmoid_random_cuda_pattern_cv.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/zigmoid_random_cuda_pattern_cv.cc -o $(OBJECTS_DIR)/zigmoid_random_cuda_pattern_cv.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/zigmoid_cuda_pattern.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true -O2  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt -lcublas $(CUDALIB64) -rdc=true -O2  -Xptxas -v
	$(CXX) -o $(BIN_DIR)/zigmoid_random_cuda_pattern_cv $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/zigmoid_random_cuda_pattern_cv.o $(OBJECTS_DIR)/cuda_pattern.o -lcublas -lcudadevrt -lcudart -m64 $(CUDALIB64) $(LFLAGS)

test_dump_triplet: test/dynamic_inverse/dump_triplet.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/test_dump_triplet.o test/dynamic_inverse/dump_triplet.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/test_dump_triplet $(OBJECTS_DIR)/test_dump_triplet.o

zigmoid_homotopy_cuda_pattern_cv: test/cuda_pattern/zigmoid_homotopy_cuda_pattern_cv.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/zigmoid_homotopy_cuda_pattern_cv.cc -o $(OBJECTS_DIR)/zigmoid_homotopy_cuda_pattern_cv.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/zigmoid_cuda_pattern.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true -O2  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt -lcublas $(CUDALIB64) -rdc=true -O2  -Xptxas -v
	$(CXX) -o $(BIN_DIR)/zigmoid_homotopy_cuda_pattern_cv $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/zigmoid_homotopy_cuda_pattern_cv.o $(OBJECTS_DIR)/cuda_pattern.o -lcublas -lcudadevrt -lcudart -m64 $(CUDALIB64) $(LFLAGS)

polynomial_matrix: test/polynomial/polynomial_matrix.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/polynomial_matrix.o test/polynomial/polynomial_matrix.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/polynomial_matrix $(OBJECTS_DIR)/polynomial_matrix.o

variate_generator_create_header: test/variate_generator/an.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/variate_generator_create_header.o test/variate_generator/create_header.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/variate_generator_create_header $(OBJECTS_DIR)/variate_generator_create_header.o

test_c1_approximation: test/pattern/test_c1_approximation.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/test_test_c1_approximation.o test/pattern/test_c1_approximation.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/test_c1_approximation $(OBJECTS_DIR)/test_test_c1_approximation.o

zigmoid_homotopy_cuda_pattern_function: test/cuda_pattern/zigmoid_homotopy_cuda_pattern_function.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/zigmoid_homotopy_cuda_pattern_function.cc -o $(OBJECTS_DIR)/zigmoid_homotopy_cuda_pattern_function.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/zigmoid_cuda_pattern.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true -O2  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt -lcublas $(CUDALIB64) -rdc=true -O2  -Xptxas -v
	$(CXX) -o $(BIN_DIR)/zigmoid_homotopy_cuda_pattern_function $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/zigmoid_homotopy_cuda_pattern_function.o $(OBJECTS_DIR)/cuda_pattern.o -lcublas -lcudadevrt -lcudart -m64 $(CUDALIB64) $(LFLAGS)

zigmoid_homotopy_cuda_pattern_c1: test/cuda_pattern/zigmoid_homotopy_cuda_pattern_c1.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/zigmoid_homotopy_cuda_pattern_c1.cc -o $(OBJECTS_DIR)/zigmoid_homotopy_cuda_pattern_c1.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/zigmoid_cuda_pattern.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true -O2  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt -lcublas $(CUDALIB64) -rdc=true -O2  -Xptxas -v
	$(CXX) -o $(BIN_DIR)/zigmoid_homotopy_cuda_pattern_c1 $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/zigmoid_homotopy_cuda_pattern_c1.o $(OBJECTS_DIR)/cuda_pattern.o -lcublas -lcudadevrt -lcudart -m64 $(CUDALIB64) $(LFLAGS)

diagonal_zigmoid_homotopy_cuda_pattern_c1: test/cuda_pattern/diagonal_zigmoid_homotopy_cuda_pattern_c1.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/diagonal_zigmoid_homotopy_cuda_pattern_c1.cc -o $(OBJECTS_DIR)/zigmoid_homotopy_cuda_pattern_c1.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/diagonal_zigmoid_cuda_pattern.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true -O2  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt -lcublas $(CUDALIB64) -rdc=true -O2  -Xptxas -v
	$(CXX) -o $(BIN_DIR)/diagonal_zigmoid_homotopy_cuda_pattern_c1 $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/zigmoid_homotopy_cuda_pattern_c1.o $(OBJECTS_DIR)/cuda_pattern.o -lcublas -lcudadevrt -lcudart -m64 $(CUDALIB64) $(LFLAGS)

random_cuda_pattern_exclude_central: test/cuda_pattern/random_cuda_pattern_exclude_central.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/random_cuda_pattern_exclude_central.cc -o $(OBJECTS_DIR)/random_cuda_pattern_exclude_central.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/cuda_pattern_exclude_central.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true -O2  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt -lcublas $(CUDALIB64) -rdc=true -O2  -Xptxas -v
	$(CXX) -o $(BIN_DIR)/random_cuda_pattern_exclude_central $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/random_cuda_pattern_exclude_central.o $(OBJECTS_DIR)/cuda_pattern.o -lcublas -lcudadevrt -lcudart -m64 $(CUDALIB64) $(LFLAGS)

fixed_cuda_pattern: test/cuda_pattern/fixed_cuda_pattern.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/fixed_cuda_pattern.cc -o $(OBJECTS_DIR)/fixed_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/cuda_pattern_new.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt $(CUDALIB64) -rdc=true -Xptxas -v
	$(CXX) -o $(BIN_DIR)/fixed_cuda_pattern $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/fixed_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o  -lcudadevrt -lcublas  -lcudart -m64 $(CUDALIB64) $(LFLAGS)

scaled_fixed_cuda_pattern: test/cuda_pattern/scaled_fixed_cuda_pattern.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/scaled_fixed_cuda_pattern.cc -o $(OBJECTS_DIR)/fixed_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/scaled_cuda_pattern_new.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt $(CUDALIB64) -rdc=true -Xptxas -v
	$(CXX) -o $(BIN_DIR)/scaled_fixed_cuda_pattern $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/fixed_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o  -lcudadevrt -lcublas  -lcudart -m64 $(CUDALIB64) $(LFLAGS)

scaler_c1_fixed_cuda_pattern: test/cuda_pattern/scaler_c1_fixed_cuda_pattern.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/scaler_c1_fixed_cuda_pattern.cc -o $(OBJECTS_DIR)/scaler_c1_fixed_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/scaler_cuda_pattern_new.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt $(CUDALIB64) -rdc=true -Xptxas -v
	$(CXX) -o $(BIN_DIR)/scaler_c1_fixed_cuda_pattern $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/scaler_c1_fixed_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o  -lcudadevrt -lcublas  -lcudart -m64 $(CUDALIB64) $(LFLAGS)

direct_cuda_pattern_weighted: test/cuda_pattern/direct_cuda_pattern_weighted.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/direct_cuda_pattern_weighted.cc -o $(OBJECTS_DIR)/direct_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/cuda_pattern_weighted.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true -O2  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt -lcublas $(CUDALIB64) -rdc=true -O2  -Xptxas -v
	$(CXX) -o $(BIN_DIR)/direct_cuda_pattern_weighted $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/direct_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o -lcublas -lcudadevrt -lcudart -m64 $(CUDALIB64) $(LFLAGS)

direct_cuda_pattern_trimmed: test/cuda_pattern/direct_cuda_pattern_trimmed.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/direct_cuda_pattern_trimmed.cc -o $(OBJECTS_DIR)/direct_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/cuda_pattern_new.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true -O2  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt -lcublas $(CUDALIB64) -rdc=true -O2  -Xptxas -v
	$(CXX) -o $(BIN_DIR)/direct_cuda_pattern_trimmed $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/direct_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o -lcublas -lcudadevrt -lcudart -m64 $(CUDALIB64) $(LFLAGS)

direct_cuda_pattern_weighted_new: test/cuda_pattern/direct_cuda_pattern_weighted_new.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/direct_cuda_pattern_weighted_new.cc -o $(OBJECTS_DIR)/direct_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/cuda_pattern_weighted_new.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true -O2  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt -lcublas $(CUDALIB64) -rdc=true -O2  -Xptxas -v
	$(CXX) -o $(BIN_DIR)/direct_cuda_pattern_weighted $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/direct_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o -lcublas -lcudadevrt -lcudart -m64 $(CUDALIB64) $(LFLAGS)

direct_cuda_pattern_trimmed_4pi: test/cuda_pattern/direct_cuda_pattern_trimmed_4pi.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/direct_cuda_pattern_trimmed_4pi.cc -o $(OBJECTS_DIR)/direct_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/cuda_pattern_new.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true -O2  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt -lcublas $(CUDALIB64) -rdc=true -O2  -Xptxas -v
	$(CXX) -o $(BIN_DIR)/direct_cuda_pattern_trimmed_4pi $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/direct_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o -lcublas -lcudadevrt -lcudart -m64 $(CUDALIB64) $(LFLAGS)

c1_zigmoid_homotopy_cuda_pattern: test/cuda_pattern/c1_zigmoid_homotopy_cuda_pattern.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/c1_zigmoid_homotopy_cuda_pattern.cc -o $(OBJECTS_DIR)/c1_zigmoid_homotopy_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/zigmoid_cuda_pattern.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true -O2  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt -lcublas $(CUDALIB64) -rdc=true -O2  -Xptxas -v
	$(CXX) -o $(BIN_DIR)/c1_zigmoid_homotopy_cuda_pattern $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/c1_zigmoid_homotopy_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o -lcublas -lcudadevrt -lcudart -m64 $(CUDALIB64) $(LFLAGS)

c1_scaled_zigmoid_homotopy_cuda_pattern: test/cuda_pattern/c1_scaled_zigmoid_homotopy_cuda_pattern.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/c1_scaled_zigmoid_homotopy_cuda_pattern.cc -o $(OBJECTS_DIR)/c1_scaled_zigmoid_homotopy_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/thickness_scaled_zigmoid_cuda_pattern.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true -O2  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt -lcublas $(CUDALIB64) -rdc=true -O2  -Xptxas -v
	$(CXX) -o $(BIN_DIR)/c1_scaled_zigmoid_homotopy_cuda_pattern $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/c1_scaled_zigmoid_homotopy_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o -lcublas -lcudadevrt -lcudart -m64 $(CUDALIB64) $(LFLAGS)

ackley: test/test_function/ackley.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/ackley.o test/test_function/ackley.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/ackley $(OBJECTS_DIR)/ackley.o

rosenbrock_valley: test/test_function/rosenbrock_valley.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/rosenbrock_valley.o test/test_function/rosenbrock_valley.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/rosenbrock_valley $(OBJECTS_DIR)/rosenbrock_valley.o

c1_constrain_scaled_zigmoid_homotopy_cuda_pattern: test/cuda_pattern/c1_constrain_scaled_zigmoid_homotopy_cuda_pattern.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/c1_constrain_scaled_zigmoid_homotopy_cuda_pattern.cc -o $(OBJECTS_DIR)/c1_constrain_scaled_zigmoid_homotopy_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/thickness_scaled_zigmoid_cuda_pattern.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true -O2  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt -lcublas $(CUDALIB64) -rdc=true -O2  -Xptxas -v
	$(CXX) -o $(BIN_DIR)/c1_constrain_scaled_zigmoid_homotopy_cuda_pattern $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/c1_constrain_scaled_zigmoid_homotopy_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o -lcublas -lcudadevrt -lcudart -m64 $(CUDALIB64) $(LFLAGS)

direct_cuda_xpattern: test/cuda_pattern/direct_cuda_xpattern.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/direct_cuda_xpattern.cc -o $(OBJECTS_DIR)/direct_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/cuda_xpattern.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true -O2  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt -lcublas $(CUDALIB64) -rdc=true -O2  -Xptxas -v
	$(CXX) -o $(BIN_DIR)/direct_cuda_pattern $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/direct_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o -lcublas -lcudadevrt -lcudart -m64 $(CUDALIB64) $(LFLAGS)

matrix_min: test/matrix/min.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/min.o test/matrix/min.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/matrix_min $(OBJECTS_DIR)/min.o

tilted_c1_constrain_scaled_zigmoid_homotopy_cuda_pattern: test/cuda_pattern/tilted_c1_constrain_scaled_zigmoid_homotopy_cuda_pattern.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/tilted_c1_constrain_scaled_zigmoid_homotopy_cuda_pattern.cc -o $(OBJECTS_DIR)/tilted_c1_constrain_scaled_zigmoid_homotopy_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/tilted_thickness_scaled_zigmoid_cuda_pattern.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true -O2  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt -lcublas $(CUDALIB64) -rdc=true -O2  -Xptxas -v
	$(CXX) -o $(BIN_DIR)/tilted_c1_constrain_scaled_zigmoid_homotopy_cuda_pattern $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/tilted_c1_constrain_scaled_zigmoid_homotopy_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o -lcublas -lcudadevrt -lcudart -m64 $(CUDALIB64) $(LFLAGS)

tilted_cuda_pattern_test: test/cuda_pattern/tilted_cuda_pattern_test.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/tilted_cuda_pattern_test.cc -o $(OBJECTS_DIR)/direct_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/tilted_thickness_scaled_zigmoid_cuda_pattern.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true -O2  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt -lcublas $(CUDALIB64) -rdc=true -O2  -Xptxas -v
	$(CXX) -o $(BIN_DIR)/tilted_cuda_pattern_test $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/direct_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o -lcublas -lcudadevrt -lcudart -m64 $(CUDALIB64) $(LFLAGS)

alpha_beta_tilted_c1_constrain_scaled_zigmoid_homotopy_cuda_pattern: test/cuda_pattern/alpha_beta_tilted_c1_constrain_scaled_zigmoid_homotopy_cuda_pattern.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/alpha_beta_tilted_c1_constrain_scaled_zigmoid_homotopy_cuda_pattern.cc -o $(OBJECTS_DIR)/alpha_beta_tilted_c1_constrain_scaled_zigmoid_homotopy_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/tilted_thickness_scaled_zigmoid_cuda_pattern.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true -O2  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt -lcublas $(CUDALIB64) -rdc=true -O2  -Xptxas -v
	$(CXX) -o $(BIN_DIR)/alpha_beta_tilted_c1_constrain_scaled_zigmoid_homotopy_cuda_pattern $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/alpha_beta_tilted_c1_constrain_scaled_zigmoid_homotopy_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o -lcublas -lcudadevrt -lcudart -m64 $(CUDALIB64) $(LFLAGS)

cuda.o:src/cuda/cuda.cu
	$(CUDACXX64) -c src/cuda/cuda.cu -O2 -o $(OBJECTS_DIR)/cuda.o

libcuda.a:cuda.o
	ar cr $(LIB_DIR)/libcuda.a $(OBJECTS_DIR)/cuda.o

alpha_beta_gamma_reverse_cuda_pattern: test/cuda_pattern/alpha_beta_gamma_reverse_cuda_pattern.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/alpha_beta_gamma_reverse_cuda_pattern.cc -o $(OBJECTS_DIR)/alpha_beta_gamma_reverse_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/alpha_beta_gamma_reverse_cuda_pattern.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true -O2  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt -lcublas $(CUDALIB64) -rdc=true -O2  -Xptxas -v
	$(CXX) -o $(BIN_DIR)/alpha_beta_gamma_reverse_cuda_pattern $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/alpha_beta_gamma_reverse_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o -lcublas -lcudadevrt -lcudart -m64 $(CUDALIB64) $(LFLAGS)

ug_test: test/pattern/ug.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/ug.o test/pattern/ug.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/ug_test $(OBJECTS_DIR)/ug.o

tilted_reverse_cuda_pattern: test/cuda_pattern/tilted_reverse_cuda_pattern.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/tilted_reverse_cuda_pattern.cc -o $(OBJECTS_DIR)/tilted_reverse_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/tilted_thickness_scaled_zigmoid_cuda_pattern.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true -O2  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt -lcublas $(CUDALIB64) -rdc=true -O2  -Xptxas -v
	$(CXX) -o $(BIN_DIR)/tilted_reverse_cuda_pattern $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/tilted_reverse_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o -lcublas -lcudadevrt -lcudart -m64 $(CUDALIB64) $(LFLAGS)


alpha_beta_tilted_reverse_homotopy_cuda_pattern: test/cuda_pattern/alpha_beta_tilted_reverse_homotopy_cuda_pattern.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/alpha_beta_tilted_reverse_homotopy_cuda_pattern.cc -o $(OBJECTS_DIR)/alpha_beta_tilted_reverse_homotopy_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/tilted_thickness_scaled_zigmoid_cuda_pattern.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true -O2  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt -lcublas $(CUDALIB64) -rdc=true -O2  -Xptxas -v
	$(CXX) -o $(BIN_DIR)/alpha_beta_tilted_reverse_homotopy_cuda_pattern $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/alpha_beta_tilted_reverse_homotopy_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o -lcublas -lcudadevrt -lcudart -m64 $(CUDALIB64) $(LFLAGS)

tilted_reverse_cuda_pattern_exclude_central: test/cuda_pattern/tilted_reverse_cuda_pattern.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/tilted_reverse_cuda_pattern.cc -o $(OBJECTS_DIR)/tilted_reverse_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/tilted_thickness_scaled_zigmoid_cuda_pattern_exclude_central.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true -O2  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt -lcublas $(CUDALIB64) -rdc=true -O2  -Xptxas -v
	$(CXX) -o $(BIN_DIR)/tilted_reverse_cuda_pattern $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/tilted_reverse_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o -lcublas -lcudadevrt -lcudart -m64 $(CUDALIB64) $(LFLAGS)

tilted_c1_constrain_scaled_zigmoid_homotopy_cuda_pattern_exclude_central: test/cuda_pattern/tilted_c1_constrain_scaled_zigmoid_homotopy_cuda_pattern.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/tilted_c1_constrain_scaled_zigmoid_homotopy_cuda_pattern.cc -o $(OBJECTS_DIR)/tilted_c1_constrain_scaled_zigmoid_homotopy_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/tilted_thickness_scaled_zigmoid_cuda_pattern_exclude_central.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true -O2  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt -lcublas $(CUDALIB64) -rdc=true -O2  -Xptxas -v
	$(CXX) -o $(BIN_DIR)/tilted_c1_constrain_scaled_zigmoid_homotopy_cuda_pattern $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/tilted_c1_constrain_scaled_zigmoid_homotopy_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o -lcublas -lcudadevrt -lcudart -m64 $(CUDALIB64) $(LFLAGS)

alpha_beta_tilted_c1_constrain_scaled_zigmoid_homotopy_cuda_pattern_exclude_central: test/cuda_pattern/alpha_beta_tilted_c1_constrain_scaled_zigmoid_homotopy_cuda_pattern.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/alpha_beta_tilted_c1_constrain_scaled_zigmoid_homotopy_cuda_pattern.cc -o $(OBJECTS_DIR)/alpha_beta_tilted_c1_constrain_scaled_zigmoid_homotopy_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/tilted_thickness_scaled_zigmoid_cuda_pattern_exclude_central.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true -O2  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt -lcublas $(CUDALIB64) -rdc=true -O2  -Xptxas -v
	$(CXX) -o $(BIN_DIR)/alpha_beta_tilted_c1_constrain_scaled_zigmoid_homotopy_cuda_pattern $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/alpha_beta_tilted_c1_constrain_scaled_zigmoid_homotopy_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o -lcublas -lcudadevrt -lcudart -m64 $(CUDALIB64) $(LFLAGS)

complex_optimization: test/optimization/complex_optimization.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/complex_optimization.o test/optimization/complex_optimization.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/complex_optimization $(OBJECTS_DIR)/complex_optimization.o

polynomial_coefficient_matrix: test/polynomial/coefficient_matrix.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/coefficient_matrix.o test/polynomial/coefficient_matrix.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/coefficient_matrix $(OBJECTS_DIR)/coefficient_matrix.o

optimization_matrix_coef_fit: test/optimization/matrix_coef_fit.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/matrix_coef_fit.o test/optimization/matrix_coef_fit.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/optimization_matrix_coef_fit $(OBJECTS_DIR)/matrix_coef_fit.o

parallel_test: test/parallel/parallel.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/parallel_test.o test/parallel/parallel.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/parallel_test $(OBJECTS_DIR)/parallel_test.o -pthread

beam_test: test/beam/beam.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/beam_test.o test/beam/beam.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/beam_test $(OBJECTS_DIR)/beam_test.o

refine_tilt_test: test/refine_tilt/refine_tilt.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/refine_tilt_test.o test/refine_tilt/refine_tilt.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/refine_tilt_test $(OBJECTS_DIR)/refine_tilt_test.o

refine_tilt_cuda_test: test/refine_tilt/refine_tilt_cuda.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/refine_tilt_test.o test/refine_tilt/refine_tilt_cuda.cc
	$(CUDACXX64) -c test/refine_tilt/refine_diff.cu -o $(OBJECTS_DIR)/refine_diff.o $(INCPATH) -m64 -gencode arch=compute_35,code=sm_35 -O2  -Xptxas -v
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/refine_tilt_cuda_test $(OBJECTS_DIR)/refine_tilt_test.o $(OBJECTS_DIR)/refine_diff.o -lcublas -lcudadevrt -lcudart -m64 $(CUDALIB64)


refine_tilt_abs_test: test/refine_tilt/refine_tilt_abs.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/refine_tilt_abs_test.o test/refine_tilt/refine_tilt_abs.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/refine_tilt_abs_test $(OBJECTS_DIR)/refine_tilt_abs_test.o

cereal_test: test/cereal/cereal.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/cereal_test.o test/cereal/cereal.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/cereal_test $(OBJECTS_DIR)/cereal_test.o

pattern_refinement_config_test: test/pattern_refinement/pattern_refinement_config.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/pattern_refinement_config_test.o test/pattern_refinement/pattern_refinement_config.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/pattern_refinement_config_test $(OBJECTS_DIR)/pattern_refinement_config_test.o

cpu_space_pattern_test: test/pattern_refinement/cpu_space_pattern.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/cpu_space_pattern_test.o test/pattern_refinement/cpu_space_pattern.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/cpu_space_pattern_test $(OBJECTS_DIR)/cpu_space_pattern_test.o

c1_pattern_refinement_test: test/pattern_refinement/c1_pattern.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/c1_pattern_test.o test/pattern_refinement/c1_pattern.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/c1_pattern_test $(OBJECTS_DIR)/c1_pattern_test.o

c1_refinement_test: test/pattern_refinement/c1_refinement.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/c1_refinement_test.o test/pattern_refinement/c1_refinement.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/c1_refinement_test $(OBJECTS_DIR)/c1_refinement_test.o

c1_refinement_exclude_central_test: test/pattern_refinement/c1_refinement_exclude_central.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/c1_refinement_exclude_central_test.o test/pattern_refinement/c1_refinement_exclude_central.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/c1_refinement_exclude_central_test $(OBJECTS_DIR)/c1_refinement_exclude_central_test.o

full_c1_refinement_exclude_central_test: test/pattern_refinement/full_c1_refinement_exclude_central.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/full_c1_refinement_exclude_central_test.o test/pattern_refinement/full_c1_refinement_exclude_central.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/full_c1_refinement_exclude_central_test $(OBJECTS_DIR)/full_c1_refinement_exclude_central_test.o

pattern_to_image_test: test/pattern_to_image/pattern_to_image.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/pattern_to_image_test.o test/pattern_to_image/pattern_to_image.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/pattern_to_image_test $(OBJECTS_DIR)/pattern_to_image_test.o

# pattern_to_image_test: test/test/pattern_to_image/pattern_to_image.cc
# 	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/pattern_to_image_test.o test/test/pattern_to_image/pattern_to_image.cc
# 	$(LINK) $(LFLAGS) -o $(BIN_DIR)/pattern_to_image_test $(OBJECTS_DIR)/pattern_to_image_test.o

matrix_save_as_bmp: test/matrix/matrix_save_as_bmp.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/matrix_save_as_bmp.o test/matrix/matrix_save_as_bmp.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/matrix_save_as_bmp $(OBJECTS_DIR)/matrix_save_as_bmp.o

matrix_save_as_full_bmp: test/matrix/matrix_save_as_full_bmp.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/matrix_save_as_full_bmp.o test/matrix/matrix_save_as_full_bmp.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/matrix_save_as_full_bmp $(OBJECTS_DIR)/matrix_save_as_full_bmp.o

generate_classic_pattern_test: test/pattern_refinement/generate_classic_pattern.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/generate_classic_pattern_test.o test/pattern_refinement/generate_classic_pattern.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/generate_classic_pattern_test $(OBJECTS_DIR)/generate_classic_pattern_test.o

new_c1_constrain_scaled_zigmoid_homotopy_cuda_pattern: test/cuda_pattern/new_c1_constrain_scaled_zigmoid_homotopy_cuda_pattern.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/new_c1_constrain_scaled_zigmoid_homotopy_cuda_pattern.cc -o $(OBJECTS_DIR)/new_c1_constrain_scaled_zigmoid_homotopy_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/thickness_scaled_zigmoid_cuda_pattern.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true -O2  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt -lcublas $(CUDALIB64) -rdc=true -O2  -Xptxas -v
	$(CXX) -o $(BIN_DIR)/new_c1_constrain_scaled_zigmoid_homotopy_cuda_pattern $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/new_c1_constrain_scaled_zigmoid_homotopy_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o -lcublas -lcudadevrt -lcudart -m64 $(CUDALIB64) $(LFLAGS)

make_ar_test: test/beam/make_ar.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/make_ar_test.o test/beam/make_ar.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/make_ar_test $(OBJECTS_DIR)/make_ar_test.o

matrix_ug: test/matrix/matrix_ug.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/matrix_ug.o test/matrix/matrix_ug.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/matrix_ug $(OBJECTS_DIR)/matrix_ug.o

dump_ug_test: test/qeda/dump_ug.cc readparams.o lib
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/dump_ug_test.o test/qeda/dump_ug.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/dump_ug_test $(OBJECTS_DIR)/dump_ug_test.o $(OBJECTS_DIR)/readparams.o $(LIB_DIR)/libf.a $(CUDALFLAGS)

refine_thickness_test: test/refine_thickness/refine_thickness.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/refine_thickness_test.o test/refine_thickness/refine_thickness.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/refine_thickness_test $(OBJECTS_DIR)/refine_thickness_test.o

refine_kt_test: test/refine_tilt/refine_kt.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/refine_kt_test.o test/refine_tilt/refine_kt.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/refine_kt_test $(OBJECTS_DIR)/refine_kt_test.o

refine_kt_se_test: test/refine_tilt/refine_kt_se.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/refine_kt_se_test.o test/refine_tilt/refine_kt_se.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/refine_kt_se_test $(OBJECTS_DIR)/refine_kt_se_test.o

refine_kt_rd_test: test/refine_tilt/refine_kt_rd.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/refine_kt_rd_test.o test/refine_tilt/refine_kt_rd.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/refine_kt_rd_test $(OBJECTS_DIR)/refine_kt_rd_test.o

cross_full_c1_refinement_exclude_central_test: test/pattern_refinement/cross_full_c1_refinement_exclude_central.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/cross_full_c1_refinement_exclude_central_test.o test/pattern_refinement/cross_full_c1_refinement_exclude_central.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/cross_full_c1_refinement_exclude_central_test $(OBJECTS_DIR)/cross_full_c1_refinement_exclude_central_test.o

make_beam_selection_test: test/beam/make_beam_selection.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/make_beam_selection_test.o test/beam/make_beam_selection.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/make_beam_selection_test $(OBJECTS_DIR)/make_beam_selection_test.o

make_tilt_list_test: test/beam/make_tilt_list.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/make_tilt_list_test.o test/beam/make_tilt_list.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/make_tilt_list_test $(OBJECTS_DIR)/make_tilt_list_test.o

make_diag_test: test/beam/make_diag.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/make_diag_test.o test/beam/make_diag.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/make_diag_test $(OBJECTS_DIR)/make_diag_test.o

potential_test: test/potential/potential.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/potential_test.o test/potential/potential.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/potential_test $(OBJECTS_DIR)/potential_test.o

make_beam_test: test/beam/make_beam.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/make_beam_test.o test/beam/make_beam.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/make_beam_test $(OBJECTS_DIR)/make_beam_test.o

make_nth_beam_test: test/beam/make_nth_beam.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/make_nth_beam_test.o test/beam/make_nth_beam.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/make_nth_beam_test $(OBJECTS_DIR)/make_nth_beam_test.o

select_beam_test: test/beam/select_beam.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/select_beam_test.o test/beam/select_beam.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/select_beam_test $(OBJECTS_DIR)/select_beam_test.o

direct_diag60_cuda_pattern: test/cuda_pattern/direct_diag60_cuda_pattern.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/direct_diag60_cuda_pattern.cc -o $(OBJECTS_DIR)/direct_diag60_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/cuda_pattern.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt $(CUDALIB64) -rdc=true -Xptxas -v
	$(CXX) -o $(BIN_DIR)/direct_diag60_cuda_pattern $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/direct_diag60_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o  -lcudadevrt -lcublas -lcudart -m64 $(CUDALIB64) $(LFLAGS)

direct_diag50_cuda_pattern: test/cuda_pattern/direct_diag50_cuda_pattern.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/direct_diag50_cuda_pattern.cc -o $(OBJECTS_DIR)/direct_diag50_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/cuda_pattern.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt $(CUDALIB64) -rdc=true -Xptxas -v
	$(CXX) -o $(BIN_DIR)/direct_diag50_cuda_pattern $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/direct_diag50_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o  -lcudadevrt -lcublas -lcudart -m64 $(CUDALIB64) $(LFLAGS)

make_a_test: test/beam/make_a.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/make_a_test.o test/beam/make_a.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/make_a_test $(OBJECTS_DIR)/make_a_test.o

refine_diffraction_test: test/refine_tilt/refine_diffraction.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/refine_diffraction_test.o test/refine_tilt/refine_diffraction.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/refine_diffraction_test $(OBJECTS_DIR)/refine_diffraction_test.o

direct_diag40_cuda_pattern: test/cuda_pattern/direct_diag40_cuda_pattern.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/direct_diag40_cuda_pattern.cc -o $(OBJECTS_DIR)/direct_diag40_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/cuda_pattern.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt $(CUDALIB64) -rdc=true -Xptxas -v
	$(CXX) -o $(BIN_DIR)/direct_diag40_cuda_pattern $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/direct_diag40_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o  -lcudadevrt -lcublas -lcudart -m64 $(CUDALIB64) $(LFLAGS)

ug_refinement_test: test/pattern_refinement/ug_refinement.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/ug_refinement_test.o test/pattern_refinement/ug_refinement.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/ug_refinement_test $(OBJECTS_DIR)/ug_refinement_test.o

direct_selected_cuda_pattern: test/cuda_pattern/direct_selected_cuda_pattern.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/direct_selected_cuda_pattern.cc -o $(OBJECTS_DIR)/direct_selected_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/cuda_pattern.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt $(CUDALIB64) -rdc=true -Xptxas -v
	$(CXX) -o $(BIN_DIR)/direct_selected_cuda_pattern $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/direct_selected_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o  -lcudadevrt -lcublas -lcudart -m64 $(CUDALIB64) $(LFLAGS)

direct_selected_cuda_pattern_full: test/cuda_pattern/direct_selected_cuda_pattern_full.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/direct_selected_cuda_pattern_full.cc -o $(OBJECTS_DIR)/direct_selected_cuda_pattern_full.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/cuda_pattern.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt $(CUDALIB64) -rdc=true -Xptxas -v
	$(CXX) -o $(BIN_DIR)/direct_selected_cuda_pattern_full $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/direct_selected_cuda_pattern_full.o $(OBJECTS_DIR)/cuda_pattern.o  -lcudadevrt -lcublas -lcudart -m64 $(CUDALIB64) $(LFLAGS)

direct_selected_cuda_pattern_weighted_full: test/cuda_pattern/direct_selected_cuda_pattern_weighted_full.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/direct_selected_cuda_pattern_weighted_full.cc -o $(OBJECTS_DIR)/direct_selected_cuda_pattern_weighted_full.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/cuda_pattern_new.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt $(CUDALIB64) -rdc=true -Xptxas -v
	$(CXX) -o $(BIN_DIR)/direct_selected_cuda_pattern_weighted_full $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/direct_selected_cuda_pattern_weighted_full.o $(OBJECTS_DIR)/cuda_pattern.o  -lcudadevrt -lcublas -lcudart -m64 $(CUDALIB64) $(LFLAGS)

direct_diag5_cuda_pattern: test/cuda_pattern/direct_diag5_cuda_pattern.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/direct_diag5_cuda_pattern.cc -o $(OBJECTS_DIR)/direct_diag5_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/cuda_pattern.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt $(CUDALIB64) -rdc=true -Xptxas -v
	$(CXX) -o $(BIN_DIR)/direct_diag5_cuda_pattern $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/direct_diag5_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o  -lcudadevrt -lcublas -lcudart -m64 $(CUDALIB64) $(LFLAGS)

direct_diag5_cuda_pattern_si: test/cuda_pattern/direct_diag5_cuda_pattern_si.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/direct_diag5_cuda_pattern_si.cc -o $(OBJECTS_DIR)/direct_diag5_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/cuda_pattern.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt $(CUDALIB64) -rdc=true -Xptxas -v
	$(CXX) -o $(BIN_DIR)/direct_diag5_cuda_pattern $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/direct_diag5_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o  -lcudadevrt -lcublas -lcudart -m64 $(CUDALIB64) $(LFLAGS)

direct_diag80_cuda_pattern: test/cuda_pattern/direct_diag80_cuda_pattern.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/direct_diag80_cuda_pattern.cc -o $(OBJECTS_DIR)/direct_diag80_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/cuda_pattern.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt $(CUDALIB64) -rdc=true -Xptxas -v
	$(CXX) -o $(BIN_DIR)/direct_diag80_cuda_pattern $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/direct_diag80_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o  -lcudadevrt -lcublas -lcudart -m64 $(CUDALIB64) $(LFLAGS)

direct_selected_cuda_pattern_weighted_full_exclude_central: test/cuda_pattern/direct_selected_cuda_pattern_weighted_full.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/direct_selected_cuda_pattern_weighted_full.cc -o $(OBJECTS_DIR)/direct_selected_cuda_pattern_weighted_full.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/cuda_pattern_exclude_central.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt $(CUDALIB64) -rdc=true -Xptxas -v
	$(CXX) -o $(BIN_DIR)/direct_selected_cuda_pattern_weighted_full $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/direct_selected_cuda_pattern_weighted_full.o $(OBJECTS_DIR)/cuda_pattern.o  -lcudadevrt -lcublas -lcudart -m64 $(CUDALIB64) $(LFLAGS)

direct_diag20_cuda_pattern: test/cuda_pattern/direct_diag20_cuda_pattern.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/direct_diag20_cuda_pattern.cc -o $(OBJECTS_DIR)/direct_diag20_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/cuda_pattern.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt $(CUDALIB64) -rdc=true -Xptxas -v
	$(CXX) -o $(BIN_DIR)/direct_diag20_cuda_pattern $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/direct_diag20_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o  -lcudadevrt -lcublas -lcudart -m64 $(CUDALIB64) $(LFLAGS)

direct_diag10_cuda_pattern: test/cuda_pattern/direct_diag10_cuda_pattern.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/direct_diag10_cuda_pattern.cc -o $(OBJECTS_DIR)/direct_diag10_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/cuda_pattern.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt $(CUDALIB64) -rdc=true -Xptxas -v
	$(CXX) -o $(BIN_DIR)/direct_diag10_cuda_pattern $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/direct_diag10_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o  -lcudadevrt -lcublas -lcudart -m64 $(CUDALIB64) $(LFLAGS)

direct_selected_cuda_pattern_weighted_full_abs: test/cuda_pattern/direct_selected_cuda_pattern_weighted_full.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/direct_selected_cuda_pattern_weighted_full.cc -o $(OBJECTS_DIR)/direct_selected_cuda_pattern_weighted_full.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/cuda_pattern_new_abs.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt $(CUDALIB64) -rdc=true -Xptxas -v
	$(CXX) -o $(BIN_DIR)/direct_selected_cuda_pattern_weighted_full_abs $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/direct_selected_cuda_pattern_weighted_full.o $(OBJECTS_DIR)/cuda_pattern.o  -lcudadevrt -lcublas -lcudart -m64 $(CUDALIB64) $(LFLAGS)

simulate_intensity_test: test/simulate_intenstiy/simulate_intensity.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/simulate_intensity_test.o test/simulate_intenstiy/simulate_intensity.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/simulate_intensity_test $(OBJECTS_DIR)/simulate_intensity_test.o

direct_selected_cuda_pattern_thickness_r: test/cuda_pattern/direct_selected_cuda_pattern_thickness_r.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/direct_selected_cuda_pattern_thickness_r.cc -o $(OBJECTS_DIR)/direct_selected_cuda_pattern_thickness_r.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/cuda_pattern_new_abs.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt $(CUDALIB64) -rdc=true -Xptxas -v
	$(CXX) -o $(BIN_DIR)/direct_selected_cuda_pattern_thickness_r $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/direct_selected_cuda_pattern_thickness_r.o $(OBJECTS_DIR)/cuda_pattern.o  -lcudadevrt -lcublas -lcudart -m64 $(CUDALIB64) $(LFLAGS)

wave_length_test: test/wave_length/wave_length.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/wave_length_test.o test/wave_length/wave_length.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/wave_length_test $(OBJECTS_DIR)/wave_length_test.o

direct_selected_cuda_rotated_pattern: test/cuda_pattern/direct_selected_cuda_rotated_pattern.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/direct_selected_cuda_rotated_pattern.cc -o $(OBJECTS_DIR)/direct_selected_cuda_rotated_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/cuda_pattern_exclude_central.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true  -Xptxas -v
	$(CUDACXX64) src/cuda_pattern/cuda_rotation_pattern.cu -o $(OBJECTS_DIR)/_cuda_rotated_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 -Xptxas -v --relocatable-device-code true
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/_cuda_rotated_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt $(CUDALIB64) -rdc=true -Xptxas -v
	$(CXX) -o $(BIN_DIR)/direct_selected_cuda_rotated_pattern $(OBJECTS_DIR)/_cuda_rotated_pattern.o $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/direct_selected_cuda_rotated_pattern.o $(OBJECTS_DIR)/cuda_pattern.o -lcudadevrt -lcublas -lcudart -m64 $(CUDALIB64) $(LFLAGS)

inverse_selected_cuda_rotated_pattern: test/cuda_pattern/inverse_selected_cuda_rotated_pattern.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/inverse_selected_cuda_rotated_pattern.cc -o $(OBJECTS_DIR)/inverse_selected_cuda_rotated_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/cuda_pattern_exclude_central.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true  -Xptxas -v
	$(CUDACXX64) src/cuda_pattern/cuda_rotation_pattern.cu -o $(OBJECTS_DIR)/_cuda_rotated_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 -Xptxas -v --relocatable-device-code true
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/_cuda_rotated_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt $(CUDALIB64) -rdc=true -Xptxas -v
	$(CXX) -o $(BIN_DIR)/inverse_selected_cuda_rotated_pattern $(OBJECTS_DIR)/_cuda_rotated_pattern.o $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/inverse_selected_cuda_rotated_pattern.o $(OBJECTS_DIR)/cuda_pattern.o -lcudadevrt -lcublas -lcudart -m64 $(CUDALIB64) $(LFLAGS)

matrix_bs: test/matrix/matrix_bs.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/matrix_bs.o test/matrix/matrix_bs.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/matrix_bs $(OBJECTS_DIR)/matrix_bs.o

matrix_900: test/matrix/matrix_900.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/matrix_900.o test/matrix/matrix_900.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/matrix_900 $(OBJECTS_DIR)/matrix_900.o

regression_pattern_test: test/pattern_refinement/regression_pattern.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/regression_pattern_test.o test/pattern_refinement/regression_pattern.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/regression_pattern_test $(OBJECTS_DIR)/regression_pattern_test.o

matrix_transpose: test/matrix/matrix_transpose.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/matrix_transpose.o test/matrix/matrix_transpose.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/matrix_transpose $(OBJECTS_DIR)/matrix_transpose.o

simplex_test: test/simplex/simplex.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/simplex_test.o test/simplex/simplex.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/simplex_test $(OBJECTS_DIR)/simplex_test.o

intensity_test: test/intensity/intensity.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/intensity_test.o test/intensity/intensity.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/intensity_test $(OBJECTS_DIR)/intensity_test.o

direct_diag240_cuda_pattern: test/cuda_pattern/direct_diag240_cuda_pattern.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/direct_diag240_cuda_pattern.cc -o $(OBJECTS_DIR)/direct_diag240_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/cuda_pattern.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt $(CUDALIB64) -rdc=true -Xptxas -v
	$(CXX) -o $(BIN_DIR)/direct_diag240_cuda_pattern $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/direct_diag240_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o  -lcudadevrt -lcublas -lcudart -m64 $(CUDALIB64) $(LFLAGS)

direct_tlnbo_selected_cuda_pattern: test/cuda_pattern/direct_tlnbo_selected_cuda_pattern.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/direct_tlnbo_selected_cuda_pattern.cc -o $(OBJECTS_DIR)/direct_tlnbo_selected_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/cuda_pattern.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt $(CUDALIB64) -rdc=true -Xptxas -v
	$(CXX) -o $(BIN_DIR)/direct_tlnbo_selected_cuda_pattern $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/direct_tlnbo_selected_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o  -lcudadevrt -lcublas -lcudart -m64 $(CUDALIB64) $(LFLAGS)

direct_cuda_pattern_exclude_5: test/cuda_pattern/direct_cuda_pattern.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/direct_cuda_pattern.cc -o $(OBJECTS_DIR)/direct_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/cuda_pattern_exclude_5.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true -O2  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt -lcublas $(CUDALIB64) -rdc=true -O2  -Xptxas -v
	$(CXX) -o $(BIN_DIR)/direct_cuda_pattern_exclude_5 $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/direct_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o  -lcudadevrt -lcublas -lcudart -m64 $(CUDALIB64) $(LFLAGS)

direct_cuda_pattern_exclude_abs: test/cuda_pattern/direct_cuda_pattern_5.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/direct_cuda_pattern_5.cc -o $(OBJECTS_DIR)/direct_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/cuda_pattern_exclude_5.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true -O2  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt -lcublas $(CUDALIB64) -rdc=true -O2  -Xptxas -v
	$(CXX) -o $(BIN_DIR)/direct_cuda_pattern_exclude_5 $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/direct_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o  -lcudadevrt -lcublas -lcudart -m64 $(CUDALIB64) $(LFLAGS)

tilt_test: test/refine_tilt/tilt.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/tilt_test.o test/refine_tilt/tilt.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/tilt_test $(OBJECTS_DIR)/tilt_test.o

any_test: test/any/any.cc include/f/any/any.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/any_test.o test/any/any.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/any_test $(OBJECTS_DIR)/any_test.o

direct_tlnbo_exclude_pattern: test/cuda_pattern/direct_tlnbo_selected_cuda_pattern.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/direct_tlnbo_selected_cuda_pattern.cc -o $(OBJECTS_DIR)/direct_tlnbo_selected_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/cuda_pattern_exclude_central.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt $(CUDALIB64) -rdc=true -Xptxas -v
	$(CXX) -o $(BIN_DIR)/direct_tlnbo_selected_cuda_pattern $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/direct_tlnbo_selected_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o  -lcudadevrt -lcublas -lcudart -m64 $(CUDALIB64) $(LFLAGS)

reflection_residual_test: test/pattern_refinement/reflection_residual.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/reflection_residual_test.o test/pattern_refinement/reflection_residual.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/reflection_residual_test $(OBJECTS_DIR)/reflection_residual_test.o

direct_cuda_pattern_reflection_5: test/cuda_pattern/direct_cuda_pattern_reflection_5.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/direct_cuda_pattern_reflection_5.cc -o $(OBJECTS_DIR)/direct_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/cuda_pattern_exclude_5.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true -O2  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt -lcublas $(CUDALIB64) -rdc=true -O2  -Xptxas -v
	$(CXX) -o $(BIN_DIR)/direct_cuda_pattern_exclude_5 $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/direct_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o  -lcudadevrt -lcublas -lcudart -m64 $(CUDALIB64) $(LFLAGS)

direct_cuda_pattern_reflection_5_se: test/cuda_pattern/direct_cuda_pattern_reflection_5_se.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/direct_cuda_pattern_reflection_5_se.cc -o $(OBJECTS_DIR)/direct_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/cuda_pattern_exclude_5_se.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true -O2  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt -lcublas $(CUDALIB64) -rdc=true -O2  -Xptxas -v
	$(CXX) -o $(BIN_DIR)/direct_cuda_pattern_exclude_5 $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/direct_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o  -lcudadevrt -lcublas -lcudart -m64 $(CUDALIB64) $(LFLAGS)

direct_cuda_pattern_reflection_5_rd: test/cuda_pattern/direct_cuda_pattern_reflection_5_rd.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/direct_cuda_pattern_reflection_5_rd.cc -o $(OBJECTS_DIR)/direct_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/cuda_pattern_exclude_5_rd.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true -O2  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt -lcublas $(CUDALIB64) -rdc=true -O2  -Xptxas -v
	$(CXX) -o $(BIN_DIR)/direct_cuda_pattern_exclude_5 $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/direct_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o  -lcudadevrt -lcublas -lcudart -m64 $(CUDALIB64) $(LFLAGS)

direct_rotated_pattern: test/cuda_rotated_pattern/cuda_rotated_pattern.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_rotated_pattern/cuda_rotated_pattern.cc -o $(OBJECTS_DIR)/direct_selected_cuda_rotated_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_rotated_pattern/cuda_rotated_pattern.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true  -Xptxas -v
	$(CUDACXX64) src/cuda_rotated_pattern/cuda_rotation_pattern.cu -o $(OBJECTS_DIR)/_cuda_rotated_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 -Xptxas -v --relocatable-device-code true
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/_cuda_rotated_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt $(CUDALIB64) -rdc=true -Xptxas -v
	$(CXX) -o $(BIN_DIR)/direct_rotated_pattern $(OBJECTS_DIR)/_cuda_rotated_pattern.o $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/direct_selected_cuda_rotated_pattern.o $(OBJECTS_DIR)/cuda_pattern.o -lcudadevrt -lcublas -lcudart -m64 $(CUDALIB64) $(LFLAGS)

direct_rotated_pattern_se: test/cuda_rotated_pattern/cuda_rotated_pattern.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_rotated_pattern/cuda_rotated_pattern.cc -o $(OBJECTS_DIR)/direct_selected_cuda_rotated_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_rotated_pattern/cuda_rotated_pattern_se.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true  -Xptxas -v
	$(CUDACXX64) src/cuda_rotated_pattern/cuda_rotation_pattern.cu -o $(OBJECTS_DIR)/_cuda_rotated_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 -Xptxas -v --relocatable-device-code true
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/_cuda_rotated_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt $(CUDALIB64) -rdc=true -Xptxas -v
	$(CXX) -o $(BIN_DIR)/direct_rotated_pattern_se $(OBJECTS_DIR)/_cuda_rotated_pattern.o $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/direct_selected_cuda_rotated_pattern.o $(OBJECTS_DIR)/cuda_pattern.o -lcudadevrt -lcublas -lcudart -m64 $(CUDALIB64) $(LFLAGS)

direct_rotated_pattern_ct: test/cuda_rotated_pattern/cuda_rotated_pattern_ct.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_rotated_pattern/cuda_rotated_pattern_ct.cc -o $(OBJECTS_DIR)/direct_selected_cuda_rotated_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_rotated_pattern/cuda_rotated_pattern_se.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true  -Xptxas -v
	$(CUDACXX64) src/cuda_rotated_pattern/cuda_rotation_pattern.cu -o $(OBJECTS_DIR)/_cuda_rotated_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 -Xptxas -v --relocatable-device-code true
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/_cuda_rotated_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt $(CUDALIB64) -rdc=true -Xptxas -v
	$(CXX) -o $(BIN_DIR)/direct_rotated_pattern_ct $(OBJECTS_DIR)/_cuda_rotated_pattern.o $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/direct_selected_cuda_rotated_pattern.o $(OBJECTS_DIR)/cuda_pattern.o -lcudadevrt -lcublas -lcudart -m64 $(CUDALIB64) $(LFLAGS)

scale_direct_diag80_cuda_pattern: test/cuda_pattern/scale_direct_diag80_cuda_pattern.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/scale_direct_diag80_cuda_pattern.cc -o $(OBJECTS_DIR)/direct_diag80_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/cuda_pattern_new_abs.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt $(CUDALIB64) -rdc=true -Xptxas -v
	$(CXX) -o $(BIN_DIR)/direct_diag80_cuda_pattern $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/direct_diag80_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o  -lcudadevrt -lcublas -lcudart -m64 $(CUDALIB64) $(LFLAGS)


complex_refinement_test: test/pattern/complex_refinement.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/pattern.o test/pattern/complex_refinement.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/complex_refinement_test $(OBJECTS_DIR)/pattern.o

simplex_refinement_test: test/pattern/simplex_refinement.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/pattern.o test/pattern/simplex_refinement.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/simplex_refinement_test $(OBJECTS_DIR)/pattern.o

direct_diag_cuda_pattern_x: test/cuda_pattern/direct_diag_cuda_pattern_x.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/direct_diag_cuda_pattern_x.cc -o $(OBJECTS_DIR)/direct_diag5_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/cuda_pattern.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt $(CUDALIB64) -rdc=true -Xptxas -v
	$(CXX) -o $(BIN_DIR)/direct_diag5_cuda_pattern $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/direct_diag5_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o  -lcudadevrt -lcublas -lcudart -m64 $(CUDALIB64) $(LFLAGS)

direct_diag_cuda_pattern_p: test/cuda_pattern/direct_diag_cuda_pattern_p.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/direct_diag_cuda_pattern_p.cc -o $(OBJECTS_DIR)/direct_diag5_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/cuda_pattern.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt $(CUDALIB64) -rdc=true -Xptxas -v
	$(CXX) -o $(BIN_DIR)/direct_diag_cuda_pattern_p $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/direct_diag5_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o  -lcudadevrt -lcublas -lcudart -m64 $(CUDALIB64) $(LFLAGS)

pattern_c1: test/pattern/pattern_c1.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/test_pattern_c1.o test/pattern/pattern_c1.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/pattern_c1 $(OBJECTS_DIR)/test_pattern_c1.o

direct_diag_cuda_pattern_homotopy: test/cuda_pattern/direct_diag_cuda_pattern_homotopy.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/direct_diag_cuda_pattern_homotopy.cc -o $(OBJECTS_DIR)/direct_diag5_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/cuda_pattern.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt $(CUDALIB64) -rdc=true -Xptxas -v
	$(CXX) -o $(BIN_DIR)/direct_diag_cuda_pattern_homotopy $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/direct_diag5_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o  -lcudadevrt -lcublas -lcudart -m64 $(CUDALIB64) $(LFLAGS)

matrix_save_as_inverse_bmp: test/matrix/matrix_save_as_inverse_bmp.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/matrix_save_as_inverse_bmp.o test/matrix/matrix_save_as_inverse_bmp.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/matrix_save_as_inverse_bmp $(OBJECTS_DIR)/matrix_save_as_inverse_bmp.o

matrix_save_as_uniform_bmp: test/matrix/matrix_save_as_uniform_bmp.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/matrix_save_as_uniform_bmp.o test/matrix/matrix_save_as_uniform_bmp.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/matrix_save_as_uniform_bmp $(OBJECTS_DIR)/matrix_save_as_uniform_bmp.o

matrix_save_as_uniform_inverse_bmp: test/matrix/matrix_save_as_uniform_inverse_bmp.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/matrix_save_as_uniform_inverse_bmp.o test/matrix/matrix_save_as_uniform_inverse_bmp.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/matrix_save_as_uniform_inverse_bmp $(OBJECTS_DIR)/matrix_save_as_uniform_inverse_bmp.o

matrix_save_as_balanced_bmp: test/matrix/matrix_save_as_balanced_bmp.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/matrix_save_as_balanced_bmp.o test/matrix/matrix_save_as_balanced_bmp.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/matrix_save_as_balanced_bmp $(OBJECTS_DIR)/matrix_save_as_balanced_bmp.o

matrix_save_as_balanced_inverse_bmp: test/matrix/matrix_save_as_balanced_inverse_bmp.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/matrix_save_as_balanced_inverse_bmp.o test/matrix/matrix_save_as_balanced_inverse_bmp.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/matrix_save_as_balanced_inverse_bmp $(OBJECTS_DIR)/matrix_save_as_balanced_inverse_bmp.o

direct_diag_cuda_pattern_si: test/cuda_pattern/direct_diag_cuda_pattern_si.cc
	$(CXX) $(CXXFLAGS) -c test/cuda_pattern/direct_diag_cuda_pattern_si.cc -o $(OBJECTS_DIR)/direct_diag5_cuda_pattern.o $(INCPATH)
	$(CUDACXX64) src/cuda_pattern/cuda_pattern.cu -o $(OBJECTS_DIR)/_cuda_pattern.o $(INCPATH) -m64 -dc -gencode arch=compute_35,code=sm_35 --relocatable-device-code true  -Xptxas -v
	$(CUDACXX64) -dlink $(OBJECTS_DIR)/_cuda_pattern.o -arch=sm_35 -o $(OBJECTS_DIR)/cuda_pattern.o -m64 -lcudadevrt $(CUDALIB64) -rdc=true -Xptxas -v
	$(CXX) -o $(BIN_DIR)/direct_diag5_cuda_pattern $(OBJECTS_DIR)/_cuda_pattern.o $(OBJECTS_DIR)/direct_diag5_cuda_pattern.o $(OBJECTS_DIR)/cuda_pattern.o  -lcudadevrt -lcublas -lcudart -m64 $(CUDALIB64) $(LFLAGS)

neural_network_test: test/neural_network/neural_network.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/neural_network.o test/neural_network/neural_network.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/neural_network_test $(OBJECTS_DIR)/neural_network.o

optional_test: test/optional/optional.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/optional.o test/optional/optional.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/optional_test $(OBJECTS_DIR)/optional.o

neural_network_nn_test: test/neural_network/nn.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/neural_network_nn.o test/neural_network/nn.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/neural_network_nn_test $(OBJECTS_DIR)/neural_network_nn.o

neural_network_nn_orig_test: test/neural_network/nn_orig.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/neural_network_nn.o test/neural_network/nn_orig.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/neural_network_nn_orig_test $(OBJECTS_DIR)/neural_network_nn.o

complex_polynomial_test: test/polynomial/complex_polynomial_test.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/complex_polynomial_test.o test/polynomial/complex_polynomial_test.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/complex_polynomial_test $(OBJECTS_DIR)/complex_polynomial_test.o

cc_polynomial_test: test/polynomial/cc_polynomial_test.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/cc_polynomial_test.o test/polynomial/cc_polynomial_test.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/cc_polynomial_test $(OBJECTS_DIR)/cc_polynomial_test.o

construct_polynomial_test: test/polynomial/construct_polynomial.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/construct_polynomial_test.o test/polynomial/construct_polynomial.cc
	$(CXX) $(LFLAGS) -o $(BIN_DIR)/construct_polynomial_test $(OBJECTS_DIR)/construct_polynomial_test.o

parasite_matrix_test: test/parasite_matrix/parasite_matrix.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/parasite_matrix_test.o test/parasite_matrix/parasite_matrix.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/parasite_matrix_test $(OBJECTS_DIR)/parasite_matrix_test.o

nn_1: test/neural_network/nn_1.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/neural_network_nn.o test/neural_network/nn_1.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/nn_1 $(OBJECTS_DIR)/neural_network_nn.o

nn_2: test/neural_network/nn_2.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/nn_2.o test/neural_network/nn_2.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/nn_2 $(OBJECTS_DIR)/nn_2.o

nn_3: test/neural_network/nn_3.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/nn_3.o test/neural_network/nn_3.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/nn_3 $(OBJECTS_DIR)/nn_3.o

nn_4: test/neural_network/nn_4.cc
	clang-tidy test/neural_network/nn_4.cc -checks='*' -- $(INCPATH) -std=c++14
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/nn_4.o test/neural_network/nn_4.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/nn_4 $(OBJECTS_DIR)/nn_4.o

tiff_test: test/tiff/tiff_test.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/tiff_test.o test/tiff/tiff_test.cc -I/usr/local/include
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/tiff_test $(OBJECTS_DIR)/tiff_test.o -L/usr/local/lib -ltiff

matrix_laplace: test/matrix/laplace.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/laplace.o test/matrix/laplace.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/matrix_laplace $(OBJECTS_DIR)/laplace.o

matrix_inverse_laplace: test/matrix/inverse_laplace.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/inverse_laplace.o test/matrix/inverse_laplace.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/matrix_inverse_laplace $(OBJECTS_DIR)/inverse_laplace.o

cuda_inverse_laplace: test/matrix/cuda_inverse_laplace.cu
	nvcc -c test/matrix/cuda_inverse_laplace.cu -gencode arch=compute_61,code=sm_61 -std=c++11 -o ./obj/cuda_inverse_laplace.o -O2
	nvcc -o ./bin/cuda_inverse_laplace ./obj/cuda_inverse_laplace.o -gencode arch=compute_61,code=sm_61 -std=c++11 -lcublas -lcusolver -lcusparse -O2

matrix_laplace_result: test/matrix/laplace_result.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/laplace_result.o test/matrix/laplace_result.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/matrix_laplace_result $(OBJECTS_DIR)/laplace_result.o

matrix_save_as_pgm: test/matrix/matrix_save_as_pgm.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/matrix_save_as_pgm.o test/matrix/matrix_save_as_pgm.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/matrix_save_as_pgm $(OBJECTS_DIR)/matrix_save_as_pgm.o

matrix_inverse_claplace: test/matrix/inverse_claplace.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/inverse_claplace.o test/matrix/inverse_claplace.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/matrix_inverse_claplace $(OBJECTS_DIR)/inverse_claplace.o

cuda_inverse_laplace_cmt: test/matrix/cuda_inverse_laplace_cmt.cu
	nvcc -c test/matrix/cuda_inverse_laplace_cmt.cu -gencode arch=compute_61,code=sm_61 -std=c++11 -o ./obj/cuda_inverse_laplace_cmt.o -O2
	nvcc -o ./bin/cuda_inverse_laplace_cmt ./obj/cuda_inverse_laplace_cmt.o -gencode arch=compute_61,code=sm_61 -std=c++11 -lcublas -lcusolver -lcusparse -O2

cuda_inverse_laplace_general: test/matrix/cuda_inverse_laplace_general.cu
	nvcc -c test/matrix/cuda_inverse_laplace_general.cu -gencode arch=compute_61,code=sm_61 -std=c++11 -o ./obj/cuda_inverse_laplace_general.o -O2
	nvcc -o ./bin/cuda_inverse_laplace_general ./obj/cuda_inverse_laplace_general.o -gencode arch=compute_61,code=sm_61 -std=c++11 -lcublas -lcusolver -lcusparse -O2

matrix_inverse_xxyy: test/matrix/inverse_xxyy.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/inverse_xxyy.o test/matrix/inverse_xxyy.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/matrix_inverse_xxyy $(OBJECTS_DIR)/inverse_xxyy.o

cuda_inverse_xxyy: test/matrix/cuda_inverse_xxyy.cu
	nvcc -c test/matrix/cuda_inverse_xxyy.cu -gencode arch=compute_61,code=sm_61 -std=c++11 -o ./obj/cuda_inverse_xxyy.o -O2
	nvcc -o ./bin/cuda_inverse_xxyy ./obj/cuda_inverse_xxyy.o -gencode arch=compute_61,code=sm_61 -std=c++11 -lcublas -lcusolver -lcusparse -O2

cuda_inverse_iterative: test/matrix/cuda_inverse_iterative.cu
	nvcc -c test/matrix/cuda_inverse_iterative.cu -gencode arch=compute_61,code=sm_61 -std=c++11 -o ./obj/cuda_inverse_iterative.o -O2
	nvcc -o ./bin/cuda_inverse_iterative ./obj/cuda_inverse_iterative.o -gencode arch=compute_61,code=sm_61 -std=c++11 -lcublas -lcusolver -lcusparse -O2

cuda_inverse_homotopy: test/matrix/cuda_inverse_homotopy.cu
	nvcc -c test/matrix/cuda_inverse_homotopy.cu -Iinclude -gencode arch=compute_61,code=sm_61 -std=c++11 -o ./obj/cuda_inverse_homotopy.o -O2
	nvcc -o ./bin/cuda_inverse_homotopy ./obj/cuda_inverse_homotopy.o -gencode arch=compute_61,code=sm_61 -std=c++11 -lcublas -lcusolver -lcusparse -O2

cuda_inverse_sparse:
	nvcc -c ./src/cuda/solver.cu -Iinclude -gencode arch=compute_61,code=sm_61 -std=c++11 -o ./obj/solver.o -O2
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/cuda_inverse_sparse.o test/matrix/cuda_inverse_sparse.cc
	nvcc -o ./bin/cuda_inverse_sparse ./obj/cuda_inverse_sparse.o ./obj/solver.o -gencode arch=compute_61,code=sm_61 -std=c++11 -lcublas -lcusolver -lcusparse -O2

matrix_inverse_laplace_1d: test/matrix/inverse_laplace_1d.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/inverse_laplace_1d.o test/matrix/inverse_laplace_1d.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/matrix_inverse_laplace_1d $(OBJECTS_DIR)/inverse_laplace_1d.o

matrix_generate_sparse: test/matrix/generate_sparse.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/generate_sparse.o test/matrix/generate_sparse.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/matrix_generate_sparse $(OBJECTS_DIR)/generate_sparse.o

matrix_inverse_xxyy_1d: test/matrix/inverse_xxyy_1d.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/inverse_xxyy_1d.o test/matrix/inverse_xxyy_1d.cc
	nvcc -c test/matrix/calculate_Atb.cu -gencode arch=compute_61,code=sm_61 -std=c++11 -o ./obj/calculate_Atb.o -O2
	nvcc -o $(BIN_DIR)/matrix_inverse_xxyy_1d $(OBJECTS_DIR)/inverse_xxyy_1d.o $(OBJECTS_DIR)/calculate_Atb.o -lcublas -lcusolver -lcusparse -O2

matrix_binary: test/matrix/matrix_binary.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/binary.o test/matrix/matrix_binary.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/matrix_binary $(OBJECTS_DIR)/binary.o

xx_yy_calibrate: test/piah/xx_yy_calibrate.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/binary.o test/piah/xx_yy_calibrate.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/xx_yy_calibrate $(OBJECTS_DIR)/binary.o

tuple_binding: test/tuple_binding/tuple_binding.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/tuple_binding.o test/tuple_binding/tuple_binding.cc
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/tuple_binding $(OBJECTS_DIR)/tuple_binding.o

