function D = mymult (C,A,B,ntrials)
%MYMULT D=C+ntrials*A*B for dense matrices A and B
%
% D = mymult (C,A,B) computes D=C+A*B
%
% D = mymult (C A,B,ntrials) computes D=C+ntrials*A*B.  It does
% it inefficiently by D=C and then computing D=D+A*B ntrials times, 
% for testing cache reuse.

error ('mymult mexFunction not found; use mymult_make to compile') ;
