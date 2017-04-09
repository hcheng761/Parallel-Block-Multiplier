
UNAME = $(shell uname)

ifeq ($(UNAME), Darwin)
    # Mac OSX, cblas uses 32-bit integer parameters
    CFLAGS += -O3 -fno-common -framework Accelerate
    LIB =
else
    # Intel MKL: sequential BLAS with 32-bit integer parameters, dynamic link
    # see https://software.intel.com/en-us/articles/intel-mkl-link-line-advisor
    #
    # do this on ADA:
    #
    #       module load intel
    #       make
    #
    CC = icc
    CFLAGS += -O3 -I${MKLROOT}/include
    LIB = -L${MKLROOT}/lib/intel64 -lmkl_intel_lp64 -lmkl_sequential -lmkl_core -lpthread -lm -ldl -lrt
endif

SRC = mymult_main.c mymult.c matrix_util.c tictoc.c load_block.c save_block.c mymult_block.c

stuff:
	echo $(UNAME)
	$(CC) -fopenmp $(CFLAGS) $(SRC) -o mymult_main $(LIB)
	./mymult_main
